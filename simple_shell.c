
#include <unistd.h> //API for Unix System Calls
#include <stdio.h> //standard input/output
#include <wait.h> //use wait() system call
#include <stdlib.h>
#include <string.h> //strtok(), strcmp(), strcat()
int main(){


char com[40];//store command
char path[256];//store path to the command
char* p;//pointer to system path
char *paths[20];//store the path information. 2D array of Paths
char* temp;//store one path temp
int cnt = 0;//store count of paths (# of paths)

char* args[15];//pointer to list of arguments (2d-array)
int argCnt;//count of all arguments
/*stdlib function searches for environment string pointed to by name we passed in the list of environment variables assiociated w/ current process.
*returns a pointer to the C string that contains the value of that environment variable (if found)*/
p = strdup(getenv("PATH"));
printf("\nThe path information is : %s", p);//we found the path, print it.
//strtok() = string token(), splits the string by the delimiter (or delimiters if its a multi-character string i guess). returns pointer to FIRST token encountered (must be called multiple times for multiple splits)
temp = strtok(p, ":");//splits path at the : token intially
while(temp != NULL){ //loop through our system path

	paths[cnt] = temp;//give temp a spot in our paths array
	printf("\n%s\n", temp);//print the path
	cnt++;//we have a path, so up the count
	temp = strtok(NULL, ":"); //going through and  splitting at each : token for our temp
}

for(;;){//loop for allowing the user to enter a command until they quit.
	argCnt = 0;//start with no arguments
	printf("%s Myshell>> ", getenv("HOME")); //fetch home dir information.. the "%s" refers to the passed argument "getenv("HOME")" and prints as a string.
	fgets(com, 40, stdin); //read a command from keyboard (stdio version of cin. fgets(pointer to store, max size to take in, and FILE* stream))
	com[strlen(com)-1] = 0; //remove newline character
	printf("\nThe command you entered was: %s\n", com);//read back the input to user
	if(strcmp(com, "exit")==0){//if command is exit..exit
		printf("\nExiting..\n");
		exit(1); //exit with 1 passed
	}

	char* token;//token char pointer for storing beginning of each new argument
	token = strtok(com, " ");//store token of first whitespace. after whitespace we start grabbing  arguments
	while(token!=NULL){//tokenize entire string
	args[argCnt++] = token;//add our argument to the array, and up the count
	token = strtok(NULL," ");//tokenize again
	}
	args[argCnt] = NULL;//NULL terminates the argument list

	for(int j = 0; j < argCnt; j++){
	printf("args[%d]: %s\n", j, args[j]); //print each argument
	}

	if(fork() == 0) //fork() -> system call spawns a child process. Returns 0 if successful.
	{
		for(int i = 0; i < cnt; i++){ //loop through all paths
			strcpy(path, paths[i]);//copy that path at i into path
			strcat(path, "/");//maintain path syntax
			strcat(path, args[0]);//put command at end of path
			printf("\nAttempting to Execute:%s\n", path);
			execv(path, args);//loads the binary file of the command we wish to execute to the child process
					//after execution the child will be terminated
		}
		printf("\n%s is not found!\n", args[0]);
		exit(1);
	}
	else{//parent process waits for child process termination
	wait(NULL);
	}
}
return 0;
}
