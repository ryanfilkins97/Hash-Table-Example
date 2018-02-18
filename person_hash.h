#define HASH_TABLE_SIZE 64
#define MAX_NUM_FRIENDS 25

typedef struct Person
{
	char *name;
	struct Person *friends[MAX_NUM_FRIENDS];
	struct Person *next;
}person;

int hashString(char *string);

void insertPersonIntoTable(person *hashTable[], char *name);

person* searchTable(person *hashTable[], char *name);

void linkFriendsInTable(person *hashTable[], char *name1, char *name2);

void unlinkFriendsInTable(person *hashTable[], char *name1, char *name2);

int checkIfFriendsInTable(person *hashTable[], char *name1, char *name2);

void listFriendsFromTable(person *hashTable[], char *name);

void freeTableMemory(person *hashTable[]);

void freePersonMemory(person *person);