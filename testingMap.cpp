#include <iostream>

int main(){
	int array[100];
	for (int i = 0; i < 100; ++i)
	{
		array[i] = 1;
	}
	int startX = 1;
	int startY = 1;
	int endX = 8;
	int endY = 8;
	int width = (endX-startX+1);
    int height = (endY-startY+1);
    int side = 10;
    for (int i = 0; i < width*height; i++)
    {
        array[( ( ((int)(i/width)) +startY) *side) + ((i%width)+startX)] = 0;
    }
    for (int i = 0; i < side*side; ++i)
    {
        if(i%side == 0){
           std::cout << std::endl;
        }
        std::cout << array[i];
    }
    std::cout << std::endl;

}