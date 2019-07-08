#include "mytime.h"

using namespace std;

void mytime::test() {

	time_t now = time(0);
	tm* time = localtime(&now);


	printf("son las %d:%m:%s", tm.tm_hour, tm.tm_min, tm.tm_sec);


}
