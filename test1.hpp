#include "test.hpp"
#include <string>

class testOne:public test {
private:
	int value = 5;
public:
	int getValue(){
		return value;
	}
};