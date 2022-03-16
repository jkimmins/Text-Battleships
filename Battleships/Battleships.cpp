// Battleships

// This section imports libraries which contain functions used throughout the program
#include <iostream> 
#include <time.h>
#include <string>

// Prototype functions are declared here
void PlaceShips(char _grid[10][10]);
void PlaceVertical(char &_character, int &_size, int &_z, char _grid[10][10]);
void PlaceHorizontal(char &_character, int &_size, int &_z, char _grid[10][10]);
void Fire(int &_ammo, char _fullGrid[10][10], char _visibleGrid[10][10], int &_aircraftCarrierHits, int &_battleshipHits, int &_destroyerHits, int &_submarineHits, int &_patrolBoatHits);
void Menu();
void Play(char _fullGrid[10][10], char _visibleGrid[10][10]);
void DisplayGrid(char _visibleGrid[10][10]);
void DisplayInstructions();
void ChooseDifficulty(int &_ammo);
void InitialiseGame(char _grid[10][10], char _visGrid[10][10]);
void CheckCondition(int &_ammo, int &_aircraftCarrierHits, int &_battleshipHits, int &_destroyerHits, int &_submarineHits, int &_patrolBoatHits);
void InputCoords(char &_x, char &_y, bool &_valX, bool &_valY, bool &_targeting);
void ConvertValue(char &_x, char &_y, int &_targetX, int &_targetY);

// The main function. This main function generates a random seed, calls the 'Menu' function and returns 0 when the user quits the game.
int main()
{
	srand(time(NULL));
	Menu();

	return 0;
}

// This function places ships within a 10x10 grid. It takes a single 10x10 2d array as an argument
void PlaceShips(char _grid[10][10])
{
	int size, randOrientation, z = 1;// Size of the ship to be placed in the array, Determines which way a ship will be placed
	char character;// The character to be placed in the array

	// This while loop will run until all 5 ships have been placed
	while (z <= 5)
	{
		// The following if statements determine the size and what character will be used for the ship being placed
		// Ship 1 is the aircraft carrier, 2 is the battleship, 3 is the destroyer, 4 is the submarine and 5 is the patrol boat
		if (z == 1)
		{
			size = 5;
			character = 'A';
		}
		else if (z == 2)
		{
			size = 4;
			character = 'B';
		}
		else if (z == 3)
		{
			size = 3;
			character = 'D';
		}
		else if (z == 4)
		{
			size = 3;
			character = 'S';
		}
		else
		{
			size = 2;
			character = 'P';
		}

		// Randomly assigns the value 1 or 0 to the variable randOrientation
		randOrientation = rand() % 2;
		// Randome value determines if the current ship will be placed vertically or horizontally
		if (randOrientation == 0)
		{
			PlaceHorizontal(character, size, z, _grid);
		}
		if (randOrientation == 1)
		{
			PlaceVertical(character, size, z, _grid);
		}
	}
}

