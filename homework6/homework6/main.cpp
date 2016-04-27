//
//  main.cpp
//  encryption
//
//  Created by Nathaniel Polley on 4/25/16.
//  Copyright (c) 2016 Nathaniel Polley. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;
vector<int>encryptedSocInt; //declare global vector to store hash addresses
vector<int>socialInt; //declare global vector to store keys
int Hashtable[100000]; //establish global hash table with arbitrary size 100000
ifstream in; //declaration of file input
vector<int> importFile(string name) //function to both import text file and parse continuous string to individual ints
{
    vector<int>int_vector; //vector to store initial ints
    string text; //string to hold read-in text

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
            if(ss.peek()==',') //if untouched returned index character is ','
            {
                ss.ignore(); //ignore all commas when adding characters to vector
            }
        }
    }
    return int_vector; //return filled integer vector
}

bool encryptFile(string name)
{
    string socialString;
    string encryptedSocStr;
    socialInt= importFile(name);
    vector<string>socialStr;
    vector<string>encryptedSoc;
    int encryptedInt;
    
    
    for(int i = 0; i<socialInt.size(); i++) //convert elements in int vector to strings
    {
        ostringstream socialConvert;
        socialConvert<< socialInt.at(i);
        socialString=socialConvert.str();
        
        socialStr.push_back(socialString);
    }
    
    for(int i = 0; i<socialStr.size(); i++)
    {
        encryptedSocStr = string()+socialStr.at(i)[2]+socialStr.at(i)[4]+socialStr.at(i)[6]+socialStr.at(i)[7]; //parse and concatinate string at set characters to create hash address
        encryptedSoc.push_back(encryptedSocStr); //push hash address back into vector
    }
    
    for(int i = 0; i<encryptedSoc.size(); i++)
    {
        encryptedInt = atoi((encryptedSoc.at(i)).c_str()); //command to convert string to int in order to be utilized as array indices
        encryptedSocInt.push_back(encryptedInt);

    }
    return true;
}

bool To_Hash(int key, int pos, int value)
{
    int i;
    if(Hashtable[pos]==0) //if index is empty
    {
        Hashtable[pos]=key; //set key to indicated index
        return pos;
    }
    else //if index is full
    {
        for(i=pos+value^2; i%100000!=pos; i++) //iterate index value depending on user input quadratic
        {
            if(Hashtable[i]==0) //if space is empty
            {
                Hashtable[i]=key; //set key to index
                return i;
            }
        }
    }
    return true;
}

int main() {
    encryptFile("encryption.txt");
    ofstream out;
    out.open("hashed_socials.txt");
    int value;
    cout<<"Enter integer for quadratic probing: ";
    cin>>value;
    if (value>39999) //to prevent crashing when large integers are entered
    {
        value = value / 10000;
    }
    for(int i = 0; i<socialInt.size(); i++) //run loop for as many times as the size of vector
    {
        To_Hash(socialInt.at(i), encryptedSocInt.at(i), value); //sends key, index, and quadratic probing value to be hashed
    }
    
    for(int i = 0; i<100000; i++) //run loop for 100000 times (the pre determined size of hash table)
    {
        if(i<99999) //add commas to everything but last element
        {
            cout<< Hashtable[i]<<", ";
            out<< Hashtable[i]<<", ";
        }
        else //do not add comma to last element
        {
            cout<< Hashtable[i];
            out<< Hashtable[i];
        }
    }
    
    in.clear();
    in.close();
    out.clear();
    out.close();
    return 0;
}
