#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>      // std::out_of_range
#include <iomanip>
#include <list>

int main(){
	std::cout << "test:" << std::endl;
	size_t tester1 = 64;
	size_t tester64 = 1;
	int tester3 = 64;
	int tester4 = 1;
	int res;
	std::cout << "---" << std::endl;
	std::cout << "64 size_t/1 size_t = " << tester1 / tester64 << std::endl;
	std::cout << "-64 size_t/1 size_t = " << (-tester1) / tester64 << std::endl;
	std::cout << "64 size_t/-1 size_t = " << tester1 / (-tester64) << std::endl;
	std::cout << "64 size_t/1 integer = " << tester1 / tester4 << std::endl;
	std::cout << "-64 size_t/1 integer = " << (-tester1) / tester4 << std::endl;
	std::cout << "64 size_t/-1 integer = " << tester1 / (-tester4) << std::endl;
	std::cout << "64 integer/1 size_t = " << tester3 / tester64 << std::endl;
	std::cout << "-64 integer/1 size_t = " << (-tester3) / tester64 << std::endl;
	std::cout << "64 integer/-1 size_t = " << tester3 / (-tester64) << std::endl;
	std::cout << "64 integer/1 integer = " << tester3 / tester4 << std::endl;
	std::cout << "-64 integer/1 integer = " << (-tester3) / tester4 << std::endl;
	std::cout << "64 integer/-1 integer = " << tester3 / (-tester4) << std::endl;
	tester1 = 1;
	tester64 = 64;
	tester3 = 1;
	tester4 = 64;
	std::cout << "---" << std::endl;
	std::cout << "1 size_t/64 size_t = " << (size_t)(tester1 / tester64) << " = " << (int)(tester1 / tester64) << std::endl;
	std::cout << "-1 size_t/64 size_t = " << (-tester1) / tester64 << std::endl;
	std::cout << "1 size_t/-64 size_t = " << tester1 / (-tester64) << std::endl;
	std::cout << "1 size_t/64 integer = " << tester1 / tester4 << std::endl;
	std::cout << "-1 size_t/64 integer = " << (-tester1) / tester4 << std::endl;
	std::cout << "1 size_t/-64 integer = " << tester1 / (-tester4) << std::endl;
	std::cout << "1 integer/64 size_t = " << tester3 / (int)tester64 << std::endl;
	std::cout << "CRIT: -1 integer/64 size_t = " << (-tester3) / tester64 << std::endl;
	std::cout << "1 integer/-64 size_t = " << tester3 / (-tester64) << std::endl;
	std::cout << "1 integer/64 integer = " << tester3 / tester4 << std::endl;
	std::cout << "-1 integer/64 integer = " << (-tester3) / tester4 << std::endl;
	std::cout << "1 integer/-64 integer = " << tester3 / (-tester4) << std::endl;
	res = (-tester3+1) / (int)tester64;
	std::cout << "RES RESULT: " << res << std::endl;
	//so:
	//if(ex<0){
	//	worldOffsetX = ((ex+1)/(int)mapSide) - 1;
	//}
	//else{
	//	worldOffsetX = ex/(int)mapSide;
	//}
 }