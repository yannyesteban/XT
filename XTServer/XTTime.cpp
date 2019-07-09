#include "XTTime.h"
namespace XT {
	char Time::_buffer[20] = "";
	time_t Time::_now = NULL;
	tm* Time::_time = NULL;

	char* Time::now() {

		_now = time(0);
		_time = localtime(&_now);

		strftime(_buffer, sizeof(_buffer), "%Y-%m-%d %H:%M:%S", _time);

		return _buffer;
	}

	void Time::test() {


		time_t now = time(0);
		tm* time = localtime(&now);
		const int len = 20;
		char buffer[len];
		strftime(buffer, len, "%Y-%m-%d %H:%M:%S", time);

		printf("hoy es %s\n\n", buffer);
		printf("%.4d-%.2d-%.2d %.2d:%.2d:%.2d",(1900+time->tm_year),time->tm_mon+1,time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec);
	}

}
