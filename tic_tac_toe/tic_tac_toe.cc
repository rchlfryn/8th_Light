/*
 * Rachel Fryan
 * Tic-Tac-Toe Game
 * Rule produced from: http://www.quora.com/Is-there-a-way-to-never-lose-at-Tic-Tac-Toe
 */
#include <iostream>
#include <string>

using namespace std;

void welcome();
//Function will display tic-tac-toe board
void display_board();
//Function will prompt player for move and make move
void player_turn();
//Computer's moves
void computer_AI(int &r, int &c, int m);
//Function will return true a block if needed
bool block(int &r1, int &c1);
//Function return true if win of 3 in a row is available
bool for_the_win(int &r2, int &c2);
//Function will prove true when game is over
bool game_over();
//Function will keep game going until 'Q' or 'q'
bool play_again();
//True is spot is empty, false if taken
bool check_spot(int row3, int column3);

char turn;
bool draw = false;
char board[3][3] = { { '1', '2', '3' }, { '4', '5', '6' }, { '7', '8', '9' } };
//num will keep track of the number of turns
int num;
//track will record the previous player move
int track;

int main() {
	num = 1;
	bool quit =false;
	cout << "Welcome to Tic Tac Toe \n";
	while(!quit){
		welcome();
		while (!game_over()) {
			display_board();
			player_turn();
			game_over();
		}

		//Game over has returned true, see who won
		if (turn == 'O' && !draw) {
			display_board();
			cout << endl << endl << "Player [X] Wins! Game Over!\n";
		} else if (turn == 'X' && !draw) {
			display_board();
			cout << endl << endl << "Computer [O] Wins! Game Over!\n";
		} else {
			display_board();
			cout << endl << endl << "You tied. Cats game. Game Over!\n";
		}
		play_again();

	}
	cout << "Goodbye!\n";
}

