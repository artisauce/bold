#include "test.hpp"
#include <string>

class testTwo:public test {
private:
	std::string value = "five";
public:
	std::string getValue(){
		return value;
	}
};