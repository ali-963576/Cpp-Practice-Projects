
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
enum enGameChoice { Stone = 1, Paper = 2, Sciser = 3 };
enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice Player1Choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;


};

struct  stGameResults
{
	short GameRounds = 0;
	short Player1WinTimes = 0;
	short ComputerWinTimes = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";

};

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
	return arrWinnerName[Winner - 1];
}


enGameChoice GetComputerChoice()
{
	return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}

	switch (RoundInfo.Player1Choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Sciser)
		{
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Sciser:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;

	}


	return enWinner::Player;

}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
	if (Player1WinTimes > ComputerWinTimes) return enWinner::Player;
	else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
	else return enWinner::Draw;
}

stGameResults FillGameResults(int GameRound, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResults GameResults;

	GameResults.GameRounds = GameRound;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.ComputerWinTimes = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);

	return GameResults;

}


string ChoiceName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone","Paper","Scissors" };
	return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";
		break;
	default:
		system("color 6F");
		break;
	}


}

enGameChoice ReadPlayer1Choice()
{
	short Choice;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> Choice;


	} while (Choice < 1 || Choice>3);
	return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
	cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
	cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;

	SetWinnerScreenColor(RoundInfo.Winner);
}

stGameResults PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choice = ReadPlayer1Choice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
			Player1WinTimes++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTimes++;
		else
			DrawTimes++;

		PrintRoundResults(RoundInfo);
	}

	return FillGameResults(HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes);
}

string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;

}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "_________________________________________________\n\n";
	cout << Tabs(2) << "              +++ G a m e  O v e r +++\n";
	cout << Tabs(2) << "_________________________________________________\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tabs(2) << "_________________________[ Game Results ]____________________________\n\n";
	cout << Tabs(2) << "Game Rounds                : " << GameResults.GameRounds << endl;
	cout << Tabs(2) << "Plyaer1 Won Time           : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Coputer Won Time           : " << GameResults.ComputerWinTimes << endl;
	cout << Tabs(2) << " Draw Time                 : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner               : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "_________________________________________________________________________";

	SetWinnerScreenColor(GameResults.GameWinner);

}

short ReadHowManyRounds()
{
	short GameRound = 1;

	do
	{
		cout << "Who Many Rounds 1 To 10 ? \n";
		cin >> GameRound;

	} while (GameRound < 1 || GameRound>10);
	return GameRound;
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';

	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);


		cout << endl << Tabs(3) << "Do You want Play again? (Y/N):";
		cin >> PlayAgain;


	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();



	return 0;
}
