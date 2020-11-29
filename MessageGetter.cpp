#include "MessageGetter.h"

MessageGetter::MessageGetter()//constructor
{

}

void MessageGetter::Init(Globals* _global)
{
	global = _global;

	pthread_attr_t tthr;
	pthread_t thrid;
	int ret;
	/* initialize an attribute to the default value */
	ret = pthread_attr_init(&tthr);
	ret = pthread_create(&thrid, &tthr, MessageGetter::FileRead, this);
	if (ret != 0 && thrid != 0)
		printf("\nFileRead Thread can't be created :[%s]", strerror(thrid));
}

int MessageGetter::strcasecmp_withNumbers(const void* void_a, const void* void_b)
{
	const char* a = (const char*)void_a;
	const char* b = (const char*)void_b;

	if (!a || !b)
	{ // if one doesn't exist, other wins by default
		return a ? 1 : b ? -1 : 0;
	}
	if (isdigit(*a) && isdigit(*b))
	{ // if both start with numbers
		char* remainderA;
		char* remainderB;
		long valA = strtol(a, &remainderA, 10);
		long valB = strtol(b, &remainderB, 10);
		if (valA != valB)
			return valA - valB;
		// if you wish 7 == 007, comment out the next two lines
		else if (remainderB - b != remainderA - a) // equal with diff lengths
			return (remainderB - b) - (remainderA - a); // set 007 before 7
		else // if numerical parts equal, recurse
			return strcasecmp_withNumbers(remainderA, remainderB);
	}
	if (isdigit(*a) || isdigit(*b))
	{ // if just one is a number
		return isdigit(*a) ? -1 : 1; // numbers always come first
	}
	while (*a && *b)
	{ // non-numeric characters
		if (isdigit(*a) || isdigit(*b))
			return strcasecmp_withNumbers(a, b); // recurse
		if (tolower(*a) != tolower(*b))
			return tolower(*a) - tolower(*b);
		a++;
		b++;
	}
	return *a ? 1 : *b ? -1 : 0;
}

bool MessageGetter::MyDataSortPredicate(const string& d1, const string& d2)
{
	return strcasecmp_withNumbers(d1.c_str(), d2.c_str()) < 0;
}

void* MessageGetter::FileRead(void* arg)
{
	while (true)
	{
		MessageGetter* pMessageGetter = (MessageGetter*)(arg);
		cout << "File Reading Starts";
		struct stat sb;
		char* linkname;
		ssize_t r;
		std::string path = "/home/nio/projects/MessageProcessor/bin/x64/Debug/MessageFiles";
		//std::string path = "/home/computer/Project/Pcap/udp_pcap";
		DIR* dir;
		struct dirent* ent;
		vector<string>dirlist;
		if ((dir = opendir(path.c_str())) != NULL)
		{
			/* print all the files and directories within directory */
			while ((ent = readdir(dir)) != NULL)
			{
				if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0)
				{
					dirlist.push_back(string(ent->d_name));
				}
			}
			closedir(dir);
			std::sort(dirlist.begin(), dirlist.end(), MyDataSortPredicate);
			for (int i = 0; i < dirlist.size(); i++)
			{
				string slist = path + "/" + dirlist[i];
				cout << "Current processing file " << slist.c_str();
				//Files Read Thread
				FILE* inf;
				struct Message inp;
				inf = fopen(slist.c_str(), "rb");
				if (inf == NULL) {
					fprintf(stderr, "\nError to open the file\n");
					exit(1);
				}
				if (strcmp(string("Out.txt").c_str(), dirlist[i].c_str()) == 0)//Ignore out file
				{
					break;
				}
				fseek(inf, 0, SEEK_SET);
				while (!feof(inf))//
				{
					int readcount = fread(&inp, Globals::MessageLen, 1, inf);
					printf("SeqNo:", inp.SeqNo);
					pMessageGetter->global->MesgCount++;
					if (pMessageGetter->global->MesgCount > pMessageGetter->MesgRate)//MessageRate Per second
					{
						//Insert in to hold queue
						pMessageGetter->global->HoldQueue.push(inp);
					}
					else
					{
						//Process message
						//Inserts in to queue
						pMessageGetter->global->ReadQueue.push(inp);
					}
					//printf("roll_no = %d name = %s\n", inp.roll_no, inp.name);
				}
				fclose(inf);

				cout << "Finish processing file " << slist.c_str();
			}
			cout << "All files processed successfully";
		}
		else
		{
			/* could not open directory */
			perror("MessageProcess FileRead::");
			// return EXIT_FAILURE;
		}
		sleep(5);
		break;
	}

}


