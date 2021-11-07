#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdbool.h"

/*************** Board ***************/
#define ROWS 6
#define COLS 7
char board[ROWS][COLS];

/*************** Struct ***************/
 /// this struct will assign each player a symbol and a number.
struct Currentplayer {
	int PlayerNum;
	char PlayerSymbol;
}; typedef struct Currentplayer Currentplayer;

/*********** Declarations ************/

/// This function initializes the game board by assigning each cell
/// with ' ' (resulting with an empty game board).
void initBoard();

/// this function prints the board bounderies and the characters in each cell.
void printboard();

/// This function gets a row number and a column number (a cell),
/// and returns the character in that cell (could be 'X', 'O' or ' ').
/// For example:
/// char c = getCell(1, 1);
char getCell(int row, int col);

/// This function gets a row number, a column number and a sign,
/// and assigns the cell with the given sign.
/// For example:
/// setCell(1, 1, 'X');
void setCell(int row, int col, char sign);

/// This function clears the screen.
void clearScreen();

/// this function (which return struct!) changes the player num and symbol each turn.
Currentplayer ChangePlayer(Currentplayer player);

/// this function let the main know if there is a winner
bool CheckWin();

///check if there is 4 similar characters in a column.
/// it returns 'win' or 'not win' to CheckWin function
int CheckCols();

///check if there is 4 similar characters in a row.
/// it returns 'win' or 'not win' to CheckWin function
int CheckRow();

/// this function checks if there is 4 of the same character in the diagonal left to right
/// it returns 'win' or 'not win' to CheckWin function
int L2RDiagonal();

/// this function checks if there is 4 of the same character in the diagonal right to left
/// it returns 'win' or 'not win' to CheckWin function
int R2LDiagonal();

/*************** Main ****************/
void main()
{
	int col;
	int countcol[7] = { 0,0,0,0,0,0,0 };  /// an array which checks the capacity of each cell
	Currentplayer player = { 1 , 'X' };
	initBoard();


	while (countcol < 42 || CheckWin() == 0) {   /// if the array is full or there is no winner it prints the first current player turn.
		printboard();
		printf(" Player number %d \n ", player.PlayerNum);


		do {
			printf("Please enter column input (a number between 1-7):\n");
			scanf("%d", &col);

			if (countcol[col - 1] == 6) {
				printf("the column you have entered is full \n");
			}

		} while (1 > col || col > 7 || countcol[col - 1] == 6);    /// while the choosen cell isnt full countinue the game.

		setCell(ROWS - countcol[col - 1], col, player.PlayerSymbol);


		countcol[col - 1]++;  /// adds 1 to the counter of the choosen cell.
		clearScreen();

		if (CheckWin()) {
			printboard();
			printf("player number %d win! :) \n\n", player.PlayerNum, player.PlayerSymbol);
		}

		player = ChangePlayer(player);




	}

}


/********** Implementations **********/
bool CheckWin() {
	if (CheckRow() || CheckCols() || L2RDiagonal() || R2LDiagonal()) {

		return 1;
	}
	return 0;

}


int R2LDiagonal() {

	int i, j;

	for (i = ROWS; i > ROWS - 3; i--) {
		for (j = 0; j < COLS - 3; j++) {
			if (board[i][j] == 'X' || board[i][j] == 'O') {
				/// check the next three diagonal cells.
				if ((board[i][j] == board[i - 1][j + 1]) && (board[i - 1][j + 1] == board[i - 2][j + 2]) && (board[i - 2][j + 2] == board[i - 3][j + 3])) {
					return 1;
				}
			}

		}

	}

	return 0;
}

int L2RDiagonal() {

	int i, j;

	for (i = 0; i < ROWS - 3; i++) {
		for (j = 0; j < COLS - 3; j++) {
			if (board[i][j] == 'X' || board[i][j] == 'O') {
				/// check the next three diagonal cells.
				if ((board[i][j] == board[i + 1][j + 1]) && (board[i + 1][j + 1] == board[i + 2][j + 2]) && (board[i + 2][j + 2] == board[i + 3][j + 3])) {
					return 1;
				}
			}

		}

	}

	return 0;
}

int CheckCols() {

	int i, j, CountSymbol = 0;
	char CurrentSymbol = '@';   /// an arbitrary sign to the first symbol 
	for (i = 0; i < COLS; i++) {
		for (j = 0; j < ROWS; j++) {
			if (board[j][i] == 'X' || board[j][i] == 'O') { /// adds 1 to the counter
				CountSymbol++;
				if (board[j][i] != CurrentSymbol) { /// checks if there is equality between the current char and the new char if not reset the counter.
					CountSymbol = 1;
				}
				CurrentSymbol = board[j][i];
			}
			if (CountSymbol == 4)
				return 1;
		}
		CountSymbol = 0;
	}

	return 0;
}


int CheckRow() {

	int i, j, CountSymbol = 0;
	char CurrentSymbol = '@'; /// an arbitrary sign to the first symbol
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			if (board[i][j] == 'X' || board[i][j] == 'O') { /// adds 1 to the counter
				CountSymbol++;
				if (board[i][j] != CurrentSymbol) {/// checks if there is equality between the current char and the new char if not reset the counter.
					CountSymbol = 1;
				}
			}

			CurrentSymbol = board[i][j];
			if (CountSymbol == 4)
				return 1;
		}
		CountSymbol = 0;
	}

	return 0;
}

void printboard()
{
	int i, j, letter = 'A';    /// prints the top boundary of the board(number 1-8)
	printf("%c", ' ');
	for (i = 1; i < 8; i++) {
		printf("    %d", i);

	}
	printf("\n");


	for (i = 0; i < ROWS; i++) {    ///prints the left boundary of the board(A-Z) and the board itself 
		printf("%c", letter);
		letter++;
		for (j = 0; j < COLS; j++) {
			printf("    %c", board[i][j]);

		}
		printf("\n");
	}


}
Currentplayer ChangePlayer(Currentplayer player) {
	if (player.PlayerNum == 1) {
		player.PlayerNum = 2;
		player.PlayerSymbol = 'O';
	}
	else {
		player.PlayerNum = 1;
		player.PlayerSymbol = 'X';
	}

	return player;
}



char getCell(int row, int col)
{
	return board[row - 1][col - 1];
}



void setCell(int row, int col, char sign)
{
	board[row - 1][col - 1] = sign;
}

void initBoard()
{
	int i, j;
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			setCell(i + 1, j + 1, ' ');
		}
	}
}

void clearScreen()
{
	system("cls");
}
