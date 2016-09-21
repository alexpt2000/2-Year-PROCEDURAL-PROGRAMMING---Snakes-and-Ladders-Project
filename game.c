////////////////////////////////////////////////////////////////////////////
//
//  Procedural Programming - Project - Snakes and Ladder Board
//  ----------------------------------------------------------
//	17/12/2015 to 04/01/2016
//	
//  @Alexander Souza - G00317835 - GMIT - Galway
//
//
///////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

//Declare variables
int i, j;
int nPlayers;
int dice;
int choice;
int choiceLadSna = 0;
char keyEnter;
char * statusGame;
int *player;


//location of ladders (first 7) location of snakes(later 7)
int locationLaddersSnakes[14];

//jump values in case of snake or ladder
int jumpLaddersSnakes[14];



//Variables with random coordinates the positions of snake and ladders
int valuesLocationLaddersSnakes[10][14] = {
	{ 06, 10, 21, 28, 40, 60, 80,    19, 33, 42, 58, 79, 90, 96 },
	{ 05, 10, 22, 29, 41, 62, 78,    17, 30, 47, 52, 75, 93, 98 },
	{ 06, 15, 23, 28, 44, 66, 70,    16, 33, 45, 58, 75, 91, 95 },
	{ 04, 10, 22, 27, 43, 62, 76,    17, 35, 47, 55, 73, 93, 98 },
	{ 07, 17, 25, 28, 44, 63, 70,    18, 33, 46, 58, 77, 92, 97 },
	{ 04, 10, 22, 26, 45, 62, 73,    17, 37, 47, 57, 76, 93, 98 },
	{ 06, 13, 26, 28, 44, 61, 70,    19, 33, 49, 58, 74, 96, 96 },
	{ 04, 10, 22, 28, 46, 62, 74,    17, 34, 47, 59, 77, 93, 98 },
	{ 03, 11, 27, 28, 44, 67, 70,    20, 33, 50, 58, 79, 92, 99 },
	{ 04, 10, 22, 30, 47, 62, 71,    17, 36, 47, 60, 78, 93, 98 },
};

int valuesJumpLaddersSnakes[10][14] = {
	{ 14, 31, 30, 84, 62, 91, 95,   -10,-10,-22,-10,-22,-20,-56 },
	{ 15, 32, 30, 84, 62, 90, 94,   -10,-10,-22,-10,-22,-20,-56 },
	{ 17, 31, 33, 89, 66, 92, 95,   -10,-10,-22,-10,-22,-20,-56 },
	{ 15, 32, 30, 84, 62, 90, 92,   -10,-10,-22,-10,-22,-20,-56 },
	{ 18, 31, 33, 84, 66, 90, 95,   -10,-10,-22,-10,-22,-20,-56 },
	{ 15, 34, 30, 88, 62, 94, 92,   -10,-10,-22,-10,-22,-20,-56 },
	{ 19, 31, 33, 84, 66, 90, 95,   -10,-10,-22,-10,-22,-20,-56 },
	{ 15, 36, 30, 85, 62, 90, 92,   -10,-10,-22,-10,-22,-20,-56 },
	{ 13, 31, 33, 84, 65, 95, 93,   -10,-10,-22,-10,-22,-20,-56 },
	{ 15, 35, 33, 84, 62, 90, 95,   -10,-10,-22,-10,-22,-20,-56 },
};


// Instaciate the pointer cfPtr to use file
FILE *cfPtr;


/*
From here begins all the methods required for the game
*/

//Generate a random number from 1 to 10 and return that number
int randTen() {
	srand(time(NULL));
	int tenRoll = rand() % 10 + 1;
	return tenRoll;
}

//Generate a random number from 1 to 6 and return that number
int rollDice() {
	srand(time(NULL));
	int diceroll = rand() % 6 + 1;
	return diceroll;
}


//Clears the screen, using system commands
void clrscr()
{
	system("@cls||clear");
}


