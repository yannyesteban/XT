#include "XTTime.h"

char XTTime::_buffer[20] = "";
time_t XTTime::_now = NULL;
tm* XTTime::_time = NULL;

char* XTTime::now() {

	_now = time(0);
	_time = localtime(&_now);

	strftime(_buffer, sizeof(_buffer), "%Y-%m-%d %H:%M:%S", _time);

	return _buffer;
}

void XTTime::test() {


	time_t now = time(0);
	tm* time = localtime(&now);
	const int len = 20;
	char buffer[len];
	strftime(buffer, len, "%Y-%m-%d %H:%M:%S", time);

	printf("hoy es %s\n\n", buffer);
	printf("%.4d-%.2d-%.2d %.2d:%.2d:%.2d",(1900+time->tm_year),time->tm_mon+1,time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
}