void DisplayGrid(char _visibleGrid[10][10])
{
	// The following output displays an x-axis labelled 1-10, a y-axis labelled a-j and the visible 2d array
	std::cout << "  " << "1" << "  " << "2" << "  " << "3" << "  " << "4" << "  " << "5" << "  " << "6" << "  " << "7" << "  " << "8" << "  " << "9" << "  " << "10" << std::endl << std::endl;
	for (int x = 0; x < 10; x++)
	{
		switch (x)
		{
		case 0:
			std::cout << "A" << " ";
			break;
		case 1:
			std::cout << "B" << " ";;
			break;
		case 2:
			std::cout << "C" << " ";;
			break;
		case 3:
			std::cout << "D" << " ";;
			break;
		case 4:
			std::cout << "E" << " ";;
			break;
		case 5:
			std::cout << "F" << " ";;
			break;
		case 6:
			std::cout << "G" << " ";;
			break;
		case 7:
			std::cout << "H" << " ";;
			break;
		case 8:
			std::cout << "I" << " ";;
			break;
		case 9:
			std::cout << "J" << " ";;
			break;
		}
		for (int y = 0; y < 10; y++)
		{
			std::cout << _visibleGrid[y][x] << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void DisplayInstructions()
{
	//Outputs the instructions for the game
	std::cout << "Objective: Sink all 5 of the computers ships before you run out of ammunition" << std::endl
		<< "To fire at a ship type '1' and then enter a co-ordinate in the following format" << std::endl
		<< "(column)(row), this will look like 1a, 5g, 9c. If you want to target" << std::endl
		<< "the 10th column you must use '#', this will look like #b, #e, #j" << std::endl
		<< "The computer's five ships consist of an aircraft carrier (5 cells)" << std::endl
		<< "battleship (4 cells)" << std::endl
		<< "a destroyer (3 cells), a submarine (3 cells) and a patrol boat (2 cells)" << std::endl
		<< "If you miss a target an 'X' will be placed in the targeted cell" << std::endl
		<< "if you hit a ship then an 'H' will be placed in the targeted cell." << std::endl
		<< "When you sink a ship the 'H' cells will" << std::endl
		<< "turn into a letter representing the ship you just destroyed" << std::endl << std::endl;
}

void ChooseDifficulty(int &_ammo)
{
	bool choose = true;// Boolean used to control the while loop
	char difficulty;// Usre's choice is input into this variable
	while (choose == true)
	{
		// While choose is true the player gets to choose a difficulty which determines how much ammo they get
		std::cout << "Choose a difficulty" << std::endl << std::endl << "1.    Demo (Unlimited ammunition)" << std::endl << "2.    Easy (40 ammunition)" << std::endl << "3.    Medium (30 ammunition)" << std::endl<< "4.    Hard (20 ammunition)" << std::endl;
		std::cout ;
		std::cin >> difficulty;
		system("CLS");
		choose = false;
		// In the following if statements the console is cleared and the user is told which difficulty they selected and their ammunition is set to the corresponding value and the while loop is terminated
		if (difficulty == '1')
		{
			std::cout << "Demo mode selected!" << std::endl << std::endl;
		}
		else if (difficulty == '2')
		{
			std::cout << "Easy mode selected!" << std::endl << std::endl;
			_ammo = 40;
		}
		else if (difficulty == '3')
		{
			std::cout << "Medium mode selected!" << std::endl << std::endl;
			_ammo = 30;
		}
		else if (difficulty == '4')
		{
			std::cout << "Hard mode selected!" << std::endl << std::endl;
			_ammo = 20;
		}
		// If the user didn't input a valid choice the while is reset and the user can try to input another value
		else
		{
			std::cout << "That isn't a valid choice!" << std::endl;
			choose = true;
		}
	}
}

void InitialiseGame(char _grid[10][10], char _visGrid[10][10])
{
	// The following for loops fill up the main grid and visible grid with the '~' character
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			_grid[y][x] = '~';
		}
	}

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			_visGrid[y][x] = '~';
		}
	}
	// Outputs that the game has started and calls the PlaceShips function
	std::cout << "Game started" << std::endl << "Placing ships" << std::endl << std::endl;
	PlaceShips(_grid);
	std::cout << "Ships Placed!" << std::endl;
}

void CheckCondition(int &_ammo, int &_aircraftCarrierHits, int &_battleshipHits, int &_destroyerHits, int &_submarineHits, int &_patrolBoatHits)
{
	// If the user has sunk every ship the following if statement triggers and tells the user they won and sends them back to the menu
	if (_aircraftCarrierHits == 5 && _battleshipHits == 4 && _destroyerHits == 3 && _submarineHits == 3 && _patrolBoatHits == 2)
	{
		std::cout << "Congratulations! You Win!";
		Menu();
	}
	// If the user runs out of ammuniton they are told they lose the game and are sent back to the menu
	if (_ammo == 0)
	{
		std::cout << "You've lost!" << std::endl << std::endl;
		Menu();
	}
}

