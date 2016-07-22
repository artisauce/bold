#include <iostream>
#include <vector>
using namespace std;
 
int main()
{
    vector<double> student_marks(20); // Manually specify
 
    for (vector<double>::size_type i = 0; i < 20; i++)
    {
        cout << "Enter marks for student #" << i+1 
             << ": " << flush;
        cin >> student_marks[i];
    }
    // ... Do some stuff with the values
 
    return 0;
}
