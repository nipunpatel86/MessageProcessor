#pragma once
class Globals
{
public:
	static const int MessageLen = sizeof(Message);
	static int Isprocess;
	//static int MesgRate = 60;//Message rate per second
	queue<Message>ProcessQueue;
	queue<Message>BkpQueue;
	queue<Message>ReadQueue;
	queue<Message>HoldQueue;
	unsigned long volatile MesgCount;

};