// This function allows the user to input a co-ordinate and then checks to see if the user hit or miss a ship and performs actions based on those results
// This function takes 2 10x10 2d arrays and 6 integers as an argument
// The first 2d array is the grid with all of the ships placed inside of it, the second 2d array is what the player is able to see
// The ammo variable is passed by reference along with 5 other variables which represent how many times each ship has been hit by the player
void Fire(int &_ammo, char _fullGrid[10][10], char _visibleGrid[10][10], int &_aircraftCarrierHits, int &_battleshipHits, int &_destroyerHits, int &_submarineHits, int &_patrolBoatHits)
{
	char x, y;// Will represent the user's x and yinput
	int targetX, targetY;// Will represent the x and y values which will be passed into the 2d arrays
	bool valX = false, valY = false, targeting = true;
	// The first 2 booleans show us whether the user's coordinates are valid or not
	// The targeting boolean is used to control the following while loop

	// This while loop runs while targeting is true
	while (targeting == true)
	{
		DisplayGrid(_visibleGrid);

		// The user is prompted to type in 2 characters which will be the x and y value and then runs the 2 functions which will turn the user inputs into acceptable integers
		std::cout << "Type the coordinates you want to target (example '1a')" << std::endl;
		std::cin >> x >> y;
		InputCoords(x, y, valX, valY, targeting);
		ConvertValue(x, y, targetX, targetY);
	}

	// This if statement checks to see if the input co-ordinates had already been targeted
	if (_visibleGrid[targetX][targetY] == '~')
	{
		// The program then looks at the main grid to see if a ship's cell has been hit or not
		// If a ship has been hit then the corresponding ship's hit value is increased by one
		// If the ship hasn't been hit enough times yet then 'H' is placed in the visible grid in the same position as the targeted position in the main grid and 'Hit!' is displayed in the console
		//If the ship has taken enough hits to be destroyed then a for loop is used to change the H's to the ship letter which was destroyed and a message is displayed telling the user they sunk a ship
		if (_fullGrid[targetX][targetY] == 'A')
		{
			_aircraftCarrierHits += 1;
			if (_aircraftCarrierHits < 5)
			{
				_visibleGrid[targetX][targetY] = 'H';
				std::cout << "Hit!" << std::endl;
			}
			else
			{
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (_fullGrid[a][b] == 'A')
						{
							_visibleGrid[a][b] = 'A';
						}
					}
				}
				std::cout << "Hit!" << std::endl << "You sunk the Aircraft Carrier!" << std::endl;
			}
		}
		else if (_fullGrid[targetX][targetY] == 'B')
		{
			_battleshipHits += 1;
			if (_battleshipHits < 4)
			{
				_visibleGrid[targetX][targetY] = 'H';
				std::cout << "Hit!" << std::endl;
			}
			else
			{
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (_fullGrid[a][b] == 'B')
						{
							_visibleGrid[a][b] = 'B';
						}
					}
				}
				std::cout << "Hit!" << std::endl << "You sunk the Battleship!" << std::endl;
			}
		}
		else if (_fullGrid[targetX][targetY] == 'D')
		{
			_destroyerHits += 1;
			if (_destroyerHits < 3)
			{
				_visibleGrid[targetX][targetY] = 'H';
				std::cout << "Hit!" << std::endl;
			}
			else
			{
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (_fullGrid[a][b] == 'D')
						{
							_visibleGrid[a][b] = 'D';
						}
					}
				}
				std::cout << "Hit!" << std::endl << "You sunk the Destroyer!" << std::endl;
			}
		}
		else if (_fullGrid[targetX][targetY] == 'S')
		{
			_submarineHits += 1;
			if (_submarineHits < 3)
			{
				_visibleGrid[targetX][targetY] = 'H';
				std::cout << "Hit!" << std::endl;
			}
			else
			{
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (_fullGrid[a][b] == 'S')
						{
							_visibleGrid[a][b] = 'S';
						}
					}
				}
				std::cout << "Hit!" << std::endl << "You sunk the Submarine!" << std::endl;
			}
		}
		else if (_fullGrid[targetX][targetY] == 'P')
		{
			_patrolBoatHits += 1;
			if (_patrolBoatHits < 2)
			{
				_visibleGrid[targetX][targetY] = 'H';
				std::cout << "Hit!" << std::endl;
			}
			else
			{
				for (int a = 0; a < 9; a++)
				{
					for (int b = 0; b < 9; b++)
					{
						if (_fullGrid[a][b] == 'P')
						{
							_visibleGrid[a][b] = 'P';
						}
					}
				}
				std::cout << "Hit!" << std::endl << "You sunk the Patrol Boat!" << std::endl;
			}
		}
		// If the player didn't hit anything then an 'X' is displayed in the targeted position and the player is told they missed
		else
		{
			_visibleGrid[targetX][targetY] = 'X';
			std::cout << "Miss!" << std::endl;
		}

		DisplayGrid(_visibleGrid);
		// 1 is subtracted from the ammo variable
		_ammo -= 1;
	}
	// If the user targets the same position twice they are told and can input another co-ordinate
	else
	{
		std::cout << "You have already targeted these co-ordinates!" << std::endl;
	}

}

