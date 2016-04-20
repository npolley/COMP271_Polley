//
//  main.cpp
//  homework5
//
//  Created by Nathaniel Polley on 4/17/16.
//  Copyright (c) 2016 Nathaniel Polley. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
int comparisons = 0; //global declaration of integer "comparisons" to be used across all functions
int exchanges = 0; //global declaration of integer "exchanges" to be used across all functions

vector<int> importFile(string name) //function to both import text file and parse continuous string to individual ints
{
    vector<int>int_vector; //vector to store initial ints
    string text; //string to hold read-in text
    ifstream in; //declaration of file input
    in.open(name); //open said file when given name
    while(!in.is_open())
    {
        cout << "The read file could not be opened. Please input another file name.\t"; //if file cannot be opened,send prompt
        cin>>name; //user input is new string "name"
        in.open(name); //open input string again
    }
    
    while(in.peek() != EOF) //do until the end of file
    {
        getline(in,text);
        stringstream ss(text); //declaration of stringstream "ss" to organize and parse ints between commas
        int i; //declatation of integer i
        while (ss>>i) //run loop while "ss" is getting assigned to int i
        {
            int_vector.push_back(i); //adds parsed int from string to int_vector vector for convenient unloading into queue
            if(ss.peek()==' ') //if untouched returned index character is ' '
            {
                ss.ignore(); //ignore all spaces when adding characters to vector
            }
        }
    }
    return int_vector; //return filled integer vector
}

vector<int> merge(vector<int> left, vector<int> right)
{
    vector<int> result;
    
    while ((int)left.size() > 0 || (int)right.size() > 0) //run loop while data is contained on either side
    {
        
        if ((int)left.size() > 0 && (int)right.size() > 0) //run loop if both sides contain data
        {
            
            if ((int)left.front() <= (int)right.front()) //run loop if front value of left vector is less than front value of right vector
            {
                comparisons++; //counts as one comparison
                result.push_back((int)left.front()); //insert int value from front of left vector into result vector
                left.erase(left.begin()); //erase beginning int from left vector
                
            }
            else //run loop if front value of right vector is less than front value of left vector
            {
                comparisons++;
                result.push_back((int)right.front()); //insert int value from front of right vector into result vector
                right.erase(right.begin()); //erase beginning int from right vector
                exchanges++; //one exchange is made
            }
        }
        else if ((int)left.size() > 0) //run loop if left side contains data
        {
            comparisons++; //constitutes one comparison
            for (int i = 0; i < (int)left.size(); i++) //run loop for as many times as the size of left vector
                result.push_back(left[i]); //push remaining ints on left side into vector
            break; //exit loop
        }
        else if ((int)right.size() > 0) //run loop if right side contains data
        {
            comparisons++; //constitutes one comparison
            for (int i = 0; i < (int)right.size(); i++) //run loop for as many times as the size of right vector
                result.push_back(right[i]); //push remaining ints on left side into vector
            break; //exit loop
        }
    }
    return result;
}

vector<int> mSort(vector<int> &sorting_vector)
{
    if (sorting_vector.size() <= 1) //simply return vector if size is less than or equal to 1
        return sorting_vector;
    
    vector<int> left, right, result; //create three vectors to divide data
    int middle = ((int)sorting_vector.size()+ 1) / 2; //sets int middle as the sorting vector size divided by 2
    
    for (int i = 0; i < middle; i++) //run loop for as many times as it takes to increment to middle value
    {
        left.push_back(sorting_vector[i]); //insert integers in vector denoting "left" values
    }
    
    for (int i = middle; i < (int)sorting_vector.size(); i++) //run loop for as many times as it takes to increment to end value from middle value
    {
        right.push_back(sorting_vector[i]); //insert integers in vector denoting "right" values
    }
    
    left = mSort(left); //recursively run left vector through mSort to be divided in half to smaller values
    right = mSort(right); //recursively run right vector through mSort to be divided in half to smaller values
    result = merge(left, right); //implement merge function for left and right vectors
    
    return result;
}

string mergeSort(string fileName)
{

    string comparisonsStr;
    string exchangesStr;
    vector<int>sorting_vector;
    
    sorting_vector = importFile(fileName); //obtains integer vector from importFile function
    
    sorting_vector = mSort(sorting_vector); //implement mSort with vector
    
    ostringstream comparisonsConvert;        //***********************************************
    comparisonsConvert << comparisons;
    comparisonsStr=comparisonsConvert.str();
                                             // code to convert ints comparisons and exchanges to string values
    ostringstream exchangesConvert;
    exchangesConvert << exchanges;
    exchangesStr=exchangesConvert.str();     //***********************************************
    
    string data = "Merge Sort  of " + fileName + " - Comparisons: " + comparisonsStr + " Exchanges: " + exchangesStr; //build string prompt of search statistics
    comparisons = 0; //reset int comparisons
    exchanges = 0; //reset int exchanges
    return data; //return statistical prompt
}

