/* 
This program demos a couple of basic statistic calcuations such as mean, median and standard deviation. 
It reads in the data from a text file and create a database. And use malloc to dynamically allocatte 
process memories on the heap. When the allocated capacity is running out, we allocate a new space that is twice the size as the current one first
then free the old one. We do this recursively for any size of data that needs to be processed.

Donglei Lin
cs402-2022Fall-session2
11/17/2022
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//---------------------- PROTOTYPE FUCTIONS -----------------------------//

// The below function loads in the data from the data file and creates the DB
float * CreateDB(char* datafile, int* xp, int* yp);

// The below function is used to print out the statistical results of the data        
void PrintDB (float arr[], int size, int total_size);

// Used for sorting
void Swap(float* xp, float* yp);
  
// Function to perform Selection Sort on Employee ID in ascending order
void SelectionSort(float arr[], int n);

// Takes in size of array that is already sorted an returns the median
float median(float arr[], int size);

// Returns mean of an array of floats
double mean(float arr[], int size);

/* Returns population standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)
where the sum() goess from 1 to N, xi is the i-th element, N is 
the number of elements in the data set, and sqrt() is the square root function.  */
double stddev(float arr[], int size);


//------------------------------ Main -----------------------------------//
/* Main function that displays the DB actions menu to the user until they choose to close out of the program. */
int main(int argc, char *argv[])
{
    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {

    }

    return 0;
}