//
//  main.cpp
//  encryption
//
//  Created by Nathaniel Polley on 4/20/16.
//  Copyright (c) 2016 Nathaniel Polley. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;
unsigned GetNumberOfDigits (unsigned i)
{
    return i > 0 ? (int) log10 ((double) i) + 1 : 1;
}

int division_method(int val, int M)
{
    return val%M;
}

double multiplication_method(int val, int M)
{
    double x = val/2;
    double A = M;
    return A*(fmod(x,1));
}

int rotation_method(int val)
{
    int first = val%10;
    int added_digit=1;
    val=(val-first)/10;
    for(int i = 0; i<GetNumberOfDigits(val); i++)
    {
        added_digit *= 10;
    }
    return (first*added_digit)+val;
    
}

int main()
{
    cout<<division_method(5102, 7)<<endl;
    cout<<multiplication_method(5102, .5)<<endl;
    cout<<rotation_method(5102);
    return 0;
}
