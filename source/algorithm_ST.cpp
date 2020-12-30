#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

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


	class Save{
		public:
			int priority;
			int index0;
			int index1;
	};
	
	class mycell{
		public:
			int orbs_num;
			int capacity;
			char color;
			int danger;
			int priority;
	};
	Save *find(Board board, char mycolor);

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	cout << RED << " " << BLUE << endl;
	Save *save;
	Save *save2;
	Board tboard;

	char mycolor = player.get_color();
	char opcolor;
	int i, j, num;
	char temp_color;
	int positive, negative, rank, brank = -40;
	int better = 0;
	tboard = board;

	if (mycolor == 'b') {
		opcolor = 'r';
//		my = red_player;
//		op = blue_player;
	}
	else {
		opcolor = 'b';
//		my = &blue_player;
//		op = &red_player;
	}
	Player my(mycolor), op(opcolor);
	cout << "into algorithm A" << endl;
	save = find(tboard, mycolor);
	save2 = find(tboard, opcolor);
	cout << save[0].index0 << " " << save[0].index1 << endl;
	cout << "into algorithm A" << endl;
	for (i = 0; i < 5; i++) {
		cout << i << "'s index try" << endl;
		for (num = 0; num < 5; num++) {
			cout << num << "'s next step" << endl;
//			tboard.place_orb(save[i].index0, save[i].index1, &my);
			cout << "my" << save[0].index0 << " " << save[i].index1 << endl;
			tboard.place_orb(save2[0].index0, save2[1].index1, &op);
	//		cout << "op" << save2[0].index0 << " " << save2[0].index1 << endl;
			cout << "op done" << endl;
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 5; j++) {
					temp_color = board.get_cell_color(i, j);
					if (temp_color == mycolor) positive++;
					else if (temp_color == 'b') negative++;
				}
			}
		}
		cout << "loop done" << rank << endl;
		rank = positive - negative;
		if (rank > brank) better = i;
		else ;
	}
	index[0] = save[better].index0;
	index[1] = save[better].index1;
	
}
	Save *find(Board board, char mycolor) {
		int priority = 100;
		int i, j, k;
		static Save save[5];
		int Index[2];
		int unchanged = 1;
		mycell temp[5][6];
	cout << "consturct temp" << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			temp[i][j].orbs_num = board.get_orbs_num(i, j);
			temp[i][j].capacity = board.get_capacity(i, j);
			temp[i][j].color = board.get_cell_color(i, j);
			temp[i][j].danger = 0; //false
		}
	}
	cout << "temp done" << endl;
	for (i = 0; i < 5; i++) {
		save[i].priority = 16;
	}
	cout << "1st consider " << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (temp[i][j].orbs_num == 7) {
				if (temp[i][j].color == mycolor) {
					if (priority >= 1) {
						Index[0] = i;
						Index[1] = j;
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
						Index[0] = i;
						Index[1] = j;
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
						Index[0] = i;
						Index[1] = j;
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
					Index[0] = i;
					Index[1] = j;
					priority = 4;
				}
			}
			else if (temp[i][j].orbs_num == 5 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 5) {
					Index[0] = i;
					Index[1] = j;
					priority = 5;
				}
			}
			else if (temp[i][j].orbs_num == 4 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 6) {
					Index[0] = i;
					Index[1] = j;
					priority = 6;
				}
			}
			else if (temp[i][j].orbs_num == 3 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 7) {
					Index[0] = i;
					Index[1] = j;
					priority = 7;
				}
			}
			else if (temp[i][j].orbs_num == 2 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 8) {
					Index[0] = i;
					Index[1] = j;
					priority = 8;
				}
			}
			else if (temp[i][j].orbs_num == 1 && !temp[i][j].danger && temp[i][j].color == mycolor) {
				if (priority >= 9) {
					Index[0] = i;
					Index[1] = j;
					priority = 9;
				}
			}
			else if (temp[i][j].orbs_num == 0) {
				if (priority >= 10) {
					Index[0] = i;
					Index[1] = j;
					priority = 10;
				}
			}
			else;
		cout << "set save arrary 1 " << endl;
		for (k = 0; k < 5 && unchanged; k++) {
			cout << save[k].priority << " " << priority << endl;
			if (save[k].priority > priority) {
				save[k].index0 = Index[0];
				save[k].index1 = Index[1];
				save[k].priority = priority;
				unchanged = 0;
			}
			else;
		}
		unchanged = 1;
		}
	}
	//priority = 100;
	cout << " 2nd consider " << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if(temp[i][j].color == mycolor) {
			if (temp[i][j].orbs_num == 7 && temp[i][j].capacity == 8 && temp[i][j].danger == 1)	{
				Index[0] = i;
				Index[1] = j;
				priority = 1;
			}
			else if (temp[i][j].orbs_num == 4 && temp[i][j].capacity == 5 && temp[i][j].danger == 1 && (priority >= 2))	{
				Index[0] = i;
				Index[1] = j;
				priority = 2;
			}
			else if (temp[i][j].orbs_num == 2 && temp[i][j].capacity == 3 && temp[i][j].danger == 1 && (priority >= 3))	{
				Index[0] = i;
				Index[1] = j;
				priority = 3;
			}
			else ;
			}
			cout << "set save array2 " << endl;
			for (k = 0; k < 5 && unchanged; k++) {
				if (save[k].priority > priority) {
					save[k].index0 = Index[0];
					save[k].index1 = Index[1];
					save[k].priority = priority;
					unchanged = 0;
				}
				else;
			}
			unchanged = 1;
		}
	}
	return save;
	}
