// Math Quiz Game - Full Version with Comments
// Developed by Abdelheq Madi

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Enumeration to represent question difficulty levels
enum enQstLevel { Easy = 1, Med = 2, Hard = 3, MixLevel = 4 };

// Enumeration to represent arithmetic operation types
enum enOpType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

// Enumeration to represent if the user's answer is correct or not
enum enResult { RightAnswer = 1, WrongAnswer = 2};

// Structure to hold information about each question
struct stQstInfo {
    short QstNumber = 0, Number1 = 0, Number2 = 0, UserAnswer = 0, RightAnswer = 0;
    enOpType OpType;
    enQstLevel QstLevel;
    char opSign = '+';
    enResult Result;
    string ResultName = "";
};

// Structure to hold summary of the game session
struct stGameResults {
    short NumberOfQst = 0, RightAnswers = 0, WrongAnswers = 0;
    string LevelName = "", OpName = "";
    enQstLevel QstLevel;
    enOpType OpType;
};

// Utility to generate a random number in a range
float ReadNumber() {
    float Number;

    cin >> Number;

    return Number;
}

// Utility to generate a random number in a range
short RandomNumber(short From, short To) {
    short RandNum = rand() % (To - From + 1) + From;

    return RandNum;
}

// Gets the number of questions from the user
int HowManyQst() {
    int Number;

    do {
        cout << "How Many Questions do you want to answer ? ";
        cin >> Number;
    } while (Number < 0);

    return Number;
}

// Reads difficulty level from user
enQstLevel ReadQstLevel() {
    short QstLevel = 1;

    do {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> QstLevel;
    } while (QstLevel < 0 || QstLevel > 4);

    return (enQstLevel)QstLevel;
}

// Reads operation type from user
enOpType ReadOpType() {
    short OpType = 1;

    do {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
        cin >> OpType;
    } while (OpType < 0 || OpType > 5);

    return (enOpType)OpType;
}

// Returns a number based on the question level
short GenerateNumbers(enQstLevel QstLevel) {
    switch (QstLevel) {
    case enQstLevel::Easy:
        return RandomNumber(1, 10);
    case enQstLevel::Med :
        return RandomNumber(10, 50);
    case enQstLevel::Hard:
        return RandomNumber(50, 100);
    case enQstLevel::MixLevel:
        return RandomNumber(1, 100);
    default:
        return RandomNumber(1, 100);
    }
}

enOpType RandomOperation() {
        return (enOpType)RandomNumber(1, 4);
}

enQstLevel RandomLevel() {
    return (enQstLevel)RandomNumber(1, 3);
}

// Converts operation type to its corresponding symbol
char OperationSymbol(enOpType OpType) {
    switch (OpType) {
    case enOpType::Add:
        return '+';
    case enOpType::Sub:
        return '-';
    case enOpType::Mul:
        return '*';
    case enOpType::Div:
        return '/';
    }
}

// Performs the arithmetic operation and returns result
short SimpleCalculator(short Number1, short Number2, enOpType OpType) {
    switch (OpType) {
    case enOpType::Add:
        return Number1 + Number2;
    case enOpType::Sub:
        return Number1 - Number2;
    case enOpType::Mul:
        return Number1 * Number2;
    case enOpType::Div:
        return (float)Number1 / Number2;
    }
}

// Compares user's answer with correct answer
enResult IsRightOrWrong(short UserAnswer, short RightAnswer) {
    if (UserAnswer == RightAnswer)
        return enResult::RightAnswer;
    else
        return enResult::WrongAnswer;
}

// Returns result description string
string QstResult(enResult QstResult) {
    switch (QstResult) {
    case enResult::RightAnswer:
        return "Right Answer :-)";
    case enResult::WrongAnswer:
        return "Wrong Answer :-(";
    }
}

// Changes console color based on result
void SetResultScreenColor(enResult QstResult) {
    switch (QstResult) {
    case enResult::RightAnswer:
        system("color 2f");
        break;
    case enResult::WrongAnswer:
        system("color 4F");
        break;
    }
}

// Resets the console screen
void ResetScreen() {
    system("cls");
    system("color 0F");
}

// Prints the formatted question
void PrintQstInfo(stQstInfo QstInfo) {
        cout << QstInfo.Number1 << endl;
        cout << QstInfo.Number2 << " " << QstInfo.opSign << endl;
        cout << "_____________" << endl;
}

