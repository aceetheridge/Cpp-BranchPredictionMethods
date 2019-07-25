#!/bin/bash
 

#To run copy the sudo line first then execute the .sh file

#sudo chmod +x RUNALL.sh
#./RUNALL.sh

# Problems 1 and 2
g++ -std=c++11 oneLevel.cpp -o oneLevelOutput

./oneLevelOutput 2

g++ -std=c++11 Global.cpp -o GlobalOutput

./GlobalOutput 2

g++ -std=c++11 gshare.cpp -o gshareOutput

./gshareOutput 2

./gshareOutput 4

./gshareOutput 6

./gshareOutput 8

g++ -std=c++11 localbranch.cpp -o localbranchOutput

./localbranchOutput 2

./localbranchOutput 4

./localbranchOutput 6

./localbranchOutput 8


#Problem 3

g++ -std=c++11 Pin_gshare_Dhrystone.cpp -o PinGshareDhrystoneOutput

./PinGshareDhrystoneOutput 2

./PinGshareDhrystoneOutput 4

./PinGshareDhrystoneOutput 6

./PinGshareDhrystoneOutput 8

g++ -std=c++11 Pin_gshare_Linpack.cpp -o PinGshareLinpackOutput

./PinGshareLinpackOutput 2

./PinGshareLinpackOutput 4

./PinGshareLinpackOutput 6

./PinGshareLinpackOutput 8

g++ -std=c++11 Pin_Local_Dhrystone.cpp -o PinLocalDhryOutput

./PinLocalDhryOutput 2

./PinLocalDhryOutput 4

./PinLocalDhryOutput 6

./PinLocalDhryOutput 8

g++ -std=c++11 Pin_Local_Linpack.cpp -o PinLocalLinOutput

./PinLocalLinOutput 2

./PinLocalLinOutput 4

./PinLocalLinOutput 6

./PinLocalLinOutput 8


#Extra Credit
g++ -std=c++11 extracredit.cpp -o extra

./extra 2

./extra 4

./extra 6

./extra 8
