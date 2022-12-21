// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"
PathNode * Node_construct (char * val);
PathNode * List_insert (PathNode * head, char* val);
int calcTurns(char *path);

/** INTERFACE FUNCTIONS **/

PathLL * buildPaths() {
	PathLL * retval = malloc(sizeof(PathLL));
	retval->head = NULL;
	return retval;
}

// Read the comments in list.h 
// to understand what you need to implement
// for each function

void freePaths(PathLL * p) {
	//fill in
	//PathNode * temp = NULL;
	
	while (p->head != NULL){
		PathNode * ptr = (p -> head)-> next;
		freeNode(p->head);
		p->head = ptr;
	}
	free(p);
}

PathNode * buildNode(char * path) {
	//fill in
	PathNode * retval = malloc(sizeof(PathNode));
	retval-> path = malloc(sizeof (char) * (strlen(path) + 1)) ;
	strcpy(retval->path,path);
	retval->next = NULL;
	return retval;
	//WARNING: don't forget to use strcpy to copy path into the
	//new node. Don't just set them equal, otherwise if the input path changes
	//the node will have the wrong path.
}

void freeNode(PathNode * p) {
	//fill in
	free(p->path);
	free(p);
}

PathNode * Node_construct (char * val)
{
  PathNode * nd = malloc ( sizeof (PathNode) );
  //nd-> path = malloc(sizeof (char) * strlen(val)) ;
  nd -> next = NULL;
  nd -> path =val;
  return nd;
}

PathNode * List_insert (PathNode * head, char* val)
{
  PathNode * ptr = Node_construct ( val );
  ptr -> next = head;
  return ptr;
}

int calcTurns(char *path)
{
    int ct = 0;
    for (int i = 0; i < strlen(path) - 1; i++)
    {
        if (path[i] != path[i + 1])
        {
            ct++;
        }
    }
    return ct;
}

bool addNode(PathLL * paths, char * path) {
	
	PathNode *curr = paths->head;
    PathNode *add = NULL;
    PathNode *before = NULL;

    int len = strlen(path);

    if (curr == NULL){
        add = buildNode(path);
        paths->head = add;
        return true;
    }

    while (curr != NULL){
        if (strlen(curr->path) > len){
            add = buildNode(path);

            if (curr == paths->head){
                add->next = curr;
                paths->head = add;
            }
            else
            {
                add->next = curr;
                before->next = add;
            }
            return true;
        }
        if (strlen(curr->path) == len){

            if (calcTurns(curr->path) > calcTurns(path)){
                add = buildNode(path);

                if (curr == paths->head){
                    add->next = curr;
                    paths->head = add;
                }

                else{
                    add->next = curr;
                    before->next = add;
                }
                return true;
            }

            else if (calcTurns(path) == calcTurns(curr->path))
            {
                if (strcmp(path, curr->path) < 0)
                {
                    add = buildNode(path);
                    if (curr == paths->head)
                    {
                        add->next = curr;
                        paths->head = add;
                    }
                    else
                    {
                        add->next = curr;
                        before->next = add;
                    }
                    return true;
                }
            }
        }
        
		if (curr->next == NULL){
            add = buildNode(path);
            add->next = NULL;
            curr->next = add;
            return true;
        }
        
		before = curr;
        curr = curr->next;
    }

    return false;
}

bool removeNode(PathLL * paths, char * path) {
	PathNode * curr = paths->head;
	while (curr != NULL){
		if (curr->path == path){
			free(curr->path);
			
			return true;
		}
		curr = curr->next;
	}

	return false;


}

bool containsNode(PathLL * paths, char * path) {
	while (paths->head != NULL){
		if (paths->head->path == path){
			return true;
		}
	}
	return false;
}

void printPaths(PathLL * paths, FILE * fptr) {
	PathNode * curr = paths->head;
	int i = 0;
	while (curr != NULL) {
		fprintf(fptr, "Path %2d: %s\n", i, curr->path);
		i++;
		curr = curr->next;
	}
}
