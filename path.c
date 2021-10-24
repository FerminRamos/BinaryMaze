#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

/******************************************************************************
 *Creates new path point. Records row and col where it lies on maze array. Also
 * records if point is an Inflection Point. Inflection Point is a point that
 * can move right AND down.
 *
 *Returns newly created Point on Path (type struct ListNode*)
 *****************************************************************************/
struct ListNode* setPathPoint(int row, int col, bool inflection)
{
  /*Creates Path Point*/
  struct ListNode* point = (struct ListNode*) malloc(sizeof(struct ListNode));
  point->row = row;
  point->col = col;

  point->isInflection = inflection;

  point->next = NULL;

  return point;
}

/******************************************************************************
 *Checks if point is Inflection Point. Inflection point is a point that can 
 * move right and down on maze.
 *
 *Returns true if point is an Inflection Point.
 *****************************************************************************/
bool checkInflectionPoint(int maze[rowSize][rowSize], int r, int c)
{
  /*If point can move right & down, return true.*/
  if(maze[r][c+1] == '1' && maze[r+1][c] == '1')
    return true;
  else
    return false;
}


/******************************************************************************
 *Delete ALL Path Points after a certain point (head) & change faulty path on 
 * maze to 0's (prevents repetition).
 *
 *Returns nothing
 *****************************************************************************/
void clearFaultyPath(int (*maze)[rowSize], struct ListNode* head)
{
  struct ListNode* currentPoint;
  struct ListNode* faultyNode;
  currentPoint = head->next;

  while(currentPoint != NULL)
  {
    /*Grabs faulty point*/
    faultyNode = currentPoint;
    currentPoint = currentPoint->next;

    /*Change point on maze to 0's (prevents repetition)*/
    maze[faultyNode->row][faultyNode->col] = 0;

    /*Frees faulty path point*/
    free(faultyNode);
  }
}

/******************************************************************************
 *Checks if point can move right and/or down. Useful for checking if return
 * for backtrack() function is not a dead point.
 *
 *Returns true if point can move right OR down. 
 *****************************************************************************/
bool canMove(int maze[rowSize][rowSize], int row, int col)
{
  if(maze[row+1][col] == '1' || maze[row][col+1] == '1')
    return true;
  return false;
}


/******************************************************************************
 *backtrack() function is responsible for grabbing the last inflection point
 * in path. Then change this inflection point to "non-inflection" status. 
 * This is because since points on path lead to a deadend, we need to restart 
 * our path on Inflection Point, meaning that our Inflection Point will no 
 * longer be an inflection point. Furthermore, If our last inflection point 
 * is NULL, we can't backtrack any further, and starting point in path 
 * (upper left point in maze) is returned. If our last inflection point isn't 
 * NULL, then we can backtrack. If we can backtrack, then call 
 * clearFaultyPath() function to clear all path points after inflection point
 * and change maze points to 0 to avoid repeating paths.
 *
 *Note, There are cases in which path backtracks all the way to the starting 
 * point (upper left point in maze), and/or function returns the starting 
 * point. There are 3 possible cases. 1. The path hit a deadend, we 
 * backtracked to the beginning, and the beginning point can still move 
 * either right or down. 2. The path hit a deadend, we backtracked to the 
 * beginning for the 2nd time (2 deadends), and the maze has NO solution.
 * 3. We ran out of inflection points, and there is NO solution. But we still
 * need to return a point. Backtrack() function accounts for all of these
 * sinarios by changing most recent inflection point (that created deadend)
 * to "non-inflection", changing faulty path on maze to 0's so we can't try to
 * access it anymore, and checking if return statement for backtrack can move
 * (i.e. sinario #2) by calling canMove() function after backtrack() return
 * statement has been returned. 
 *
 *Returns most recent Inflection Point (may include starting point) or 
 * starting point if maze has NO solution (see note description for details)
 *****************************************************************************/
struct ListNode* backtrack(int (*maze)[rowSize], struct ListNode* path)
{
  struct ListNode* currentPoint = path;
  struct ListNode* lastInflectionPoint = NULL;

  /*Iterate until last known inflection point is found*/
  while(currentPoint->next != NULL)
  {
    /*Records last inflection point on path (We'll return this value)*/
    if(currentPoint->isInflection == true)
      lastInflectionPoint = currentPoint;

    /*Grab next position*/
    currentPoint = currentPoint->next;
  }

  /*If we can backtrack, backtrack. If not, then maze has NO solution*/
  if(lastInflectionPoint != NULL)
  {
    /*Since path was faulty, change inflection point status to non-inflection*/
    lastInflectionPoint->isInflection = false;

    /*Clears faulty path points + changes path on maze to 0's*/
    clearFaultyPath(maze, lastInflectionPoint);

    /*This wil allow us to restart our path from here*/
    return lastInflectionPoint;
  }
  else
  {
    /*Change point status to non-inflection*/
    path->isInflection = false;

    /*Clears faulty path points + changes path on maze to 0's*/
    clearFaultyPath(maze, path);

    /*Backtracking not possible, return starting point (see description)*/
    return path;
  }
}

/******************************************************************************
 *Prints the Maze. Is called when solution was found.
 *
 *Returns nothing
 *****************************************************************************/
void printMaze(int maze[rowSize][rowSize], struct ListNode* path)
{
  /*r = Maze Row * c = Maze Col*/
  int r, c;

  struct ListNode* currentPoint = path;

  /*Iterates through Maze*/
  for(r = 0; r < rowSize; r++)
  {
    for(c = 0; c < rowSize; c++)
    {
      /*If point on Mae = point on Path, print 1. Else print 0*/
      if(r == currentPoint->row && c == currentPoint->col)
      {
	printf("1");

	/*Move on to the next point on path to compare*/
	currentPoint = currentPoint->next;
      }
      else
	printf("0");
    }
    printf("\n");
  } 
}

/******************************************************************************
 *Prints Error Message. Is called when NO solution was found.
 *****************************************************************************/
void printErrorMsg()
{
  printf("no path found.\n");
}

/******************************************************************************
 *Frees Path List
 *
 *Returns nothing.
 *****************************************************************************/
void freeList(struct ListNode* head)
{
  struct ListNode* tmp;

  while(head != NULL)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }
}
