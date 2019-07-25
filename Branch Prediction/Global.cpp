//Aaron Etheridge 
//aetheri2@uncc.edu 800936351
//ECGR 4181 Hw4

// To compile
// g++ -std=FILENAME.cpp -o OUTPUTFILENAME 
// To run ./OUTPUTFILENAME 2 ((2 being the number of saturating bits can range from 2-8))

// Two Level Global Predictor

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

int main(int argc, char *argv[]){
    for(int i = 0; i < 1024; i++){
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
    input.open("branch-trace-gcc.trace");
    output.open("output.txt");
    while(true){
        int appendbit = 0;
        input >> address >> take;
        int x = stoi(tenbits,nullptr,2);
        if(pht[x] < 1){ // if the prediction is N
            if(take == "T" || take == "1"){
                pht[x]++;
            }
            else if(take == "N" || take == "0"){
                hit++;
                if(pht[x] > ((statebits *(-1))+1)){
                    pht[x]--;
                }
            }
        }
        else{ //If the prediction is T
            if(take == "T" || take == "1"){
                hit++;
                if(pht[x] < statebits){
                    pht[x]++;
                }
            }
            else if(take == "N" || take == "0"){
                pht[x]--;
            }
        }

        if(take != "T"){ // adds a 0 to the pht if N
            tenbitsinput = "0";
        }
        else{ // adds a 1 to the pht if T
            tenbitsinput = "1";
        }
        tenbits = tenbits + tenbitsinput; // shifts the pht after the new bit is added
        tenbits = tenbits.substr(1,10);
        count++;
        
        if(input.eof()){
            break;
        }
    }
    input.close();
    output.close();
    cout << endl << hit << "<-hit   count:" << count << " Global Predictor  Miss Percentage: " << 1-((double)hit/(double)count) << endl;

    return 0;
}
int argument_to_int(char *arg[]){
    int result = 0;
    result = (atoi(arg[0]))*(1); //posible errors
    cout << result << endl;
    return result;
}