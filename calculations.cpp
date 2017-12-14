#include <iostream>
#include <sstream>
#include <math.h>
#include "calculations.h"

using namespace std;


//constructors
calculations::calculations(){
    //initialize the arrays
    for(int i = 0; i<1000; i++){
        temps2[i] = 0;
        tracker2[i] = 0;
    }

    avg = 0;
}

calculations::~calculations(){
    //dtor
}

/*
This function will calculate the average decimal difference between each year in the file
it will take in the difference array with all of the differences and add each diff in this array
after each element in the array has been added,they will be divided to get the average and then
I will use functionalities from the rounding function to round these values to the nearest tenth
*/
float calculations::calculateAvg(float difference[], int dcount){
    cout << dcount << endl;

 //calculate average difference in temps between each consecutive day,month,or year
    float sum = 0;


    //add up all differences in the array
    for(int i = 0; i<dcount; i++){

        sum += difference[i];

    }
        cout << "sum is " << sum << endl;

    //find the average of the differences
    avg = sum/dcount;


    cout << "average before change: " << avg << ", ";

    //manipulate average so it is only 2 numbers long and is rounded to the nearest tenth
    avg = rounding2(avg);

    cout << "average after change: " << avg << endl;

    return avg;


}

/*
This function will predict the next temp. It will take the temperature array from the
Builder class, the count for the temps array and the average difference between each year.
the function will then add the average difference to the last temperature for the last year
in the file to calculate the temperature for the next year.
*/
float calculations::predict(float temps[], int count, float avg){

    int lastIndex = count - 1;
    float NextTemperature;

    //calculate the temperature for the next year by adding the avg difference to the last year
    NextTemperature = avg + temps[lastIndex];
    cout << "Next temperature before is: " << NextTemperature << endl;
    NextTemperature = rounding2(NextTemperature);

     return NextTemperature;


}

/*
This function will round manipulate the float entered
by making the number 2 characters long and rounding it to the nearest tenth
*/
int calculations::rounding(float diff){

    //create a string stream and store the number to manipulate it
    stringstream ss;
    ss << diff;
    //create two strings from the string stream
    string s1(ss.str());
    string s(ss.str());

    //find the decimal point and remove all the characters before and including it
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
                //erase all the values after the first behind the decimal (only want one decimal place)
                s.erase(i+3, s.length());
        }


    //make the edited number a float value to be rounded
    diff = stof(s);

    //if the number is negative, subtract 0.05
    if (diff < 0){
        diff = diff - 0.05;
    }

    //if the number is positive, add 0.05
    else{
        diff = diff + 0.05;
    }
    //multiply the rounded number by ten in order to finish rounding it then make it an integer
    //so that it can be used as a limiter in the for loops to build the histograms
    diff = diff*10;
    diff = int(diff);
    }

    return diff;

}
/*
This rounding function will be used in both the calculate average function (to round
the average difference) and the what year function to round the temperatures being incremented through
this function takes the number the user wishes to manipulate
the function uses similar functionality to the original rounding function
*/
float calculations::rounding2(float num){
   //manipulate the difference so that there are only two decimal places
    stringstream ss;
    ss << num;
    string s1(ss.str());
    string s(ss.str());

    //get rid of decimal point to see how long the number is after the decimal
    for(int i = 0; i<=s1.length(); i++){
        if(s1[i]=='.'){
            s1.erase(0,i+1);
        }
    }

    //if there is only 1 decimal place, no need to round; set the avg value here
    if (s1.length() < 2){
        num = stof(s);
    }

    //if there are two or more decimal values, round those values, erase any extra (more than 1)
    else{
        for(int i = 0; i<=s.length(); i++){
            //round the number to the nearest tenth
            if (s[i] == '.'){
                s.erase(i+3, s.length());
                    if ((s[3] >= '5' )&&(s[3]<='9')){
                        s.erase(3,1);
                        num = stof(s);
                        num = num + 0.1;
                    }
                        else{
                            s.erase(3,1);
                            num = stof(s);
                        }
            }


        }


    }

    return num;
}

/*
This function will take in a temperature from the user, then using the temps and tracker arrays
the function will try and find what year the temperature entered will occur based on the average
difference between each year. The function will use the calculate average function to get this difference
and the rounding function to round the temps being incremented through
*/
int calculations::whatYear(float temperature, float temps[], int tracker[], int count, float average){

    //make copies of the arrays
    for(int i = 0; i < count; i++){

       temps2[i] = temps[i];
       tracker2[i] = tracker[i];
       cout << tracker2[i] << " : " << temps2[i] << endl;
    }

    //check to see when the temperature will be at the one given by user
    for (int i = count; i<1000; i++){
        //increase year by one
        tracker2[i] = tracker2[i-1] + 1;
        cout << tracker2[i-1] << endl;
        //cout <<"next year is: " << tracker2[i] << endl;
        //increase temperature by avg difference
        cout << temps2[i-1] << endl;
        temps2[i] = rounding2(temps2[i-1] + average);


            //if the temp is equal to the one given, print the year
            if(temps2[i] == temperature){
                return tracker2[i];
            }
            //if the temp is above the one give, print that year (thats the closest it got while still reaching the temperature inputed)
            else if(temps2[i]>temperature){
                return tracker2[i];
            }

    }




}
