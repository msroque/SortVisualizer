#include "Sort.h"

Sort::Sort(int arr[], int size)
{
    for(int i = 0; i < size; i++)
    {
        this->arr[i] = arr[i];
    }
    this->size = size;
}

Sort::Sort(int type, int size)
{
    // Make random numbers from 0 - 100
    random_device rand;
    mt19937 mt(rand());
    uniform_int_distribution dist(0, 100);

    if(type == 0)   // C Array
    {
        
        cout << endl << "You made a C Array!" << endl;
        for(int i = 0; i < size; i++)
        {
            arr[i] = dist(mt);
            cout << arr[i] << " ";
        }
        cout << endl;
        this->size = size;
    }
}

Sort::~Sort()
{
    
}

void Sort::bubbleSort()
{
    // For 0 to size
    for(int i = 0; i < size; i++)
    {
        // For size-1 to target+1
        for(int j = size - 1; j > i; j--)
        {
            // If element less than element before,
            if(arr[j] < arr[j-1])
            {
                // swap
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
    cout << endl << "You ran Bubble Sort!" << endl;
    cout << *this;
}

ostream& operator << (ostream& out, Sort &sortArr)
{
    // cout << "Array:";
    for(int i = 0; i < sortArr.size; i++)
    {
        cout << " " << sortArr.arr[i];
    }
    cout << endl << "Size: " << sortArr.size<< endl << endl;
    return out;
}