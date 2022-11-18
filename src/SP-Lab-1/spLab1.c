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
typedef struct database dbstruct;

struct myData
{
    int size;
    dbstruct *ptr;
};
typedef struct myData Data;

Data getInputData();

void printData(dbstruct *ptr, int size);

void lookupByID(dbstruct *ptr, int size);

void lookupByLastName(dbstruct *ptr, int size);

Data addNewEmployee(dbstruct *ptr, int size);

void Swap(dbstruct *a, dbstruct*b);

void SortByID(dbstruct *ptr, int size);

void SortBySalary(dbstruct *ptr, int size);

Data removeEmployee(dbstruct *ptr, int size);

Data updateEmployee(dbstruct *ptr, int size);

void printTopEmployeesbySalary(dbstruct *ptr, int size, int top);

void employeeWithSameLastName(dbstruct *ptr, int size);


int main()
{
    int choice;
    int row;
    int top;
    dbstruct *p;
    Data data;


    // get data from database
    data = getInputData();

    bool done;
    do
    {
        printf( "Employee DB Menu -- Choose an option from below to perform: \n" );
        printf( "1. Print the Database\n" );
        printf( "2. Lookup employee by ID\n" );
        printf( "3. Lookup employee by last name\n" );
        printf( "4. Add an employee\n" );
        printf( "5. Done and Exit\n" );
        printf( "6. Remove an employee\n");
        printf( "7. Update an employee's information\n");
        printf( "8. Print employee infomation with the highest M salaries\n");
        printf( "9. Find all employees with matching last name\n");
        printf( "Enter your choice: \n" );
        scanf( "%d", &choice);

        switch ( choice ) {
        case 1:            
            printData(data.ptr, data.size);
            break;
        case 2:          
            lookupByID(data.ptr, data.size);
            break;
        case 3:         
            lookupByLastName(data.ptr, data.size);
            break;
        case 4:        
            data = addNewEmployee(data.ptr, data.size);
            break;
        case 5:
            // exit and free memory
            done = T;
            printf("goodbye!\n");
            free(data.ptr);
            break;
        default:            
            printf( "Bad input, please try again...\n" );
            break;
        case 6:
            data = removeEmployee(data.ptr, data.size);
            break;
        case 7:
            data = updateEmployee(data.ptr, data.size);
            break;
        case 8:
            printf("How many employee records do you want to show?\n");
            scanf("%d", &top);
            printTopEmployeesbySalary(data.ptr, data.size, top);
            break;
        case 9:
            employeeWithSameLastName(data.ptr, data.size);
            break;
        }
    } while (!done);
    
    return 0;
}

Data getInputData()
{
     struct database *ptr;
     Data dt;

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
    
    while (!feof(input))
    {
        // printf("%s\n", line);
        sscanf( line, "%d %s %s %f", &(ptr+i)->id, (ptr+i)->fname, (ptr+i)->lname, &(ptr+i)->salary );
        // printf( "%d %s %s %f\n", (ptr+i)->id, (ptr+i)->fname, (ptr+i)->lname, (ptr+i)->salary );
        fgets( line, sizeof(line), input);
        i++;
    }

    if ((i+1) < MINROW)
    {
        ptr = realloc(ptr, (i+1) * sizeof(struct database));
    }
    
    fclose(input);

    SortByID(ptr, i);

    dt.size = i;
    dt.ptr = ptr;

    return dt;
};

void Swap(dbstruct *a, dbstruct*b)
{
    dbstruct tmp = *a;
    *a = *b;
    *b = tmp;
}

void SortByID(dbstruct *ptr, int size)
{
    int i, j, min_idx;

    for ( i = 0; i > size - 1; i++)
    {
        min_idx = 1;

        for ( j = i + 1; i < size + 1; i++)
        {
            if (ptr[j].id < ptr[min_idx].id)
            {
                min_idx = j;
            }
            
        }
    Swap(&ptr[min_idx], &ptr[i]);  
    }
    
}

void SortBySalary(dbstruct *ptr, int size)
{
    int i, j, position;

    for ( i = 0; i < size -1; i++)
    {
        // set the base position to compare with, find the minimum element in unsorted array
        position = i;
        for ( j = i + 1; j < size; j++)
        {
            if (ptr[position].salary < ptr[j].salary)
            {
                position = j;
            }
             
        }
        // swap the found maximum elelment with the first element
        if (position != i)
        {
            Swap(&ptr[position], &ptr[i]); 
        }
        
    }
    
}

