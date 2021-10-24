#ifndef HEADERFILE_H
#define HEADERFILE_H

struct ListNode
{
  int row;
  int col;

  bool isInflection;

  struct ListNode* next;
};

extern int rowSize;

struct ListNode* setPathPoint(int row, int col, bool inflection);

bool checkInflectionPoint(int maze[rowSize][rowSize], int r, int c);

void clearFaultyPath(int (*maze)[rowSize], struct ListNode* head);

bool canMove(int maze[rowSize][rowSize], int row, int col);

struct ListNode* backtrack(int (*maze)[rowSize], struct ListNode* path);

void printMaze(int maze[rowSize][rowSize], struct ListNode* path);

void printErrorMsg(void);

void freeList(struct ListNode* head);
#endif
