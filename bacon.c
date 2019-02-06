#include <stdio.h>
#include <string.h>
#include "graphTools.h"
#include <stdlib.h>

int status;
extern struct Actor *hdActor;
extern struct Movie *hdMovie;



int main(int argc, char* argv[]){
	int checkL = 0;
	FILE *fp = NULL;
	int i;
	char *buff = NULL;
	size_t len = 0; 
	char movieCheck[7];
	char *ptr = NULL;
	char *movieName = NULL;
	char *actorName = NULL;
	


	status = 0;

	//check to make sure there are enough arguments input into program
	if(argc < 2){
		fprintf(stderr, "Not enough arguments\n");
		return 1;
	}

	//checks the inputs to make sure it is just 1 file and as many -l as the user wants to input
	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-l") == 0){
			checkL = 1;
		}
		else if(fp == NULL){
			fp = fopen(argv[i], "r");
			if(fp == NULL){
				fprintf(stderr, "Invalid file\n");
				return 1;
			}
		}
		else{
			fprintf(stderr, "Too many files\n");
			return 1;
		}
	}

	//if no file was input fatal error
	if(fp == NULL){
		fprintf(stderr, "No file input\n");
		return 1;
	}

	//scan through ea line of file and call to parseFile
	while (getline(&buff, &len, fp) != EOF){
		for(i = 0; i < strlen(buff); i++){
			if(buff[i] == '\n'){
				buff[i] = '\0';
			}

		}
		sscanf(buff, "%6s", movieCheck);
		if(strcmp(movieCheck, "Movie:") == 0){
			ptr = buff;
			ptr = ptr + 7;
			movieName = strdup(ptr);
			addMovie(movieName);
		}
		else{
			actorName = strdup(buff);
			addActor(actorName, movieName);
		}


	}

	free(movieName);
	free(actorName);
	


	setScore();



	while(getline(&buff, &len, stdin) > 0){
		for(i = 0; i < strlen(buff); i++){
			if(buff[i] == '\n'){
				buff[i] = '\0';
			}
		}
		printScore(checkL, buff);
	}

	free(buff);
	fclose(fp);
	freeMem();

	return status;
}