// ==============================================================================
// Project: Rock-Paper-Scissors (Optimized Edition)
// Author: Mohamed Ashraf Ahmed Faraj
// 
// [ARCHITECTURE & PERFORMANCE HIGHLIGHTS]:
// 1. Time Complexity: O(1) for all game logic (Zero if/switch conditions).
// 2. Memory Management: Heavy use of 'static const' to store arrays in the 
//    .rodata segment, preventing reallocation during runtime.
// 3. CPU Optimization: Small data types (enums, shorts) are passed by Value 
//    to avoid the 8-byte pointer overhead and dereferencing cost of References.
// 4. Robustness: Full Input Validation to prevent infinite loops and crashes.
// ==============================================================================

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

//enum size is usaully 4 bytes same( int ) data type
enum enGameItem { Stone = 0, Paper = 1, Scissor = 2 };

enum enWhoWin { Draw = 0, UserWin = 1, ComputerWin = 2 };

struct RoundInfo
{
	unsigned short CurrentRound = 1;
	enGameItem UserChoice = ::Stone;
	enGameItem ComputerChoice = ::Stone;
	enWhoWin RoundWinner = ::Draw;

};

struct stGameInfo {
	unsigned short TotalRounds = 0;
	unsigned short UserWinCount = 0;
	unsigned short ComputerWinCount = 0;
	unsigned short DrawCount = 0;
	enWhoWin GameWinner = ::Draw;
};

// [SECURITY & ROBUSTNESS]: Prevents the program from crashing if the user enters a character instead of a number
void InputValidation() {
	if (cin.fail()) {  //Check if the previous input failed (e.g., wrong data type)

		cin.clear();  //Clear the error flags to allow future input operations

	}
	cin.ignore(numeric_limits< streamsize >::max(), '\n'); // Discard remaining invalid characters in the buffer
}

// Returns true if the user wants to play another game, otherwise false.
bool ShouldContinue() {
	char Response = 'F';
	cout << "\nDo you want to play again? (Y/N): ";
	cin >> Response;
	return (Response == 'y' || Response == 'Y');
}

// Returns the terminal to its default state by prompting ("color 0F") 
// to set the background to black and ("cls") to clear all text
void ReSetScreenColor() {
	system("color 0F");
	system("cls");
}

//Genrate Random Number By Calculate Number Of Seconds From 1970 
short RandomNumber(short From, short To)
{
	short randNum = rand() % (To - From + 1) + From; // [TYPE CHOICE]: Using 'short' instead of 'unsigned' to support 
	// potential negative ranges in future game updates
	return randNum;
}

// Read total Number by send  Message  By Referance To Optimize Memory ( send address instead object )
//const protect Message From Updat in Run time and Make temp Address
unsigned short ReadTotalRounds(const string& Message)
{
	//make MAX_ROUNDS for protect Crash Data Over Flow  
	//By less than The Number unsigned short can contain it  65535
	// Function InputValidation() If Number Over Flow Resat To max Size Data can contain
	const unsigned short MAX_ROUNDS = 65534;
	unsigned short TotalRound = 0;

	do {

		cout << Message;

		cin >> TotalRound;
		// Prevents crashes from non-numeric input or data overflow
		InputValidation();

	} while (!(TotalRound > 0 && TotalRound <= MAX_ROUNDS));

	return TotalRound;
}
// Read Player Choice by send  Message  By Referance To Optimize Memory ( send address instead object )
//const protect Message From Updat in Run time and Make temp Address
enGameItem ReadPlayerChoice(const string& Message) {
	unsigned short Choice = 0;

	do {

		cout << "\n==========================================================\n\n";
		cout << Message << endl;
		cout << "\n===========================================================\n\n";
		cout << "Your Choice [1 to 3] : ";
		cin >> Choice;
		// Prevents crashes from non-numeric input or data overflow
		InputValidation();

	} while (!(Choice >= 1 && Choice <= 3));

	// [INDEX MAPPING]: Subtracting 1 to convert user-friendly input (1-3) 
	return (enGameItem)(Choice - 1); // to zero-based indexing (0-2) for internal array/logic compatibility.
}
//We Get Computer Choice By Using function Rondom in Range(0 : 2)
enGameItem GetComputerChoice() {


	return  (enGameItem)RandomNumber(0, 2);
}

//this function more optimize this Game we store Row and Column same Order
// and write all propabilty can happen and the diagonal Equal Draw
//and upper Triangle The diagonal different than  Lower Triangle
enWhoWin WhoWin(enGameItem PlayerChoice, enGameItem ComputerChoice)
{
	// [MEMORY & SAFETY]: 
	// 'const' prevents any accidental modification of the matrix during runtime.
	// 'static' avoids the overhead of repetitive creation of winMatrix in the Stack every call
	static const enWhoWin winMatrix[3][3] =
	{
		/* Computer Choice  For Column  (0) = Stone : (1) = Paper : (2) = Scissor */

		  { Draw ,        ComputerWin,     UserWin    },// User Choice (0)=Stone

		  { UserWin ,     Draw,            ComputerWin},// User Choice (1)=Paper

		  { ComputerWin , UserWin,         Draw       }// User Choice (2)=Scissor


	};

	//Direct memory access for O(1) Time Complexity
	return winMatrix[PlayerChoice][ComputerChoice];

}