// Prints the result of a single question
void PrintQstResults(stQstInfo QstInfo) {
    cout << QstInfo.ResultName << endl;

    SetResultScreenColor(QstInfo.Result);
}

// Displays pass/fail result
string FinalResult(short RightAnswers, short WrongAnswers) {
    if (RightAnswers > WrongAnswers) {
        system("color 2F");
        return "Pass :-)";
    }
    else {
        system("color 4F");
        return "Fail :-(";
    }
}

// Prints final result of the game
void PrintFinalResult(short RightAnswers, short WrongAnswers) {
    cout << "\n\n_____________________________________________\n\n";
    cout << "Final Results is " << FinalResult(RightAnswers, WrongAnswers) << endl;
    cout << "_____________________________________________\n\n";
}

// Converts level enum to name
string LevelName(enQstLevel QstLevel) {
    switch (QstLevel) {
    case enQstLevel::Easy:
        return "Easy";
    case enQstLevel::Med:
        return "Med";
    case enQstLevel::Hard:
        return "Hard";
    case enQstLevel::MixLevel:
        return "Mix";
    }
}

// Converts op enum to name
string OpName(enOpType OpType) {
    switch (OpType) {
    case enOpType::Add:
        return "Add";
    case enOpType::Sub:
        return "Sub";
    case enOpType::Mul:
        return "Mul";
    case enOpType::Div:
        return "Div";
    case enOpType::MixOp:
        return"Mix";
    }
}

// Main game logic for one session
stGameResults PlayGame(short HowManyQst) {
    stQstInfo QstInfo;

    short RightAnswers = 0, WrongAnswers = 0;

    QstInfo.QstLevel = ReadQstLevel();
    if (QstInfo.QstLevel == enQstLevel::MixLevel)
        QstInfo.QstLevel = RandomLevel();

    QstInfo.OpType = ReadOpType();
    if (QstInfo.OpType == enOpType::MixOp)
        QstInfo.OpType = RandomOperation();

    for (short QstNumber = 1; QstNumber <= HowManyQst; QstNumber++) {
        cout << "\nQuestion [" << QstNumber << "/" << HowManyQst << "]\n" << endl;
        QstInfo.QstNumber = QstNumber;
        
        QstInfo.Number1 = GenerateNumbers(QstInfo.QstLevel);
        QstInfo.Number2 = GenerateNumbers(QstInfo.QstLevel);
        QstInfo.opSign = OperationSymbol(QstInfo.OpType);

        PrintQstInfo(QstInfo);

        QstInfo.UserAnswer = ReadNumber();
        QstInfo.RightAnswer = SimpleCalculator(QstInfo.Number1, QstInfo.Number2, QstInfo.OpType);
        QstInfo.Result = IsRightOrWrong(QstInfo.UserAnswer, QstInfo.RightAnswer);
        QstInfo.ResultName = QstResult(QstInfo.Result);

        PrintQstResults(QstInfo);

        if (QstInfo.Result == enResult::RightAnswer)
            RightAnswers++;
        else
            WrongAnswers++;
    }

    PrintFinalResult(RightAnswers, WrongAnswers);

    stGameResults GameResults;

    GameResults.NumberOfQst = HowManyQst;
    GameResults.LevelName = LevelName(QstInfo.QstLevel);
    GameResults.OpName = OpName(QstInfo.OpType);
    GameResults.RightAnswers = RightAnswers;
    GameResults.WrongAnswers = WrongAnswers;

    return GameResults;
}

// Displays the final summary of the quiz
void PrintFinalScreen(stGameResults GameResults) {
    cout << "\nNumber Of Questions : " << GameResults.NumberOfQst << endl;
    cout << "Questions Level     : " << GameResults.LevelName << endl;
    cout << "OpType              : " << GameResults.OpName << endl;
    cout << "Number of Right Answers : " << GameResults.RightAnswers << endl;
    cout << "Number of Wrong Answers : " << GameResults.WrongAnswers << endl;
    cout << "\n_____________________________________________\n\n";
}

// Starts the game loop, allowing replay
void StartGame() {

    char PlayAgain = 'Y';

    do {
        ResetScreen();
        stGameResults GameResults = PlayGame(HowManyQst());;
        PrintFinalScreen(GameResults);

        cout << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');

}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}   