/*
Prints the logo of the game
snake in ASCII code.
*/
void printLogo()
{
	clrscr();
	printf("*****************************************************************************\n");
	printf("                  Snakes and Ladders - Alexander Souza G00317835\n");
	printf("*****************************************************************************\n");
	printf("\n                    /^\\/^\\");
	printf("\n                  _|__|  O|");
	printf("\n         \\/     /~     \\_/ \\");
	printf("\n          \\____|__________/  \\");
	printf("\n                 \\_______      \\");
	printf("\n                         `\\     \\                 \\");
	printf("\n                           |     |                  \\");
	printf("\n                          /      /                    \\");
	printf("\n                         /     /                       \\");
	printf("\n                       /      /                         \\ \\");
	printf("\n                      /     /                            \\  \\");
	printf("\n                    /     /             _----_            \\   \\");
	printf("\n                   /     /           _-~      ~-_         |   |");
	printf("\n                  (      (        _-~    _--_    ~-_     _/   |");
	printf("\n                   \      ~-____-~    _-~    ~-_    ~-_-~    /");
	printf("\n                     ~-_           _-~          ~-_       _-~");
	printf("\n                        ~--______-~                ~-___-~\n\n");
}



//Prints on the screen the board positions
void printBoard()
{
	clrscr();
	printf(" ---------------------------------------------------------------------         Status ==> %s\n", statusGame);
	printf("| 100  |  99  |  98  |  97  |  96  |  95  |  94  |  93  |  92  |  91  |\n");
	printf("|  81  |  82  |  83  |  84  |  85  |  86  |  87  |  88  |  89  |  90  |\n");
	printf("|  80  |  79  |  78  |  77  |  76  |  75  |  74  |  73  |  72  |  71  |\n");
	printf("|  61  |  62  |  63  |  64  |  65  |  66  |  67  |  68  |  69  |  70  |\n");
	printf("|  60  |  59  |  58  |  57  |  56  |  55  |  54  |  53  |  52  |  51  |\n");
	printf("|  41  |  42  |  43  |  44  |  45  |  46  |  47  |  48  |  49  |  50  |\n");
	printf("|  40  |  39  |  38  |  37  |  36  |  35  |  34  |  33  |  32  |  31  |\n");
	printf("|  21  |  22  |  23  |  24  |  25  |  26  |  27  |  28  |  29  |  30  |\n");
	printf("|  20  |  19  |  18  |  17  |  16  |  15  |  14  |  13  |  12  |  11  |\n");
	printf("|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |  10  |\n");
	printf(" ---------------------------------------------------------------------\n");

	printf("Ladders #%d=> ", choiceLadSna);

	for (i = 0; i < 7; i++) {
		printf(" | %d to %d", locationLaddersSnakes[i], jumpLaddersSnakes[i]);
	}

	printf("\nSnakes  #%d=> ", choiceLadSna);
	for (i; i < 14; i++) {
		printf(" | %d to %d", locationLaddersSnakes[i], (locationLaddersSnakes[i] + jumpLaddersSnakes[i]));
	}
	printf("\n");
}


//Game menu
void PrintMenu() {
	choice = 0;
	while (!choice) {

		printf("Let's go play?\n");
		printf("---------------------------------------------------------------------\n");
		printf("1. New Game\n");
		printf("2. Load Game\n");
		printf("3. Exit \n");
		scanf("%d", &choice);

		if (choice <= 0 || choice > 3) {
			choice = 0;
			printf("Invalid option\n");
		}
	}
}



//Initializes the variables needed to start a new game
void StartNewGame() {
	//Ask for the number of Players
	do
	{
		printf("Please enter the number of Players (2 to 6) => ");
		scanf("%d", &nPlayers);

	} while (!(nPlayers >= 2 && nPlayers <= 6));

	// create the player to get the array
	player = (int*)malloc(sizeof(int) * nPlayers);

	// Populate the variable player to be 0 zero
	for (i = 0; i < nPlayers; i++) {
		*(player + i) = 0;
	}

	// Random 1 to 10 for options board 
	choiceLadSna = randTen();

	// Populate array locationLaddersSnakes and jumpLaddersSnakes pre load values diferents positions
	for (i = 0; i < 14; i++)
	{
		locationLaddersSnakes[i] = valuesLocationLaddersSnakes[choiceLadSna - 1][i];
		jumpLaddersSnakes[i] = valuesJumpLaddersSnakes[choiceLadSna - 1][i];
	}

	// Game Status
	statusGame = "New Game";

	getchar();
}


