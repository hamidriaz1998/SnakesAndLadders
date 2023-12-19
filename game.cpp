#include <iostream>
#include <windows.h>
#include <iomanip>
#include <conio.h>
#include <ctime>
using namespace std;
// Main Menu
void printBanner();
void printMenu();
// Game Functions
int rollDice();
void Grid(int grid[10][10], int player1pos, int player2pos, char player1, char player2, int laddersStart[], int snakesStart[]);
int Score(int playerScore, int dice, int laddersStart[], int laddersLand[], int snakesStart[], int snakesLand[]);
bool inArr(int arr[], int n, int size);
// Colors
string setcolor(unsigned short color);
int black = 0, blue = 1, green = 2, cyan = 3, red = 4, magenta = 5, brown = 6, lightwhite = 7, darkwhite = 8, lightblue = 9, lightgreen = 10, lightcyan = 11, lightred = 12, lightmagenta = 13, yellow = 14, white = 15;
int main()
{ // Data Structure
    int grid[10][10] = {{100, 99, 98, 97, 96, 95, 94, 93, 92, 91},
                        {81, 82, 83, 84, 85, 86, 87, 88, 89, 90},
                        {80, 79, 78, 77, 76, 75, 74, 73, 72, 71},
                        {61, 62, 63, 64, 65, 66, 67, 68, 69, 70},
                        {60, 59, 58, 57, 56, 55, 54, 53, 52, 51},
                        {41, 42, 43, 44, 45, 46, 47, 48, 49, 50},
                        {40, 39, 38, 37, 36, 35, 34, 33, 32, 31},
                        {21, 22, 23, 24, 25, 26, 27, 28, 29, 30},
                        {20, 19, 18, 17, 16, 15, 14, 13, 12, 11},
                        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    int laddersStart[8] = {4, 9, 20, 28, 40, 63, 71, 88};
    int laddersLand[8] = {14, 31, 38, 84, 59, 81, 91, 98};
    int snakesStart[8] = {17, 54, 62, 64, 87, 93, 95, 99};
    int snakesLand[8] = {7, 34, 18, 60, 24, 73, 75, 78};

    while (true)
    {
        printBanner();
        printMenu();
        cout << "Your Choice: ";
        int choice;
        cin >> choice;
        if (choice == 2)
        {
            system("cls");
            return 0;
        }
        else if (choice == 1)
        {
            char player = '*', computer = 'x';
            int playerPosition = 0, computerPosition = 0;
            int dice;
            char turn = player;

            while (!(playerPosition >= 100 || computerPosition >= 100)) // Game loop
            {
                system("cls");
                if (turn == player)
                {
                    cout << endl;
                    cout << "It's Your turn.\nPress any key to roll the dice................. " << endl;
                    cout << endl;
                    getch();
                    dice = rollDice();
                    cout << "You've got " << dice << endl;
                    cout << "Let's see where that gets you." << endl;
                    playerPosition = Score(playerPosition, dice, laddersStart, laddersLand, snakesStart, snakesLand);
                    Grid(grid, playerPosition, computerPosition, player, computer, laddersStart, snakesStart);
                    turn = computer;
                    cout << endl;
                    cout << "You've played your turn\nPress any key to let the computer play................." << endl;
                    getch();
                }
                else
                {
                    cout << endl;
                    cout << "It's computer's turn now\nLet's see what he gets......:)" << endl;
                    Sleep(1000);
                    dice = rollDice();
                    cout << "He's got " << dice << endl;
                    computerPosition = Score(computerPosition, dice, laddersStart, laddersLand, snakesStart, snakesLand);
                    Grid(grid, playerPosition, computerPosition, player, computer, laddersStart, snakesStart);
                    turn = player;
                    cout << endl;
                    cout << "Press any key to play your continue...........";
                    getch();
                }
            }
            system("cls");
            char winner = playerPosition >= 100 ? player : computer;
            if (winner == player)
            {
                cout << "Congrats! You have won" << endl;
            }
            else
            {
                cout << "Boooooo! You have lost" << endl;
            }
            cout << "Press any key to return to main menu..........";
            getch();
        }
    }
}

void printBanner()
{
    system("cls");
    cout << "   _____             _                               _   _               _     _                " << endl;
    cout << "  / ____|           | |                             | | | |             | |   | |               " << endl;
    cout << " | (___  _ __   __ _| | _____  ___    __ _ _ __   __| | | |     __ _  __| | __| | ___ _ __ ___  " << endl;
    cout << "  \\___ \\| '_ \\ / _` | |/ / _ \\/ __|  / _` | '_ \\ / _` | | |    / _` |/ _` |/ _` |/ _ \\ '__/ __| " << endl;
    cout << "  ____) | | | | (_| |   <  __/\\__ \\ | (_| | | | | (_| | | |___| (_| | (_| | (_| |  __/ |  \\__ \\ " << endl;
    cout << " |_____/|_| |_|\\__,_|_|\\_\\___||___/  \\__,_|_| |_|\\__,_| |______\\__,_|\\__,_|\\__,_|\\___|_|  |___/ " << endl;
}
void printMenu()
{
    cout << endl;
    cout << "Select one of the following option: " << endl;
    cout << "1. Play Game" << endl;
    cout << "2. Exit" << endl;
}
int rollDice()
{
    int num;
    srand(time(0));
    num = (rand() % 6) + 1;
    return num;
}

void Grid(int grid[10][10], int player1pos, int player2pos, char player1, char player2, int laddersStart[], int snakesStart[])
{
    int i, j;
    bool printed = false;
    for (i = 0; i < 10; i++)
    {
        cout << "\n";
        for (j = 0; j < 10; j++)
        {
            if (inArr(laddersStart, grid[i][j], 8)) // if this is a ladder
            {
                if (grid[i][j] == player1pos)
                {
                    cout << left << setw(4) << player1;
                }
                else if (grid[i][j] == player2pos)
                {
                    cout << left << setw(4) << player2;
                }
                else
                {
                    cout << left << setw(4) << "L";
                }
                printed = true;
            }
            else if (inArr(snakesStart, grid[i][j], 8)) // if this is a snake
            {
                if (grid[i][j] == player1pos)
                {
                    cout << left << setw(4) << player1;
                }
                else if (grid[i][j] == player2pos)
                {
                    cout << left << setw(4) << player2;
                }
                else
                {
                    cout << left << setw(4) << "S";
                }
                printed = true;
            }
            if (!printed)
            {
                if (grid[i][j] == player1pos)
                {
                    cout << left << setw(4) << player1;
                }
                else if (grid[i][j] == player2pos)
                {
                    cout << left << setw(4) << player2;
                }
                else
                {
                    cout << left << setw(4) << grid[i][j];
                }
            }
            printed = false;
        }
    }
    cout << "\n";
}
int Score(int playerScore, int dice, int laddersStart[], int laddersLand[], int snakesStart[], int snakesLand[])
{
    int score;
    score = playerScore + dice;
    if (score > 100)
    {
        score = playerScore;
        return score;
    }
    for (int i = 0; i < 8; i++)
    {
        if (score == laddersStart[i])
        {
            score = laddersLand[i];
            break;
        }
        else if (score == snakesStart[i])
        {
            score = snakesLand[i];
            break;
        }
    }
    return score;
}
bool inArr(int arr[], int n, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == n)
            return true;
    }
    return false;
}
string setcolor(unsigned short color)
{
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, color);
    return "";
}