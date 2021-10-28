# BinaryMaze
BinaryMaze is a Depth-First search algorithm written in C. It is designed to find a 
solution to a maze as quickly as possible. Maze files are written with 0's and 1's. 
The table below visually summarizes the use of 0's and 1's in our maze.

| Value | Status      |
| :---: | :----:      |
| 1     | Can Move to |
| 0     | Non-Usable  |

The inputed maze may, or may not, have a solution. The only requirements for the maze is for
it to be a complete rectangle or square, composed of only 1's and 0's, and the upper-left 
number to be a 1, as this will act as our "spawn" point. The algorithm is designed to 
handle mazes without solutions and deadends, as long as the maze is in the correct form. 
Maze formats summarized in the chart below.

| Maze Type        | Status  | Reason |
| :-----:          | :----:  | :----: |
| 11110 <br> 00111 | Valid   | Only Contains 1's & 0's, is a rectangle, top left number is a 1 |
| 10000 <br> 00000 | Valid   | Only Contains 1's & 0's, is a rectangle, top left number is a 1 |
| 00000 <br> 00000 | Invalid | Upper-left number (spawn) is not a 1                            |
| 1000  <br> 00000 | Invalid | Is not a complete square or rectangle                           |
| 12030 <br> 00010 | Invalid | Should only contain 1's or 0's                                  |


## Features
1. Speed - Program can hanlde maze files spanning hundreds of lines long. A large emphasis
           was placed on being able to output answers to the mazes within milliseconds. 
2. InflectionPoints - Cut down time by implementing "InflectionPoint" logic. Essentially, 
                      instead of checking each individual point when backtracking, the program
                      would jump directly back to the nearest InflectionPoint (a point that
                      can move in more than 1 direction). Saving us valuable time. 
3. Pointers - Program avoided wasting time re-arranging the maze by utilizing pointers. 
              This allowed large portions of the maze to be manipulated quickly and be assigned
              values (such as isInflection, row, column) to each point. 
