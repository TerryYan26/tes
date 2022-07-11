/*
 * CSE30 WI22 HW3
 * Username: cse30wi22xx (Fill in your username)
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[]) {
	char x[] = {'a','b','c','d','e','f'};

	int length;
	

	length = sizeof(x)/sizeof(x[0]);
	
	if((strcmp(argv[1],"-c")==0)&& (atoi(argv[2]) == length)){
		 
		 for(int i = 3; i<argc; i++){
			if(argv[i]>argv[3]){
				break;
			}
			printf("%c",x[atoi(argv[i])]);
		 }
		
			printf("\nNumber:%d\n" "longest%d\n",length,length);
		
	}
	else if((atoi(argv[1]) == length)){
		for(int i = 2; i<argc; i++){
			
			printf("%c",x[atoi(argv[i])]);
		 }
		
			
	}
	
	
}
