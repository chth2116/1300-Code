#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include "Builder.h"
#include "calculations.h"
using namespace std;

calculations object;
//constructors
Builder::Builder(string type){
    measurementType = type;
    count = 0;
    dcount = 0;


    for (int i = 0; i<1000; i++){
        temps[i] = 0;
        tracker[i] = 0;
        difference[i] = 0;
    }
}

Builder::~Builder(){
//dtor
}

//getters and setters
int Builder::getCount(){
return count;
}

int Builder::getDcount(){
    return dcount;
}
//functions
int Builder::buildArrays(string filename){
    //open file for input
    ifstream inStream;
    inStream.open(filename);

    //cycle through and store data
    string tempStr;
    while(getline(inStream, tempStr)){
        for(int i = 0; i<tempStr.length(); i++){
            if (tempStr[i] == ' '){
                tracker[count] = stoi(tempStr.substr(0, i));
                temps[count] = stof(tempStr.substr(i+1, tempStr.length()));
                count++;
            }
        }
    }
    inStream.close();
}

/*
this function will get the difference between two years temperatures and round it to the nearest tenth
function will then return the value to be used by the buildHistogram function
*/
/*int Builder::rounding(float diff){

//manipulate the difference so that there are only two decimal places
stringstream ss;
ss << diff;
string s1(ss.str());
string s(ss.str());
//tempStr;
for(int i = 0; i<=s1.length(); i++){
    if(s1[i]=='.'){
        s1.erase(0,i+1);
    }
}

//if there is only 1 decimal place, no need to round; set the difference value here
if (s1.length() < 2){
    diff = stof(s) * 10;
}

//if there are two or more decimal values, round those values, erase any extra (more than 2)
else{
for(int i = 0; i<=s.length(); i++){
    if (s[i] == '.')
        s.erase(i+3, s.length());
}

//make the edited number a float value to be manipulated
diff = stof(s);

//if the number is negative, subtract 0.5
if (diff < 0){
    diff = diff - 0.05;
}

//if the number is positive, add 0.5
else{
diff = diff + 0.05;
}
//round this number to the nearest tenth then make it an integer
diff = diff*10;
diff = int(diff);
}

return diff;
}
*/

int Builder::buildHistogram(){
    float diff1;
    int diff;
    int spaces = 0;
    int spaces1 = 0;


    //look for negative numbers to format spaces for dividing line
    for(int i = 0; i<count-1; i++){
        //reset spaces1
        spaces1 = 0;
        //calculate difference of all elements in temps array
        diff1 = temps[i+1] - temps[i];
        diff = object.rounding(diff1);
        //round down the values in difference array so that they can be incremented properly in loops
       // diff = floorf(diff1 * 100)/100;

        //if there is a negative, let's figure out the spaces needed before the dividing line
        if (diff < 0){
            //make the difference positive and a whole number
            diff = diff * -1;
        //get the number of spaces by counting the number of symbols that will be used
        for (int i = 0; i<diff; i++){
            spaces1 ++;
        }
        //if there is a new max spaces count, set it to the new max
        if (spaces1 > spaces){
            spaces = spaces1;
        }
    }
    }
    //cycle through temps array and compare each pair of temps
    for(int i = 0; i<count-1; i++){
        diff1 = temps[i+1] - temps[i];

        diff = object.rounding(diff1);
        //diff = floorf(diff1 * 100)/100;

        //format negative changes in temperature
        if (diff < 0){
            diff = diff * -1;
        cout << "[" << tracker[i] << "-" << tracker[i+1] << "]";

       //must put the correct number of spaces before the first symbol so that the dividing line is aligned
       for (int j = 0; j<spaces-diff; j++){
            cout << " ";
       }
        for (int i = 0; i<diff; i++){
            cout << "*";

        }
        cout << "|" << endl;

        }

       //if there was no change in temperature, just out put a ~ symbol
       else if (diff == 0){
            cout << "[" << tracker[i] << "-" << tracker[i+1] << "]";
            //format spaces so dividing line is aligned
            for (int i = 0; i<spaces; i++){
                cout << " ";
            }


            //print dividing line and symbol after the spaces
           cout << "|" << "~" << endl;
        }


        //build rows with the correct spaces and * symbols
        else{
                //make difference a whole number so that it can be indexed through

        cout << "[" << tracker[i] << "-" << tracker[i+1] << "]";
        //print all the necessary spaces in front of the dividing line
        for (int i = 0; i<spaces; i++){
            cout << " ";
        }
        cout << "|";

        //print out all of the necessary symbols to represent the change in temperature
        //cout << "[";
        for (int i = 0; i<diff; i++){
            cout << "*";

        }
        cout <<endl;
    }

  }
}
 int Builder::makeDiffArray(){
  //cycle through temps array and compare each pair of temps
  float diff;
  int diff2;
  float diff1;
  for(int i = 0; i<count-1; i++){


    //calculate difference between the temps
   diff1 = temps[i+1] - temps[i];

        //cout << diff1 << endl;



        //format the temps, round up and give one decimal
        diff2 = object.rounding(diff1);
        diff = float(diff2);
        diff = diff/10;
        //store the difference into the difference array, increase count
        difference[dcount] = diff;
        dcount++;


  }

  return dcount;
}



 void Builder::appendNextTemp(string filename){
    //open file for input
    fstream outStream;
    outStream.open(filename, std::fstream::app);

    if(!outStream){
        cout << "didn't open";
    }
    int d = getDcount();
    int c = getCount();
    float avg = object.calculateAvg(difference, d);

    float NextTemperature = object.predict(temps, c, avg);
    outStream << endl << tracker[count-1] + 1 << " " << NextTemperature;

 }


