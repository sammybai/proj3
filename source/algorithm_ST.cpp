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
	Save *find(Board board, char mycolor, int number);
	int get_index(Board tboard, int num, Player my, Player op, char mycolor, char opcolor);

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	Save *save;
	Save *save2;
	Board tboard;
	Board s1board;
	static bool first_two_step = true;

	static char mycolor = player.get_color();
	static char opcolor;
	int i, j, num;
	int s1, s2;
	int index0, index1;
	char temp_color;
	int positive = 0, negative = 0;
	int rank = -40, trank ;
	int better = 0;
	int stop = 0;
	tboard = board;

	int round = 0;

	if (mycolor == 'b') {
		opcolor = 'r';
	}
	else {
		opcolor = 'b';
	}
	cout << rank << endl;
	Player my(mycolor), op(opcolor);
//	cout << "important find" << endl;
	save = find(board, mycolor, 5);
	cout<< "result of save" << endl;
	for (i = 0; i < 5; i++) {
		cout << save[i].index0 << " " << save[i].index1 << endl;
	}	
//	cout << "into algorithm A" << endl;
	for (s1 = 0; s1 < 5; s1++) {
		tboard = board;
		tboard.place_orb(save[s1].index0, save[s1].index1, &my);
		save2 = find(tboard, opcolor, 1);
		s1board = board;
//		for (s2 = 0; s2 < 5; s2++) {
//			tboard = s1board;
			tboard.place_orb(save2[0].index0, save2[0].index1, &op);
//			cout << "(" << s1 << ", " << s2 << ")" << endl;
			trank = get_index(tboard, 2, my, op, mycolor, opcolor);
			cout << rank << endl;
			cout << "		main rank: " << trank << " " << rank <<  endl;
			if (trank > rank) {
				rank = trank;
				index[0] = save[s1].index0;
				index[1] = save[s1].index1;
				cout << save[s1].index0 << " " << save[s1].index1 << endl;
				cout << "refresh" << index[0] << "  " << index[1]<< endl;
			}
			else;
//		}
//		cout << "out s2" <<endl;
		delete save2;
	}
	cout << "out main loop " << endl;
	delete save;
	return ;
}
	
