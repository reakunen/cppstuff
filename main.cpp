// 
//main.cpp
// Brian Mai
// 9/12/2021
// Tic Tac Toe
// 

#include <iostream>
#include <random> 
#include <iomanip> 

using namespace std;

void clearTable(int a[][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[i][j] = 0; 
        }
        cout << endl; 
    }
    return; 
}

void printTable(int a[][3], ostream& out, int turn, bool bot)
{
    // true, O, false, X

    (turn&1)==0 ? out << "O's Turn: " << endl : out << "X's Turn: " << endl; 
    char type; 
    out << '\n' << flush; 
    out << "Column: 1" <<setw(10) << "    2    3" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //0, null, 1, O, 2, X
            if(j==0) out << "Row " <<  i+1 << flush; 
            if (a[i][j] == 0)
            {
                out << "  " << setw(1) << ' ' << setw(2) << " "<<  flush;
            }
            else if (a[i][j] == 1)
            {
                out << "  " << setw(1) << 'O' << setw(2) << " "<<  flush;

            }
            else 
            {
                out << "  " << setw(1) << 'X' << setw(2) << " "<<  flush;
            }
            if (j < 2) out << '|';

        }
        out << endl; 
        if (i < 2)
        out << "      ---------------" << endl;
    }
    out << '\n'; 
}

void makeMove(int a[][3], int &turn, ostream &out, istream &in, bool bot) 
{   
    bool ok = false, ok2 = false, ok3 = false;  
    int rows1 = 0, rows2 = 0, col1 = 0, col2 = 0; 
    if ((turn&1)==0) 
    {
        while (!ok)
        {
            out << "Player 1, enter rows: " << flush; 
            in >> rows1; 

            out << "Player 1, enter columns: " << flush; 
            in >> col1; 
            ((col1 <= 3) && (rows1 <= 3) && (a[rows1-1][col1-1] == 0))? ok = true : ok = false; 
            ok ? out << endl : out << "Error. Please enter again!" << endl; 
        }
    }
    else if (bot && (turn&1) == 1)
    {
        while (!ok3)
        {
            srand(time(0));
            col2 = (rand() % 3) + 1;
            rows2 = (rand() % 3) + 1;

            ((col2 <= 3) && (rows2 <= 3) && (a[rows2-1][col2-1] == 0))? ok3 = true : ok3 = false; 
        }
    }
    else 
    {
        while (!ok2)
        {
            out << "Player 2, enter rows: " << flush; 
            in >> rows2; 

            out << "Player 2, enter columns: " << flush; 
            in >> col2; 
            ((col2 <= 3) && (rows2 <= 3) && (a[rows2-1][col2-1] == 0))? ok2 = true : ok2 = false; 
            
            ok2 ? out << endl : out << "Error. Please enter again!" << endl; 
        }    
    }

    (turn&1)==0 ? a[rows1-1][col1-1] = 1 : a[rows2-1][col2-1] = 2; 
    
    turn++; 
}

bool checkWin (int a1, int a2, int a3) 
{
    return(((a1 == a2) && (a3 == a2) && (a1 != 0)) ? true : false);
    //true = win, false = no win
}

bool didWin (int a[][3])
{
    bool win = false; 
    for (int i = 0; i < 3; i++)
    {
        if ((checkWin(a[i][2], a[i][1], a[i][0])) || (checkWin(a[2][i], a[1][i], a[0][i])))
        {
            win = true;  
            break; 
        }
    }
    if (checkWin(a[0][0], a[1][1], a[2][2]) || checkWin(a[2][0], a[1][1], a[0][2]))
    {
        //diagonal win 
        win = true;  
    }

    return win;
}

void printWin(int turn, ostream &out)
{
    (turn&1)==1 ? out << "O has won the game!" << endl : out << "X has won the game!" << endl; 
    
    return; 
}

bool keepPlaying(ostream &out, istream &in) 
{
    string a; 
    out << "Do you still want to keep playing? y/n: " << flush; 
    in >> a; 
    
    return((a == "y") || (a == "yes") ?  true :  false); 
}

bool player(ostream &out, istream &in)
{   
    int players = -1; 
    out << "Enter players: ";
    in >> players; 
    while(players < 0 || players > 2)
    {
        out << "Enter # Of Players: " << flush;
        in >> players; 
    }
    // if 1 player, return true (meaning return bot);
    return (players == 1 ? true : false); 
}

int main ()
{
    //player 1 is O, player 2 is X
    int table[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    static int turn = 0; 
    bool won = false, keepPlay = true;  
    cout << "Welcome to Tic Tac Toe!" << endl; 
    bool bot = player(cout, cin); 
        while (!won && keepPlay) 
        {
        printTable(table, cout, turn, bot); 
        makeMove(table, turn, cout, cin, bot); 
            if (turn > 8 && !won)
            {
                printTable(table, cout, turn, bot); 
                cout << "Nobody wins. The game was tied." << endl; 
                keepPlay = keepPlaying(cout, cin); 
                if (keepPlay) 
                {
                    clearTable(table); 
                    won = false; 
                }
                else
                {
                    cout << "Thanks for playing!" << endl;
                    break;
                }
            }
            if (turn > 4) 
            {
                won = didWin(table);
                if (won) 
                {
                    printTable(table, cout, turn, bot); 
                    printWin(turn, cout);
                    keepPlay = keepPlaying(cout, cin); 
                    turn = 0; 
                    if (keepPlay) 
                    {
                        clearTable(table); 
                        won = false; 
                    }
                    else 
                    {
                        cout << "Thanks for playing!" << endl;
                        break;
                    }
                }
            }
        }
    
    return 0; 
}