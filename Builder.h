#include <iostream>
using namespace std;

class Builder{

public:
//constructors int buildArrays(string filename);
Builder(string);
~Builder();

//data members
string measurementType; //daily, monthly, or yearly

/*
this array will store the specific day month or year being measured
if temp is measured daily, days will go up to "Sunday" (7 days)
if temp is measured monthly, tracker will go up to "December" (12 months)
if temp is measured annually, tracker will go up to any year (ex: 2040) for up to a 20 year span (20 years)
*/
int tracker[1000];

/*
this array will store the temperature associated with the
month, day, or year
*/
float temps[1000];


/*create an array that stores all the consecutive differences of temperatures*/
float difference[1000];

float avg;
float NextTemperature;
//methods

//this function will be used to make the arrays from the file with the information on the temperatures
//function will also return the size of the arrays
int buildArrays(string filename);
//this will make an array that stores all of the changes in temperature between each consecutive year
int makeDiffArray();
//this function will be used to build the histogram with the temps array and the tracker array
int  buildHistogram();

void whatsgood();

//this function will be used to predict the temperature for the following day month or year and will return that value
float predict();

//this function will round the difference to the nearest tenth, then multiply that number by 10 to give the total decimal point difference
//int rounding(float);

//this function will take the temperature from the predict function and append it to the original file
void appendNextTemp(string);
//getters and setters
int getCount();
int getDcount();
private:
//this will keep track of the array size for both arrays
int count;
int dcount;

};
