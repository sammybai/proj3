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
	#define Is_fault -40000000
	#define illegal -20000000
	#define WIN 10000000
	#define LOSE -10000000

int cont_critical(int row, int col, Board board, char color);
int getscore(Board board, Player player, int row, int col);
int critical(int row, int col, Board board, char color);
int minmax(int row, int col, Player my, Player op, Board board, char mycolor, char opcolor, int MAX, int depth, int a, int b, Player nowplayer);

void algorithm_A(Board board, Player player, int index[]){

    //////your algorithm design///////////
	srand(time(NULL));
	Board tboard;
	Board s1board;
	static bool first_two_step = true;

	static char mycolor = player.get_color();
	static char opcolor;
	int i, j, num;
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
				if (score < newscore && newscore != Is_fault) {
					index[0] = i;
					index[1] = j;
					score = newscore;
				if (a < newscore) a = newscore;
				if (b <= a) return;
				}
		}
	}
	cout << index[0] << " " << index[1] << endl;
}

int minmax(int row, int col, Player my, Player op, Board board, char mycolor, char opcolor, int MAX, int depth, int a, int b, Player nowplayer) {
	char nowcolor = nowplayer.get_color();
	int i, j;
	int score = illegal;
	int newscore = 0;
	

	if (depth == MAX) {
		if ((board.get_cell_color(row, col) != opcolor) && (board.get_cell_color(row, col) != 'w')) {
			return Is_fault;
		}
		else board.place_orb(row, col, &op);
		if (board.win_the_game(my))		return WIN;
		else if (board.win_the_game(op))		return LOSE;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				newscore = getscore(board, nowplayer, i, j);
				if (newscore > score)	score = newscore;
			}
		}
		return score;
	}
	if (nowcolor == mycolor) {
		if ((board.get_cell_color(row, col) != opcolor) && (board.get_cell_color(row, col) != 'w')) {
			return Is_fault;
		}
		else board.place_orb(row, col, &op);
		if (board.win_the_game(my)) 	return WIN;
		else if (board.win_the_game(op)) 	return LOSE;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				newscore = minmax(i, j, my, op, board, mycolor, opcolor, 3, 1 + depth, a, b, op);
				if (newscore > score && (newscore != Is_fault))	score = newscore;
				if (a < newscore) a = newscore;
				if (b <= a) 
					return score;
			}
		}
		return score;
	}
	if (nowcolor == opcolor) {
		if ((board.get_cell_color(row, col) != mycolor) && (board.get_cell_color(row, col) != 'w')) {
			return Is_fault;
		}
		else	board.place_orb(row, col, &my);
		if (board.win_the_game(my)) 	return WIN;
		else if (board.win_the_game(op)) 	return LOSE;
		score = 200000000;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 6; j++) {
				newscore = minmax(i, j, my, op, board, mycolor, opcolor, 3, 1 + depth, a, b, my);
				if(newscore < score && (newscore >= illegal)) score = newscore;
				if(b > newscore && (newscore >= illegal)) b = newscore;
				if(b <= a)	return score;
			}
		}
		return score;
	}
	return score;
}

int getscore(Board board, Player player, int row, int col) {
	char nowcolor = player.get_color();
	int i, j;
	int score = 0;
	int conti = 0;
	int num_of_crit = 0;
	Player red(RED);
	Player blue(BLUE);

	if (board.get_cell_color(i, j) != player.get_color() && board.get_cell_color(i, j) != 'w') return illegal;
		board.place_orb(row, col, &player);
		if (board.win_the_game(player))		score += WIN;
		if (nowcolor == 'r') {
			if (board.win_the_game(blue))	score += LOSE;
		}
		else if (nowcolor == 'b') {
			if (board.win_the_game(red))	score += LOSE;
		}
		else;
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
	int cont = 0;

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


