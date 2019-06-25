#include "Counter.h"
void Counter::init(int _delta) {
	delta = _delta;
	ftime(&start);

}
int Counter::getDiff() {
	return (int)(1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
}
bool Counter::ready() {
	ftime(&end);

	


	if (getDiff() >= delta) {
		ftime(&start);
		F();
		return true;
	}

	return false;
}