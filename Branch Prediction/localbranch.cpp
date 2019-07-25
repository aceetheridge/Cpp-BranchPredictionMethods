//Aaron Etheridge 
//aetheri2@uncc.edu 800936351
//ECGR 4181 Hw4

// To compile
// g++ -std=FILENAME.cpp -o OUTPUTFILENAME 
// To run ./OUTPUTFILENAME 2 ((2 being the number of saturating bits can range from 2-8))

// Two Level local Branch Predictor
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
    for(int i = 0; i < 1024; i++){ // fills the array with Strongly Not Taken
        pht[i]= -1;
    }

    int statebits = (pow(2,argument_to_int(&argv[1])))/2;
    string tenbits = "0000000000";
    string tenbitsinput;
    string address;
    string take;
    long int hit = 0;
    long int count = 0;
    int prediction = 0;
    string strprediction;
    int stateinput;

    ifstream input;
    ofstream output;
    //input.open("testtrace.trace"); //branch-trace-gcc
    input.open("branch-trace-gcc.trace");
    output.open("output.txt");
    while(true){
        int appendbit = 0;
        input >> address >> take;
        long int temp = stol(address, nullptr, 10);
        if (temp < 999999999 && temp > 111){ // makes the pc address long enough
            address = "0" + address;
            appendbit = 1;
        }
        else{
            address = address;
        }

        string takebits = address.substr(6,4);
        takebits = "0000"+ takebits + "00"; // finds a PC values
        int y = stoi(takebits,nullptr,16)%128; // finds a PC value
        //int x = stoi(tenbits,nullptr,2);

        if(pht[local[y]] < statebits){ // if prediction is N
            if(take == "T" || take == "1"){
                pht[local[y]]++; // increments the saturating counter
            }
            else if(take == "N" || take == "0"){
                hit++;
                if(pht[local[y]] > (statebits *(-1)+1)){
                    pht[local[y]]--; // decrements the saturating counter
                }
            }
        }
        else{ //if prediction is T
            if(take == "T" || take == "1"){
                hit++;
                if(pht[local[y]] < statebits){
                    pht[local[y]]++;
                }
            }
            else if(take =="N" || take == "0"){
                pht[local[y]]--;
            }
        }
        if(take == "T" || take == "1"){ // shifts the local history table
            local[y] = local[y] << 1;
            local[y] = local[y] + 1;
        }
        else if(take == "N" || take == "0"){ // shifts the local history table
            local[y]= local[y] << 1;
        }
        if(local[y] > 1023){
            local[y] = local[y] ^ 1024; // makes sure that local[y] is between 0-1023
        }
        count++;
        
        if(input.eof()){
            break;
        }
    }
    input.close();
    output.close();
    cout << endl << hit << "<-hit   count:" << count << " Two Level Local Prediction  Miss Percentage: " << 1-((double)hit/(double)count) << endl;

    return 0;
}
int argument_to_int(char *arg[]){
    int result = 0;
    result = (atoi(arg[0]))*(1); //posible errors
    cout << result << endl;
    return result;
}