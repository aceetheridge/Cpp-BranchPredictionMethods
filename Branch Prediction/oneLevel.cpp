//Aaron Etheridge 
//aetheri2@uncc.edu 800936351
//ECGR 4181 Hw4

// To compile
// g++ -std=FILENAME.cpp -o OUTPUTFILENAME 
// To run ./OUTPUTFILENAME 2 ((2 being the number of saturating bits can range from 2-8))


// One Level Branch Predictor

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
int state(int, int, int);
int main(int argc, char *argv[]){
    int statebits =(pow(2,argument_to_int(&argv[1])))/2; // Takes arguments
    string address;
    string take;
    long int hit = 0;
    long int count = 0;
    int prediction = -1;
    string strprediction;
    int stateinput = 0;

    ifstream input;
    ofstream output;
    input.open("branch-trace-gcc.trace");
    output.open("output.txt");
    while(true){
        int appendbit = 0;
        if(prediction >= 1){ // reads prediction
            strprediction = "T";
            }
       else if(prediction < 1){
           strprediction = "N";
            }
        input >> address >> take; // reads address
        long int temp = stol(address, nullptr, 10);
        if (temp < 999999999 && temp > 111){ // if address is to small append it
            address = "0" + address;
            appendbit = 1;
        }
        else{
            address = address;
        }
        if(take == "N"){ // condition for shifting the state in the state function
            stateinput = -1;
        }
        else{
            stateinput = 1;
        }
        if(take == strprediction){ // checks if hit or miss
            hit++;
        }
        prediction = state(stateinput, prediction, statebits);
        count++;
        
        
        //cout << address << " " << take << endl;
        if(input.eof()){
            break;
        }
    }
    input.close();
    output.close();
    cout << endl << hit << "<-hit   count:" << count << " One Level Predictor  Miss Percentage: " << 1-((double)hit/(double)count) << endl;

    return 0;
}
int state(int input, int currentstate, int bits){ // shifts the saturating bit up or down based on prediction
    if ((currentstate < bits) && (currentstate > ((bits *(-1))+1))){
        currentstate = currentstate + input;
    }
    else if(currentstate == bits && input == -1){
        currentstate = currentstate + input;
    }
    else if(currentstate == ((bits *(-1))+1) && input == 1){
        currentstate = currentstate + input;
    }
    else {
        currentstate = currentstate;
    }
    return currentstate;
}
int argument_to_int(char *arg[]){
    int result = 0;
    result = (atoi(arg[0]))*(1); //posible errors
    cout << result << endl;
    return result;
}