// This function is the first thing the user sees and shows the user their options
void Menu()
{
	bool choose = true;
	char choice;
	char grid[10][10];// Initialises a 10x10 2d array which will have the 5 ships placed inside
	char visGrid[10][10];// Initialises a 10x10 2d array which will be the grid the user sees
	std::cout << "Welcome to Battleships!" << std::endl << std::endl;

	// while the choose variable is true
	while (choose == true)
	{
		//Prints out the numbers with a corresponding action and tells the user to type a number in and stores that number in the choice variable
		std::cout << "Type in a number to choose the corresponding action!" << std::endl << std::endl << "1.    Play" << std::endl << "2.    Instructions" << std::endl << "3.    Exit" << std::endl;
		std::cin >> choice;
		system("CLS");

		if (choice == '1')
		{
			// Choose becomes false to end the while loop, the game is then initialised and played
			// The Play function is then called with both 2d arrays being passed into it
			choose = false;
			InitialiseGame(grid, visGrid);
			Play(grid, visGrid);
		}
		// If choice equals 2 then instructions are displayed
		else if (choice == '2')
		{
			DisplayInstructions();
		}
		// If choice equals 3 the while loop is ended and the programs returns to the main function and is then ended
		else if (choice == '3')
		{
			std::cout << "Quitting game" << std::endl;
			choose = false;
		}
		// If the user inputs an invalid choice they are notified and the while loop returns to the beginning
		else
		{
			std::cout << "Invalid input, please enter a number that is listed" << std::endl << std::endl;
		}
	}

}

// The Play function has 2 2d arrays passed into it
void Play(char _fullGrid[10][10], char _visibleGrid[10][10])
{
	bool playing = true;// Controls while loop
	char action;// User input variable
	int aircraftCarrierHits = 0, battleshipHits = 0, destroyerHits = 0, submarineHits = 0, patrolBoatHits = 0, ammo = 101;// Ship hit variables and user ammo
	// User chooses their difficulty
	ChooseDifficulty(ammo);
	
	// While playing is true
	while (playing == true)
	{
		CheckCondition(ammo, aircraftCarrierHits, battleshipHits, destroyerHits, submarineHits, patrolBoatHits);
		// If the difficulty isn't demo mode then the user is told how much ammo they have left and what actions they can take
		std::cout << "Remaining ammunition: " << ammo << std::endl;
		std::cout << "Choose an action" << std::endl << "1.    Fire!" << std::endl << "2.    Instructions" << std::endl << "3.    Exit" << std::endl;
		std::cin >> action;
		system("CLS");
		// If the user decides to fire the console is cleared and the Fire function is called with the ammo and hit variables being passed along with the main grid and visible grid
		if (action == '1')
		{
			Fire(ammo, _fullGrid, _visibleGrid, aircraftCarrierHits, battleshipHits, destroyerHits, submarineHits, patrolBoatHits);
		}
		// If the user wants to see the instructions the screen is cleared and instructions are printed
		else if (action == '2')
		{
			DisplayInstructions();
		}
		// If the user chooses 3 then the while loops end and the program is sent to the main function where it terminates
		else if (action == '3')
		{
			std::cout << "Quitting game";
			playing = false;
		}
		// The user is told if they don't input a correct action and the while loop resets letting them type in another value
		else
		{
			std::cout << "That's not a valid action!" << std::endl;
		}
	}
}

