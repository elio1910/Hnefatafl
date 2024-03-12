#include <iostream>
#include "typeDef.h"
#include "functions.h"
#include <iomanip>
#include <cstdlib>

using namespace std;



void clearConsole()
{
    system("cls");
}

void displayHnefataflLogo()
{
    cout<<R"(
             ██╗  ██╗███╗   ██╗███████╗███████╗ █████╗ ████████╗ █████╗ ███████╗██╗
             ██║  ██║████╗  ██║██╔════╝██╔════╝██╔══██╗╚══██╔══╝██╔══██╗██╔════╝██║
             ███████║██╔██╗ ██║█████╗  █████╗  ███████║   ██║   ███████║█████╗  ██║
             ██╔══██║██║╚██╗██║██╔══╝  ██╔══╝  ██╔══██║   ██║   ██╔══██║██╔══╝  ██║
             ██║  ██║██║ ╚████║███████╗██║     ██║  ██║   ██║   ██║  ██║██║     ███████╗
             ╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝     ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚═╝     ╚══════╝
                                                                               )"<<endl;
}

bool chooseSizeBoard(BoardSize& aBoardSize)
{
    string val;
    cout<<"Which size you want to play (big(13) or little(11)): ";
    cin>>val;
    if (val != "big" && val != "little" && val != "11" && val != "13")
    {
        cout<<"Please enter a correct value"<<endl;
        return false;
    }
    if (val == "big" || val == "13")
    {
        aBoardSize = BoardSize::BIG;
        cout<<"You choose 13x13"<<endl;
    }
    else
    {
        aBoardSize = BoardSize::LITTLE;
        cout<<"You choose 11x11"<<endl;
    }
    return true;
}

void initializeBoard(Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    for(int i=0 ; i < aBoardSize ; i++)
    {
        for(int j=0 ; j < aBoardSize ; j++)
        {
            aBoard[i][j].itsCellType=NORMAL;
            aBoard[i][j].itsPieceType=NONE;
        }
    }
    for(int i = 0; i < aBoardSize;i++)
    {
        for(int j=0 ; j < aBoardSize;j++)
        {
            if(i==0 && j==0) // The forteress in the fourth corners
            {

                aBoard[i][j].itsCellType=FORTRESS;
                aBoard[aBoardSize-1][j].itsCellType=FORTRESS;
                aBoard[i][aBoardSize-1].itsCellType=FORTRESS;
                aBoard[aBoardSize-1][aBoardSize-1].itsCellType=FORTRESS;

            }
            if(i==aBoardSize/2 && j==aBoardSize/2) // the king and the shield common to the both models
            {
                aBoard[i][j].itsCellType=CASTLE;
                aBoard[i][j].itsPieceType=KING;
                aBoard[i-1][j].itsPieceType=SHIELD;
                aBoard[i][j-1].itsPieceType=SHIELD;
                aBoard[i+1][j].itsPieceType=SHIELD;
                aBoard[i][j+1].itsPieceType=SHIELD;
                aBoard[i-2][j].itsPieceType=SHIELD;
                aBoard[i+2][j].itsPieceType=SHIELD;
                aBoard[i][j+2].itsPieceType=SHIELD;
                aBoard[i][j-2].itsPieceType=SHIELD;

                if (aBoardSize == 11) // the king and the shield for the model LITTLE ( SIZE = 11 )
                {
                    aBoard[i+1][j+1].itsPieceType=SHIELD;
                    aBoard[i-1][j+1].itsPieceType=SHIELD;
                    aBoard[i+1][j-1].itsPieceType=SHIELD;
                    aBoard[i-1][j-1].itsPieceType=SHIELD;
                }
                else // the king and the shield for the model BIG ( SIZE = 13 )
                {
                    aBoard[i+3][j].itsPieceType=SHIELD;
                    aBoard[i-3][j].itsPieceType=SHIELD;
                    aBoard[i][j+3].itsPieceType=SHIELD;
                    aBoard[i][j-3].itsPieceType=SHIELD;
                }


            }
            else if(i==0) // the sword which have the same pattern of the both models
            {
                for (int k=aBoardSize/3;k<aBoardSize-(aBoardSize/3);k++ )
                {
                    if(k==aBoardSize/2) // the swords which that go out of the lines of swords
                    {
                        aBoard[1][k].itsPieceType=SWORD;

                        aBoard[k][1].itsPieceType=SWORD;

                        aBoard[aBoardSize-2][k].itsPieceType=SWORD;

                        aBoard[k][aBoardSize-2].itsPieceType=SWORD;

                    }
                    // the lines of swords
                    aBoard[i][k].itsPieceType=SWORD;
                    aBoard[aBoardSize-1][k].itsPieceType=SWORD;
                    aBoard[k][i].itsPieceType=SWORD;
                    aBoard[k][aBoardSize-1].itsPieceType=SWORD;

                }

            }



        }
    }
}

