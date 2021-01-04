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


	class mycell{
		public:
			int orbs_num;
			int capacity;
			char color;
			int danger;
			int priority;
	};
	#define mINF -1000000000
	#define INF 100000000
	#define Is_fault -400000000
	#define illegal -200000000

int cont_critical(int row, int col, Board board, char color);
int getscore(Board board, Player player);
int critical(int row, int col, Board board, char color);
int minmax(int row, int col, Player my, Player op, Board board, char mycolor, char opcolor, int MAX, int depth, int a, int b, Player nowplayer);

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	Board tboard;
	Board s1board;
	static bool first_two_step = true;

	static char mycolor = player.get_color();
	static char opcolor;
	int i, j, num;
	int s1, s2;
	char temp_color;
	int a = mINF;
	int b = INF;
	int newscore;
	int score = mINF;
	char ncolor;

	if (mycolor == 'b')	opcolor = 'r';
	else opcolor = 'b';

	Player my(mycolor), op(opcolor);
	
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
				newscore = minmax(i, j, my, op, board, mycolor, opcolor, 3, 0, a, b, op);
				cout << "main : "<< newscore <<" " << score << endl;
				if (score < newscore) {
					index[0] = i;
					index[1] = j;
					score = newscore;
				}
				if (a < newscore) a = newscore;
				if (b <= a) return;
		}
	}
	cout << index[0] << " " << index[1] << endl;
}

int minmax(int row, int col, Player my, Player op, Board board, char mycolor, char opcolor, int MAX, int depth, int a, int b, Player nowplayer) {
	int WIN = 100000000;
	int LOSE = -100000000;
	char nowcolor = nowplayer.get_color();
	int i, j;
	int score = mINF;
	int newscore = 0;

	if ((board.get_cell_color(row, col) != nowcolor) && (board.get_cell_color(row, col) != 'w')) 
		{
		cout << "is fault" << endl;
		return Is_fault;
		}

	if (depth == MAX) {
		cout << "minmax end : " << depth <<  endl;
		board.place_orb(row, col, &nowplayer);
		if (board.win_the_game(nowplayer))		return WIN;
		if (board.win_the_game(my))		return LOSE;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				newscore = getscore(board, nowplayer);
				if (newscore > score && !newscore)	score = newscore;
			}
		}
		return score;
	}
	if (nowcolor == mycolor) {
		cout << "minmax my : " << depth << endl;
		board.place_orb(row, col, &my);
		if (board.win_the_game(my)) 	return WIN;
		if (board.win_the_game(op)) 	return LOSE;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				if (board.get_cell_color(i, j) != opcolor) 	newscore = minmax(i, j, my, op, board, mycolor, opcolor, 3, 1 + depth, a, b, op);
				if (newscore != Is_fault) {
					if (newscore > score)	score = newscore;
				}
				if (a < newscore) a = newscore;
				if (b <= a) return score;
			}
		}
		cout << "my : " << score << endl;
		return score;
	}
	if (nowcolor == opcolor) {
		cout << "minmax op : " << depth << endl;
		board.place_orb(row, col, &op);
		if (board.win_the_game(op)) 	return WIN;
		if (board.win_the_game(my)) 	return LOSE;
		score = 2000000000;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				if (board.get_cell_color(i, j) != mycolor)	newscore = minmax(i, j, my, op, board, mycolor, opcolor, 3, 1 + depth, a, b, my);
				if (newscore != Is_fault) { 
					if(newscore < score) score = newscore;
				}
				if(b > newscore) b = newscore;
				if(b <= a) return score;
			}
		}
		cout << "op : " << score << endl;
		return score;
	}
}

int getscore(Board board, Player player) {
	char nowcolor = player.get_color();
	int i, j;
	int score = 0;
	int conti = 0;
	int num_of_crit = 0;

	for (i = 0; i < 5; i++) {
		for (j = 0; j < 6; j++) {
			if (board.get_cell_color(i, j) == nowcolor) {
				score += board.get_orbs_num(i, j);
				num_of_crit = critical(i, j, board, nowcolor);
				score += num_of_crit;
				if (num_of_crit == 0) {
					if ((i == 0 && j == 0) || (i == 4 && j == 0) || (i == 0 && j == 5) || (i == 4 && j == 5))
						score += 3;
					else if (i == 0 || i == 4 || j == 0 || j == 5) 
						score += 2;
					if ((board.get_orbs_num(i, j) + 1) == board.get_capacity(i, j)) 
						score += 2;
				}
				if ((board.get_orbs_num(i, j) + 1) == board.get_capacity(i, j)) {
					conti = cont_critical(i, j, board, nowcolor);
					score += 2 * conti;
				}
			}
		}
	}
	return score;
}

int critical(int row, int col, Board board, char color) {
	char opcolor;
	int score = 0;

	if (color == 'r') 	opcolor = 'b';
	else opcolor = 'r';

	if ((row - 1) >= 0) {
		if ((board.get_cell_color(row - 1, col) == opcolor) && (board.get_orbs_num(row - 1, col) + 1 == board.get_capacity(row - 1, col))) 
			score -= 5;
	}
	if ((col - 1) >= 0) {
		if ((board.get_cell_color(row, col - 1) == opcolor) && (board.get_orbs_num(row, col - 1) + 1 == board.get_capacity(row, col -1))) 
			score -= 5;
	}
	if ((col + 1) <= 5) {
		if ((board.get_cell_color(row, col + 1) == opcolor) && (board.get_orbs_num(row, col + 1) + 1 == board.get_capacity(row, col + 1))) 
			score -= 5;
	}
	if ((row + 1) <= 4) {
		if ((board.get_cell_color(row + 1, col) == opcolor) && (board.get_orbs_num(row + 1, col) + 1 == board.get_capacity(row + 1, col))) 
			score -= 5;
	}
	return score;
}

int cont_critical(int row, int col, Board board, char color) {
	int cont;

	if ((row - 1) >= 0) 
		if ((board.get_cell_color(row - 1, col)) == color) cont++;
	if ((col - 1) >= 0) 	
		if ((board.get_cell_color(row, col - 1)) == color) cont++;
	if ((row + 1) <= 4) 
		if ((board.get_cell_color(row + 1, col)) == color) cont++;
	if ((col + 1) <= 5)
		if ((board.get_cell_color(row, col + 1)) == color) cont++;
	return cont;
}


/*	for (i = 0; i < 5; i++) {
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
				if (temp[i][j].color == mycolor) myc = 1;
				else  opc = 1;
					temp[i - 1][j - 1].danger = 1;
					temp[i - 1][j].danger = 1;
					temp[i - 1][j + 1].danger = 1;
					temp[i][j - 1].danger = 1;
					temp[i][j + 1].danger = 1;
					temp[i + 1][j - 1].danger = 1;
					temp[i + 1][j].danger = 1;
					temp[i + 1][j + 1].danger = 1;
				
			}
			else if(temp[i][j].orbs_num == 4 && temp[i][j].capacity == 5) {
				if (temp[i][j].color == mycolor) {
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
