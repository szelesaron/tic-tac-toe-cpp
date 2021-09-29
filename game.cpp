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

void show_array()
{
    for (size_t i = 0; i < dimension; i++)
    {
        for (size_t j = 0; j < dimension; j++)
            cout << arr[i][j] << " ";
    cout << endl;
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
bool full_or_not()
{
    for (size_t i = 0; i < dimension; i++)
    {
        for (size_t j = 0; j < dimension; j++)
        {
            if (arr[i][j] == -1)
                return false;
        }
        
    }
    return true;
    
}

bool won_or_not(int res, int player_id)
{
    int row = res /10;
    int column = res %10;
    bool won = true;

    //row wise
    for (size_t i = 0; i < dimension; i++)
    {
        if (arr[row][i] != player_id)
        {
            won = false;
            break;
        }
    }
    
    //resetting for column wise check
    if(won)
        return won;
    else
        won = true;

    //columns wise
    for (size_t i = 0; i < dimension; i++)
    {
        if (arr[i][column] != player_id)
        {
            won = false;
            break;
        }
    }

    //resetting for cross wise check
    if(won)
        return won;
    else
        won = true;

    //cross wise - 1 top left to bottom right
    for (size_t i = 0; i < dimension; i++)
    {
        if (arr[i][i] != player_id)
        {
            won = false;
            break;
        }
    }
    
    if(won)
        return won;
    else
        won = true;

    //cross wise - 2 bottom left to top right
    for (size_t i = 0; i < dimension; i++)
    {
        if (arr[dimension-i-1][i] != player_id)
        {
            won = false;
            break;
        }
        
    }

    return won;
}   

//if place not occupied insert value and return 1 otherwise 0
int play(int res, int player_num)
{
    //player1 = O, player2 = X


    if (arr[res/10][res%10] not_eq -1 || res < 0 || res > (dimension*10+dimension))
    {
        return 0;
    }

    if(player_num == 0)
    {
        arr[res/10][res%10] = 0;
    }
    else
    {
        arr[res/10][res%10] = 1;
    }
    return 1;
}
/*
TODO:
    1. Make game fluid - if step is invalid ,request new - done
    2. check when one player wins or full - done
    3. handle exceptions ->longer input, string ect. - done
    
    4. draw game - in progress...

    5. use names make it fancy refactor
*/

int main()
{

    //string start_signal;
    //string * names  = setup();
    //cout << "Welcome " << names[0] << " and " << names[1] << ". Type \"go\" to start the game." << endl;
    //cin >> start_signal;
    reset_array();

    while (!game_over)
    {
        //checking if input is correct
        bool correct = false;
        while(!correct && !game_over)
        {            
            string response_1_str;
            cout << "Player 1 make a move: ";
            cin >> response_1_str;

            //checking for correct input - strings
            bool correct_type = true;
            while(1)
            {
                for (size_t i = 0; i < response_1_str.length(); i++)
                {
                    if (!isdigit(response_1_str[i]))
                    {
                        cout << "Wrong input type, try again." << endl;
                        correct_type = false;
                        cout << "Player 1 make a move: ";
                        cin >> response_1_str;
                        break;
                    }
                    else correct_type = true;
                }
                if (correct_type) break;  
            }
            
            //convert back to int
            int response_1 = stoi(response_1_str);


            correct = play(response_1, 0);
            if(!correct) 
                cout << "Invalid step, try again." << endl;

            else
            {
                if(won_or_not(response_1, 0))
                {
                    cout << "player 1 won" << endl;
                    game_over = true;
                }
            }
        }

        //checking for draw
        if(full_or_not()){
            game_over = true;
            cout << "Draw." << endl;
        }

        correct = false;
        while(!correct && !game_over)
        {            
            string response_2_str;
            cout << "Player 2 make a move: ";
            cin >> response_2_str;

            //checking for correct input - strings
            bool correct_type = true;
            while(1)
            {
                for (size_t i = 0; i < response_2_str.length(); i++)
                {
                    if (!isdigit(response_2_str[i]))
                    {
                        cout << "Wrong input type, try again." << endl;
                        correct_type = false;
                        cout << "Player 2 make a move: ";
                        cin >> response_2_str;
                        break;
                    }
                    else correct_type = true;
                }
                if (correct_type) break;  
            }
            
            //convert back to int
            int response_2 = stoi(response_2_str);


            correct = play(response_2, 1);
            if(!correct)
                cout << "Invalid step, try again." << endl;
            else
            {
                if(won_or_not(response_2, 1))
                {
                    cout << "player 2 won" << endl;
                    game_over = true;
                }
            }
        }

        //checking for draw
        if(full_or_not()){
            game_over = true;
            cout << "Draw." << endl;
        }

        //draw();
        show_array();

    }
    cout << endl;
    cout << "Game over, thanks for playing." << endl;
    return 0;
}