string shellSort(string fileName)
{

    string comparisonsStr;
    string exchangesStr;
    vector<int>sorting_vector;
    
    sorting_vector = importFile(fileName); //obtains integer vector from importFile function
    
    int temp, gap, i;
    int swapped;
    gap = sorting_vector.size()/2; //sets gap as half of sorting_vector size
    do //run loop while gap/2 is greater than 1
    {
        do //run loop while swapped is equal to 1
        {
            swapped = 0;
            for(i = 0; i<sorting_vector.size()-gap; i++) //run loop for as many times as size of vector minus half of size of vector
            {
                if(sorting_vector.at(i)>sorting_vector.at(i+gap)) //run loop if sorting vector at initial index is greater than sorting vector at initial index plus half of sorting vector size
                {
                    temp = sorting_vector.at(i); //sets temp placeholder value as value at initial index
                    sorting_vector.at(i) = sorting_vector.at(i+gap); //replaces value at initial index with value at initial index plus gap
                    sorting_vector.at(i+gap) = temp; //initial index plus gap gets assigned as index value
                    swapped = 1; //swapped is marked as one
                    exchanges++; //whole process constitutes one exchange
                }
                comparisons+=i; //each run through for loop constitutes one comparison
            }
        } while(swapped == 1); //as many times as there needs to be swappage in sector of vector
    } while((gap = gap/2) >= 1);
    
    ostringstream comparisonsConvert;        //***********************************************
    comparisonsConvert << comparisons;
    comparisonsStr=comparisonsConvert.str();
                                             // code to convert ints comparisons and exchanges to string values
    ostringstream exchangesConvert;
    exchangesConvert << exchanges;
    exchangesStr=exchangesConvert.str();     //***********************************************
    
    string data = "Shell Sort of " + fileName + " - Comparisons: " + comparisonsStr + " Exchanges: " + exchangesStr; //build string prompt of search statistics
    comparisons = 0; //reset int comparisons
    exchanges = 0; //reset int exchanges
    return data; //return statistical prompt
}

int partition(vector<int> &sorting_vector, int low, long high)
{
    int x = sorting_vector.at(low); //sets x as index "low" of vector
    int i = low; //sets i as int low
    
    for(int j=low+1; j<high; j++) //run loop for as many times as high-(low+1)
    {
        comparisons++;
        if(sorting_vector.at(j)<=x) //run loop if
        {
            i++; //increment i
            swap(sorting_vector.at(j), sorting_vector.at(i)); //switch index at j with index at i
            exchanges++; //each run through this loop constitutes one exchange
        }
    }
    swap(sorting_vector.at(i), sorting_vector.at(low)); //swap initial index of vector with index after i has been fully incremented
    return i;
}

void qsort(vector<int> &sorting_vector, int low, long high)
{
    int k; //sets arbitrary integer k
    if (low < high) //run loop as long as low is less than high
    {
        comparisons++;
        k = partition(sorting_vector, low, high); //partitions vector according to low and high values
        qsort(sorting_vector, low, k); //run new values through recursive function
        qsort(sorting_vector, k+1, high); //run new values through recursive function
        
    }
}

string quickSort(string fileName) //master function for quick sorting algorithm
{
    string comparisonsStr;
    string exchangesStr;
    vector<int>sorting_vector;
    
    sorting_vector = importFile(fileName); //obtains integer vector from importFile function
    
    int low = 0; //sets int low as 0 (starting index)
    long high = sorting_vector.size(); //sets int high as vector size (ending index)
    
    qsort(sorting_vector, low, high); //implement qsort of vector along with low and high int values

    ostringstream comparisonsConvert;        //***********************************************
    comparisonsConvert << comparisons;
    comparisonsStr=comparisonsConvert.str();
                                             // code to convert ints comparisons and exchanges to string values
    ostringstream exchangesConvert;
    exchangesConvert << exchanges;
    exchangesStr=exchangesConvert.str();     //***********************************************
    
    string data = "Quick Sort of " + fileName + " - Comparisons: " + comparisonsStr + " Exchanges: " + exchangesStr; //build string prompt of search statistics
    comparisons = 0; //reset int comparisons
    exchanges = 0; //reset int exchanges
    return data; //return statistical prompt
}

