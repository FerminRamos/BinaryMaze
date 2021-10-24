/******************************************************************************
 *Fermin Ramos
 *This program grabs a maze from a file and finds a path from top-left corner
 * to bottom-right corner of the maze. Assumes the maze is a square and both
 * top-left and bottom-right corners are both 1. All other points inside the
 * maze may be either 1's or 0's. 1's are possible path points. The program
 * first checks if we can move right. If it can't, then it checks if we can
 * move down. Again, if it can't then it backtracks to the most recent 
 * Inflection Point (a point that can move BOTH right and down), and restart
 * our search from there. If no solution is found, then print an error message.
 * However, if solution is found, then print the maze with only the correct
 * path showing. 
 * 
 * This program is part of a 3 file system: main.c, path.c, and header.h
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "header.h"

/*Global Variables*/
int rowSize;

int main()
{
  /*Pointer for 1st line, of unknown size, later moved to array (for speed)*/
  int *tempRow = (int *) malloc(sizeof(int));
        
  /*Reads 1st Line of File ONLY*/
  int c;
  while((c = getchar()) != '\n')
  {
    /*Copy int to tempRow*/
    *(tempRow + rowSize) = c;
    rowSize++;
    
    /*Allocates more memory for 1st line*/
    tempRow = realloc(tempRow, sizeof(int) * (rowSize+1));
  }
  

  
  /*Allocate Maze Array & Move 1st Row Data into new Array*/
  int maze[rowSize][rowSize];
  int i;
  for(i = 0; i < rowSize; i++)
    maze[0][i] = *(tempRow + i);

  /*Free TempRow*/
  free(tempRow);
  
  /*Grab remaining input (add 2nd+ row), we already grabbed 1st row input*/
  int row = i;
  int col = i;
  for(row = 1; row < rowSize; row++)
  {
    for(col = 0; col < rowSize; col++)
    {
      /*Grab Character from input*/
      c = getchar();
      
      /*Add to Maze*/
      maze[row][col] = c;
    }
    /*Grabs newline, but doesn't assign (skips)*/
    c = getchar();
  }
  

  
  /*Path starts on top-left point on maze*/
  bool inflection;
  bool solved = false;
  
  struct ListNode* head = NULL;
  struct ListNode* newNode = NULL;
  
  inflection = checkInflectionPoint(maze, 0, 0);
  head = setPathPoint(0, 0, inflection);

  
  /*Keeps track of where we are in the maze array*/
  struct ListNode* currentNode = head;
  char status;
  int r;
  r = c = 0;
  
  /*Main Loop. Loops until end is reached or no solution*/
  while(!solved)
  {
    /*Checks if point moved(m) right/down or is deadend (x)*/
    status = 'x';
    
    /*Checks if we can move right or down*/
    if((maze[r][c+1] == '1' || maze[r+1][c] == '1') && r < rowSize &&
                                                       c < rowSize)
    { 
      /*Moves either right or down*/
      status = 'm';
      if(maze[r][c+1] == '1')
	c++;
      else
	r++;

            
      /*Checks if point can move in 2 directions (Inflection Point)*/
      inflection = checkInflectionPoint(maze, r, c);
      
      /*Insert to Path*/
      newNode = setPathPoint(r, c, inflection);
      currentNode->next = newNode;
      currentNode = newNode;
      
    }

    /*If point is deadend (can't move right or down) -> backtrack*/
    if(status == 'x')
    {      
      /*Returns to most recent inflection point and erases faulty path*/
      struct ListNode* inflectionPoint = backtrack(maze, head);
      
      /*Checks if returned point isn't dead (see backtrack() description)*/
      if(canMove(maze, inflectionPoint->row, inflectionPoint->col))
      {
	/*If Inflection point can still move,  grab new positions*/
	r = inflectionPoint->row;
	c = inflectionPoint->col;

	/*Restart path on inflection point*/
	currentNode = inflectionPoint;
      }
      else
      {
	/*Prints Error Message (No Solution)*/
	printErrorMsg();

	/*Stop Program*/
	solved = true;
      }
      
    }
    
    /*SOLVED! (If bottom right point is reached in maze)*/
    if(r == rowSize-1 && c == rowSize-1)
    {
      /*Stop Program*/
      solved = true;

      /*Print Maze Solution*/
      printMaze(maze, head);

      /*Free List*/
      freeList(head);
    }
  }
  
  
  return 0;
}