string PrintGameItem(enGameItem Choice)
{
	// 'const' prevents any accidental modification of the array during runtime.
	// 'static' avoids the overhead of repetitive creation of 'items' array in the Stack every call.
	static const string items[3] = { "Stone", "Paper", "Scissor" };

	return items[Choice];

}

string PrintWhoWin(enWhoWin Winner)
{
	// 'const' prevents any accidental modification of the array during runtime.
	// 'static' avoids the overhead of repetitive creation of 'winners' array in the Stack every call.
	static const string winners[3] = { "Draw", "User Winner", "Computer Winner" };

	return winners[Winner];

}

// take Who Winner and Print color on Terminal 
void SetScreenColor(enWhoWin Winner) {
	//Why use Static To don't repeat Creation in Stack (Minimizes CPU utilization) 
	// 'const' prevents any accidental modification of the array during runtime.
	//char* This is Creates Array Of Pointer Data Type Char 
	// and Pointer Index 0 pointer to First Element in (color 6F)= "c" 
	// and make Loop To Execute This Prompt To recreacheshe d\0 to stop
	// The Benefit is Less memory usage By Object in string 
	static const char* colors[3] = { "color 6F", "color 2F", "color 4F" };

	system(colors[Winner]);

	if (Winner == enWhoWin::ComputerWin) {
		cout << "\a";
	}
}

void DisplayTitleRound(unsigned short CurrentRound) {
	//Updata The UI 
	cout << "============================[" << CurrentRound << "]============================\n\n";
}

void DisplayCurrentRound(unsigned short CurrentRound) {
	cout << "Round [" << CurrentRound << "] Begins :\n";

}

void DisplayRoundInfo(enGameItem UserChice, enGameItem ComputerChoice, enWhoWin Winner) {

	cout << "\nUser Choice is :[" << PrintGameItem(UserChice) << "]" << endl;
	cout << "Computer Choice is :[" << PrintGameItem(ComputerChoice) << "]" << endl;
	cout << "The  Winner is :[" << PrintWhoWin(Winner) << "]\n" << endl;
}

void UpdateGameResults(enWhoWin Winner, stGameInfo& GameResults) {

	if (Winner == enWhoWin::UserWin) {
		GameResults.UserWinCount++;
	}
	else if (Winner == enWhoWin::ComputerWin) {
		GameResults.ComputerWinCount++;
	}
	else
	{
		GameResults.DrawCount++;
	}

}

enWhoWin WhoWinner(stGameInfo& Winner) {
	if (Winner.ComputerWinCount == Winner.UserWinCount)
	{
		return enWhoWin::Draw;
	}
	else if (Winner.ComputerWinCount < Winner.UserWinCount)
	{
		return enWhoWin::UserWin;
	}
	else
	{
		return enWhoWin::ComputerWin;
	}
}

string Tabs(unsigned short Number) {

	string T = "";
	for (int i = 0; i < Number; i++) {
		T += "\t";
	}
	return T;
}

void DisplayTitleGameInfo() {


	cout << Tabs(3) << "===========================================================\n\n\n";
	cout << Tabs(5) << "    +++Game Over+++\n\n";
	cout << Tabs(3) << "===========================================================\n\n";


}

void DisplayFinalGameResults(stGameInfo& GameResults) {

	DisplayTitleGameInfo();
	cout << Tabs(3) << "Game Rounds        : " << GameResults.TotalRounds << endl;
	cout << Tabs(3) << "User Winning Times : " << GameResults.UserWinCount << endl;
	cout << Tabs(3) << "Computer Win Times : " << GameResults.ComputerWinCount << endl;
	cout << Tabs(3) << "Draw Times         : " << (GameResults.DrawCount) << endl;
	cout << Tabs(3) << "Final Winner       : " << PrintWhoWin(GameResults.GameWinner) << endl;

	cout << Tabs(3) << "===========================================================\n";

	SetScreenColor(GameResults.GameWinner);

}

void RunRound(stGameInfo& GameResults) {
	RoundInfo Info;

	for (Info.CurrentRound = 1; Info.CurrentRound <= GameResults.TotalRounds; Info.CurrentRound++) {

		DisplayTitleRound(Info.CurrentRound);
		DisplayCurrentRound(Info.CurrentRound);
		Info.UserChoice = ReadPlayerChoice("[1]: Stone, [2]: Paper, [3]: Scissor");

		Info.ComputerChoice = GetComputerChoice();
		Info.RoundWinner = WhoWin(Info.UserChoice, Info.ComputerChoice);

		DisplayRoundInfo(Info.UserChoice, Info.ComputerChoice, Info.RoundWinner);
		SetScreenColor(Info.RoundWinner);
		UpdateGameResults(Info.RoundWinner, GameResults);
	}
}

void RunGame() {

	do
	{
		ReSetScreenColor();

		stGameInfo GameResults;

		GameResults.TotalRounds = ReadTotalRounds("How many rounds do you want to play Betwenn [ 1 : 65534 ]?\n");

		RunRound(GameResults);

		GameResults.GameWinner = WhoWinner(GameResults);

		DisplayFinalGameResults(GameResults);

	} while (ShouldContinue());
}

int main() {
	srand((unsigned)time(NULL));

	RunGame();

}
