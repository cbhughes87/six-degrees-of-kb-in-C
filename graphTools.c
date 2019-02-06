#include "graphTools.h"
#include <string.h>
#include <ctype.h>
#include<stdio.h>
#include<stdlib.h>

//Global variables
struct Actor *hdActor = NULL;
struct Movie *hdMovie = NULL;

extern int status;

/*
function to add actors to a list of actors
intakes a name of an actor and the movie acted in
*/
void addActor(char *aName, char *aMovie){

	struct Movie *moviePtr = hdMovie;
	while(moviePtr != NULL){
		if(strcmp(moviePtr->name, aMovie) == 0){
			break;
		}
		moviePtr = moviePtr->next;
	}	

	//initializes the hd
	if(hdActor == NULL){
		hdActor = malloc(sizeof(Actor));
		if(hdActor == NULL){
			fprintf(stderr, "Out of memory\n");
			status = 1;
			exit(1);
		}

		hdActor->name = strdup("Kevin Bacon");
		hdActor->score = 0;
		hdActor->movieList = NULL;
		hdActor->actorPlaced = NULL;
		hdActor->moviePlaced = NULL;
		hdActor->next = NULL;
	}

	

	struct Actor *actorPtr = hdActor;

	//look through list to see if actor exists or add to the end of the list
	while(actorPtr != NULL){
		if(strcmp(actorPtr->name, aName) == 0){
			addLists(actorPtr, moviePtr);
			return;

		}

		else if(actorPtr->next == NULL){
			struct Actor *newActor = malloc(sizeof(Actor));
			
			if(newActor == NULL){
				fprintf(stderr, "Out if memory\n");
				exit(1);
			}
			newActor->name = strdup(aName);
			newActor->score = INT_MAX;
			newActor->movieList = NULL;
			newActor->moviePlaced = NULL;
			newActor->actorPlaced = NULL;
			newActor->next = NULL;

			actorPtr->next = newActor;
			addLists(newActor, moviePtr);

			return;

		}


		actorPtr = actorPtr->next;
	}


}

/*
a function to create a cast list in a movie and a mocie list for an actor
*/
void addLists(struct Actor *anActor, struct Movie *aMovie){
	struct MovieList *newMovieList = malloc(sizeof(MovieList));
	struct Cast *newCast = malloc(sizeof(Cast));
	if(newCast == NULL || newMovieList == NULL){
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}

	newMovieList->movie = aMovie;
	newMovieList->next = NULL;
	newCast->actor = anActor;
	newCast->next = NULL;

	if(anActor->movieList == NULL){
		anActor->movieList = newMovieList;
	}
	else{
		struct MovieList *movieListPtr = anActor->movieList;
		while(movieListPtr->next != NULL){
			movieListPtr = movieListPtr->next;
		}
		movieListPtr->next = newMovieList;
	}

	if(aMovie->castList == NULL){
		aMovie->castList = newCast;
	}
	else{
		struct Cast *castPtr = aMovie->castList;
		while(castPtr->next != NULL){
			castPtr = castPtr->next;
		}
		castPtr->next = newCast;
	}

}

//adds a movie to a list of movies
void addMovie(char *aName){

	if(hdMovie == NULL){
		hdMovie = malloc(sizeof(Movie));
		if(hdMovie == NULL){
			fprintf(stderr, "Out of memory\n");
			exit(1);
		}
		hdMovie->name = strdup(aName);
		hdMovie->next = NULL;
		hdMovie->castList = NULL;
	}

	else{
		struct Movie *ptr = hdMovie;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}

		struct Movie *newMovie = malloc(sizeof(Movie));
		if(newMovie == NULL){
			fprintf(stderr, "Out of memory\n");
			exit(1);
		}
		newMovie->name = strdup(aName);
		newMovie->castList = NULL;
		newMovie->next = NULL;
		ptr->next = newMovie;
	
	}

}

//frees the memory
void freeMem(){
	
	struct Actor *tempAct = hdActor;
	struct MovieList *tempMovieList;

	while(tempAct != NULL){
		tempMovieList = tempAct->movieList;
		while(tempMovieList != NULL){
			tempMovieList = tempAct->movieList->next;
			free(tempAct->movieList);
			tempAct->movieList = tempMovieList;
		}
		tempAct = hdActor->next;
		free(hdActor->name);
		free(hdActor);
		hdActor = tempAct;
	}

	struct Movie *tempMovie = hdMovie;
	struct Cast *tempCast;

	while(tempMovie != NULL){
		tempCast = tempMovie->castList;
		while(tempCast != NULL){
			tempCast = tempCast->next;
			free(tempMovie->castList);
			tempMovie->castList = tempCast;
		}
		tempMovie = hdMovie->next;
		free(hdMovie->name);
		free(hdMovie);
		hdMovie = tempMovie;
	}
}


//does a breadth first search to score each actor
void setScore(){
	struct Queu *tempQ = NULL;
	struct MovieList *listPtr = NULL;
	struct Cast *castPtr = NULL;
	
	hdActor->score = 0;

	struct Queu *queu = malloc(sizeof(Queu));
	if(queu == NULL){
		fprintf(stderr, "Out of memory\n");
		exit(1);
	}

	queu->actor = hdActor;
	queu->next = NULL;

	while(queu != NULL){

		
		listPtr = queu->actor->movieList;

		while(listPtr != NULL){

			
			castPtr = listPtr->movie->castList;

			while(castPtr != NULL){

				
				if(castPtr->actor->score == INT_MAX){
					castPtr->actor->score = queu->actor->score + 1;
					castPtr->actor->actorPlaced = queu->actor;
					castPtr->actor->moviePlaced = listPtr->movie;
					
					struct Queu *newQ = malloc(sizeof(Queu));
					if(newQ == NULL){
						fprintf(stderr, "Out of memory\n");
						exit(1);
					}

					tempQ = queu;
					while(tempQ->next != NULL){
						tempQ = tempQ->next;
					}

					tempQ->next = newQ;
					newQ->actor = castPtr->actor;
					newQ->next = NULL;
				}

				castPtr = castPtr->next;
			}


			listPtr = listPtr->next;
		}



		tempQ = queu->next;
		free(queu);
		queu = tempQ;
	}


}

//print out the score of a given actor
void printScore(int check, char *aName){

	struct Actor *ptr = hdActor;

	while(ptr != NULL){
		if(strcmp(ptr->name, aName) == 0){
			if(ptr->score != INT_MAX){
				printf("Score: %d\n", ptr->score);	
				

				if(check == 1){
					while(ptr != hdActor){
						printf("%s\nwas in %s with\n", ptr->name, ptr->moviePlaced->name);
						ptr = ptr->actorPlaced;
					}
					printf("Kevin Bacon\n");
				}

				return;


			}
			else{
				printf("Score: No Bacon!\n");
				return;
			}
			
		}
		ptr = ptr->next;
	}

	printf("No actor name %s entered\n", aName);
}