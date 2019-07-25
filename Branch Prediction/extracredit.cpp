// Aaron Etheridge
// 800936351 aetheri2@uncc.edu
// 
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

int main(int argc, char *argv[]){
    int statebits = (pow(2,argument_to_int(&argv[1])))/2;
    int bht[4096];
    int bias[4096];
    int meta[4096];
    //int finmeta[4096];
    for(int i = 0; i< 4096; i++){ // starts all tables at strongly not taken
        bht[i] = -1;
        // bias[i] = 0;
        meta[i] = -1;
        //finmeta[i] = -1;
    }
    string address;
    string take;
    string condition;
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
    string bhtstr = "000000000000";
    int biasindex;
    string result1;
    string result2;
    string resultfinal;
    string select;
    string combine;
    string metastr;
    string taken;
    string biasstr;

    long int hit = 0;
    long int count = 0;

    ifstream input;
    input.open("branch-trace-gcc.trace");
    while (true)
    { // comment these two if statements to run pin.trace input
        input >> address >> taken;
        if(taken == "T"){
            take = "1";
        }
        if(taken == "N"){
            take = "0";
        } 
        // uncomment this code to run the pin files
        // input >> empty1 >> take >> condition >> empty4 >> empty5 >> empty6 >> empty7 >> address >> empty9 >> empty2 >> empty3;
        // if (empty3 == "ret")
        // {
        // }
        // else
        // {
        //     input >> empty10;
        //     if (empty10 == "qword")
        //     {
        //         input >> empty2 >> empty2; // all this sorts the valuable data
        //     }
        //     else if (empty10 == "jmp")
        //     {
        //         input >> empty2;
        //     }
        // }
        //if (condition == "1")
        //{
            address = address.substr(2,12);
            int x = stoi(bhtstr,nullptr,2);
            long long y = stoll(address,nullptr,16);
            biasindex = y % 4096;
            int z = (x^y) % 4096;

            if(bht[x%4096] > 0){ //another prediction result
                result2 = "1";

            }
            else if(bht[x%4096] < 1){
                result2 = "0";
            }



            if(meta[z] > 0  && bias[biasindex] > 0){ // combines two predictions and outputs a prediction
                result1 = "1";
            }
            else if(meta[z] > 0  && bias[biasindex] < 1){
                result1 = "1";
            }
            else if(meta[z] <= 0  && bias[biasindex] > 0){
                result1 = "1";
            }
            else if(meta[z]  <= 0  && bias[biasindex] < 1){
                result1 = "0";
            }
            
            // if(finmeta[biasindex] > 0){
            //     select = 1;
            // }
            // else if(finmeta[biasindex] < 1){
            //     select = 0;
            // }

            
            // This just shifts the counters for next iteration
            if(take == "T" || take == "1" ){
                if(meta[z] < statebits){
                   meta[z]++; 
                }
                if(bht[x%4096] < statebits){
                    bht[biasindex]++;
                }
                bias[biasindex] = 1;
            }
            else if(take == "N" || take == "0"){
                if(meta[z] > (statebits *(-1)+ 1)){
                    meta[z]--;
                }
                if(bht[x%4096] > (statebits *(-1)+ 1)){
                    bht[biasindex]--;
                }
                bias[biasindex] = 0;
            }



            // converts two predictions to strings
            if(meta[z] > 0){
                metastr = "1";
            }
            else if(meta[z] < 1){
                metastr = "0";
            }
            if(bias[biasindex] >0){
                biasstr = "1";
            }
            else if(bias[biasindex] < 1){
                biasstr = "0";
            }

            // combines all the results from all of the predictors into one predictor


            combine = result1 + result2 + metastr + biasstr;
            ///////////3/////////2//////////1/////////1   /// these comments tell the weights of the predictions // if the total is greater than 3 then its a T 
            if(combine == "0000" || combine == "0001" || combine == "0010" || combine == "0011"
             || combine == "0100"|| combine == "1000"){
                resultfinal = "0";
            }
            else if(combine == "0101"||  combine == "0110" || combine == "0111" ||  combine == "1001" || combine =="1010" || combine == "1011" // if less than 4 its a N
            || combine == "1100" || combine == "1101" || combine == "1110" || combine == "1111"){
                resultfinal = "1";
            }
            
            

            // if(select > 1){
            //     resultfinal = result1;
            // }
            // else if(select < 2){
            //     resultfinal == result2;
            // }

            if(take == resultfinal){
                //if(finmeta[biasindex] < statebits){
                  //  finmeta[biasindex]++;                    
                //}
                hit++;
                count++;
            }
            else if(take != resultfinal){
                //if(finmeta[biasindex] > (statebits *(-1)+ 1)){
                  //  finmeta[biasindex]--;
                //}
                count++;
            }

            
            if(take == "T" || take == "1"){ //shifts the past history table string
                bhtstr = bhtstr + "1";

            }
            else if(take == "N" || take == "0" ){
                bhtstr = bhtstr + "0";
            }
            bhtstr = bhtstr.substr(1,12);


        //}
        if(input.eof()){
            break;
        }
        
    }
    cout << "Hit: " << hit << " Count: " << count << " Miss Rate: " << (1-((double)hit/(double)count))*100 << endl;
    input.close();


    return 0;
}
int argument_to_int(char *arg[]){ // Takes in the arguments
    int result = 0;
    result = (atoi(arg[0]))*(1);
    cout << result << endl;
    return result;
}

