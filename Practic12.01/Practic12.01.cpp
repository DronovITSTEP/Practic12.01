#include <iostream>
#include <algorithm>

using namespace std;

// Крестики - Нолики

#define S(X) (X) ? 'X' : 'O'

const int SIZE_BOARD = 3;
char board[SIZE_BOARD][SIZE_BOARD]
{   {'_', '_', '_'},
    {'_', '_', '_'},
    {' ', ' ', ' '} 
};

int compTurn[9]{ 00,01,02,10,11,12,20,21,22 }; // возможные ходы компьютера

void ShowBoard(); // отображение доски в консоли
int PlayerTurn(); // ход игрока
int ComputerTurn(); // ход компьютера
bool IsWin(char); // проверка на победу
void LogicGame(); // основная логика игры
bool IsFreeCell(int(*)(), char); // свободна ли клетка
int main()
{
    setlocale(LC_ALL, "");

    srand(time(0));
    random_shuffle(begin(compTurn), end(compTurn));

    LogicGame();

}

void ShowBoard() {
    for (int i = 0; i < SIZE_BOARD; i++) {
        for (int j = 0; j < SIZE_BOARD; j++) {
            if (j != 0) cout << '|';
            cout << board[i][j];           
        }
        cout << endl;
    }
    cout << endl;
}
int PlayerTurn() {
    int x;
    while (true)
    {   
    cout << "Введите координаты (без пробелов) - "; cin >> x;
    if ((x/10 <= 3 && x/10 >= 1) && (x%10 <= 3 && x%10 >= 1)) return x-11;
    cout << "Введене неверное значение, повторите попытку\n";
    }   
}
int ComputerTurn() {
    for (static int i = 0; i < 9;) {
        return compTurn[i++];
    }
}
bool IsWin(char c) {
    // проверка по строкам
    for (int i = 0; i < SIZE_BOARD; i++)
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return true;

    // проверака по столбцам
    for (int j = 0; j < SIZE_BOARD; j++)
        if (board[0][j] == c && board[1][j] == c && board[2][j] == c) return true;

    // проверка по диагонали
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return true;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return true;

    return false;
}
bool IsFreeCell(int(*p)(), char c) {
    int x = p() / 10;
    int y = p() % 10;

    if (board[x][y] == 'X' || board[x][y] == 'O') {
        cout << "Клетка занята\n";
        return false;
    }
    board[x][y] = c;
    return true;
}
void LogicGame() {
    int turn = rand() % 2;
    char player = S(turn), comp = S(!turn);

    ShowBoard();

    int count = 0;
    for (; count <= 9;) {       
        if (!IsFreeCell((count % 2) ? PlayerTurn : ComputerTurn,
            (count % 2) ? player : comp)) continue;

        ShowBoard();

        if (IsWin((count % 2) ? player : comp)) {
            cout << "Победа!\n";
            break;
        }
        count++;
    }
}