string insertionSort(string fileName) //master function for insertion sorting algortithm
{
    string comparisonsStr;
    string exchangesStr;
    vector<int>sorting_vector;
    
    sorting_vector = importFile(fileName); //obtains integer vector from importFile function
    
    int i, j, element;
    for(i=1; i<sorting_vector.size(); i++) //run loop for size of vector starting with int 1
    {
        element = sorting_vector.at(i); //sets initial element at insertion value
        j = i; //sets index value as j
        while((j>0) && (sorting_vector.at(j-1)>element)) //run loop while both index value is greater than zero and preceding element is greater than succeeding element
        {
            sorting_vector.at(j) = sorting_vector.at(j-1); //replace value at intial index with value at proceeding index
            j = j-1; //decrement index reference value j
            exchanges++; //action counts as one exchange
        }
        sorting_vector.at(j)=element; //fills final void with insertion value
        comparisons+=i; //each run through for loop counts as one comparison
    }
    
    ostringstream comparisonsConvert;        //***********************************************
    comparisonsConvert << comparisons;
    comparisonsStr=comparisonsConvert.str();
                                             // code to convert ints comparisons and exchanges to string values
    ostringstream exchangesConvert;
    exchangesConvert << exchanges;
    exchangesStr=exchangesConvert.str();     //***********************************************
    
    string data = "Insertion Sort of " + fileName + " - Comparisons: " + comparisonsStr + " Exchanges: " + exchangesStr; //build string prompt of search statistics
    comparisons = 0; //reset int comparisons
    exchanges = 0; //reset int exchanges
    return data; //return statistical prompt
}

string bubbleSort(string fileName) //master function for bubble sorting algortithm
{
    string comparisonsStr;
    string exchangesStr;
    vector<int>sorting_vector;
    
    sorting_vector = importFile(fileName); //obtains integer vector from importFile function
    
    int i,j,temp;
    for(i=1; i<sorting_vector.size(); i++) //run loop for size of vector
    {
        for(j=0; j<sorting_vector.size()-1; j++) //run loop for size of vector-1
        {
            
            if(sorting_vector.at(j)>sorting_vector.at(j+1)) //run loop if element value in initial index is greater than its successor
            {
                temp=sorting_vector.at(j); //hold initial value in int temp
                sorting_vector.at(j)=sorting_vector.at(j+1); //replace initial value with succeeding value
                sorting_vector.at(j+1)=temp; //replace succeeding value with initial value stored in temp
                exchanges++; //count this whole transaction as one exchange
            }
            
        }
        comparisons+=i; //combination of both inner and outer for loops count at one comparison
    }
    
    ostringstream comparisonsConvert;        //***********************************************
    comparisonsConvert << comparisons;
    comparisonsStr=comparisonsConvert.str();
                                             // code to convert ints comparisons and exchanges to string values
    ostringstream exchangesConvert;
    exchangesConvert << exchanges;
    exchangesStr=exchangesConvert.str();     //***********************************************
    
    string data = "Bubble Sort of " + fileName + " - Comparisons: " + comparisonsStr + " Exchanges: " + exchangesStr; //build string prompt of search statistics
    comparisons = 0; //reset int comparisons
    exchanges = 0;  //reset int exchanges
    return data;    //return statistical prompt
}

int main() {
    cout<<bubbleSort("fewUnique.txt")<<endl;
    cout<<bubbleSort("nearlySorted.txt")<<endl;
    cout<<bubbleSort("random.txt")<<endl;
    cout<<bubbleSort("reversed.txt")<<endl;
    cout<<endl;
    cout<<insertionSort("fewUnique.txt")<<endl;
    cout<<insertionSort("nearlySorted.txt")<<endl;
    cout<<insertionSort("random.txt")<<endl;
    cout<<insertionSort("reversed.txt")<<endl;
    cout<<endl;
    cout<<quickSort("fewUnique.txt")<<endl;
    cout<<quickSort("nearlySorted.txt")<<endl;
    cout<<quickSort("random.txt")<<endl;
    cout<<quickSort("reversed.txt")<<endl;
    cout<<endl;
    cout<<shellSort("fewUnique.txt")<<endl;
    cout<<shellSort("nearlySorted.txt")<<endl;
    cout<<shellSort("random.txt")<<endl;
    cout<<shellSort("reversed.txt")<<endl;
    cout<<endl;
    cout<<mergeSort("fewUnique.txt")<<endl;
    cout<<mergeSort("nearlySorted.txt")<<endl;
    cout<<mergeSort("random.txt")<<endl;
    cout<<mergeSort("reversed.txt")<<endl;

    cout<<endl;
    return 0;
}
