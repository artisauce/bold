#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <vector>

int main()
{
    vector<double> student_marks; // Manually specify
 
    for (vector<double>::size_type i = 0; i < 20; i++)
    {
        cout << "Enter marks for student #" << i+1 
             << ": " << flush;
        cin >> student_marks[i];
    }
    // ... Do some stuff with the values
 
    return 0;
}
