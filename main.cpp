#include "Terrain.h"
#include <time.h>
#include <cstdlib>

using namespace TerrainSpace;

int main(int argc, char* argv[])
{
    char Select;
    int Num_rows,Num_cols,Num_obstacles,Num_energy,Num_mines;
    int Player_energy = 7;
    bool Resume = true;
    bool blncontinue = true;
    srand(time(nullptr));

    int playerR,playerC;

    if(argc!=6) //error handling for arguments.
    {
        cout << " Not enough number of arguments. " << endl;
        exit(ERR_ARGC);
    }


    Num_rows = string_to_int(argv[1]);
    Num_cols = string_to_int(argv[2]);
    Num_obstacles = string_to_int(argv[3]);
    Num_energy = string_to_int(argv[4]);
    Num_mines = string_to_int(argv[5]);

    //Range check
    if(Num_rows<minRow || Num_rows>maxRow || Num_cols<minCol || Num_cols>maxCol)
    {
        cout << "Number of rows must be less than " << minRow << " and greater than " << maxRow << "." << endl;
        cout << "Number of columns must be less than " << minCol << " and greater than " << maxCol << "." << endl;
        exit(ERR_Range);
    }

    //make the gameboard
    Two_D_Array game;
    game = alloc2D(Num_rows,Num_cols);
    inarr(game,Num_rows,Num_cols);

    do{
        system("cls");
        cout << "Welcome, Would you like to play  the game?" << endl
            << "Option A: Start the game." << endl
            << "Option X: Exit." << endl << endl;

        cout << "Number of Rows: " << Num_rows << endl;
        cout << "Number  of columns: " << Num_cols << endl;
        cout << "Number of obstacles: " << Num_obstacles << endl;
        cout << "Number of energy units: " << Num_energy << endl;
        cout << "Number of mines: " << Num_mines << endl << endl;
    cin >> Select;


    switch(Select)
    {
        case 'a':
        case 'A':


            //setting up the gameboard and placing all the necessary pieces.
            placepiece(game,Num_rows,Num_cols,Imm_obstacles,Num_obstacles);
            placepiece(game,Num_rows,Num_cols,Energy_units,Num_energy);
            placepiece(game,Num_rows,Num_cols,Mines,Num_mines);
            playerR = Num_rows-1;
            placeplayer(game,Num_rows,Num_cols,Player,playerC);

            //Playing the game
            Play_Game(game,playerR,playerC,Player_energy,Num_rows,Num_cols,Resume);

            break;
        case 'x':
        case 'X':
            cout << "Hope you had a good game, lets play again next time." << endl;
            Dealloc(game,Num_rows);
            blncontinue = false;
            exit(ERR_Exit);
            break;
        default:
            cerr << "Invalid input " << endl;
            //Pause();
            break;
    }
    cout << endl;
    Pause();
    }while(blncontinue);
    //deallocating memory
    Dealloc(game,Num_rows);

}