void printData(dbstruct *ptr, int size)
{
    printf("Employee ID\tFirst Name\tLast Name\tSalary is: \n");
    for (size_t i = 0; i < size; i++)
    {
        printf("%d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
    }
    
}

void lookupByID(dbstruct *ptr, int size)
{
    int lookupId;

    printf( "Enter the 6 digit employee id you want to lookup: ");
    scanf( "%d", &lookupId);

    for (size_t i = 0; i < size; i++)
    {
        if (ptr[i].id == lookupId)
        {
            printf("Found employee with ID %d\n", lookupId);
            printf("Employee ID\tFirst Name\tLast Name\tSalary is: \n");
            printf("%d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
            break;
        }
        else
        {
            printf("Employee with the id you entered is not found in DB.");
            break;
        }
    }
    
}

void lookupByLastName(dbstruct *ptr, int size) /* recursive loop to find all employees with the same last name */
{
    bool found = F;
    char lookupLname[MAXNAME];
    int result;

    printf("Enter the Employee's last name to lookup: ");
    scanf("%s", &lookupLname);

    for (size_t i = 0; i < size; i++)
    {
        result = strcmp(ptr[i].lname, lookupLname);
        if (result == 0)
        {
            found = T;
            printf("%d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
        } 
    }
    if (!found)
    {
        printf("Employee with the last name you entered is not found in DB.\n");
    }    
}

Data addNewEmployee(dbstruct *ptr, int size)
{
    Data dt;
    int new;

    printf("How many employee records to add? \n");
    scanf("%d", &new);

    /* create safety net to realloc space and assign to ptr only if realloc succeed */
    dbstruct *temp; 
    temp = (dbstruct*) realloc(ptr, (new + size + 1) * sizeof(dbstruct));
    if (temp != NULL) ptr = temp;
    else
    {
        printf("realloc fails.\n");
    }
     
    for (size_t i = size; i < size + new; i++)
    {
        printf( "Enter the first name of the employee: " ); 
        scanf("%s", ptr[i].fname); 
        printf( "Enter the last name of the employee: " ); 
        scanf("%s", ptr[i].lname); 
        printf( "Enter the ID for this employee: " ); 
        scanf("%d", &ptr[i].id); 
        printf( "Enter employee's salary (30000 to 150000): " ); 
        scanf("%f", &ptr[i].salary); 
    }
    
    size = size + new; /* adjust data size to include new rows */

    SortByID(ptr, size);

    dt.size = size;
    dt.ptr = ptr;

    return dt;
}

Data removeEmployee(dbstruct *ptr, int size)
{
    int confirm;
    int lookupId;
    bool found = F;
    Data dt;

    printf( "Remove an Employee.\n");
    printf( "Enter the 6 digit employee id to proceed: ");
    scanf( "%d", &lookupId);

    for (int i = 0; i < size; i++)
    {
        if (ptr[i].id == lookupId)
        {
            found = T;
            printf("Employee ID\tFirst Name\tLast Name\tSalary is: \n");
            printf("%d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
            printf("Confirm to remove employee? (Enter 1 for Yes or 0 for No)\n");
            scanf("%d", &confirm);
            if (confirm ==1)
            {
                for (int j = i; j < size; j++)
                {
                    ptr[j] = ptr[j + 1];
                }
                
            }
            else
            {
                printf("Cancelling action.\n");
            }
        
        }
    }

    if (!found) printf("No employee with the ID you provided.\n");

    size = size - 1; 
    SortByID(ptr, size);

    dt.size = size;
    dt.ptr = ptr;

    return dt;
}

Data updateEmployee(dbstruct *ptr, int size)
{
    int updateid;
    int choice;
    char nfname[MAXNAME];
    char nlname[MAXNAME];
    float nsalary;
    bool found = F;
    Data dt;

    printf( "Enter the ID for this employee: " ); 
    scanf("%d", &updateid); 
    
    for (size_t i = 0; i < size; i++)
    {
        if (ptr[i].id == updateid)
        {
            found = T;
            printf("Found employee with ID %d\n", updateid);
            printf("Employee ID\tFirst Name\tLast Name\tSalary is: \n");
            printf("%d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
            printf("Which field you want to edit?\n");
            printf("1. First Name\n2. Last Name\n3. Salary\n4. All\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch ( choice ) {
                case 1:            
                    printf("Enter the new first name: ");
                    scanf("%s", &nfname);
                    strcpy(ptr[i].fname, nfname);
                    break;
                case 2:          
                    printf("Enter the new last name: ");
                    scanf("%s", &nlname);
                    strcpy(ptr[i].lname, nlname);
                    break;
                case 3:         
                    printf("Enter the new salary number: ");
                    scanf("%d", &nsalary);
                    ptr[i].salary = nsalary;
                    break;
                case 4:        
                    printf("Enter employee's First Name, Last Name and Salary, seperated by space: \n");
                    scanf("%s %s %d", &nfname, &nlname, &nsalary);
                    strcpy(ptr[i].fname, nfname);
                    strcpy(ptr[i].lname, nlname);
                    ptr[i].salary = nsalary;
                    break;
                default:            
                    printf( "Bad input, quitting!\n" );
                    break;
            }

            printf("\n Updated record: \n %d\t%-15s\t%-15s\t\t%.2f\n", ptr[i].id, ptr[i].fname, ptr[i].lname, ptr[i].salary);
        }
    }
    if (!found)
    {
        printf("Employee with the last name you entered is not found in DB.\n");
    }    

    dt.size = size;
    dt.ptr = ptr;

    return dt;
}

void printTopEmployeesbySalary(dbstruct *ptr, int size, int top)
{
    dbstruct *tmp = ptr;
    
    if (top > size) printf("Bad input. The number you entered must between 0 and %d. Please try again.\n", &size);
    else
    {
        
        SortBySalary(tmp, size);

        printf("Employee ID\tFirst Name\tLast Name\tSalary is: \n");
        for (size_t i = 0; i < top; i++)
        {
            printf("%d\t%-15s\t%-15s\t\t%.2f\n", tmp[i].id, tmp[i].fname, tmp[i].lname, tmp[i].salary);
        }
    }
    
}

void employeeWithSameLastName(dbstruct *ptr, int size)
{
    lookupByLastName(ptr, size);
}