//Initializes the variables required to load an existing game
void LoadGame() {
	int count;
	int nGame;

	// open the file
	cfPtr = fopen("game.txt", "r");
	int valuePlayer[10000][8];
	count = 0;
	printf("Game - Players   Board  Player1  Player2  Player3  Player4  Player5  Player6");
	printf("\n============================================================================\n");

	// Read the file and load the variable
	while (!feof(cfPtr)) {
		fscanf(cfPtr, "%d %d ", &valuePlayer[count][0], &valuePlayer[count][1]);
		printf("%4d %7d %7d ", count + 1, valuePlayer[count][0], valuePlayer[count][1]);

		for (i = 0; i < valuePlayer[count][0]; i++) {
			fscanf(cfPtr, "%d ", &valuePlayer[count][i + 2]);
			printf("%8d ", valuePlayer[count][i + 2]);
		}
		printf("\n");
		count++;
	}

	//Clouse the file
	fclose(cfPtr);

	//Ask for the number of Game to load
	do
	{
		printf("\nEnter the number Game you would like to load (1 to %d) => ", count);
		scanf("%d", &nGame);
	} while (!(nGame >= 1 && nGame <= count));

	// create the player to get the array
	nPlayers = valuePlayer[nGame - 1][0];
	player = (int*)malloc(sizeof(int) * nPlayers);

	// Populate the variable player
	for (i = 0; i < nPlayers; i++) {
		*(player + i) = valuePlayer[nGame - 1][2 + i];
	}

	// options board 
	choiceLadSna = valuePlayer[nGame - 1][1];

	// Populate array locationLaddersSnakes and jumpLaddersSnakes pre load values diferents positions
	for (i = 0; i < 14; i++)
	{
		locationLaddersSnakes[i] = valuesLocationLaddersSnakes[choiceLadSna - 1][i];
		jumpLaddersSnakes[i] = valuesJumpLaddersSnakes[choiceLadSna - 1][i];
	}

	// Game Status
	statusGame = "Load Game";

	getchar();
}



//Save the game in file 
void SaveGame() {
	// open the file
	cfPtr = fopen("game.txt", "a");

	// Save n. playes and number correponds board
	fprintf(cfPtr, "%d %d ", nPlayers, choiceLadSna);

	for (i = 0; i < nPlayers; i++) {
		fprintf(cfPtr, "%d ", *(player + i));
	}

	// print blank line
	fprintf(cfPtr, "\n");

	statusGame = "Saved";

	//Clouse the file
	fclose(cfPtr);
}


