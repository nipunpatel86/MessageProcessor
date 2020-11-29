#include <cstdio>
#include <iostream>
#include "Structure.h"
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "Globals.h"
#pragma once
class Test
{
public:
	void DummyWrite(int seqno, FILE *of);
	void FileWrite(int seq);
	void FileWrite2(int seq);
	void Execute();
};