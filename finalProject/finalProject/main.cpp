//
//  main.cpp
//  finalProject
//
//  Created by Nathaniel Polley on 5/2/16.
//  Copyright (c) 2016 Nathaniel Polley. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

vector<long>catCells;
long divsRemaining [61];
vector<long>randoms;
vector<long>buckets(22, 0);

int irand(int min, int max) {
    return ((double)rand() / ((double)RAND_MAX + 1.0)) * (max - min + 1) + min;
}

vector<long>Randomize(long at_21) //function to create quasi-randomization of cell counts after "21 divisions remaining"
{
    long at_20 = (at_21+1)/2; //sets int at_20 to previous value/2 (+1 to account for systematic biological error)
    
    if(at_21==1) //if value at 21 is equal to 1
    {
        buckets.push_back(1); //only insert value 1 into vector to be returned
        return buckets; //return vector to main
    }
    if(at_21==0) //if value at 21 is equal to 0
    {
        buckets.push_back(1); //only insert value 1 into vector to be returned
        return buckets; //return vector to main
    }
    
    else //if other value exists at 21, proceed to standard randomization to create values to add to value at 20
    {
        int count = 22; //total random values to be generated for vector
        long max_val = at_20;
        long max_sum = at_20;
        

        srand(time(0)); //generates random value based upon time
        long remaining = max_sum; //sets value at 20 to be the target sum for succeeding values
        while(remaining>0) //while long remaining is positive
        {
            long rndBucketIdx = irand(0, count-1); 
            if(buckets[rndBucketIdx] == max_val) //if index at rndBucketIdx is equal to the maximum value
            {
                continue; //proceed as normal
            }
            buckets[rndBucketIdx]++;
            remaining--;
        }
        return buckets;
    }
    return buckets;
}

vector<long>CategorizeCells(long total) //function to apportion cell counts to corresponding index in vector
{
    
    long category = total;
    
    while(category!=1) //until long category reaches 1
    {
        category = category/2; //divide by 2
        catCells.push_back(category); //place in vector
    }
    return catCells; //return vector with decrementing cell counts corresponding to "divisions remaining" to main
}

long TotalCells(int reps) //function to generate value for total cells manipulated in program from user input
{
    long total = 2;

    for(int i = 0; i<reps; i++)//for as many times as value "reps"
    {
        total *= 2; //self increment to the power of 2 to establish geometric exponential growth
    }
    
    return total; //return long to main
}

int main() {
    int replications;
    long totalCells;
    int j=60;
    int mode;
    cout<<"Welcome to MitosisHostess®."<<endl<<endl; //snazzy copyright notice
    cout<<"1. Standard"<<endl<<"2. Non-Random After 40 Replications"<<endl<<"3. HeLa Immortality"<<endl<<endl<<"Select mode: "; //user selects mode for cell division simulation
    cin>>mode; //submitted integer gets assigned as int mode
    while(mode>3 || mode<1) //to verify that user inters the correct mode
    {
        cout<<"Invalid entry. Please select from the options above: ";
        cin>>mode;
    }
    cout<<"Enter number of replications (0-60): "; //prompt user to enter number of times cell has divided
    cin>>replications; //assign value to int replications
    totalCells = TotalCells(replications); //set long totalCells as the output of function TotalCells() when replications is passed
    
    CategorizeCells(totalCells); //pass totalCells through function CategorizeCells
    if(mode==3) //if selected user mode is "3"
    {
        cout<<endl<<totalCells<<" cells with indefinite lifelines."<<endl<<endl; //simply writes total number of cells with indefinite lifelines
        return 0; //end program
    }
    for(int i = 0; i<catCells.size(); i++) //run loop for as many times as there are elements in "catCells"
    {
        if(i == 40 && mode==1) //run loop if iterator reaches value 40 and user is in mode 1
        {
            randoms = Randomize(divsRemaining[21]); //randoms vector is filled to reach the sum of the value of "divsRemaining[ ]" at  index 21
            break; //exit loop
        }
        if(i<=40 && (mode==1||mode==2)) //if iterator does not reach 40 and user selects mode 1 or 2
        {
            randoms.push_back(0); //set randoms vector to be zero
        }
        divsRemaining[60-i]=catCells.at(i); //fill array "divsRemaining[ ]" with values from vector catCells starting at 60
    }
    if(mode==1) //if user is in mode 1
    {
        for(int i = 0; i<randoms.size()-1; i++) //for the size of vector randoms
        {
            divsRemaining[20-i]=randoms.at(i); //assign remaining indexes of divsRemaining[ ] the semirandom values in vector randoms
        }
    }
    while(j>=0) //while counter j is positive
    {
        if(divsRemaining[j]!=0) //only write out lines where index is filled
        {
            cout<<endl<<"Cells with "<<j<<" Divisions Remaining: "<<divsRemaining[j]; //prompt user with frequency of cells per their number of divisions remaining
        }
        j--; //decrement counter j
    }

    cout<<endl<<endl<<"Dead cells: "<<randoms.front()<<endl; //arbitrary excess random value unused found in vector randoms is written as theoretical "dead" cells
    cout<<endl<<"Total living cells: "<<totalCells-randoms.front()-1<<endl<<endl; //writes out total living cells entailing the total amount of cells minus the determined "dead" cells minus 1 to correct for exponential growth
    return 0; //end program
}
