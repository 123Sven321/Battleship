#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define EMPTY 0
#define PLAYING 10
#define MISS 10

int stillPlaying = 0;

int field[2][100];

char letters[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };

int shipHitCount[2][5] = { {4, 3, 3, 2, 6}, {4, 3, 3, 2, 6} };




void printWinMessage(int winner) {

	if (winner == 1) {

		printf("  _____  _                      __    __          ___           \n");
		printf(" |  __ \\| |                    /_ |   \\ \\        / (_)          \n");
		printf(" | |__) | | __ _ _   _  ___ _ __| |    \\ \\  /\\  / / _ _ __  ___ \n");
		printf(" |  ___/| |/ _` | | | |/ _ | '__| |     \\ \\/  \\/ / | | '_ \\/ __|\n");
		printf(" | |    | | (_| | |_| |  __| |  | |      \\  /\\  /  | | | | \\__ \\\n");
		printf(" |_|    |_|\\__,_|\\__, |\\___|_|  |_|       \\/  \\/   |_|_| |_|___/\n");
		printf("                  __/ |                                         \n");
		printf("                 |___/                                          \n");
		
	}
	else {

		printf("  _____  _                     ___     __          ___           \n");
		printf(" |  __ \\| |                   |__ \\    \\ \\        / (_)          \n");
		printf(" | |__) | | __ _ _   _  ___ _ __ ) |    \\ \\  /\\  / / _ _ __  ___ \n");
		printf(" |  ___/| |/ _` | | | |/ _ | '__/ /      \\ \\/  \\/ / | | '_ \\/ __|\n");
		printf(" | |    | | (_| | |_| |  __| | / /_       \\  /\\  /  | | | | \\__ \\\n");
		printf(" |_|    |_|\\__,_|\\__, |\\___|_||____|       \\/  \\/   |_|_| |_|___/\n");
		printf("                  __/ |                                          \n");
		printf("                 |___/                                           \n");
	
	}
}

void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {

	}
}

