#include<stdio.h>
#include<iostream>
#include <chrono>
#include <thread>
using namespace std;

//constant
bool game_over = false;
const int dimension = 3;
const int box_size = 12;
//-1 is the empty value
int arr[dimension][dimension];




//functions
void reset_array()
{
    for (size_t i = 0; i < dimension; i++)
    {
        for (size_t j = 0; j < dimension; j++)
            arr[i][j] = -1;
    }
}



string * setup()
{
    string player_1, player_2;

    cout << "Please insert your name player 1: ";
    cin >> player_1;

    cout << "Please insert your name player 2: ";
    cin >> player_2;

    string * names = new string[2];
    names[0] = player_1;
    names[1] = player_2;

    return names;
}

void draw()
{
    system("clear");
    /*
    12 * 12
    lines at pos 4

        |   |   
    ------------
        |   |   
    ------------
        |   |   
    
        
    */
    for (size_t i = 0; i < (2* dimension) -1; i++)
    {
        if (i % 2 == 0)
            cout << "   |   |   " << endl; 
        
        else
        {
            for (size_t i = 0; i < box_size; i++)
                cout <<"-"; 
            cout << endl;
        }
        
    }
    cout << endl;


    
}

int play(int res)
{
    //player1 = O, player2 = X

    if (arr[res/10][res%10] != -1)
    {
        cout << "taken";
        return 0;
    }

    arr[res/10][res%10] = 0;
    return 1;
}


int main()
{
    if (!game_over)
    {
        string start_signal;
        string * names  = setup();
        cout << "Welcome " << names[0] << " and " << names[1] << ". Type \"go\" to start the game." << endl;
        cin >> start_signal;
        if (start_signal == "go")
        {
            reset_array();
            while (!game_over)
            {
                int respone_1;
                cout << "Player 1 make a move: ";
                cin >> respone_1;
                play(respone_1);

                int respone_2;
                cout << "Player 2 make a move: ";
                cin >> respone_2;
                play(respone_1);
            

                //input positions of existing xs and os
                //draw();


            }
            

        }
            
    }
    


    return 0;
}