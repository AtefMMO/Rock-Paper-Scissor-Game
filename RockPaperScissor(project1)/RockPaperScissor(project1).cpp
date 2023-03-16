

#include <iostream>
#include <cstdlib>
#include <array>
#include <string>
#include <windows.h>
using namespace std;
enum  enChoice //enum to add the three main player/pc choices
{
	enRock=1,enPaper=2,enScissor=3
};
int checkNumberBetween(int from, int to, string message,string warnning) {//check if the number you inputed is between the parameters you aseked for
	int number = 0;
	cout << message << endl;
	cin >> number;
	do {
		if (number < from || number > to) {
			cout << warnning << endl;
			cin >> number;
		}
	} while (number < from || number > to);
	return number;
}
int randomNumber(int from ,int to) {//returns a random number between two numbers
	int randomNumber = rand() % (to - from + 1) + from;
	return randomNumber;
}
void arrayFill(int array[10], int& arrayLength,int number) {//function that fills an array by giving it the array it's length and the number you want to add to it
	array[arrayLength] = number;
	arrayLength++;
}
int arraySum(int array[10], int arrayLength) {
	int arraySum = 0;
	for (int i = 0; i < arrayLength; i++) {
		arraySum += array[i];
	}
	return arraySum;
}
int gameJudge(int sumWin, int sumLoose, int sumDraw) {// function takes the sum of array of every category and returns indication about the largest sum
	int win = 1;
	int loose = 2;
	int draw = 3;
	if (sumWin > sumLoose) {
		return win;
	}
	else if (sumWin < sumLoose) {
		return loose;
	}
	else if (sumDraw > sumWin && sumDraw > sumLoose) {
		if (sumWin > sumLoose) {
			return win;
		}
		else if (sumWin < sumLoose) {
			return loose;
		}
		else {
			return draw;
		}
	}
	else return draw;
}
void roundData(int arrayWin[10], int arrayLoose[10], int arrayDraw[10], int& arrayWinLength, int& arrayLooseLength, int& arrayDrawLength, int win,int loose,int draw) {
	//fill each array with data that indicates the state of the round (win/draw/loose) by 1 in winning and 0 in loosing
	arrayFill(arrayWin, arrayWinLength, win);
	arrayFill(arrayLoose, arrayLooseLength, loose);
	arrayFill(arrayDraw, arrayDrawLength, draw);
}
int computerChoice() {//computer choice function
	int computerChoice = randomNumber(1, 3);
	return computerChoice;
}
void consoleColor(char color) {
	switch (color) {
	case 'g':system("color 20");
		break;
	case 'r':system("color 40");
		break;
	case 'y':system("color 60");
		break;
	}
}
int choiceCompare(enChoice player, enChoice computer) {//function that takes the human/pc choices from the choice function and deciding the winner
	//1 for winning , 2 for loosing , 3 for drawing
	int win = 1;
	int loose = 2;
	int draw = 3;
	if (player == enChoice::enPaper && computer == enChoice::enRock || player == enChoice::enRock && computer == enChoice::enScissor || player == enChoice::enScissor && computer == enChoice::enPaper) {
		return win;
	}
	else if (computer == enChoice::enPaper && player == enChoice::enRock || computer == enChoice::enRock && player == enChoice::enScissor || computer == enChoice::enScissor && player == enChoice::enPaper) {
		return loose;
	}
	else {
		return draw;
	}
}
void printGameOverScreen(int gameRounds, int wonRounds, int lostRounds, int drawRounds) {
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << "           ++++++++++++++++Game Over++++++++++++++++\n";
	cout << endl;
	cout << "-----------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl;
	cout << "Game Rounds : " << gameRounds;
	cout << endl;
	cout << "Player won : " << wonRounds;
	cout << endl;
	cout << "Computer won : " << lostRounds;
	cout << endl;
	cout << "Draw rounds : " << drawRounds;
	cout << endl;
}
int RoundsCounter() {//Asks the player how many rounds he wants to play
	int roundCounter=0;
	roundCounter= checkNumberBetween(1,10, "please enter how many rounds you want (1-->10) : ", "The number you entered is out of poundries please enter it again \n");
	return roundCounter;
}
enChoice Choice(int choice) {//gets the number the player inputed and determine that number refers to which choice
	switch (choice) {
	case 1: return enChoice::enRock;
		break;
	case 2: return enChoice::enPaper;
		break;
	case 3: return enChoice::enScissor;
		break;
	}
}
void clearScreen() {
	system("cls");
	system("color 0");
}
void roundPlay(int arrayWin[10],int arrayLoose[10],int arrayDraw[10], int& arrayWinLength ,int& arrayLooseLength ,int& arrayDrawLength ) {
	//the round activation from asking the player about his choice untill the end of the round 
	int PlayerChoice,ComputerChoice;
	int roundCounter = RoundsCounter();
	cout << endl;
	for (int i = 1; i <= roundCounter; i++) {
		PlayerChoice = checkNumberBetween(1, 3, "your choice \n[1]Rock  , [2]Paper , [3]Scissor\n", "The number you entered is out of poundries please enter it again \n");
		ComputerChoice = computerChoice();
		if (choiceCompare(Choice(PlayerChoice), Choice(ComputerChoice)) == 1) { //the player win
			consoleColor('g'); //green color   ,  sys("color xy") x is for background and y for text
			roundData(arrayWin, arrayLoose, arrayDraw, arrayWinLength, arrayLooseLength, arrayDrawLength, 1, 0, 0);
		}
		else if (choiceCompare(Choice(PlayerChoice), Choice(ComputerChoice)) == 2) {//the computer win
			cout << "\a";
			consoleColor('r'); //red color
			roundData(arrayWin, arrayLoose, arrayDraw, arrayWinLength, arrayLooseLength, arrayDrawLength, 0, 1, 0);
		}else{
			consoleColor('y'); //yellow color
			roundData(arrayWin, arrayLoose, arrayDraw, arrayWinLength, arrayLooseLength, arrayDrawLength, 0, 0, 1);
		}
	}
}
void printResult(int result) {
	if (result == 1) {
		consoleColor('g');
		cout << "Final winner : Player\n";
		cout << "-----------------------------------------------------------------" << endl;
	}
	else if (result == 2) {
		consoleColor('r');
		cout << "Final winner : Computer\n";
		cout << "-----------------------------------------------------------------" << endl;
	}
	else {
		consoleColor('y');
		cout << "Game ended in a draw\n";
		cout << "-----------------------------------------------------------------" << endl;
	}
}
bool playAgain() {
	char playAgain;
	cout << "Do you want to play again ? (y/n)" << endl;
	cin >> playAgain;
	if (playAgain == 'y' || playAgain == 'Y') {
		return true;
	}
	else {
		return false;
	}
}
void ExecuteGame() {//game excution function
	int arrayWin[10], arrayLoose[10], arrayDraw[10];
	int arrayWinLength = 0, arrayLooseLength = 0, arrayDrawLength = 0; //we must declare there value in order for the arrays to start at zero
    cout << "Welcome to the game.\n";
	roundPlay(arrayWin,arrayLoose, arrayDraw, arrayWinLength, arrayLooseLength, arrayDrawLength);
	int gameRounds = arraySum(arrayWin, arrayWinLength) + arraySum(arrayLoose, arrayLooseLength) + arraySum(arrayDraw, arrayDrawLength);
	int wonRounds = arraySum(arrayWin, arrayWinLength);
	int lostRounds = arraySum(arrayLoose, arrayLooseLength);
	int drawRounds = arraySum(arrayDraw, arrayDrawLength);
	int result = gameJudge(wonRounds, lostRounds, drawRounds);
	printGameOverScreen(gameRounds, wonRounds, lostRounds, drawRounds);
	printResult(result);
	if (playAgain()) {
		clearScreen();
		ExecuteGame();
	}
}
int main()
	{
	srand((unsigned)time(NULL));
	ExecuteGame();
	return 0;
	}