void clearScreen(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void genField(int fieldOf) {

	if(stillPlaying == PLAYING){

		printf("Format: y x   E.g. G 3 or G3\n");

	}else{

		printf("Format: ship1 h G 3\n");
		printf("          ^   ^ ^ ^\n");
		printf("          |   | | |\n");
		printf("      shipID  | | |\n");
		printf("             alignment(h=horizontally, v=vertically)\n");
		printf("                | |\n");
		printf("                y x\n");

	}
	
	printf("\n  1 2 3 4 5 6 7 8 9 10");

	//loop through positions of field array
	for (int i = 0; i < 100; i++) {

		//print letters on beginning of new line
		if (i % 10 == 0) {
			printf("\n");
			printf("%c ", letters[(i + 1) / 10]);
			
		}

		
		if (field[fieldOf][i] > 0 && field[fieldOf][i] <= 5) {
			//when entering print '#', when playing print '.' for placed ships
			if (stillPlaying != PLAYING) {
				printf("# ");
			}
			else {
				printf(". ");
			}
		}
		else if (field[fieldOf][i] == EMPTY) {
			//print '.' for empty Fields
			printf(". ");
		}
		else if (field[fieldOf][i] == MISS) {
			//print 'x' for missed shots
			printf("x ");
		}
		else if (field[fieldOf][i] < 0 && field[fieldOf][i] >= -5) {
			//print '*' for hits
			printf("* ");
		}
		else if (field[fieldOf][i] <= -10) {
			//print 'O' for destroyed ships
			printf("O ");
		}

	}

	printf("\n\n");

	//print remaining ship info
	for (int i = 0; i < 3; i++) {
		//loop through all ships
		for (int j = 0; j < 5; j++) {
			//if ship is still available
			if (shipHitCount[fieldOf][j] != 0) {
				if (j == 0) {
					if (i == 0) {
						printf("ship1        ");
					}
					else if (i == 1) {
						printf("* * * *      ");
					}
					else if (i == 2) {
						printf("             ");
					}
				}
				else if (j == 1) {
					if (i == 0) {
						printf("ship2        ");
					}
					else if (i == 1) {
						printf("* * *        ");
					}
					else if (i == 2) {
						printf("             ");
					}
				}
				else if (j == 2) {
					if (i == 0) {
						printf("ship3        ");
					}
					else if (i == 1) {
						printf("* * *        ");
					}
					else if (i == 2) {
						printf("             ");
					}
				}
				else if (j == 3) {
					if (i == 0) {
						printf("ship4        ");
					}
					else if (i == 1) {
						printf("* *          ");
					}
					else if (i == 2) {
						printf("             ");
					}
				}
				else if (j == 4) {
					if (i == 0) {
						printf("ship5        ");
					}
					else if (i == 1) {
						printf("* * *        ");
					}
					else if (i == 2) {
						printf("  * * *      ");
					}
				}
			}
		}
		printf("\n");
	}

}

void enterShips(int player) {

	//loop to enter all five ships
	for (int i = 5; i >= 1; i--) {

		char ship[6];
		char align;
		char posYchar;

		int posX;
		int posY;
		int shipNum;
		int shipElCount;

		printf("\n%d ships remaining\n", i);

		//get ship information
		int returnVal = scanf("%5s %c %c %d", ship, &align, &posYchar, &posX);
		clearScreen();

		//make input fit the format for if statements
		for (int i = 0; i < 4; i++) {
			ship[i] = tolower(ship[i]);
		}
		align = tolower(align);
		posYchar = toupper(posYchar);

		clearInputBuffer();

		//check for coorect syntax
		if (returnVal == 4) {
			//check for shipID to be correct
			if (strcmp(ship, "ship1") == 0 || strcmp(ship, "ship2") == 0 || strcmp(ship, "ship3") == 0 || strcmp(ship, "ship4") == 0 || strcmp(ship, "ship5") == 0) {
				//check for align value to be correct
				if (align == 'h' || align == 'v') {
					//check for y coordinate to be correct
					if (posYchar == 'A' || posYchar == 'B' || posYchar == 'C' || posYchar == 'D' || posYchar == 'E' || posYchar == 'F' || posYchar == 'G' || posYchar == 'H' || posYchar == 'I' || posYchar == 'J') {
						//check for x coordinate to be correct
						if (posX > 0 && posX <= 10) {
		
							//translate y to number
							switch (posYchar) {
							case 'A':
								posY = 0;
								break;
							case 'B':
								posY = 10;
								break;
							case 'C':
								posY = 20;
								break;
							case 'D':
								posY = 30;
								break;
							case 'E':
								posY = 40;
								break;
							case 'F':
								posY = 50;
								break;
							case 'G':
								posY = 60;
								break;
							case 'H':
								posY = 70;
								break;
							case 'I':
								posY = 80;
								break;
							case 'J':
								posY = 90;
								break;
							}

							//get ship and save element count of ship
							switch (ship[4]) {
							case '1':
								shipNum = 0;
								shipElCount = 4;
								break;
							case '2':
								shipNum = 1;
								shipElCount = 3;
								break;
							case '3':
								shipNum = 2;
								shipElCount = 3;
								break;
							case '4':
								shipNum = 3;
								shipElCount = 2;
								break;
							case '5':
								shipNum = 4;
								shipElCount = 3;
								break;
							}

							//when ship is already placed
							if (shipHitCount[player][shipNum] == 0) {
								printf("Ship is already placed!\n");
								i++;
							}
							else {

								if (align == 'h') {
									int overlap = false;
									//check for overlap
									//loop through elements to be placed and check for existing ship on position
									for (int i_el = 0; i_el < 6; i_el++) {
										if (i_el < shipElCount) {
											int newX = posX + i_el;
											if (newX > 10) {
												overlap = true;
												printf("Ship is out of matrix\n\n");
												i++;
												break;
											}
											else {
												if (field[player][newX + posY - 1] != 0) {
													overlap = true;
													printf("Ships are overlapping\n\n");
													i++;
													break;
												}
											}
										}
									}
									//check noose of ship5
									if (!overlap && shipNum == 4) {
										for (int i_noose = 1; i_noose <= 3; i_noose++) {
											int newX = posX + i_noose;
											if (newX > 10 || posY + 10 > 90) {
												overlap = true;
												printf("Ship is out of matrix\n\n");
												i++;
												break;
											}
											else {
												if (field[player][newX + posY + 10 - 1] != 0) {
													overlap = true;
													printf("Ships are overlapping\n\n");
													i++;
													break;
												}
											}
										}
									}

									//enter ship when no overlap
									if (!overlap) {
										for (int i_el = 0; i_el < 6; i_el++) {
											if (i_el < shipElCount) {
												int newX = posX + i_el;
												field[player][newX + posY - 1] = shipNum + 1;
												//set hit count 0 to simulate ship getting destroyed so it wont appear on remaining ships info
												shipHitCount[player][shipNum] = 0;
											}
										}
										if (shipNum == 4) {
											//enter noose of ship5
											for (int i_noose = 1; i_noose <= 3; i_noose++) {
												int newX = posX + i_noose;
												field[player][newX + posY + 10 - 1] = shipNum + 1;
											}
										}
									}
								}
								//when vertical
								else {
									int overlap = false;
									//check for overlap
									for (int i_el = 0; i_el < 6; i_el++) {
										if (i_el < shipElCount) {
											int newY = posY + i_el * 10;
											if (newY > 100) {
												overlap = true;
												printf("Ship is out of matrix\n\n");
												i_el = 6;
												i++;
											}
											else {
												if (field[player][newY + posX - 1] != 0) {
													overlap = true;
													printf("Ships are overlapping\n\n");
													i_el = 6;
													i++;
												}
											}
										}
									}
									//check for noose of ship5
									if (!overlap && shipNum == 4) {
										for (int i_noose = 1; i_noose <= 3; i_noose++) {
											int newY = posY + i_noose * 10;
											if (newY > 90 || posX - 1 < 1) {
												overlap = true;
												printf("Ship is out of range\n\n");
												i_noose = 4;
												i++;
											}
											else {
												if (field[player][newY + posX - 1 - 1] != 0) {
													overlap = true;
													printf("Ships are overlapping\n\n");
													i_noose = 4;
													i++;
												}
											}
										}
									}
									//save coordinates in field array
									if (!overlap) {
										for (int i_el = 0; i_el < 6; i_el++) {
											if (i_el < shipElCount) {
												int newY = posY + i_el * 10;
												field[player][newY + posX - 1] = shipNum + 1;
												//set hit count 0 to simulate ship getting destroyed so it wont appear on remaining ships info
												shipHitCount[player][shipNum] = 0;
											}
										}
										if (shipNum == 4) {
											//coordinates for noose of ship5
											for (int i_noose = 1; i_noose <= 3; i_noose++) {
												int newY = posY + i_noose * 10;
												field[player][newY + posX - 1 - 1] = shipNum + 1;

											}
										}
									}
								}
							}
						}
						else {
							printf("Something went wrong, probably the x coordinate is wrong or not in range. --- Range: 1-10\n\n");
							i++;
						}
					}
					else {
						printf("Something went wrong, probably the y coordinate is wrong or not in range. --- Range: A-J\n\n");
						i++;
					}
				}
				else {
					printf("Something went wrong, probably the wrong align value. --- E.g. h=horizontal, v=vertical\n\n");
					i++;
				}
			}
			else {
				printf("Something went wrong, probably the wrong shipID. --- E.g. ship1, ship2, ship3, ...\n\n");
				i++;
			}
		}
		else {
			printf("Something went wrong, probably the wrong syntax. --- E.g. ship4 v E 2\n\n");
			i++;
		}

		genField(player);

	}
	clearScreen();

	//initialize array contents
	for (int i = 0; i < 2; i++) {
		shipHitCount[i][0] = 4;
		shipHitCount[i][1] = 3;
		shipHitCount[i][2] = 3;
		shipHitCount[i][3] = 2;
		shipHitCount[i][4] = 6;
	}
}

int hitCheck(int fieldOf) {

	while(true){

		char posYchar;
		int x;
		int y;
	
		printf("Enter your guess\n");
		genField(fieldOf);

		if (fieldOf == 0) {
			printf("\nPlayer 2\n");
		}
		else {
			printf("\nPlayer 1\n");
		}
	
		//get hit location
		int returnVal = scanf(" %c %d", &posYchar, &x);
		clearScreen();

		posYchar = toupper(posYchar);

		clearInputBuffer();

		//check for correct syntax
		if (returnVal == 2) {
			//check for correct y coordinate
			if (posYchar == 'A' || posYchar == 'B' || posYchar == 'C' || posYchar == 'D' || posYchar == 'E' || posYchar == 'F' || posYchar == 'G' || posYchar == 'H' || posYchar == 'I' || posYchar == 'J') {
				//check for correct x coordinate
				if (x > 0 && x <= 10) {

					//translate to numbers
					switch (posYchar) {
					case 'A':
						y = 0;
						break;
					case 'B':
						y = 10;
						break;
					case 'C':
						y = 20;
						break;
					case 'D':
						y = 30;
						break;
					case 'E':
						y = 40;
						break;
					case 'F':
						y = 50;
						break;
					case 'G':
						y = 60;
						break;
					case 'H':
						y = 70;
						break;
					case 'I':
						y = 80;
						break;
					case 'J':
						y = 90;
						break;
					}

					//if hit on intact ship element
					if (field[fieldOf][x + y - 1] > 0 && field[fieldOf][x + y - 1] <= 5) {

						//save shipID from hit position, set to minus to indicate element being hit
						int valHitPos = field[fieldOf][x + y - 1];
						field[fieldOf][x + y - 1] = field[fieldOf][x + y - 1] * (-1);
						shipHitCount[fieldOf][valHitPos - 1]--;

						//on ship destroyed, mark field as so by multiplying by 10
						if (shipHitCount[fieldOf][valHitPos - 1] == 0) {
							for (int i = 0; i < 100; i++) {
								if (field[fieldOf][i] == valHitPos * (-1)) {
									field[fieldOf][i] = field[fieldOf][i] * 10;
								}
							}
						}

						clearScreen();

						//check if game ended and return victor
						if (shipHitCount[fieldOf][0] == 0 && shipHitCount[fieldOf][1] == 0 && shipHitCount[fieldOf][2] == 0 && shipHitCount[fieldOf][3] == 0 && shipHitCount[fieldOf][4] == 0) {
							if (fieldOf == 1) {
								return 1;
							}
							else {
								return 2;
							}
						}

					}
					//if hit on empty field
					else if (field[fieldOf][x + y - 1] == 0) {

						clearScreen();
						//mark position as missed shot
						field[fieldOf][x + y - 1] = MISS;
						
						return PLAYING;

					}
					//if field already hit 
					else {
						printf("Position already hit\n\n");
					}
				}
				else {
					clearScreen();
					printf("Something went wrong, probably the x coordinate is wrong or out of range. --- Range: 1-10\n\n");
				}
			}
			else {
				clearScreen();
				printf("Something went wrong, probably the y coordinate is wrong or out of range. --- Range: A-J\n\n");
			}
		}
		else {
			clearScreen();
			printf("Something went wrong, probably the syntax is wrong. --- E.g. H 3\n\n");
		}
	}

	
	
}

int main(int* argc, char* argv[]) {
	
	clearScreen();

	printf("Please enter your ships: \nPlayer 1\n\n");
	
	genField(0);
	enterShips(0);

	printf("Please enter your ships: \nPlayer 2\n\n");

	genField(1);
	enterShips(1);


	printf("Lets go!\n\n");

	stillPlaying = PLAYING;
	int whichPlayer = 0;

	while (stillPlaying == PLAYING) {

		//switch player after missed shot
		if (whichPlayer % 2 == 0) {
			
			stillPlaying = hitCheck(1);
		}
		else {
		
			stillPlaying = hitCheck(0);
		}

		whichPlayer++;

	}

	printWinMessage(stillPlaying);


	printf("Press Enter to exit.");
	getchar();
	
}