void displayBoard(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    cout<<endl;
    cout<<" \u25CF -> SWORD "<<" \u25CB -> SHIELD "<<" \u2654 -> KING "<<" X -> Fortress "<<" \u2616 -> Castle"<<endl;
    cout<<endl;
    char col='A';

    cout<<"     "<<1; // display of the Columns
    for(int k=2; k < aBoardSize+1 ; k++)
    {
        if (k>9)
        {
            cout<<"  "<<k;
        }
        else
        {
            cout<<"   "<<k;
        }

    }
    cout<<endl;
    for(int i=0 ;i < aBoardSize;i++) // display of the lines, the piece, the box and the cells
    {

        cout<<"   +";
        for(int k=0; k < aBoardSize; k++)
        {
            cout<<"---+";

        }
        cout<<endl<<' '<<col<<" |";
        col++;
        for(int j=0;j< aBoardSize;j++)
        {
            cout<<' ';

            if(aBoard[i][j].itsPieceType == SWORD)
            {
                cout<<"\u25CF";
            }
            else if(aBoard[i][j].itsPieceType == SHIELD)
            {
                cout<<"\u25CB";
            }
            else if(aBoard[i][j].itsPieceType == KING)
            {
                cout<<"\u2654";
            }
            else if(aBoard[i][j].itsCellType == FORTRESS)
            {
                cout<<'X';
            }
            else if(aBoard[i][j].itsCellType == CASTLE)
            {
                cout<<"\u2616";
            }
            else
            {
                cout<<' ';
            }
            cout<<" |";

        }
        cout<<endl;
    }
    cout<<"   +";
    for(int k=0; k < aBoardSize; k++)
    {
        cout<<"---+";

    }
}

Position getPositionFromInput()
{
    int col;
    char row;
    string rest;//the rest of the input, he is empty if the last caracter is a integer
    Position Pos;
    cout<<"What is the position ('row column' without space): ";
    cin>>row>>col;
    getline(cin, rest);
    row = tolower(row);
    if(!(row>='a' && row<='z') || !(col>0) || !rest.empty())
    {
        return {-1,-1};
    }
    else
    {
        Pos.itsCol=col-1;
        Pos.itsRow=row-97;
    }
    return Pos;
}

bool isValidPosition(const Position& aPos, const BoardSize& aBoardSize)
{
    return aPos.itsCol<aBoardSize && aPos.itsRow<aBoardSize && aPos.itsCol > -1 && aPos.itsRow > -1;
}

bool isEmptyCell(const Cell aBoard[][BOARD_SIZE_MAX], const Position& aPos)
{
    return aBoard[aPos.itsRow][aPos.itsCol].itsPieceType == NONE;
}

bool isValidMovement(const PlayerRole& aPlayer, const Cell aBoard[][BOARD_SIZE_MAX],const Position& aStartPos,const Position& aEndPos)
{
    if((aStartPos.itsCol != aEndPos.itsCol && aStartPos.itsRow != aEndPos.itsRow) || isEmptyCell(aBoard,aStartPos))
    {
        return false;
    }
    if(aPlayer == ATTACK && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != SWORD)
    {
        return false;
    }
    if(aPlayer == DEFENSE && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType == SWORD)
    {
        return false;
    }
    Position Pos;
    int depRow = (aStartPos.itsRow<aEndPos.itsRow)?aStartPos.itsRow:aEndPos.itsRow;
    int endRow = (aStartPos.itsRow>aEndPos.itsRow)?aStartPos.itsRow:aEndPos.itsRow;
    for (depRow ; depRow <= endRow ; depRow++) // The check is from the lowest position to the highest position
    {
        int depCol = (aStartPos.itsCol<aEndPos.itsCol)?aStartPos.itsCol:aEndPos.itsCol;
        int endCol = (aStartPos.itsCol>aEndPos.itsCol)?aStartPos.itsCol:aEndPos.itsCol;
        for (depCol ; depCol <= endCol ; depCol++)
        {
            Pos.itsCol = depCol;
            Pos.itsRow = depRow;
            if((aBoard[Pos.itsRow][Pos.itsCol].itsCellType == FORTRESS || aBoard[Pos.itsRow][Pos.itsCol].itsCellType == CASTLE) && aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType != KING)
            {
                cout<<"There is just the King who can cross the castle or the fortress"<<endl;
                return false;
            }
            if((depCol != aStartPos.itsCol || depRow != aStartPos.itsRow ) && !isEmptyCell(aBoard, Pos))
            {
                cout<<"There is a piece on the way"<<endl;
                return false;
            }

        }
    }

    return true;

}

void movePiece(Cell aBoard[][BOARD_SIZE_MAX], const Position& aStartPos, const Position& aEndPos)
{
    aBoard[aEndPos.itsRow][aEndPos.itsCol].itsPieceType=aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType;
    aBoard[aStartPos.itsRow][aStartPos.itsCol].itsPieceType=NONE;

}

