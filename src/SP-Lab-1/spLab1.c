#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXNAME 64              /* define and use constants for first name and last name */
#define MINROW 20
typedef enum { F, T } boolean;  /* Declaration of enum */ 
struct database
{
	int id;
	char fname[MAXNAME];
	char lname[MAXNAME];
	float salary;
};

struct database* readFile();

void displayDetail(struct database *ptr);

void lookupByID(struct database *ptr);

void lookupByLastName(struct database *ptr);

void addNewEmployee(struct database *ptr);

int main()
{
    int choice;
    bool done;

    struct database* data; 
    struct database* newdata;

    data = readFile();

    do
    {
        printf( "Employee DB Menu -- Choose an option from below to perform: \n" );
        printf( "1. Print the Database\n" );
        printf( "2. Lookup employee by ID\n" );
        printf( "3. Lookup employee by last name\n" );
        printf( "4. Add an employee\n" );
        printf( "5. Done and Exit\n" );
        printf( "Enter your choice: \n" );
        scanf( "%d", &choice);

        switch ( choice ) {
        case 1:            
            displayDetail(data);
            break;
        case 2:          
            lookupByID(data);
            break;
        case 3:         
            lookupByLastName(data);
            break;
        case 4:        
            addNewEmployee(data);
            break;
        case 5:
            done = T;
            printf("goodbye!\n");
            break;
        default:            
            printf( "Bad input, please try again...\n" );
            break;
        }
    } while (!done);
    
    return 0;
}

struct database* readFile()
{
    struct database *ptr;

    /* allocate the memory of at least MINROW numbers of struct database. And use the ptr pointer to access elements of database */
    ptr = (struct database*) malloc(MINROW * sizeof(struct database));                  
    
    FILE *input = fopen("small.txt", "r");
    if (input == NULL)
    {
        printf("Cannot open file. \n");
        exit(1);
    }
    
    char line[500];
    fgets(line, sizeof(line), input);

    /* Read the contents of the textfile and store in Database variable */

    int i = 0;                         /* initiate line counter */
    int count = 1;                     /* initiate row counter */
    while (!feof(input))
    {
        // printf("%s\n", line);
        sscanf( line, "%d %s %s %f", &(ptr+i)->id, &(ptr+i)->fname, &(ptr+i)->lname, &(ptr+i)->salary );
        // printf( "%d %s %s %f\n", (ptr+i)->id, (ptr+i)->fname, (ptr+i)->lname, (ptr+i)->salary );
        fgets( line, sizeof(line), input);
        i++;
        count++;
    }

    // if (count < MINROW)
    // {
    //     ptr = realloc(ptr, count * sizeof(struct database));
    // }
    
    fclose(input);

    return ptr;
}

void displayDetail(struct database *ptr)
{
    printf("Employee First Name, Last Name, ID and Salary: \n");
    int next = 0;
    while (next < MINROW && ptr[next].id != NULL)
    {
        printf("%s      %s      %d      %f\n", ptr[next].fname, ptr[next].lname, ptr[next].id, ptr[next].salary);
        next++;
    }
    
}

void lookupByID(struct database *ptr)
{
    bool notFound = T;
    int lookupId; 
    int result;
    int next;
    printf( "Please enter a 6 digit employee id: " );  /* Asks for ID number */
    scanf( "%d", &lookupId );     

    next = 0;
    while (ptr[next].id != NULL && notFound)
    {

        if (ptr[next].id == lookupId)
        {
            notFound = F;
            printf("Found employee with ID %d\n", lookupId);
            printf("Employee First Name, Last Name ID and Salary is: \n");
            printf("%s %s %d %f\n", ptr[next].fname, ptr[next].lname, ptr[next].id, ptr[next].salary);
            break;
        }
        next++;
    }

    if (notFound)
    {
        printf("Employee with the id you entered is not found in DB.");
    }
    
}

void lookupByLastName(struct database *ptr)
{
    bool notFound = T;
    int result;
    int next;
    char lookupLastName[MAXNAME];                         /* Need a variable... */
    printf( "Enter Employee's last name (no extra spaces): " );     /* Asks for ID number */
    scanf("%s", &lookupLastName);     

    next = 0;
    while (ptr[next].fname != NULL && notFound)
    {
        result = strcmp(ptr[next].lname, lookupLastName);

        if (result == 0)
        {
            notFound = F;
            printf("Found employee with Last Name %s\n", lookupLastName);
            printf("Employee First Name, Last Name, ID and Salary is: \n");
            printf("%s %s %d %f\n", ptr[next].fname, ptr[next].lname, ptr[next].id, ptr[next].salary);
            break;
        }
        next++;
    }

    if (notFound)
    {
        printf("Employee with the last name you entered is not found in DB.\n");
    }
    
}

void addNewEmployee(struct database *ptr)
{
    int next = 0;

    while (next < MINROW && ptr[next].id != NULL)
    {
        next++;
    }

    // get new employee record
    printf( "Enter the first name of the employee: " ); 
    scanf("%s", ptr[next].fname); 
    printf( "Enter the last name of the employee: " ); 
    scanf("%s", ptr[next].lname); 
    printf( "Enter employee's salary (30000 to 150000): " ); 
    scanf("%f", &ptr[next].salary); 
    printf( "Enter the ID for this employee: " ); 
    scanf("%d", &ptr[next].id); 

    printf("Display updated DB info: \n");

    for (size_t new = 0; new < next + 1; new++)
    {
        printf("%s %s %d %f\n", ptr[new].fname, ptr[new].lname, ptr[new].id, ptr[new].salary);
    }

};

