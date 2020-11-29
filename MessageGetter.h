#pragma once

#include<map>
#include "Structure.h"
#include <cstdio>
#include <iostream>
#include "pthread.h"
#include "dirent.h"
#include <cstdlib>
//#ifndef MESSAGEGETTER_H
//#define MESSAGEGETTER_H

#include <string.h>
#include <algorithm>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <queue>
#include "Globals.h"
using namespace std;

//This class get message from MAP.
class MessageGetter
{
public:
	MessageGetter();
	void Init(Globals* global);
	static void* FileRead(void* arg);
	static bool MyDataSortPredicate(const string& d1, const string& d2);
	static int strcasecmp_withNumbers(const void* void_a, const void* void_b);
	int MesgRate;
	Globals* global;

};

