#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "person_hash.h"

int hashString(char *string)
{
	int i = 0;
	double hash = 0;
	int multiplier = 1;

	// Hash string into integer, multiplier ensures that order of characters matters (hashString("ABC") != hashString("CBA"))
	for(i = 0; i < strlen(string) - 1; i++)
	{
		hash += (double) (*(string + i) * multiplier);
		multiplier++;
	}

	// Use hash and hashMultiplier to create a percentage
	double hashMultiplier = (sqrt(5) - 1) / 2;
	double indexMultiplier = (hashMultiplier * hash) - floor((hashMultiplier * hash));

	// Multiply maximum hash table index by percentage to get index in array where string is mapped
	int index = (int) floor((HASH_TABLE_SIZE - 1) * indexMultiplier);

	return index;
}

void insertPersonIntoTable(person *hashTable[], char *name)
{
	// Create new person, ensure that malloc() did not fail
	person *newPerson = malloc(sizeof(person));
	if(newPerson == NULL)
	{
		printf("A memory allocation error occured, %s could not be added\n", name);
		return;
	}

	char *newName = malloc(sizeof(char) * (strlen(name) + 1));
	if(newName == NULL)
	{
		printf("A memory allocation error occured, %s could not be added\n", name);
		free(newPerson);
		return;
	}
	strcpy(newName, name);

	// Assign name to newPerson, initialize their friends list to NULL, then insert them into the hash table
	newPerson->name = newName;

	int i = 0;
	for(i = 0; i < MAX_NUM_FRIENDS; i++)
	{
		newPerson->friends[i] = NULL;
	}

	newPerson->next = hashTable[hashString(name)];

	hashTable[hashString(name)] = newPerson;

	return;
}

person* searchTable(person *hashTable[], char *name)
{
	person *current = NULL;

	current = hashTable[hashString(name)];

	// Search the linked list located at hashTable[hashString(name)]
	while(current != NULL)
	{
		if(strcmp(current->name, name) == 0)
		{
			return current;
		}

		current = current->next;
	}

	// Return NULL if person is not found in the table
	return NULL;
}

void linkFriendsInTable(person *hashTable[], char *name1, char *name2)
{
	int i = 0;
	int person1SpaceFlag = 0;
	int person2SpaceFlag = 0;
	person *person1 = searchTable(hashTable, name1);
	person *person2 = searchTable(hashTable, name2);

	// Make sure neither person already has a full friends list, then make them friends
	for(i = 0; i < MAX_NUM_FRIENDS; i++)
	{
		if(person1->friends[i] == NULL)
		{
			person1SpaceFlag = 1;
		}

		if(person2->friends[i] == NULL)
		{
			person2SpaceFlag = 1;
		}
	}

	if(person1SpaceFlag == 0 && person2SpaceFlag == 0)
	{
		printf("%s and %s already have the maximum number of friends\n", name1, name2);
		return;
	}
	else if(person1SpaceFlag == 0)
	{
		printf("%s already has the maximum number of friends\n", name1);
		return;
	}
	else if(person2SpaceFlag == 0)
	{
		printf("%s already has the maximum number of friends\n", name2);
		return;
	}
	else
	{
		for(i = 0; i < MAX_NUM_FRIENDS; i++)
		{
			if(person1->friends[i] == NULL)
			{
				person1->friends[i] = person2;
				break;
			}
		}

		for(i = 0; i < MAX_NUM_FRIENDS; i++)
		{
			if(person2->friends[i] == NULL)
			{
				person2->friends[i] = person1;
				break;
			}
		}
	}
}

void unlinkFriendsInTable(person *hashTable[], char *name1, char *name2)
{
	// Delete both people from each others friends list
	int i = 0;
	person *person1 = searchTable(hashTable, name1);
	person *person2 = searchTable(hashTable, name2);

	for(i = 0; i < MAX_NUM_FRIENDS; i++)
	{
		if(person1->friends[i] == person2)
		{
			person1->friends[i] = NULL;
		}

		if(person2->friends[i] == person1)
		{
			person2->friends[i] = NULL;
		}
	}

	return;
}

int checkIfFriendsInTable(person *hashTable[], char *name1, char *name2)
{
	// Determine if person2 exists in person1's friends list
	int i = 0;
	person *person1 = searchTable(hashTable, name1);
	person *person2 = searchTable(hashTable, name2);

	for(i = 0; i < MAX_NUM_FRIENDS; i++)
	{
		if(person1->friends[i] != NULL)
		{
			if(person1->friends[i] == person2)
			{
				return 1;
			}
		}
	}

	return 0;
}

void listFriendsFromTable(person *hashTable[], char *name)
{
	person *person = searchTable(hashTable, name);
	printf("%s's friends:\n", name);

	// Print list of person's friends
    int i = 0;
    int noFriendsFlag = 1;

    for(i = 0; i < MAX_NUM_FRIENDS; i++)
    {
    	if(person->friends[i] != NULL)
        {
        	if(person->friends[i]->name != NULL)
        	{
        		printf("%s\n", person->friends[i]->name);
        		noFriendsFlag = 0;
        	}
        }
    }

    // If friends list was empty, print that person does not have any friends yet
    if(noFriendsFlag == 1)
    {
        printf("%s does not have any friends yet\n", name);
    }
}

void freeTableMemory(person *hashTable[])
{
	// Free all alocated memory from hash table
	int i = 0;
	person *current = NULL;
	person *next = NULL;

	for(i = 0; i < HASH_TABLE_SIZE; i++)
	{
		current = hashTable[i];

		while(current != NULL)
		{
			next = current->next;
			freePersonMemory(current);
			current = next;
		}
	}
}

void freePersonMemory(person *person)
{
	// Free all allocated memory for person
	free(person->name);
	free(person);
}