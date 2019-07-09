#pragma once

#define BOOST_RESULT_OF_USE_DECLTYPE
#include <iostream>
#include <list>
#include <iterator>
#include <boost/algorithm/string.hpp>

using namespace std;
namespace XT {
	class Tool {

	public:
	
		static list<string> split(string text, char delimeter);
		static void test();
	private:




	};
}


