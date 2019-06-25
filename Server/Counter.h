#pragma once

#include<sys/timeb.h>

class Counter
{

public:
	struct timeb start, end;
	int delta;
	void init(int _delta);
	
	int getDiff();
	bool ready();
	void (*F)() ;
	//void (*T)(char* token);
private:

};

