#include <iostream>
#include <cstdlib> 
#include <ctime>
using namespace std;

struct stCountWin
{
    short UserNumberWin = 0;
    short ComputerNumberWin = 0;
    short NoOneWin = 0;

};

enum enChoiceType { Stone = 1, Paper = 2, Scissor = 3 };

enum enWhoWin { Computer = 0, User = 1, Equal = 2 };
//take How Many Game Round ;
short ReadNumberRoundsGame(string Message, short From, short To)
{
    short Number = 0;

    do
    {
        cout << Message << "Between " << From << " to " << To << " ? ";
        cin >> Number;
        cout << "\n";
    } while (!(Number > 0 && Number >= From && Number <= To));
    return Number;
}
// Declare immidatly Round ;
void RoundLevel(short ٌRound)
{
    cout << "Round [" << ++ٌRound << "] Begging\n";
}
// Display Opetion OF Game 
void DisplayChoiceType()
{
    cout << "\nWe Are Have Three Choice : \n";
    cout << "\n\t[1] = Stone\t";
    cout << "[2] = Paper\t";
    cout << "[3] = Scissor\n";
}

enChoiceType UserChoice()
{
    short Choice = 0;
    do
    {
        cout << "\nWhat Is Your Choice [1 to 3] : ";
        cin >> Choice;
        cout << "\n";
    } while (!(Choice >= 1 && Choice <= 3));
    return (enChoiceType)Choice;
}

enChoiceType ComputerChoice()
{
    short ComputerChoice = rand() % (3 - 1 + 1) + 1;
    return (enChoiceType)ComputerChoice;
}

enWhoWin WhoWin(enChoiceType User, enChoiceType Computer)
{
    {

        if (User == Computer)
        {

            return enWhoWin::Equal;
        }

        if (
            (User == enChoiceType::Stone && Computer == enChoiceType::Scissor) ||
            (User == enChoiceType::Paper && Computer == enChoiceType::Stone) ||
            (User == enChoiceType::Scissor && Computer == enChoiceType::Paper)
            )
        {

            return enWhoWin::User;
        }


        return enWhoWin::Computer;
    }

}

string ChoiceName(enChoiceType Choice) {
    string arr[] = { "", "Stone", "Paper", "Scissor" };
    return arr[Choice];
}

void ColorMode(enWhoWin Index)
{

    if (Index == enWhoWin::Computer)
    {
        system("color 4F");
    }
    else if (Index == enWhoWin::User)
    {
        system("color 2F");
    }
    else
    {
        system("color 6F");
    }
}

void CountTotalWin(stCountWin& Winner, enWhoWin Index)
{
    switch (Index)
    {
    case enWhoWin::Computer:Winner.ComputerNumberWin++; break;
    case enWhoWin::User:Winner.UserNumberWin++; break;
    case enWhoWin::Equal:Winner.NoOneWin++; break;
    }
}

void DisplayRoundState(string whoWin[], enChoiceType UserChoice, enChoiceType ComputerChoice, short Round, stCountWin& Winner)
{
    enWhoWin Index = WhoWin(UserChoice, ComputerChoice);
    ColorMode(Index);
    cout << "_________________Round[" << ++Round << "]___________________\n";
    cout << "The User Choice : [" << ChoiceName(UserChoice) << "]\n";
    cout << "The Computer Choice : [" << ChoiceName(ComputerChoice) << "]\n";
    cout << "The Result Of Game : [" << whoWin[Index] << "]\n";
    cout << "__________________________________________________________\n";
    CountTotalWin(Winner, Index);
}

enWhoWin DetermineFinalWinner(stCountWin Winner) {
    if (Winner.UserNumberWin > Winner.ComputerNumberWin) {
        return enWhoWin::User;
    }
    else if (Winner.ComputerNumberWin > Winner.UserNumberWin) {
        return enWhoWin::Computer;
    }
    else {
        return enWhoWin::Equal;
    }
}

string DisplayFinalWinnerInGame(string FinalWinner[], enWhoWin Index)
{
    return FinalWinner[Index];
}

void GameOver(int Round, stCountWin& Winner, string FinalWinner[])
{
    cout << "\t\t\t_________________________________________________________________\n\n";
    cout << "\t\t\t\t\t\t+++ Game Over +++\n";
    cout << "\t\t\t_________________________________________________________________\n\n";
    cout << "\t\t\t_________________________[Game Results]__________________________\n\n";


    cout << "\t\t\t\tGame Rounds          : " << Round << endl;
    cout << "\t\t\t\tPlayer1 won times    : " << Winner.UserNumberWin << endl;
    cout << "\t\t\t\tComputer won times   : " << Winner.ComputerNumberWin << endl;
    cout << "\t\t\t\tDraw times           : " << Winner.NoOneWin << endl;
    cout << "\t\t\t\tFinal Winner         : " << DisplayFinalWinnerInGame(FinalWinner, DetermineFinalWinner(Winner)) << endl;

    cout << "\t\t\t_________________________________________________________________\n\n";
}

bool ShouldContinue()
{
    char Response;
    cout << "\nDo you want to play again? (Y/N): ";
    cin >> Response;
    return (Response == 'y' || Response == 'Y');
}

void ResetScreen() {
    system("cls");
    system("color 0F");
}
void RunGame()
{
    do {
        ResetScreen();
        stCountWin Winner;
        string StatesOFGame[3]{ "Stone","Paper","Scissor" };
        string whoWin[3]{ "Computer Winner","User Winner","No One Win" };
        int TotalRound = ReadNumberRoundsGame("Please Enter Number Of Round ? ", 1, 10);
        for (int i = 0; i < TotalRound; i++)
        {
            RoundLevel(i);
            DisplayChoiceType();
            enChoiceType user = UserChoice();
            enChoiceType Computer = ComputerChoice();
            DisplayRoundState(whoWin, user, Computer, i, Winner);
        }
        GameOver(TotalRound, Winner, whoWin);
    } while (ShouldContinue());
}

int main()
{
    srand((unsigned)time(NULL));
    RunGame();
    return 0;
}
