#include<iostream>
#include<string>
using namespace std;

// function prototype

void displaymenu();
bool check(int a, int b);
int drop(int b, char player);
char place[6][7];//available for whole program

void displaymenu()  //function to  display memu
{
	cout<< "WELCOME TO CONNECT 4\n";
	cout << "1-Play Game\n";
	cout << "2-Credits\n";
	cout << "3-Instruction\n";
	cout << "4-Record\n";
	cout << "5-Exit\n";
}
void display()
{
	cout << " 1   2   3   4   5   6   7\n";
	for (int a = 0; a <= 5; a++)
	{
		for (int b = 0; b <= 6; b++)
		{
			cout << char(218) << char(196) << char(191) << " ";
		}
		cout << '\n';
		for (int b = 0; b <= 6; b++)
		{
			cout << char(179) << place[a][b] << char(179) << " ";
		}
		cout << '\n';
		for (int b = 0; b <= 6; b++)
		{
			cout << char(192) << char(196) << char(217) << " ";
		}
		cout << '\n';
	}
}
bool check(int a, int b)
{

	int vertical = 1;//(|)

	int horizontal = 1;//(-)

	int diagonal1 = 1;//(\)

	int diagonal2 = 1;//(/)

	char player = place[a][b];

	int i;//vertical

	int ii;//horizontal

		   //check for vertical(|)

	for (i = a + 1; place[i][b] == player && i <= 5; i++, vertical++);//Check down
	{
		for (i = a - 1; place[i][b] == player && i >= 0; i--, vertical++);//Check up
		{
			if (vertical >= 4)
			{
				return true;
			}
		}
	}
	//check for horizontal(-)
	for (ii = b - 1; place[a][ii] == player && ii >= 0; ii--, horizontal++);//Check left
	{
		for (ii = b + 1; place[a][ii] == player && ii <= 6; ii++, horizontal++);//Check right
		{
			if (horizontal >= 4)
			{
				return true;
			}
		}
	}
	//check for diagonal 1 (\)
	for (i = a - 1, ii = b - 1; place[i][ii] == player && i >= 0 && ii >= 0; diagonal1++, i--, ii--);//up and left
	{
		for (i = a + 1, ii = b + 1; place[i][ii] == player && i <= 5 && ii <= 6; diagonal1++, i++, ii++);//down and right
		{
			if (diagonal1 >= 4)
			{
				return true;
			}
		}
	}
	//check for diagonal 2(/)

	for (i = a - 1, ii = b + 1; place[i][ii] == player && i >= 0 && ii <= 6; diagonal2++, i--, ii++);//up and right
	{

		for (i = a + 1, ii = b - 1; place[i][ii] == player && i <= 5 && ii >= 0; diagonal2++, i++, ii--);//up and left
		{
			if (diagonal2 >= 4)
			{
				return true;
			}
		}
	}

	if (diagonal2 >= 4)
	{
		return true;
	}
	else
	{
		return false;
	}

}
int drop(int b, char player)
{
	if (b >= 0 && b <= 6)
	{

		if (place[0][b] == ' ')
		{
			int i;
			for (i = 0; place[i][b] == ' '; i++)

				if (i == 5)
				{
					place[i][b] = player;

					return i;
				}

			i--;

			place[i][b] = player;

			return i;

		}
		else
		{

			return -1;

		}

		
	}
	else
	{

		return -1;

		
	}

}

int main()
{
	string p1, p2; //player name input
	string c;         //Try entering a non number without this, 2 see what this does
	int opt;
	do
	{
		displaymenu();
		cout << "Enter your choice = ";
		cin >> opt;
		switch (opt)
		{
		case 1:
		{
			cout << "Enter player 1 name = ";
			getline(cin, p1);
			cin.ignore();
			cout << "Enter player 2 name = ";
			getline(cin, p2);
			cin.ignore();
			for (int a = 0; a <= 5; a++)
			{     //fill place with whitespace
				for (int b = 0; b <= 6; b++)
				{
					place[a][b] = ' ';
				}
			}
			//Displays for first time so players can see the board
			int hold;//Will hold user row choice
			int hold2 = 0;//will hold drop value
			int charsPlaced = 0;//Number of peices dropped so can end game if a draw
			bool gamewon = false;//Will be changed to true when game is won and will exit while loop
			char player = 15;//start as player 2 will change back 2 player 1
			while (!gamewon)
			{//will stop when game is won, ! means NOT makes the oppisite be checked

				if (hold2 != -1)
				{//check if there was a error in the last drop

					if (player == 15) {//if player 2 lasted dropped a piece so its player 1s turn

						cout << p1 << " drop where?";

						player = 254;//char of players piece

					}
					else
					{

						cout << p2 << " drop where?";

						player = 15;//char of player piece

					}
				}
				while (true)
				{//will run untill 'break;'

					if (charsPlaced == 42) break;//if draw

					cin >> hold;//get user input

					hold--;//take off 1 to account for arrays starting at 0 not 1

					if (hold <= 6 && hold >= 0)
					{
						break;//if within valid range stop loop
					}
					else
					{
						cout << "\nplease enter a value between 1 and 7 :";//ask for input and loop again
					}

					if (cin.fail()) //catch a non number
					{

						cin.clear();        //Stops cin trying to put its value in to hold
						
						cin >> c;           //

					}                       //Catch a non number

				}

				if (charsPlaced == 42) break;//if draw

				hold2 = drop(hold, player);//drop the player store the row in hold2

				if (hold2 == -1)
				{
					cout << "Colom is full\n";
					cout << "Please enter anothor number between 1 and 7:";//if error -1 row is full
				}
				else
				{

					gamewon = check(hold2, hold);//check if game is run
					charsPlaced++;//another character has been succesfully placed
					system("cls");//This clears the screen works with windows, not nesscery to run game
					display();//displayed updated board
				}
			}
			system("cls");//this clears the screen
			if (charsPlaced == 42)
			{//if draw

				cout << "No winner, Game was draw\n";

				return 0;

			}

			if (player == 15)//if won by player 2
			{
				cout << "Gamewon by " << c << "\n";
			}
			else
			{
				cout << "Gamewon by " << c << "\n";
			}
			return 0;
		}






		case 2:
		{
			cout << "\nCredits\n";
			cout << "This game made by Ayesha and Maryam.\n";
			cout << "Roll # 21F-9136 & 21F-9337\n";
			break;
		}
		case 3:
		{
			cout << "\nConnect Four (also known as Four Up, Plot Four, Find Four, Four in a Row, Four in a Line, Drop Four, and Gravitrips in the Soviet Union) is a two - player connection board game, in which the players choose a colorand then take turns dropping colored discs into a seven - column, six - row vertically suspended grid.The pieces fall straight down, occupying the lowest available space within the column.The objective of the game is to be the first to form a horizontal, vertical, or diagonal line of four of one's own discs. Connect Four is a solved game. The first player can always win by playing the right moves.\n";
			break;
		}
		case 4:
		{
			cout << "\nThis section is divided in to further two sub-sections\n";
			cout << "a.Game Winner Section : This section contains the name of the player who won the game with his / her number of turns.\n";
			cout << "b.Game draw section : This section contains a total number of turns taken by both players with their names.\n";
			break;

		}
		case 5:
		{
			cout << "\nGame Exit\n";
			exit(0);
			break;
		}
		default:
		{
			cout << "Invalid Input. \n";
			break;
		}

		}
	} 
	while (opt != 5);
	system("pause");
	return 0;
}