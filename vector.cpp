#include <iostream>
#include <vector>
using namespace std;
 
int main()
{
    vector<double> student_marks;
 
    for (int i = 0; i < student_marks.size()+1; i++)
    {
        cout << "Enter marks for student #" << i+1 
             << ": " << flush;
             double red = -1.0;
        cin >> red;
        if(red >= 0){
        	student_marks.push_back(red);
        	//cout << student_marks.capacity() << endl; Doubles every time after n = 4.
        }
        else{
        	cout << endl;
        	//cout << student_marks.capacity() << endl;
        }
    }
    for (int i = 0; i < student_marks.size(); ++i)
    {
    	cout << "Marks for student #" << i+1 
             << ": " << student_marks[i] << endl;
    }
 
    // vector.shrink_to_fit();
    std::vector<int> v;
    std::cout << "Default-constructed capacity is " << v.capacity() << '\n';
    v.resize(100);
    std::cout << "Capacity of a 100-element vector is " << v.capacity() << '\n';
    v.clear();
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    
    return 0;
}
