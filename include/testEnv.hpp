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

struct coordinate {
    int y;
    int x;
	coordinate* up;
	coordinate* down;
};

class testerClass {
public:
	std::list<std::list<coordinate> > intMap;
	std::list<coordinate> integ;
	testerClass();
	~testerClass();
};