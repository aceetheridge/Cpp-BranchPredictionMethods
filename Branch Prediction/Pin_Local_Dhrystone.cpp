//Aaron Etheridge 
//aetheri2@uncc.edu 800936351
//ECGR 4181 Hw4

// To compile
// g++ -std=FILENAME.cpp -o OUTPUTFILENAME 
// To run ./OUTPUTFILENAME 2 ((2 being the number of saturating bits can range from 2-8))

// Pin Version for Two level Local Prediction
#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <math.h>
#include <sstream>
#include <typeinfo>

using namespace std;

int argument_to_int(char *arg[]);
int state(int input, int currentstate, int bits);

int pht[1024];
int local[128];

int main(int argc, char *argv[]){
    for(int i = 0; i < 1024; i++){
        pht[i]= -1;
    }

    int statebits = (pow(2,argument_to_int(&argv[1])))/2;
    string tenbits = "0000000000";
    string tenbitsinput;
    string address;
    string take;
    string empty1;
    string empty2;
    string empty3;
    string empty4;
    string empty5; // empty strings to read in data properly
    string empty6;
    string empty7;
    string empty8;
    string empty9;
    string empty10;
    
    string condition;
    string empty;
    long int hit = 0;
    long int count = 0;
    int prediction = 0;
    string strprediction;
    int stateinput;

    ifstream input;
    ofstream output;
    //input.open("testtrace.trace"); //branch-trace-gcc
    input.open("dry.trace");
    output.open("output.txt");
    while(true){
        input >> empty1 >> take >> condition >> empty4 >> empty5 >> empty6 >> empty7 >> address >> empty9 >> empty2 >> empty3;
            if(empty3 == "ret"){
            }
            else{
                input >> empty10;
                if (empty10 == "qword"){
                    input >> empty2 >> empty2;  // all this sorts the valuable data
                }
                else if(empty10 == "jmp"){
                    input >> empty2;
                }
            }
            if(condition == "1"){ // take PC under different conditions
                if(address.size() < 10){
                    address = (address.substr(2,6));
                }
                else{
                address = (address.substr(7,6));
                }
                long int y = stol(address, nullptr, 16)%128; // gets a number between 0-128 for local history table

        if(pht[local[y]] < statebits){ // if prediction is T
            if(take == "T" || take == "1"){
                pht[local[y]]++;
            }
            else if(take == "N" || take == "0"){
                hit++;
                if(pht[local[y]] > (statebits *(-1)+1)){
                    pht[local[y]]--;
                }
            }
        }
        else{ // if prediction is N
            if(take == "T" || take == "1"){
                hit++;
                if(pht[local[y]] < statebits){
                    pht[local[y]]++;
                }
            }
            else if(take == "N" || take == "0"){
                pht[local[y]]--;
            }
        }
        if(take == "T" || take == "1"){ // shifts the local history table
            local[y] = local[y] << 1;
            local[y] = local[y] + 1;
        }
        else if(take == "N" || take == "0"){
            local[y]= local[y] << 1;
        }
        if(local[y] > 1023){ // makes sure local history address isnt larger than 1023
            local[y] = local[y] ^ 1024;
        }
        count++;
        }
        if(input.eof()){
            break;
        }
    }
    input.close();
    output.close();
    cout << endl << hit << "<-hit   count:" << count << " Pin Version of Local Predictor with Dhrystone  Miss Percentage: " << 1-((double)hit/(double)count) << endl;

    return 0;
}
int argument_to_int(char *arg[]){
    int result = 0;
    result = (atoi(arg[0]))*(1); //posible errors
    cout << result << endl;
    return result;
}