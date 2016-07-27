#import "test.hpp"
#import "test1.hpp"
#import "test2.hpp"
#include <iostream>



int main (){
	testOne taser1;
	testTwo taser2;
	taser1.testPoint = &taser2;
	taser2.testPoint = &taser1;
	std::cout << taser1.value << std::endl;
	std::cout << taser2.value << std::endl;
	newTaser* taserPointee dynamic_cast<testTwo> (taser1.testPoint);
	std::cout << taser1.testPoint->value << std::endl;
	std::cout << taser2.testPoint->value << std::endl;

}