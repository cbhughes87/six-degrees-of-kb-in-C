#ifndef GRAPHTOOLS_H
#define GRAPHTOOLS_H

#define INT_MAX 2147483647

/*
linked list of actors
each actor has a name
a score
a list of movies acted in
a pointer to the actor that attached them
a pointer to the movie that placed them
*/
typedef struct Actor{
	char *name;
	int score;
	struct MovieList *movieList;
	struct Actor *actorPlaced;
	struct Movie *moviePlaced;
	struct Actor *next;
}Actor;


/*
a linked list of movies that each actor has acted in
*/
typedef struct MovieList{
	struct Movie *movie;
	struct MovieList *next;
}MovieList;


/*
linked list of all the movies
each movie has a name
a cast of actors
*/
typedef struct Movie{
	char *name;
	struct Cast *castList;
	struct Movie *next;
}Movie;

/*
a linked list of actors that each movie has in it
*/
typedef struct Cast{
	struct Actor *actor;
	struct Cast *next;
}Cast;

/*
a list to keep track of all the actors being scored
*/
typedef struct Queu{
	struct Actor *actor;
	struct Queu *next;
}Queu;


void addActor(char *aName, char *aMovie);
void addMovie(char *aName);
void addLists(struct Actor *anActor, struct Movie *aMovie);
void freeMem();
void setScore();
void printScore(int check, char *aName);


extern struct Actor *hdActor;
extern struct Movie *hdMovie;


#endif