int get_index(Board board, int num, Player my, Player op, char mycolor, char opcolor) {
		static int rank = -100000, trank;
		int s1, s2, i, j;
		double positive = 0, negative = 0;
		Save *save, *save2;
		char temp_color;
		int out = 0;
		int Num = num; 
		bool first_two_step = false;
		Board tboard;

		save = find(board, mycolor, 5);
	cout<< num << " result of save" << endl;
	for (i = 0; i < 5; i++) {
		cout << save[i].index0 << " " << save[i].index1 << " " << save[i].priority << endl;
	}	
	for (s1 = 0; s1 < 5; s1++) {
		cout << "	in s1 :" << s1 << endl;
		tboard = board;
		tboard.place_orb(save[s1].index0, save[s1].index1, &my);
		save2 = find(tboard, opcolor, 1);
//		for (s2 = 0; s2 < 5; s2++) {
		num = Num;
		cout << "num: " << num << endl;
		tboard.place_orb(save2[0].index0, save2[0].index1, &op);
		cout << "下棋 ok " << endl;
		if (tboard.win_the_game(my)) {
			cout << "I won " << num << endl;
			rank = 10000000;
		}
		else if (tboard.win_the_game(op)) {
			cout << "I lost" << endl;
			trank = -10000000;
		}
		else if (num > 0) 	{
			cout << "call other function" << endl;
			trank = get_index(tboard, num - 1, my, op, mycolor, opcolor);
		}
		else {
			cout << "calulate function" << endl;
			positive = 0;
			negative = 0;
			for (i = 0; i < 5; i++) {
				for (j = 0; j < 6; j++) {
					temp_color = tboard.get_cell_color(i, j);
					if (temp_color == mycolor) positive += tboard.get_orbs_num(i, j);
					else if (temp_color == opcolor) negative += tboard.get_orbs_num(i, j);
					else positive += 1;
				}
			}
			trank = positive - negative;
		}
		if (trank > rank) rank = trank;
		else  rank = rank;
//		}
		delete save2;
	}
	delete save;
	cout << "go to pre funciont" << rank << endl;
	return rank;	
}
/*Save *find(Board board, char mycolor, int number) {
		int priority = 100;
		int i, j, k, l;
		Save *save;
		int Index[2];
		int unchanged = 1;
		mycell temp[5][6];

	save = new Save[number];		
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
	for (i = 0; i < number; i++) {
		save[i].priority = 16;
	}
//	cout << "1st consider " << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
//			cout << "check next cell" << endl;
			if (temp[i][j].orbs_num == 7) {
				if (temp[i][j].color == mycolor) {
					if (priority >= 1) {
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
			//else if (temp[i][j].orbs_num == 6 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 6 && temp[i][j].color == mycolor) {
				if (priority >= 4) {
					priority = 4;
				}
			}
			//else if (temp[i][j].orbs_num == 5 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 5 && temp[i][j].color == mycolor) {
				if (priority >= 5) {
					priority = 5;
				}
			}
			//else if (temp[i][j].orbs_num == 4 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 4 && temp[i][j].color == mycolor) {
				if (priority >= 6) {
					priority = 6;
				}
			}
			//else if (temp[i][j].orbs_num == 3 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 3 && temp[i][j].color == mycolor) {
				if (priority >= 7) {
					priority = 7;
				}
			}
			//else if (temp[i][j].orbs_num == 2 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 2 && temp[i][j].color == mycolor) {
				if (priority >= 8) {
					priority = 8;
				}
			}
			//else if (temp[i][j].orbs_num == 1 && !temp[i][j].danger && temp[i][j].color == mycolor) {
			else if (temp[i][j].orbs_num == 1 && temp[i][j].color == mycolor) {
				if (priority >= 9) {
					priority = 9;
				}
			}
			else if (temp[i][j].orbs_num == 0) {
				if (priority >= 10) {
					priority = 10;
				}
			}
			else;
		for (k = 0; k < number && unchanged; k++) {
			if (save[k].priority >= priority) {
				for (l = number - 1; l - 1 >= k; l--) {
					save[l].index0 = save[l - 1].index0;
					save[l].index1 = save[l - 1].index1;
					save[l].priority = save[l - 1].priority;
				}
				save[k].index0 = i;
				save[k].index1 = j;
				save[k].priority = priority;
				unchanged = 0;
			}
			else;
		}
		for (k = 0; k < number; k++) {
			if (save[k].priority == 16) {
				save[k].index0 = save[0].index0;
				save[k].index1 = save[0].index1;
			}
		}
//		for (l = 0; l < 5; l++) {
//			cout << "l: " << l << " ";
//			cout << save[l].index0 << " " << save[l].index1 << " " << save[l].priority << endl;
//		}	
		unchanged = 1;
		priority = 17;
		}
	}
	priority = 100;
//	cout << " 2nd consider " << endl;
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if(temp[i][j].color == mycolor) {
				if (temp[i][j].orbs_num == 7 && temp[i][j].capacity == 8 && temp[i][j].danger == 1)	{
					priority = 1;
			}
			else if (temp[i][j].orbs_num == 4 && temp[i][j].capacity == 5 && temp[i][j].danger == 1 && (priority >= 2))	{
				priority = 2;
			}
			else if (temp[i][j].orbs_num == 2 && temp[i][j].capacity == 3 && temp[i][j].danger == 1 && (priority >= 3))	{
				priority = 3;
			}
			else ;
			}
//			cout << "set save array2 " << endl;
			for (k = 0; k < number && unchanged; k++) {
				if (save[k].priority >= priority) {
					for (l = number - 1; l - 1 >= k; l--) {
						save[l].index0 = save[l - 1].index0;
						save[l].index1 = save[l - 1].index1;
						save[l].priority = save[l - 1].priority;
					}
					save[k].index0 = i;
					save[k].index1 = j;
					save[k].priority = priority;
					unchanged = 0;
				}
				else;
			}
			unchanged = 1;
			priority = 17;
		}
	}
//	if (temp) {
//		for (i = 0; i < 5; i++) {
//			if (temp[i]) delete temp[i];
//		}
//	}
	return save;
	}*/