void welcome(){
	char c;
	cout << "Would you like to go first? Y or N >> ";
	cin >> c;

	if (c == 'Y' || c == 'y')
		turn = 'X';
	else if (c == 'N' || c == 'n')
		turn = 'O';
	else{
		cout << "Invalid input. Please try again.\n";
		welcome();
	}
}
void display_board() {
	cout << "     |     |     " << endl;
	cout << "  " << board[0][0] << "  |  " << board[0][1] << "  |  "
			<< board[0][2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[1][0] << "  |  " << board[1][1] << "  |  "
			<< board[1][2] << endl;
	cout << "_____|_____|_____" << endl;
	cout << "     |     |     " << endl;
	cout << "  " << board[2][0] << "  |  " << board[2][1] << "  |  "
			<< board[2][2] << endl;
	cout << "     |     |     " << endl;
}

void player_turn() {
	int choice = 0;
	int row = 0, column = 0;
	if (turn == 'X') {
		cout << "Players turn [X]: ";
		cin >> choice;
		if(cin.fail()){
			cout << "Please enter a number 1-9\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			player_turn();
		}

		//Choice will be assigned a row and column, also checks if valid
		switch (choice) {
		case 1:
			row = 0;
			column = 0;
			track = 0;
			break;
		case 2:
			row = 0;
			column = 1;
			track = 1;
			break;
		case 3:
			row = 0;
			column = 2;
			track = 2;
			break;
		case 4:
			row = 1;
			column = 0;
			track = 10;
			break;
		case 5:
			row = 1;
			column = 1;
			track = 11;
			break;
		case 6:
			row = 1;
			column = 2;
			track = 12;
			break;
		case 7:
			row = 2;
			column = 0;
			track = 20;
			break;
		case 8:
			row = 2;
			column = 1;
			track = 21;
			break;
		case 9:
			row = 2;
			column = 2;
			track = 22;
			break;
		default:
			cout << "Please enter a number 1-9\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			player_turn();
			return;
		}
		//Checks to see if block is empty move then changes turn to 'O'
		if (board[row][column] != 'X' && board[row][column] != 'O') {
			board[row][column] = 'X';
			num++;
			turn = 'O';
		}
		//Returns error block is used
		else {
			cout << "Seat's taken! Block already used! Try again\n";
			player_turn();
		}
	} else if (turn == 'O') {
		cout << "Computer's turn [O]...\n";
		//Calls for compuer's move
		computer_AI(row, column, turn);
		board[row][column] = 'O';
		num++;
		turn = 'X';
	}

}
void computer_AI(int &r, int &c, int m) {

	while (!for_the_win(r, c) && !block(r, c)) {
		if (num == 2) {
			r = 1; c = 1;
			if(check_spot(r,c)){return;}
		}
		if (num == 3) {
			//Opponent takes corner, take opposite corner
			if (track == 12 || track == 21 || track == 22 ) {
				r = 0; c =0;
				if(check_spot(r,c)){return;}
			}
			if (track == 1 || track == 0 || track == 10) {
				r = 2; c = 2;
				if(check_spot(r,c)){return;}
			}
			//Opponent takes edge, take diagonal
			if (track == 2) {
				r = 2; c = 0;
				if(check_spot(r,c)){return;}
			}
			if (track == 20) {
				r = 0; c = 2;
				if(check_spot(r,c)){return;}
			}
		}
		//Pick an side then empty corner
		if (num == 4) {
			if (track == 0 || track == 2) {
				r = 0; c = 1;
				if(check_spot(r,c)){return;}
			}
			else if (track == 20 ||track == 22) {
				r = 2; c = 1;
				if(check_spot(r,c)){return;}
			}
			else{
				for (int i = 0; i < 3; i += 2) {
					for (int j = 0; j < 3; j +=2) {
						if (board[i][j] != 'X' && board[i][j] != 'O') {
							r = i; c = j;
							if(check_spot(r,c)){return;}
						}
					}
				}
			}
		}
		//Fills in 'O' in next available space
		else{
			for (int i = 0; i < 3; i += 2) {
				for (int j = 0; j < 3; j +=2) {
					if (board[i][j] != 'X' && board[i][j] != 'O') {
						r = i; c = j;
						if(check_spot(r,c)){return;}
					}
				}
			}
			if (check_spot(1,1)) {
				r = 1; c = 1; return;
			}
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					if (board[i][j] != 'X' && board[i][j] != 'O') {
						r = i;	c = j;
						if(check_spot(r,c)){return;}
					}
				}
			}
		}
	}
}
bool block(int &r1, int &c1) {
	for (int i = 0; i < 3; i++) {
		//Block first column of row
		if (board[i][1] == board[i][2] && board[i][2] == 'X') {
			r1 = i;	c1 = 0;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
		//Block middle colum1n of row
		if (board[i][0] == board[i][2] && board[i][2] == 'X') {
			r1 = i;	c1 = 1;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
		//Need to block last column in row
		if (board[i][0] == board[i][1] && board[i][0] == 'X') {
			r1 = i;	c1 = 2;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
		//Block first row of column
		if (board[1][i] == board[2][i] && board[2][i] == 'X') {
			r1 = 0;	c1 = i;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
		//Block middle row of column
		if (board[0][i] == board[2][i] && board[2][i] == 'X') {
			r1 = 1;	c1 = i;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
		//Need to block last row in column
		if (board[0][i] == board[1][i] && board[1][i] == 'X') {
			r1 = 2;	c1 = i;
			if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
				return true;
			}
		}
	}
	//Block first diagonal right
	if (board[1][1] == board[2][2] && board[2][2] == 'X') {
		r1 = 0;	c1 = 0;
		if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
			return true;
		}
	}
	//Block first diagonal left
	if (board[1][1] == board[2][0] && board[1][1] == 'X') {
		r1 = 0;	c1 = 2;
		if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
			return true;
		}
	}
	//Block middle diagonal
	if ((board[0][0] == board[2][2] && board[2][2] == 'X')
			|| (board[2][0] == board[0][2] && board[0][2] == 'X')) {
		r1 = 1;	c1 = 1;
		if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
			return true;
		}
	}
	//Block last diagonal left
	if (board[1][1] == board[0][0] && board[1][1] == 'X') {
		r1 = 2;	c1 = 2;
		if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
			return true;
		}
	}
	//Block last diagonal right
	if (board[1][1] == board[0][2] && board[0][2] == 'X') {
		r1 = 2; c1 = 0;
		if (board[r1][c1] != 'X' && board[r1][c1] != 'O') {
			return true;
		}
	}
	return false;
}

