#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameItem{Stone = 1,Paper = 2,Scissor = 3};

enum enWhoWin{UserWin=1,ComputerWin = 2,Draw = 3};

struct RoundInfo
{
	unsigned short CurrentRound = 1;
	enGameItem UserChoice;
	enGameItem ComputerChoice;
	enWhoWin RoundWinner;
};

struct stGameInfo {
	unsigned short TotalRounds = 0;
	unsigned short UserWinCount = 0;
	unsigned short ComputerWinCount = 0;
	unsigned short DrawCount = 0;
	enWhoWin GameWinner;
};

bool ShouldContinue() {
	char Response;
	cout << "\nDo you want to play again? (Y/N): ";
	cin >> Response;
	return (Response == 'y' || Response == 'Y');
}

void ReSetScreenColor() {
	system("color 0F");
	system("cls");
}

short RandomNumber(short From, short To)
{
	short randNum = rand() % (To - From + 1) + From;
	return randNum;
}

unsigned short ReadTotalRounds(string Message) {
	unsigned short TotalRound = 0;

	do {
		
		cout << Message;
		
		cin >> TotalRound;

	} while (!(TotalRound > 0));

	return TotalRound;
}

enGameItem ReadPlayerChoice(string Message) {
	unsigned short Choice = 0;

	do {
	
		cout << "\n_________________________________________________________\n";
		cout << Message << endl;
		cout << "_________________________________________________________\n";
		cout << "Your Choice [1 to 3]: ";

		cin >> Choice;

	} while (!(Choice >= 1 && Choice <= 3));

	return (enGameItem)Choice;
}

enGameItem GetComputerChoice() {
	

	return  (enGameItem)RandomNumber(1, 3);
}

enWhoWin WhoWin(enGameItem& PlayerChoice, enGameItem& ComputerChoice) {
	if (PlayerChoice == ComputerChoice)
	{
		return enWhoWin::Draw;
	}

	if (
		(PlayerChoice == enGameItem::Stone && ComputerChoice== enGameItem::Scissor) ||
		(PlayerChoice == enGameItem::Paper && ComputerChoice == enGameItem::Stone) ||
		(PlayerChoice == enGameItem::Scissor && ComputerChoice == enGameItem::Paper)
		)
	{
		return enWhoWin::UserWin;
	}
	else
	{
		return enWhoWin::ComputerWin;
	}

}

string PrintGameItem(enGameItem& Choice)
{
	switch (Choice)
	{
	case enGameItem::Stone: return "Stone";
	case enGameItem::Paper: return "Paper";
	case enGameItem::Scissor: return "Scissor";
	default:return "Unknown";
	}
}

string PrintWhoWin(enWhoWin& Winner) {
	switch (Winner)
	{
	case enWhoWin::UserWin: return "User Winner";
	case enWhoWin::ComputerWin: return "Computer Winner";
	case enWhoWin::Draw: return "Draw";
	default:return "Unknown";
	}

}

void SetScreenColor(enWhoWin& Winner) {
	switch (Winner) {
	case enWhoWin::UserWin:
		system("color 2F"); 
		break;
	case enWhoWin::ComputerWin:
		system("color 4F"); 
		cout << "\a";      
		break;
	case enWhoWin::Draw:
		system("color 6F");
		break;
	default:
		system("color 07");
		break;
	}
}

void DisplayCurrentRound(unsigned short& CurrentRound) {
	cout << "Round [" << CurrentRound << "] Begins :\n\n";

}
 
void DisplayTitleRound(unsigned short& CurrentRound) {

	cout << "___________________[" << CurrentRound << "]___________________\n\n";
}

void DisplayRoundInfo(enGameItem& UserChice, enGameItem& ComputerChoice,enWhoWin& Winner) {

	cout << "User Choice is :[" << PrintGameItem(UserChice) << "]" << endl;
	cout << "Computer Choice is :[" << PrintGameItem(ComputerChoice) << "]" << endl;
	cout << "The  Winner is :[" << PrintWhoWin(Winner) << "]" << endl;
}

void UpdateGameResults(enWhoWin& Winner, stGameInfo& GameResults) {

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


	cout << "\n"<<Tabs(3)<<"_________________________________________________________\n\n\n";
	cout << Tabs(5) << "    +++Game Over+++\n\n";
	cout << Tabs(3) << "_________________________________________________________\n\n";


}

void DisplayFinalGameResults(stGameInfo& GameResults) {

	DisplayTitleGameInfo();
		cout << Tabs(3) << "Game Rounds        : " << GameResults.TotalRounds << endl;
		cout << Tabs(3) << "User Winning Times : " << GameResults.UserWinCount << endl;
		cout << Tabs(3) << "Computer Win Times : " << GameResults.ComputerWinCount << endl;
		cout << Tabs(3) << "Draw Times         : " << (GameResults.DrawCount) << endl;
		cout << Tabs(3) << "Final Winner       : " << PrintWhoWin(GameResults.GameWinner) << endl;

		cout << Tabs(3)<< "_______________________________________________________\n";

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

		GameResults.TotalRounds = ReadTotalRounds("How many rounds do you want to play?\n");

		RunRound(GameResults);

		GameResults.GameWinner = WhoWinner(GameResults);

		DisplayFinalGameResults(GameResults);

	} while (ShouldContinue());
}

int main() {
	srand((unsigned)time(NULL));

	RunGame();

}
