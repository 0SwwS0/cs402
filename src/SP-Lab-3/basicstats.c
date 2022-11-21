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
#include <stdbool.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 100
#define START 20;


//---------------------- FUCTION DECLARATION -----------------------------//


// Used for sorting
void swap(float* xp, float* yp);
  
// Sort array ascending order
void selectionSortAsce(float *dtptr, int n);

// Takes in size of array that is already sorted an returns the median
float median(float *dtptr, int );

// Returns mean of an array of floats
double mean(float *dtptr, int total);

/* Returns population standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)
where the sum() goess from 1 to N, xi is the i-th element, N is 
the number of elements in the data set, and sqrt() is the square root function.  */
double stddev(float *dtptr, int size);


int main()
{
    float *dtptr, *temp;
    float number;
    int start = 20;
    char filename[FILENAME_MAX];
    char line[MAX_LINE];

    // Ask user for filename
    printf("Enter the filename: ");
    scanf("%s", filename);
    
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file. \n");
        return 1;
    }
    
    size_t increase = START;
    size_t allocated = increase;
    size_t total = 0;

    // Dynamically allocate memory on the heap
    dtptr = (float*)malloc(allocated * sizeof(float));

    while (!feof(file) && !ferror(file))
    {
        fgets(line, sizeof(line), file);
        number = strtof(line, NULL);
        dtptr[total] = number;
        total++;

        if (total >= allocated)
        {
            
            temp = (float*)malloc(allocated * sizeof(float));
            memcpy(temp, dtptr, (allocated)* sizeof(float));

            for (size_t t = 0; t < total; t++)
            {
                printf("The %zu data copied to temp is: %.2f\n", t, temp[t]);
            }
            
            free(dtptr);

            allocated += increase;

            dtptr = (float*)malloc(allocated * sizeof(float));

            memcpy(dtptr, temp, (allocated)* sizeof(float));

            free(temp);

        }
        
    }

    fclose(file);

    for (size_t i = 0; i < total; i++)
    {
        printf("Number %zu is: %.2f\n", i, dtptr[i] );
    }
    

    printf("\nResults:\n");
    printf("-----------\n");
    
    printf("Num values:\t\t%zu\n", total);
    printf("Mean\t\t\t%.3lf\n", mean(dtptr, total));
    printf("Median:\t\t\t%.3f\n", median(dtptr, total));
    printf("Stddev:\t\t\t%.3lf\n", stddev(dtptr, total));
    printf("Unsed array capacity: \t\t%lu\n", allocated - total);

    return 0;
}

void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSortAsce(float *dtptr, int n)
{
    int i, j, min_idx;

    // one by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in the unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (dtptr[j] < dtptr[min_idx])
                min_idx = j;
        // Swap the found minimum element with the first element
        swap(&dtptr[min_idx], &dtptr[i]);
    }
}


// Takes in size of array that is already sorted an returns the median
float median(float *dtptr, int size)
{
    float median = 0;
    // if number of elements are even
    if(size % 2 == 0)
    {
        median = (dtptr[(size-1)/2] + dtptr[size/2])/2.0;
    }
    // if number of elements are odd
    else
    {
        median = dtptr[size/2];
    }
    return median;
}

// Returns mean of an array of floats
double mean(float *dtptr, int size)
{
    int counter;
    float sum;
    double avg;

    sum = avg = 0;
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + dtptr[counter];
    }
   
    avg = (double)sum / size;
    return avg;
}

/* Returns population standard deviation by using the following formula: 
   stddev = sqrt((sum((xi - mean)^2))/N)
where the sum() goess from 1 to N, xi is the i-th element, N is 
the number of elements in the data set, and sqrt() is the square root function.  */
double stddev(float *dtptr, int size)
{
    int counter;
    float sum;
    double avg, stddev;

    avg = mean(dtptr, size); 
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + ((dtptr[counter] - avg) * (dtptr[counter] - avg));
    }
   
    stddev = (double) sqrt(sum / size);
    return stddev;

}

