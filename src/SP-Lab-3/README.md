http://cs.iit.edu/~virgil/cs402/mail.fall2022/Labs/C/lab-3/lab3.html
This program demonstrates 3 basic stat calculation functions: mean, median and standard deviation.
mean: the average of values in the set. For example, if the set is S={5, 6, 4, 2, 7}, then the average is 4.8

median: the middle value in the set of values. For the same set S the median value is 5 (2 and 4 are smaller and 6 and 7 are larger). If the set has an even number of values, then you average the two values that are left and right of center.

standard deviation: you are going to calculate the population standard deviation by using the following formula:

stddev = sqrt((sum((xi - mean)^2))/N);
where the sum() goess from 1 to N, xi is the i-th element, N is the number of elements in the data set, and sqrt() is the square root function.

Data Source:  We read in the values from 2 file: small.txt and large.txt into an array of floats, and return a pointer to the array to user *dtptr.
Memory Usage: The array of values are dynamically allocated on the heap by calling malloc(). We start out allocating an array of 20 float values:
  dtptr = (float*)malloc(allocated * sizeof(float)) where allocated is 20

When running out of capacity: 
  Call malloc to allocate space for a new array that is twice the size of the current full one.
  Copy values from the old full array to the new array (and make the new array the current one).
  Free the space allocated by the old array by calling free.
  NOTE: there are other ways to do the memory allocation/re-allocation than described above, however for this assignment you have to use the method described above.
  
 Results on small.txt:
 Results:
-----------
Num values:             14
Mean                    73.522
Median:                 175.459
Stddev:                 88.897
Unsed array capacity:           6

--------------------------------------------
 
 Results on large.txt:
 Results:
-----------
Num values:             30
Mean                    2035.600
Median:                 1742.500
Stddev:                 nan
Unsed array capacity:           10
 
