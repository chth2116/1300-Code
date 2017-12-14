#include <iostream>
using namespace std;

class calculations{

public:
//constructor(s)
calculations();
~calculations();

//data members
float avg;
float temps2[1000];
int tracker2[1000];

//this function will calculate the average of all the values stored in the difference array
float calculateAvg(float[], int);
//this function will be used to predict the temperature for the following day month or year and will return that value
float predict(float[], int, float);
//this function will round the difference to the nearest tenth, then multiply that number by 10 to give the total decimal point difference
int rounding(float);

float rounding2(float);

int whatYear(float, float[], int[], int, float);

//this function will take in a temperature from the user and predict what year the temperature will be at the specified temperature
//int whatYear(float temps[], int tracker[], int count);


};