/*
Starts the main method
*/
void main()
{
	while (1) {

		int inGame = 1; // Define value to 1 to stay in Game
		int oldValue;

		printLogo();  //Print the game logo
		PrintMenu(); // Call Menu Game

		// Verif option correpond in PrintMenu()
		switch (choice) {
		case(1) :
			StartNewGame(); //New Game - Setup all variables to star a new game
			break;
		case(2) :

			// open the file
			cfPtr = fopen("game.txt", "r");

			// Verified if the file not exist
			if (cfPtr == NULL) {
				printf("No records are stored, start a new game.\n\n");

				keyEnter = fgetc(stdin);
				StartNewGame(); //New Game - Setup all variables to star a new game
				break;
			}
			else {
				LoadGame(); //Load Game - Setup all variables to load a saved game
				break;
			}

		case(3) :
			return 0; // Exit the Game
		default:
			return 1;
		}

		//Keep in game until InGame == 1
		while (inGame == 1) {

			printBoard(); // Print Board for Game

			//Print number of players on Screen
			for (i = 0; i < nPlayers; i++) {
				printf("\nPlayer %d value is ==> %d", i + 1, *(player + i));
			}

			printf("\n---------------------------------------------------------------------");

			// This loop correpond each player for roll the Dice
			for (i = 0; i < nPlayers; i++) {
				printf("\nPlayer %d  ==> Press Enter to roll the dice", i + 1);

				//Pause waiting press ENTER to roll the dice
				keyEnter = fgetc(stdin);

				//dice = 0;
				//get value for method rollDice (1 to 6)
				dice = rollDice();

				//Storage old value player before set a new value
				oldValue = *(player + i);

				//Add a new value for the player
				*(player + i) += dice;
				printf("Player %d  ==> The dice is ==> %d <== , now your new value is %d\n", i + 1, dice, *(player + i));

				// Verifies that the data value and 6 and if the value of the player and less than 100
				if (*(player + i) < 100 && dice == 6) {
					do {
						//Pause waiting press ENTER to roll the dice
						printf("Player %d  ==> Press Enter to roll the dice again ", i + 1);
						keyEnter = fgetc(stdin);

						//get value for method rollDice (1 to 6)
						dice = rollDice();

						//Storage old value player before set a new value
						oldValue = *(player + i);

						//Add a new value for the player
						*(player + i) += dice;
						printf("Player %d  ==> The dice is ==> %d <== , now your new value is %d\n", i + 1, dice, *(player + i));

						// Verifies player got 100 to win the game
						if (*(player + i) == 100) {
							break; // Exit the loop
						}

						// If player is over 100, the player still in game and back the old value
						if (*(player + i) > 100) {
							*(player + i) = oldValue;
						}

					} while (!(dice < 6) && *(player + i) >= 100); // Loop different value of 6 and greater than 100
				}

				// Checks if the player has reached the value 100
				if (*(player + i) == 100) {

					printf("\n****************************************************************");
					printf("\n**************   Player %d  ==> IS THE WINNER :)  ***************", i + 1);
					printf("\n****************************************************************\n\n");
					i = nPlayers;
					inGame = 0;
				}

				// If player is over 100, the player still in game and back the old value
				else if (*(player + i) > 100) {
					*(player + i) = oldValue;
				}

				//This loop checks if the player has reached a value that correponde the head of the snake or ladder
				for (j = 0; j <= 7; j++) {

					if (*(player + i) == locationLaddersSnakes[j]) {
						oldValue = *(player + i);

						if (jumpLaddersSnakes[j] < 1) {
							*(player + i) += jumpLaddersSnakes[j];
							printf("Player %d  ==> You got a Snake to back from %d to %d\n", i + 1, oldValue, *(player + i));
						}
						else {
							*(player + i) = jumpLaddersSnakes[j];
							printf("Player %d  ==> You got a ladder to jump from %d to %d\n", i + 1, oldValue, *(player + i));
						}
					}
				}
			}

			// Finsh the firt round - this stage the player can start a new game, save or Load a game
			printf("\n---------------------------------------------------------------------");
			printf("\nPress Enter to play      => (N) new game - (S) save - (L) load a game\n");

			// loop waiting press any key
			while (!kbhit()) {}

			int ch;
			ch = getch(); // Storage the key pressed

			// Correpond a new game (n or N)
			if (ch == 78 || ch == 110) // Represents N and n in ASCII table
			{
				clrscr();		//Cleanner Screen
				StartNewGame(); //New Game
			}

			// Correpond save game (s or S)
			if (ch == 83 || ch == 115) // Represents S and s in ASCII table
			{
				SaveGame(); //Save the Game
			}

			// Correpond load game (l or L)
			if (ch == 76 || ch == 108) // Represents L and l in ASCII table
			{
				clrscr();	//Cleanner Screen
				LoadGame(); //Load the Game
			}
		}
	}
} //End main
