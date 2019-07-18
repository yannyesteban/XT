#pragma once

#define BOOST_RESULT_OF_USE_DECLTYPE
#include <iostream>
#include <list>
#include <iterator>
#include <regex>
#include <boost/algorithm/string.hpp>

using namespace std;
namespace XT {
	class Tool {

	public:
	
		static list<string> split(string text, char delimeter);
		static void test();


		static void getItem(std::string w[], int &len, const char* buffer){

			std::smatch m;
			std::string ss(buffer);

			//std::regex Pala("[0-9.a-zA-ZñÑáéíóúÁÉÍÓÚäëïöüÄËÏÖÜ]+");
			std::regex Pala("[0-9.a-zA-Z]+");
			len = 0;
			while (std::regex_search(ss, m, Pala)) {
				
				for (int i = 0; i < m.size(); i++) {
					w[len++] = m[i].str();
		
				}
				/*
				for (auto x : m) {
					//w[j++] = (const char *)x;
					
				}
				*/
				//std::cout << std::endl;
				ss = m.suffix().str();

			}

		}
	private:




	};
}


