#include "testEnv.hpp"

testerClass::testerClass(){
	long unsigned int sizer = intMap.end()->size();
	std::cout << "WELP " << sizer << std::endl;
	integ.push_back({0,0,NULL,NULL});
	std::cout << "WELP" << std::endl;
	intMap.push_back(integ);
	sizer = intMap.end()->size();
	std::cout << "WELP " << sizer << std::endl;
}

testerClass::~testerClass(){
	
}

int main( int argc, char* args[] )
{
	testerClass newTest;
	
}