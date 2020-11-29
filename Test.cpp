#include "Test.h"

void Test::DummyWrite(int seqno, FILE* of)
{
	Message msg;// = new Message();
	msg.MesgType = 'A';
	msg.Price = 23.23;
	msg.SeqNo = seqno;
	msg.Side = 'B';
	strcpy(msg.Ticker, "ABC");
	msg.Size = 2000;
	fwrite(&msg, Globals::MessageLen, 1, of);
}

void Test::FileWrite(int seq)
{
	FILE* of;
	of = fopen("MessageFiles/InFile1.txt", "wb");
	if (of == NULL) {
		fprintf(stderr, "\nError to open the file.May be MeesageFiles directory not exist.\n");
		exit(1);
	}

	Message msg;// = new Message();
	msg.MesgType = 'A';
	msg.Price = 23.23;
	msg.SeqNo = 3;
	msg.Side = 'B';
	strcpy(msg.Ticker, "ABC");
	msg.Size = 2000;
	fwrite(&msg, Globals::MessageLen, 1, of);

	Message msg2;// = new Message();
	msg2.MesgType = 'B';
	msg2.Price = 24.23;
	msg2.SeqNo = 4;
	msg2.Side = 'S';
	strcpy(msg2.Ticker, "XYZ");
	msg2.Size = 3000;
	//int len = sizeof(Message);
	fwrite(&msg2, Globals::MessageLen, 1, of);
	DummyWrite(12, of);
	DummyWrite(9, of);
	DummyWrite(1, of);
	DummyWrite(2, of);
	DummyWrite(2, of);
	if (fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	// close file 
	fclose(of);
}

void Test::FileWrite2(int seq)
{
	FILE* of;
	of = fopen("MessageFiles/InFile2.txt", "wb");
	if (of == NULL) {
		fprintf(stderr, "\nError to open the file\n");
		exit(1);
	}

	Message msg;// = new Message();
	msg.MesgType = 'A';
	msg.Price = 23.23;
	msg.SeqNo = 2;
	msg.Side = 'B';
	strcpy(msg.Ticker, "ABC");
	msg.Size = 2000;
	fwrite(&msg, Globals::MessageLen, 1, of);

	Message msg2;// = new Message();
	msg2.MesgType = 'B';
	msg2.Price = 24.23;
	msg2.SeqNo = 5;
	msg2.Side = 'S';
	strcpy(msg2.Ticker, "XYZ");
	msg2.Size = 3000;
	//int len = sizeof(Message);
	fwrite(&msg2, Globals::MessageLen, 1, of);
	DummyWrite(6, of);
	DummyWrite(8, of);
	DummyWrite(7, of);
	DummyWrite(10, of);
	DummyWrite(11, of);
	if (fwrite != 0)
		printf("contents to file written successfully !\n");
	else
		printf("error writing file !\n");

	// close file 
	fclose(of);
}

void FileRead()
{
	//cout << "File Reading Starts";
	struct stat sb;
	char* linkname;
	ssize_t r;
	/*string slist = path + "/" + dirlist[i];
	cout << "Current processing file " << slist.c_str();*/
	//Files Read Thread
	FILE* inf;
	struct Message inp;
	inf = fopen("MessageFiles/Out.txt", "rb");
	if (inf == NULL) {
		fprintf(stderr, "\nError to open the file\n");
		exit(1);
	}
	fseek(inf, 0, SEEK_SET);
	while (!feof(inf))//
	{
		int readcount = fread(&inp, Globals::MessageLen, 1, inf);
		printf("SeqNo:", inp.SeqNo);
		//if (false)//
		//{
			//ProcessMesg(inp, false);
		/*}
		else
		{*/
			//Inserts in to queue
			//ReadQueue.push(inp);
		//}
		//printf("roll_no = %d name = %s\n", inp.roll_no, inp.name);
	}
	fclose(inf);
}

void Test::Execute()
{
	if (true)
	{
		FileRead();
	}
	else
	{
		FileWrite(0);
		FileWrite2(0);
	}

}
//};