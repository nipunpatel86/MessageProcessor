#include <cstdio>
#include <iostream>
#include "Structure.h"
#include "pthread.h"
#include "dirent.h"
#include <cstdlib>
#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Test.h"
#include "MessageGetter.h"
using namespace std;
//Sequential data


pthread_mutex_t lock;
//class Test;
unsigned long LocalProcessSeq = 0;

void ProcessMesg(Message msg, Globals* global)
{
	pthread_mutex_lock(&lock);
	unsigned long CurrentSeqNo = msg.SeqNo;
	if (CurrentSeqNo == LocalProcessSeq + 1)
	{
		global->ProcessQueue.push(msg);
		LocalProcessSeq = CurrentSeqNo;
		//Globals::Messages.insert(pair<uint32_t, Message>(Appseq, msg));
	}
	else if (CurrentSeqNo > LocalProcessSeq + 1)//Read only	&& Readqueue
	{
		global->BkpQueue.push(msg);
		cout << "Hold mesg for further process:" << CurrentSeqNo;
	}
	else if (CurrentSeqNo < LocalProcessSeq + 1)
	{
		//Discard
	}
	pthread_mutex_unlock(&lock);
}



void* QueueRead(void* arg)
{
	Globals* global = (Globals*)arg;

	while (true)
	{
		while (!global->ReadQueue.empty())
		{
			Message msg = global->ReadQueue.front();
			global->ReadQueue.pop();
			ProcessMesg(msg, global);
		}
		sleep(1);
	}
}

void* QueueBkp(void* arg)
{
	Globals* global = (Globals*)arg;
	while (true)
	{
		while (!global->BkpQueue.empty())
		{
			Message msg = global->BkpQueue.front();
			ProcessMesg(msg, global);
			global->BkpQueue.pop();

		}
		sleep(1);
	}
}

void* QueueProcess(void* arg)
{
	int Count;
	FILE* of;
	of = fopen("MessageFiles/Out.txt", "wb");
	Globals* global = (Globals*)arg;
	while (true)
	{
		while (!global->ProcessQueue.empty())
		{
			Message msg = global->ProcessQueue.front();
			global->ProcessQueue.pop();
			if (of == NULL) {
				fprintf(stderr, "\nError to open the file\n");
				exit(1);
			}
			fwrite(&msg, Globals::MessageLen, 1, of);
			if (fwrite != 0)
				printf("contents to file written successfully !\n");
			else
				printf("error writing file !\n");

		}
		Count++;

		sleep(1);
		if (Count % 5 == 0)
		{
			fflush(of);
		}
	}
	// close file 
	fclose(of);
}

void* Timer(void* arg)
{
	Globals* global = (Globals*)arg;
	while (true)
	{
		if (global->MesgCount > 0)
		{
			cout << "Reset MesgCount:" << global->MesgCount;

			global->MesgCount = 0;//Reset Mesg count on every second.
		}
		//else
		//{
		if (!global->HoldQueue.empty())
		{
			global->HoldQueue.swap(global->ReadQueue);
		}
		//}
		sleep(1);
	}
}

int main()
{
	printf("Application Starts.");

	Test test;
	test.Execute();//Test
	exit(0);

	if (pthread_mutex_init(&lock, NULL) != 0) {
		printf("\n mutex init has failed\n");
		return 1;
	}

	Globals* global = new Globals();

	MessageGetter messageget;
	messageget.Init(global);

	pthread_t thr2;
	int ret2 = pthread_create(&thr2, NULL, QueueRead, global);//Process File and store in readqueue
	if (ret2 != 0)
		printf("\nThread can't be created :[%s]", strerror(ret2));

	pthread_t thr3;
	int ret3 = pthread_create(&thr3, NULL, QueueBkp, global);//Process Readqueue and store in bkpqueue and process queue
	if (ret3 != 0 )
		printf("\nThread can't be created :[%s]", strerror(ret3));

	pthread_t thr4;
	int ret4 = pthread_create(&thr4, NULL, QueueProcess, global);//Process queueprocess and write to o/p file
	if (ret4 != 0 )
		printf("\nThread can't be created :[%s]", strerror(ret4));

	pthread_t thr5;
	int ret5 = pthread_create(&thr5, NULL, Timer, global);//Process queueprocess and write to o/p file
	if (ret5 != 0)
		printf("\nThread can't be created :[%s]", strerror(ret5));

	while (true)
	{
		sleep(1 * 60);
	}
	pthread_mutex_destroy(&lock);
	return 0;
}