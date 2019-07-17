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


		static void split2(const std::string w[], const char* buffer){

			const char* v[30];
			//std::string w[30];

			std::smatch m;
			std::string ss(buffer);

			std::regex Pala("[0-9\.a-zA-ZñÑáéíóúÁÉÍÓÚäëïöüÄËÏÖÜ]+");
			int j = 0;
			while (std::regex_search(ss, m, Pala)) {
				//std::cout << "Pala\n";
				for (int i = 0; i < m.size(); i++) {
					//w[j++] = m[i].str();
					//v[j++] = (const char *)m.str(i);
					std::cout << m.str(i) << " !!";
				}
				for (auto x : m) {
					//v[j++] = (const char *)x;
					
				}
				std::cout << std::endl;
				ss = m.suffix().str();

			}
			for (int a = 0; a < 5; a++) {

				printf("--- (%s) ----", w[a].c_str());
			}
			//return w;
		}
	private:




	};
}


