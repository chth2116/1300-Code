#include <iostream>
#include <fstream>
#include "Builder.h"
#include "calculations.h"
using namespace std;

int main()
{

  Builder object("Annual");
  calculations object2;

 object.buildArrays("annualTemps.txt");
 int j = object.getCount();

    for (int i = 0; i<j; i++){
        cout << object.tracker[i] << " : " << object.temps[i] << endl;
    }


   object.buildHistogram();

   object.makeDiffArray();

    /*
   //call get dcount and count to get array sizes for calculation class methods
   int dcount = object.getDcount();
   int count = object.getCount();
   //call calculateAvg function
   float avg = object2.calculateAvg(object.difference, dcount);

   float NextTemperature = object2.predict(object.temps, count, avg);
*/

   float avg = object2.calculateAvg(object.difference, object.getDcount());
   object.appendNextTemp("annualTemps.txt");
   int count = object.getCount();


    cout << object2.whatYear(100.0, object.temps, object.tracker, count, avg) << endl;

  return 0;
}
