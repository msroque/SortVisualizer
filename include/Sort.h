#pragma once

#include <iostream>
#include <random>

const int SORT_SIZE = 100;

using namespace std;

class Sort
{
public:
    Sort(int arr[], int size);      // C Array
    Sort(int type, int size);       // can choose type, for visuals
    ~Sort();

    void bubbleSort();

    friend ostream& operator << (ostream& out, Sort &sortArr);
private:
    int arr[SORT_SIZE];
    int size;
};
