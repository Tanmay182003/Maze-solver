// ***
// *** You MUST modify this file
// ***

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

void printlist(PathNode* head) { 
PathNode* temp = head; 
if (temp != NULL)

		{
    		printf("%s\n", temp-> path);
    		temp = temp -> next;
		}
}

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
	//path[step] = '\0';
    if(atEnd(curpos,m)){
		if (successPaths->head != NULL) {
		//printf("path1: %s\n", successPaths->head->path);
		}
		path[step] = '\0';
		addNode(successPaths, path);
		//printf("path: %s\n", successPaths->head->path);
		//printlist(successPaths->head);
		return;
	}
	if(!squareOK(curpos, m)){
		return;
	}
	m->maze[curpos.ypos][curpos.xpos].visited = true;
	
	char direction[4] = {NORTH, SOUTH, EAST, WEST};
	MazePos steps[4] = {
		{.xpos = curpos.xpos, .ypos = curpos.ypos - 1}, //NORTH
		{.xpos = curpos.xpos, .ypos = curpos.ypos + 1}, //SOUTH
		{.xpos = curpos.xpos + 1, .ypos = curpos.ypos}, //EAST
		{.xpos = curpos.xpos - 1, .ypos = curpos.ypos}  //WEST
	};
	
	for (int i = 0; i < 4; i++) {
		//Try to make a move and see if it's successful
		path[step] = direction[i];
		(depthFirstSolve(m, steps[i], path, step + 1 ,successPaths));
			//If successful, record this step in the path
	}

	m->maze[curpos.ypos][curpos.xpos].visited = false;
	return;

}