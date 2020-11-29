#include "map"
#include <queue>

using namespace std;
#pragma once
//#pragma pack(1)
struct Message
{
	char MesgType;
	uint32_t SeqNo;
	char Side;
	uint32_t Size;
	char Ticker[10];//Assumption ticker length is 10
	double Price;
}__attribute__ ((packed));


