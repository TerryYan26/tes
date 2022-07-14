/*
 * CSE30 WI22 HW3
 * Username: cse30wi22xx (Fill in your username)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void copyString(char *copy, const char *strtocopy, size_t size)
{
   size_t index;
   for (index = 0; index < size && strtocopy[index] != '\0'; index++)
	   copy[index] = strtocopy[index];
    for ( ; index < size; index++)
	   copy[index] = '\0';
}


int main(int argc, char* argv[]) {
	/* Local Variables */
	int numLines = 0,longestChar = 0;
	int numberOfColumns = 0;
	int *listOfColumns;
	int lenOfList = 0;
	int startOfList = 2;

	/* save the other cli args */
	if(strcmp(*(argv+1),"-c") == 0)
	{
		startOfList = 3;
	}
	numberOfColumns = atoi(*(argv+startOfList-1)); //gets the number of columns
	//creates an array of strings dynamically
	char **stringArray = (char**) malloc(sizeof(char*) * numberOfColumns);
	char** line = (char**) malloc(sizeof(char*)*numberOfColumns);
	//creates the array of list of columns
	listOfColumns = (int*) malloc(sizeof(int) * (argc - startOfList));

	//loops and stores the values in the array
	for (int i = startOfList; i < argc; ++i) {
		 *(listOfColumns+lenOfList)= atoi(*(argv+i));
		 lenOfList++;
	}
	/* process the input as described in the writeup */
	size_t size = 0;

	//loops and gets line by line from std input
	while(1)
	{
		//gets the line and counts the number of chars
		size_t chars = getline(line,&size,stdin);

		//checks if its the end of std input
		if( (int) chars == -1)
			break;

		//creates some variables used for iteration
		int j = 0;
		int k = 0;
		char str[15];

		//loops and converts the sentence into array of words
		for (int i = 0; i < (int)chars; ++i) {
			if( *(*line+i) == ' ' || *(*line+i) == '\t' || *(*line+i) == '\n')
			{
				str[j] = '\0';
				//copies the word to the array at an index
				*(stringArray+k) = (char*) malloc(sizeof(char*));
				copyString(*(stringArray+k), str, strlen(str));

				//determines the longest char
				if((int)strlen(str) > longestChar)
					longestChar = strlen(str);
				k++;
				//restarts the index count
				j=0;
				str[0] = '\0'; //nullifies the string
			}
			else
			{
				str[j] = *(*line+i); //copies the character
				j++;
			}

		}
		//copies the last string
		*(stringArray+k) = (char*) malloc(sizeof(char*));
		copyString(*(stringArray+k), str, strlen(str));

		//determines the longest character
		if((int)strlen(str) > longestChar)
		longestChar = strlen(str);

		//loops and prints the results in the array according to the
		//list of indices in the list of columns
		for (int i = 0; i < lenOfList; ++i) {
			int index = listOfColumns[i];
			if(index < 0)
				index = numberOfColumns + index;
			printf("%s ",*(stringArray+index));
		}
		printf("\n");
		numLines++;
	}

	/* Format string for output to be printed when -c option is given */
	if(startOfList == 3)
		printf("Number of lines: %d\n"
		"Longest field: %d characters\n",
		numLines,longestChar);

	//frees the pointers in the array
	for (int i = 0; i < numberOfColumns; ++i) {
		free(*(stringArray+i));
	}
	//frees the pointers
	free(stringArray);
	free(listOfColumns);
}
