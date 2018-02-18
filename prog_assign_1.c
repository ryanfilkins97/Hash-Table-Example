#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input_validation.h"
#include "person_hash.h"

int main(int argc, char** argv) 
{
	// Program takes no command line arguments
    if(argc > 1)
    {
        printf("Incorrect command line arguments\n");
        return 1;
    }
    
    // Create hash table and initialize values to NULL
    person *hashTable[HASH_TABLE_SIZE] = {NULL};

    // Get input and ensure that malloc() did not fail
    char *inputString = getInput();
    while(inputString == NULL)
    {
    	printf("A memory allocation error occured, please try again\n");
    	inputString = getInput();
    }

    char *delim = " \n";
    char *token = strtok(inputString, delim);
    
    while(strcmp(token, "X") != 0)
    {
        if(strcmp(token, "P") == 0)
        {
        	char *name = strtok(NULL, delim);

        	if(searchTable(hashTable, name) == NULL)
			{
				insertPersonIntoTable(hashTable, name);
			}
			else
			{
				printf("%s has already been created\n", name);
			}
        }

        if(strcmp(token, "F") == 0)
        {
        	char *name1 = strtok(NULL, delim);
        	char *name2 = strtok(NULL, delim);

        	// Make sure both people exist in table and are not friends already, than make them friends
        	if(searchTable(hashTable, name1) == NULL && searchTable(hashTable, name2) == NULL)
			{
				printf("Neither %s nor %s have been created\n", name1, name2);
			}
			else if(searchTable(hashTable, name1) == NULL)
			{
				printf("%s has not been created\n", name1);
			}
			else if(searchTable(hashTable, name2) == NULL)
			{
				printf("%s has not been created\n", name2);
			}
			else if(checkIfFriendsInTable(hashTable, name1, name2) == 1)
			{
				printf("%s and %s are already friends\n", name1, name2);
			}
			else if(strcmp(name1, name2) == 0)
			{
				printf("A person cannot be friends with themself\n");
			}
			else
			{
				linkFriendsInTable(hashTable, name1, name2);
			}
        }

        if(strcmp(token, "U") == 0)
        {
        	char *name1 = strtok(NULL, delim);
        	char *name2 = strtok(NULL, delim);

        	// Make sure both people exist in table, then make them no longer friends
        	if(searchTable(hashTable, name1) == NULL && searchTable(hashTable, name2) == NULL)
			{
				printf("Neither %s nor %s have been created\n", name1, name2);
			}
			else if(searchTable(hashTable, name1) == NULL)
			{
				printf("%s has not been created\n", name1);
			}
			else if(searchTable(hashTable, name2) == NULL)
			{
				printf("%s has not been created\n", name2);
			}
			else if(checkIfFriendsInTable(hashTable, name1, name2) == 0)
			{
				printf("%s and %s were not friends\n", name1, name2);
			}
			else
			{
				unlinkFriendsInTable(hashTable, name1, name2);
			}
        }

        if(strcmp(token, "L") == 0)
        {
        	char *name = strtok(NULL, delim);

        	// Make sure person exists in table, then list friends
        	if(searchTable(hashTable, name) != NULL)
        	{
        		listFriendsFromTable(hashTable, name);
        	}
        	else
        	{
        		printf("%s has not been created\n", name);
        	}
        }

        if(strcmp(token, "Q") == 0)
        {
        	char *name1 = strtok(NULL, delim);
        	char *name2 = strtok(NULL, delim);

        	// Make sure both people exist in table, then check if they are friends
        	if(searchTable(hashTable, name1) == NULL && searchTable(hashTable, name2) == NULL)
			{
				printf("Neither %s nor %s have been created\n", name1, name2);
			}
			else if(searchTable(hashTable, name1) == NULL)
			{
				printf("%s has not been created\n", name1);
			}
			else if(searchTable(hashTable, name2) == NULL)
			{
				printf("%s has not been created\n", name2);
			}
			else if(strcmp(name1, name2) == 0)
			{
				printf("A person cannot be friends with themself\n");
			}
			else
			{
				if(checkIfFriendsInTable(hashTable, name1, name2) == 1)
				{
					printf("%s and %s are friends\n", name1, name2 );
				}
				else
				{
					printf("%s and %s are not friends\n", name1, name2 );
				}
			}
        }

		free(inputString);

		// Get next input and ensure that malloc() did not fail
        inputString = getInput();
        while(inputString == NULL)
	    {
	    	printf("A memory allocation error occured, please try again\n");
	    	inputString = getInput();
	    }

        token = strtok(inputString, delim);
    }
    
    // Free all allocated memory
    free(inputString);
    freeTableMemory(hashTable);

    return 0;
}