#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions 
 * 1. ~ 4. are listed in next block)
 * 
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 * 
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/


void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	class mycell{
		public:
			int orbs_num;
			int capacity;
			char color;
			int danger;
			int priority;
	};
	mycell temp[5][6];
	char mycolor = player.get_color(); 
	int priority = 100;
	int i, j;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			temp[i][j].orbs_num = board.get_orbs_num(i, j);
			temp[i][j].capacity = board.get_capacity(i, j);
			temp[i][j].color = board.get_cell_color(i, j);
			temp[i][j].danger = 0; //false
		}
	}
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (temp[i][j].orbs_num == 7) {
				if (temp[i][j].color == mycolor) {
					if (priority >= 1) {
						index[0] = i;
						index[1] = j;
						priority = 1;
					}
				}
				else {
					temp[i - 1][j - 1].danger = 1;
					temp[i - 1][j].danger = 1;
					temp[i - 1][j + 1].danger = 1;
					temp[i][j - 1].danger = 1;
					temp[i][j + 1].danger = 1;
					temp[i + 1][j - 1].danger = 1;
					temp[i + 1][j].danger = 1;
					temp[i + 1][j + 1].danger = 1;
				}	
			}
			else if(temp[i][j].orbs_num == 4 && temp[i][j].capacity == 5) {
				if (temp[i][j].color == mycolor) {
					if (priority >= 2) {
						index[0] = i;
						index[1] = j;
						priority = 2;
					}
				}
				else {
					if ((i - 1) >= 0 && (j-1) >= 0)	temp[i - 1][j - 1].danger = 1;
					if ((i - 1) >= 0)	temp[i - 1][j].danger = 1;
					if ((i - 1) >= 0 && (j + 1) <= 5)	temp[i - 1][j + 1].danger = 1;
					if ((j - 1) >= 0)	temp[i][j - 1].danger = 1;
					if ((j + 1) <= 5)	temp[i][j + 1].danger = 1;
					if ((i + 1) <= 4 && (j - 1) >= 0)	temp[i + 1][j - 1].danger = 1;
					if ((i + 1) <= 4)	temp[i + 1][j].danger = 1;
				}
			}
			else if(temp[i][j].orbs_num == 2 && temp[i][j].capacity == 3) {
				if (temp[i][j].color == mycolor) {
					if (priority >= 3) {
						index[0] = i;
						index[1] = j;
						priority = 3;
					}
				}
				else {
					if ((i - 1) >= 0 && (j-1) >= 0)	temp[i - 1][j - 1].danger = 1;
					if ((i - 1) >= 0)	temp[i - 1][j].danger = 1;
					if ((i - 1) >= 0 && (j + 1) <= 5)	temp[i - 1][j + 1].danger = 1;
					if ((j - 1) >= 0)	temp[i][j - 1].danger = 1;
					if ((j + 1) <= 5)	temp[i][j + 1].danger = 1;
					if ((j - 1) >= 0)	temp[i + 1][j - 1].danger = 1;
					if ((i + 1) <= 4)	temp[i + 1][j].danger = 1;
				}
			}
			else if (temp[i][j].orbs_num == 6 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 4) {
					index[0] = i;
					index[1] = j;
					priority = 4;
				}
			}
			else if (temp[i][j].orbs_num == 5 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 5) {
					index[0] = i;
					index[1] = j;
					priority = 5;
				}
			}
			else if (temp[i][j].orbs_num == 4 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 6) {
					index[0] = i;
					index[1] = j;
					priority = 6;
				}
			}
			else if (temp[i][j].orbs_num == 3 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 7) {
					index[0] = i;
					index[1] = j;
					priority = 7;
				}
			}
			else if (temp[i][j].orbs_num == 2 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 8) {
					index[0] = i;
					index[1] = j;
					priority = 8;
				}
			}
			else if (temp[i][j].orbs_num == 1 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 9) {
					index[0] = i;
					index[1] = j;
					priority = 9;
				}
			}
			else if (temp[i][j].orbs_num == 0) {
				if (priority >= 10) {
					index[0] = i;
					index[1] = j;
					priority = 10;
				}
			}
			else;
		}
	}
	//priority = 100;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if(temp[i][j].color == mycolor) {
			if (temp[i][j].orbs_num == 7 && temp[i][j].capacity == 8 && temp[i][j].danger == 1)	{
				index[0] = i;
				index[1] = j;
				priority = 1;
			}
			else if (temp[i][j].orbs_num == 4 && temp[i][j].capacity == 5 && temp[i][j].danger == 1 && (priority >= 2))	{
				index[0] = i;
				index[1] = j;
				priority = 2;
			}
			else if (temp[i][j].orbs_num == 2 && temp[i][j].capacity == 3 && temp[i][j].danger == 1 && (priority >= 3))	{
				index[0] = i;
				index[1] = j;
				priority = 3;
			}
			else ;
			}
		}
	}

				

}
