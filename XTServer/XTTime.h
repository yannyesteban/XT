#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>

namespace XT {
	class Time {
	public:

		static char* now();
		void test();
	private:
		static char _buffer[20];
		static time_t _now;
		static tm* _time;
	};
}


