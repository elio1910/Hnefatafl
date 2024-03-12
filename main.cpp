/**
* @file main.cpp
*
* @brief Implementation of the Hnefatafl game.
*
* This file contains the implementation of the Hnefatafl game, including setup, gameplay, and outcome
determination.
* It also provides a testing suite for various game functions.
*
* @author Elio SAPIN
* @date 20/11/2023
*/

#include <iostream>
#include "typeDef.h"
#include "functions.h"
#include "tests.h"
#include <iomanip>
#include <fstream>

using namespace std;

/**
* @brief Function to play the Hnefatafl game.
*
* This function orchestrates the Hnefatafl game, including setup, gameplay, and outcome determination.
*/
void playGame()
{
    string np1,np2;
    int turn=0;
    BoardSize Size;
    displayHnefataflLogo();
    Cell Board[BOARD_SIZE_MAX][BOARD_SIZE_MAX];
    bool sizeCorr = true;    
    do
    {
        sizeCorr=chooseSizeBoard(Size);
        if(sizeCorr)
        {
            initializeBoard(Board,Size);
        }
        else
        {
            cout<<"Choose big or little for the size"<<endl;
            clearConsole();
        }
    }while(!sizeCorr);
    cout<<"Name player1 (attack): "<<"Name player2 (defense): ";
    cin>>np1>>np2;
    PlayerRole Player;
    Position StartPos,EndPos;
    displayBoard(Board,Size);
    while(!isKingCaptured(Board,Size) && isSwordLeft(Board,Size) && !isKingEscaped(Board,Size))
    {  
        cout<<endl;
        if(turn%2 == 0)
        {
            Player=PlayerRole::ATTACK;
            cout<<"[ATTACK] Your turn "<<np1<<" Start piece"<<endl;
            StartPos=getPositionFromInput();
            cout<<"[ATTACK] End Position"<<endl;
            EndPos=getPositionFromInput();
        }
        else
        {
            Player=PlayerRole::DEFENSE;
            cout<<"[DEFENSE] Your turn "<<np2<<" Start piece"<<endl;
            StartPos=getPositionFromInput();
            cout<<"[DEFENSE] End Position"<<endl;
            EndPos=getPositionFromInput();
        }

        if (isValidPosition(StartPos,Size) && isValidPosition(EndPos,Size))
        {
            if(isValidMovement(Player,Board,StartPos,EndPos))
            {
                movePiece(Board,StartPos,EndPos);
                capturePieces(Player,Board,Size,EndPos);
                turn++;
                clearConsole();
                displayBoard(Board,Size);
            }
            else
            {
                cout<<"Invalid Movement"<<endl;
            }
        }
        else
        {
            cout<<"Invalid Postition"<<endl;
        }


    }
    if(isKingCaptured(Board,Size))
    {
        cout<<endl;
        cout<<np1<<" win the game"<<endl;
    }
    else
    {
        cout<<endl;
        cout<<np2<<" win the game"<<endl;
    }

}

/**
* @brief Launches the testing suite.
*
* This function runs a suite of tests to validate various game functions.
*/
void launchTests()
{
    cout << endl << "********* Start testing *********" << endl << endl;
    test_capturePieces();
    //test_isKingCapturedV2();
    cout << endl << "********** End testing **********" << endl << endl;
}

/**
* @brief Main function of the game.
*
* The main function serves as the entry point for the Hnefatafl game. It can be used to start the game or run tests.
*
* @return 0 for successful execution.
*/

int main()
{
    launchTests();
    //playGame();
    return 0;
}