void capturePieces(const PlayerRole& aPlayer, Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize, const Position& aEndPos)
{
    if (aPlayer == ATTACK)
    {
        if(aEndPos.itsCol == 0)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsCol == aBoardSize-1)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsRow == 0)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsRow == aBoardSize-1)
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SWORD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SHIELD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SWORD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }

    }
    else
    {
        if(aEndPos.itsCol == 0)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsCol == aBoardSize-1)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsRow == 0)
        {
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else if(aEndPos.itsRow == aBoardSize-1)
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == KING  || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS  || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == KING || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
        else
        {
            if(aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow-1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType == SWORD && (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == SHIELD || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == KING || aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow+2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow+1][aEndPos.itsCol].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol-2].itsPieceType == KING || aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsCellType == CASTLE && aBoard[aEndPos.itsRow-2][aEndPos.itsCol].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol-1].itsPieceType = NONE;
            }
            if(aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType == SWORD && (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == SHIELD || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == KING || aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == FORTRESS || (aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsCellType == CASTLE && aBoard[aEndPos.itsRow][aEndPos.itsCol+2].itsPieceType == NONE)))
            {
                aBoard[aEndPos.itsRow][aEndPos.itsCol+1].itsPieceType = NONE;
            }
        }
    }
}

bool isSwordLeft(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    for (int i = 0; i < aBoardSize; ++i)
    {
        for (int j = 0; j < aBoardSize; ++j)
        {
            if(aBoard[i][j].itsPieceType == SWORD)
            {
                return true;
            }
        }
    }
    return false;
}

Position getKingPosition(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    Position Pos;
    for (int i = 0; i < aBoardSize; ++i)
    {
        for (int j = 0; j < aBoardSize; ++j)
        {
            Pos.itsRow=i;
            Pos.itsCol=j;
            if(aBoard[i][j].itsPieceType == KING)
            {
                return Pos;
            }
        }
    }
    return {-1, -1};
}

bool isKingEscaped(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    Position King = getKingPosition(aBoard,aBoardSize);
    return aBoard[King.itsRow][King.itsCol].itsCellType == FORTRESS;
}

bool isKingCaptured(const Cell aBoard[][BOARD_SIZE_MAX], const BoardSize& aBoardSize)
{
    Position King = getKingPosition(aBoard,aBoardSize);
    if (King.itsCol == 0)
    {
        return (aBoard[King.itsRow+1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow+1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow+1][King.itsCol].itsCellType == CASTLE)
                && (aBoard[King.itsRow-1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow-1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow-1][King.itsCol].itsCellType == CASTLE)
                && (aBoard[King.itsRow][King.itsCol+1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol+1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol+1].itsCellType == CASTLE);
    }
    else if (King.itsRow == 0)
    {
        return (aBoard[King.itsRow+1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow+1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow+1][King.itsCol].itsCellType == CASTLE)
                && (aBoard[King.itsRow][King.itsCol+1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol+1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol+1].itsCellType == CASTLE)
                && (aBoard[King.itsRow][King.itsCol-1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol-1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol-1].itsCellType == CASTLE);
    }
    else if (King.itsCol == aBoardSize-1)
    {
        return (aBoard[King.itsRow+1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow+1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow+1][King.itsCol].itsCellType == CASTLE)
               && (aBoard[King.itsRow][King.itsCol-1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol-1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol-1].itsCellType == CASTLE)
               && (aBoard[King.itsRow-1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow-1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow-1][King.itsCol].itsCellType == CASTLE);
    }
    else if (King.itsRow == aBoardSize-1)
    {
        return (aBoard[King.itsRow][King.itsCol+1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol+1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol+1].itsCellType == CASTLE)
               && (aBoard[King.itsRow][King.itsCol-1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol-1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol-1].itsCellType == CASTLE)
               && (aBoard[King.itsRow-1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow-1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow-1][King.itsCol].itsCellType == CASTLE);
    }
    else
    {
        return (aBoard[King.itsRow][King.itsCol+1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol+1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol+1].itsCellType == CASTLE)
               && (aBoard[King.itsRow][King.itsCol-1].itsPieceType == SWORD || aBoard[King.itsRow][King.itsCol-1].itsCellType == FORTRESS || aBoard[King.itsRow][King.itsCol-1].itsCellType == CASTLE)
               && (aBoard[King.itsRow-1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow-1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow-1][King.itsCol].itsCellType == CASTLE)
               && (aBoard[King.itsRow+1][King.itsCol].itsPieceType == SWORD || aBoard[King.itsRow+1][King.itsCol].itsCellType == FORTRESS || aBoard[King.itsRow+1][King.itsCol].itsCellType == CASTLE);
    }
}