bool for_the_win(int &r2, int &c2) {
	for (int i = 0; i < 3; i++) {
		//Block first column of row
		if (board[i][1] == board[i][2] && board[i][2] == 'O') {
			r2 = i;	c2 = 0;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
		//Block middle column of row
		if (board[i][0] == board[i][2] && board[i][2] == 'O') {
			r2 = i;	c2 = 1;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
		//Need to block last column in row
		if (board[i][0] == board[i][1] && board[i][0] == 'O') {
			r2 = i;	c2 = 2;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
		//Block first row of column
		if (board[1][i] == board[2][i] && board[2][i] == 'O') {
			r2 = 0;	c2 = i;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
		//Block middle row of column
		if (board[0][i] == board[2][i] && board[2][i] == 'O') {
			r2 = 1;	c2 = i;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
		//Need to block last row in column
		if (board[0][i] == board[1][i] && board[1][i] == 'O') {
			r2 = 2;	c2 = i;
			if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
				return true;
			}
		}
	}
	//Block first diagonal right
	if (board[1][1] == board[2][2] && board[2][2] == 'O') {
		r2 = 0;	c2 = 0;
		if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
			return true;
		}
	}
	//Block first diagonal left
	if (board[1][1] == board[2][0] && board[1][1] == 'O') {
		r2 = 0;	c2 = 2;
		if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
			return true;
		}
	}
	//Block middle diagonal
	if ((board[0][0] == board[2][2] && board[2][2] == 'O')
			|| (board[2][0] == board[0][2] && board[0][2] == 'O')) {
		r2 = 1;	c2 = 1;
		if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
			return true;
		}
	}
	//Block last diagonal left
	if (board[1][1] == board[0][0] && board[1][1] == 'O') {
		r2 = 2;	c2 = 2;
		if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
			return true;
		}
	}
	//Block last diagonal right
	if (board[1][1] == board[0][2] && board[0][2] == 'O') {
		r2 = 2;	c2 = 0;
		if (board[r2][c2] != 'X' && board[r2][c2] != 'O') {
			return true;
		}
	}
	return false;
}

bool game_over() {
	//Checks for a winner
	for (int i = 0; i < 3; i++) {
		//Straight across win
		if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
			return true;
		//Straight down win
		if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
			return true;
		//Diagonal left corner win
		if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
			return true;
		//Diagonal right corner win
		if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
			return true;

	}
	//Checks for a cats game
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] != 'X' && board[i][j] != 'O') {
				return false;
			}
		}
	}
	draw = true;
	return true;
}
bool play_again(){
	char answer;
	cout << "\nWould you like to play another game?\n"
		 <<"Type ANY character to continue and 'Q' to quit>>";
	cin >>answer;
	if (answer == 'q' || answer =='Q'){
		return false;
	}
	else{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		char refill = '1';
		for(int i =0; i <= 2; i++){
			for (int j=0; j <= 2; j++){
				board[i][j] = refill;
				refill++;
			}
		}
		num=1;
		return true;
	}
}
bool check_spot(int row3, int column3){
	if (board[row3][column3] != 'X' && board[row3][column3] != 'O') {
		return true;
	}
	else{
		return false;
	}
}