void PlaceHorizontal(char &_character, int &_size, int &_z, char _grid[10][10])
{
	int duplicate = 0;
	// A random value between 0 and 10 minus the size of the ship is given to the xPos variable
	// The size of the ship is subtracted from 10 to make sure the end of the ship can only be placed at position 10 and not over
	int xPos = rand() % (10 - _size);
	// A random value between 0 and 9 is given to Ypos which represents the cell's y position
	int yPos = rand() % 10;

	// This for loop runs through the 2d array and checks to see if the cells which the ship is going to be placed in is empty or not
	// If a cell is already occupied then 1 is added to the duplicate variable
	for (int i = xPos; i < (xPos + _size); i++)
	{
		if (_grid[yPos][i] != '~')
		{
			duplicate += 1;
		}
	}

	// This if statement runs if the selected cells are empty and available to be used
	if (duplicate == 0)
	{
		// This for loop is similar to the previous for loop which checks for duplicates except it writes values into the 2d array instead and adds 1 to z to show that the next ship can be placed
		for (int i = xPos; i < (xPos + _size); i++)
		{
			_grid[yPos][i] = _character;
		}
		_z += 1;
	}

	// If one of the selected cells wasn't empty then duplicate is reset back to 0 and the while loop resets and attempts to place the same ship in the grid again
	if (duplicate != 0)
	{
		duplicate = 0;
	}
}

void PlaceVertical(char &_character, int &_size, int &_z, char _grid[10][10])
{
	int duplicate = 0;
	// This if statement is the same as the horizontal function except the y position has the size of the ship subtracted from 10
	int xPos = rand() % 10;
	int yPos = rand() % (10 - _size);

	for (int i = yPos; i < (yPos + _size); i++)
	{
		if (_grid[i][xPos] != '~')
		{
			duplicate += 1;
		}
	}

	if (duplicate == 0)
	{
		for (int i = yPos; i < (yPos + _size); i++)
		{
			_grid[i][xPos] = _character;
		}
		_z += 1;
	}

	if (duplicate != 0)
	{
		duplicate = 0;
	}
}

void InputCoords(char &_x, char &_y, bool &_valX, bool &_valY, bool &_targeting)
{
	// The following if statements validates and converts the users inputs into values between 0 and 9 by shifting the inputted values through ascii
	if (_x >= '1' && _x <= '9')
	{
		_valX = true;
		_x = _x - 1;
	}
	else if (_x == '#')
	{
		_valX = true;
		_x = '#';
	}
	else
	{
		_valX = false;
	}

	if (_y >= 'a' && _y <= 'j')
	{
		_y = _y - 49;
		_valY = true;
	}
	else if (_y >= 'A' && _y <= 'J')
	{
		_y = _y - 17;
		_valY = true;
	}
	else
	{
		_valY = false;
	}

	// If both values which the user input are valid then targeting becomes false to end the while loop, valX and valY become false again and the console is cleared
	if (_valX == true && _valY == true)
	{
		_targeting = false;
		_valX = false;
		_valY = false;
		system("CLS");
	}
	// If the user didn't input correct values then they are notified. valX, valY, x and y are reset and targeting remains true so that the user can have another go at inputting correct values
	else
	{
		std::cout << "Those co-ordinates aren't valid!" << std::endl;
		_targeting = true;
		_valX = false;
		_valY = false;
		_x = NULL;
		_y = NULL;
	}
}

void ConvertValue(char &_x, char &_y, int &_targetX, int &_targetY)
{
	// This for loop takes the y character which is between a and j and shifts the value by -48 across the ascii table which will be an integer between 0 and 9
	// this integer is then stored in the targetY variable
	for (int i = 48; i < 58; i++)
	{
		if (_y == i)
		{
			_targetY = (i - 48);
		}
	}

	// This if statement checks to see if the inputted x value is a # or not. Since # is equal to 10 the targetX variable becomes 9
	if (_x == '#')
	{
		_targetX = 9;
	}
	// If the x input was not # then the same thing as the last for loop happens for the targetX variable
	else
	{
		for (int i = 48; i < 57; i++)
		{
			if (_x == i)
			{
				_targetX = (i - 48);
			}
		}
	}
}