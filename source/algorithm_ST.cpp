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
	int get_index(Board tboard, int num, Player my, Player op, char mycolor, char opcolor);

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	cout << RED << " " << BLUE << endl;
	Save *save;
	Save *save2;
	Board tboard;

	static char mycolor = player.get_color();
	static char opcolor;
	int i, j, num;
	int s1, s2;
	char temp_color;
	int positive, negative, rank, brank = -40;
	int better = 0;
	int stop = 0;
	tboard = board;

	if (mycolor == 'b') {
		opcolor = 'r';
	}
	else {
		opcolor = 'b';
	}
	Player my(mycolor), op(opcolor);
	cout << "important find" << endl;
	save = find(tboard, mycolor);
	save2 = find(tboard, opcolor);
	cout<< "result of save" << endl;
	for (i = 0; i < 5; i++) {
		cout << save[i].index0 << " " << save[i].index1 << endl;
	}	
	cout << "result of save2" << endl;
	for (i = 0; i < 5; i++) {
		cout << save2[i].index0 << " " << save2[i].index1 << endl;
	}	
	cout << "into algorithm A" << endl;
	for (s1 = 0; s1 < 5; s1++) {
		cout << s1 << "'s index try" << endl;
		for (s2 = 0; s2 < 5; s2++) {
			cout << num << "'s next step" << endl;
			tboard.place_orb(save[s1].index0, save[s1].index1, &my);
	//		cout << "my" << save[0].index0 << " " << save[i].index1 << endl;
			tboard.place_orb(save2[s2].index0, save2[s2].index1, &op);
	//		cout << "op" << save2[0].index0 << " " << save2[0].index1 << endl;
			if (tboard.win_the_game(my) || tboard.win_the_game(op))	stop = 1;
			else rank = get_index(tboard, 5, my, op, mycolor, opcolor);
			if (rank >= brank) {
				index[0] = save[s1].index0;
				index[1] = save[s1].index1;
			}
		}
	}
	cout << "out main loop " << endl;
	return ;
}
	
int get_index(Board tboard, int num, Player my, Player op, char mycolor, char opcolor) {
		static int rank = -40;
		int s1, s2, i, j;
		int positive = 0, negative = 0;
		Save *save, *save2;
		int stop = 0;
		char temp_color;

		cout << num << ": " <<"get find" << endl;
		save = find(tboard, mycolor);
		save2 = find(tboard, opcolor);
		for (s1 = 0; s1 < 5; s1++) {
			cout << s1 << "'s index try" << endl;
			for (s2 = 0; s2 < 5; s2++) {
				for (; num > 0 && !stop;) {
				cout << num << "'s next step" << endl;
				tboard.place_orb(save[s1].index0, save[s1].index1, &my);
	//			cout << "my" << save[0].index0 << " " << save[i].index1 << endl;
				tboard.place_orb(save2[s2].index0, save2[s2].index1, &op);
	//			cout << "op" << save2[0].index0 << " " << save2[0].index1 << endl;
				if (tboard.win_the_game(my) || tboard.win_the_game(op))	stop = 1;
				else get_index(tboard, --num, my, op, mycolor, opcolor);
				}
				if (stop) 	rank = 100; // best 
				for (i = 0; i < 4; i++) {
					for (j = 0; j < 5; j++) {
						temp_color = tboard.get_cell_color(i, j);
						if (temp_color == mycolor) positive++;
						else if (temp_color == opcolor) negative++;
					}
				}
			cout << "small loop done" << rank << endl;
			rank = positive - negative;
			}
		}
		return rank;	
}
Save *find(Board board, char mycolor) {
		int priority = 100;
		int i, j, k, l;
		Save *save;
		int Index[2];
		int unchanged = 1;
		mycell temp[5][6];

	save = new Save[5];		
//	cout << "consturct temp" << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			temp[i][j].orbs_num = board.get_orbs_num(i, j);
			temp[i][j].capacity = board.get_capacity(i, j);
			temp[i][j].color = board.get_cell_color(i, j);
			temp[i][j].danger = 0; //false
		}
	}
//	cout << "temp done" << endl;
	for (i = 0; i < 5; i++) {
		save[i].priority = 16;
	}
//	cout << "1st consider " << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
//			cout << "check next cell" << endl;
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
//		cout << "set save arrary 1 " << endl;
		for (k = 0; k < 5 && unchanged; k++) {
//			cout << save[k].priority << " " << priority << endl;
			if (save[k].priority > priority) {
				for (l = 5; l - 1 < k; l--) {
					save[l].index0 = save[l - 1].index0;
					save[l].index1 = save[l - 1].index1;
					save[l].priority = save[l - 1].priority;
				}
//				save[k].index0 = Index[0];
//				save[k].index1 = Index[1];
				save[k].index0 = i;
				save[k].index1 = j;
				save[k].priority = priority;
				unchanged = 0;
			}
			else;
//			cout << "k :" << k << endl;
		}	
//		for (l = 0; l < 5; l++) {
//			cout << "l: " << l << " ";
//			cout << save[l].index0 << " " << save[l].index1 << " " << save[l].priority << endl;
//		}	
		unchanged = 1;
		priority = 16;
		}
	}
//	priority = 100;
/*	cout << " 2nd consider " << endl;
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
					for (l = 5; l - 1 < k; l--) {
						save[l].index0 = save[l - 1].index0;
						save[l].index1 = save[l - 1].index1;
						save[l].priority = save[l - 1].priority;
					}
					save[k].index0 = Index[0];
					save[k].index1 = Index[1];
					save[k].priority = priority;
					unchanged = 0;
				}
				else;
			}
			unchanged = 1;
		}
	}*/
	return save;
	}
