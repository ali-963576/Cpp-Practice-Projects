
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, sub = 2, mul = 3, Div = 4, MixOp = 5 };


string GetOpTypeSymbol(enOperationType OpType)
{

	switch (OpType)
	{
	case enOperationType::Add:
		return"+";
	case enOperationType::sub:
		return"-";
	case enOperationType::mul:
		return"x";
	case enOperationType::Div:
		return"/";
	default:
		return"Mix";
	}

}

string GetQuestionLevelText(enQuestionsLevel QuestionsLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix" };
	return arrQuestionLevelText[QuestionsLevel - 1];
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // Green for correct answers.
	else
	{
		system("color 4F"); // Red for incorrect answers.
		cout << "\a"; // Plays an alert sound.
	}
}

int RandomNumber(int From, int To)
{
	return rand() % (To - From + 1) + From;
}

short ReadWhoManyQuestions()
{
	short NumberOfQuestion = 0;
	do
	{
		cout << "Who Many Questions you wont to answer ?  ";
		cin >> NumberOfQuestion;


	} while (NumberOfQuestion < 1 || NumberOfQuestion >10);
	return NumberOfQuestion;
}

enQuestionsLevel ReadQuestionLevel()
{
	short QuestionLevel = 0;

	do
	{
		cout << "Enter Question Level [1] Easy , [2] Med , [3] Hard , [4] Mix ?";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel >4);

	return  (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;
	do
	{

		cout << "Enter Operation Type [1] Add , [2] Sub , [3] Mul , [4] Div , [5] Mix ?";
		cin >> OpType;

	} while (OpType < 1 || OpType >5);
	return (enOperationType)OpType;

}


struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQuestionsLevel QuestionLevel;
	int CorrectAnswers = 0;
	int PlayerAnswers = 0;
	bool AnswerResult;

};

struct  stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQustion;
	enQuestionsLevel QuestionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;

};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::sub:
		return Number1 - Number2;
	case enOperationType::mul:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}



}

enOperationType GatRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;
}

stQuestion GeneratQuestion(enQuestionsLevel QuestionsLevel, enOperationType OpType)
{
	stQuestion Question;

	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GatRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionsLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;

	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswers = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;

	}
	return Question;
}

void GeneratQuizzQuestion(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQustion; Question++)
	{
		Quizz.QuestionList[Question] = GeneratQuestion(Quizz.QuestionLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNunber)
{
	cout << "\n";
	cout << "Question [" << QuestionNunber + 1 << "/" << Quizz.NumberOfQustion << "] \n\n";
	cout << Quizz.QuestionList[QuestionNunber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNunber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNunber].OperationType);
	cout << "\n__________" << endl;


}

void CorrectTheQiestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswers != Quizz.QuestionList[QuestionNumber].CorrectAnswers)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( /n";
		cout << "The right Answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswers;
		cout << "/n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) /n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);


}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQustion; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswers = ReadQuestionAnswer();
		CorrectTheQiestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);

}

string GetFinalResultText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";

}

void PrintQuizzResult(stQuizz Quizz)
{
	cout << "\n";
	cout << "_____________________________\n\n";
	cout << "Final Resulte is " << GetFinalResultText(Quizz.isPass);
	cout << "\n____________________________\n\n";

	cout << "Number Of Question : " << Quizz.NumberOfQustion << endl;
	cout << "Qusetion Level     : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
	cout << "OpType              : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number Of Right Answer:" << Quizz.NumberOfRightAnswers << endl;
	cout << "Number Of Wrong Answer :" << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";


}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQustion = ReadWhoManyQuestions();
	Quizz.QuestionLevel = ReadQuestionLevel();
	Quizz.OpType = ReadOpType();

	GeneratQuizzQuestion(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResult(Quizz);

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
		PlayMathGame();
		cout << endl << "Do you want Play Again? Y/y";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();

	return 0;
}

