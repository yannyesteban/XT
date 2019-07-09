#include "XTTool.h"
using namespace std;

namespace XT {
	list<string> Tool::split(string text, char delimeter) {

		list<string>results;
	
		boost::split(results, text, [delimeter](char c) { return c== delimeter; });

		return results;
	
	}

	void Tool::test() {
		string text = "one,two,three,four,five";
		char delimeter = ',';
		list<string>results;

		boost::split(results, text, [delimeter](char c) { return c == delimeter; });
		//boost::split(results, text, boost::is_any_of((char)token));
		list <string> ::iterator it;
		cout << "text: " <<text << "Delimeter: " << delimeter << std::endl;
		for (it = results.begin(); it != results.end(); ++it) {
			cout << "=>" << *it << endl;
		}
		
		cout << "*****\n";

	
	}
}

