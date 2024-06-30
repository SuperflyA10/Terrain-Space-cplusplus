#include "Terrain.h"


using namespace std;

namespace TerrainSpace
{
    int string_to_int(string str) //Function for convertiing string to integer
    {
        int num;
        stringstream ss(str);
            ss>>num;

            if(ss.fail())
            {
                cout << "Invalid arguments."<< endl;
            }
            return num;
    }

    int gen_rand(int low, int high) //function for generating randon number
    {
        int result;
        result = low + (rand()%(high-low));
        return result;
    }

     void Pause() //Pause function
     {
        cin.ignore(100, '\n');
        cout << "Press Enter to continue." << endl;
        cin.get();
     }
    void Display(Two_D_Array &arr,int row,int col,int playerE) //function for displaying the 3d array
    {
         for(int r=0;r<row;r++)
        {
            for(int c=0;c<col;c++)
            {
                cout << arr[r][c] << " ";
            }
            cout << endl;
        }
        cout << endl << "Player energy units left: " << playerE<< " units." << endl;
    }

    Two_D_Array alloc2D(int row, int col) //function for allocating memory into a 2d array
    {
        Two_D_Array newArray;
        newArray = new One_D_Array[row];
        for(int r=0;r<row;r++)
        {
            newArray[r] = new char(col);
        }
        return newArray;
    }

    void Dealloc(Two_D_Array &arr, int row) //function for deallocating memory into a 2d array
    {
        for(int r=0; r<row; r++)
        {
            delete[] arr[r];
        }
        delete[] arr;
        arr=nullptr;
    }

    void inarr(Two_D_Array &arr,int row, int col) //function for intitialising the array
    {
        for(int r=0;r<row;r++)
        {
            for(int c=0;c<col;c++)
            {
                arr[r][c]= Space;
            }
        }
    }

     void placepiece(Two_D_Array &arr,int row, int col, char feature, int num) //function for randomly placing the pieces on the board(2d array)
     {
         int ROW,COL;
         int temp=0;
         while(temp<num)
         {
             ROW = gen_rand(0,row);
             COL = gen_rand(0,col);
            while(arr[ROW][COL]== Space)
            {
                arr[ROW][COL] = feature;
                temp+=1;
            }
         }
     }

     void placeplayer(Two_D_Array &arr,int row, int col, char feature,int &pCol) //functiion for randomly placing the player piece on the board
     {
         int ROW,COL;
         int temp=0;
         while(temp<1)
         {
             ROW = row-1;
            COL = gen_rand(0,col);
            while(arr[ROW][COL]== Space)
            {
                arr[ROW][COL] = feature;
                pCol = COL;
                temp+=1;
            }
         }
     }

     void Play_Game(Two_D_Array &arr, int &pRow,int &pCol, int pEnergy,int r,int c,bool Gamecontinue) //function for playing the gae
     {
         char Movement;
         cout << endl;
         Display(arr,r,c,pEnergy);

         do{
            system("cls");
            cout << "Press to move: " << endl
            << "W is up" << endl
            << "S is down" << endl
            << "A is left" << endl
            << "D is right" << endl
            << "Q to quit" << endl << endl;
            Display(arr,r,c,pEnergy); // dsiplay the gaameboard

            if(pEnergy < 1) //checking if the play has energy to continue with game.
            {
                cout << "You have lost,Player is out of Energy." << endl;
                Gamecontinue = false;
                break;
            }
            else{

            cin >> Movement;

            switch(Movement) //switch case for moving the players peice
            {
                case 'w': //moving the player the up
                case 'W':
                    if(arr[pRow-1][pCol]==Space) //checking if the play move up
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow-1][pCol] = Player;
                        pRow-=1;
                        if(pRow == 0) //checking the play has won after moving up
                        {
                            cout << "Congratulations, you have WON, you reached your destination!!!" << endl;
                            Display(arr,r,c,pEnergy);
                            Gamecontinue = false;
                        }
                        pEnergy -= 1;
                        break;
                    }
                    else if(arr[pRow-1][pCol]==Energy_units) //checking if there is an energy unit to increase the players energy
                    {
                        arr[pRow-1][pCol] = Player;
                        arr[pRow][pCol] = Space;
                        pRow-=1;
                        if(pRow == 0)
                        {
                            cout << "Congratulations, you have WON, you reached your destination!!!" << endl;
                            Display(arr,r,c,pEnergy);
                            Gamecontinue = false;
                        }
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if(arr[pRow-1][pCol]==Mines) ////checking if there is mine
                    {
                        cout << "Player lost, Player entered a mine at Row " <<pRow-1<< " ,column " << pCol<< "."<< endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Imm_obstacles)
                    {
                        arr[pRow][pCol] = Player;
                        break;
                    }
                break;

                case 's': //Moving the player piece down
                case 'S':

                    if(pRow+1>=r)
                    {
                        cout << "Player may not move outside of the game world" << endl;
                        pEnergy -= 1;
                        //break;
                    }
                    else{
                    if(arr[pRow+1][pCol]==Space) //empty space
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow+1][pCol] = Player;
                        pRow+=1;
                        pEnergy -= 1;
                        break;
                    }
                    else if(arr[pRow+1][pCol]==Energy_units) //energy unit
                    {
                        arr[pRow+1][pCol] = Player;
                        arr[pRow][pCol] = Space;
                        pRow+=1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if(arr[pRow+1][pCol]==Mines) //Mines
                    {
                        cout << "Player lost, Player entered a mine at Row " <<pRow+1<< " ,column " << pCol<< "."<< endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Imm_obstacles)
                    {
                        arr[pRow][pCol] = Player;
                        break;
                    }
                    }
                    break;

                case 'a': //Moving the player piece left
                case 'A':
                    if(pCol-1<0)
                    {
                        cout << "Player may not move outside of the game worls" << endl;
                        pEnergy -= 1;
                        break;
                    }
                    else{
                    if(arr[pRow][pCol-1]==Space) //empty space
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow][pCol-1] = Player;
                        pCol-=1;
                        pEnergy -= 1;
                        break;
                    }
                    else if(arr[pRow][pCol-1]==Energy_units) //energy unit
                    {
                        arr[pRow][pCol-1] = Player;
                        arr[pRow][pCol] = Space;
                        pCol-=1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if(arr[pRow][pCol-1]==Mines) //Mines
                    {
                        cout << "Player lost, Player entered a mine at Row " <<pRow<< " ,column " << pCol-1<< "."<< endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Imm_obstacles)
                    {
                        arr[pRow][pCol] = Player;
                        break;
                    }
                    }
                    break;

                case 'd': //Moving the player piece right
                case 'D':

                    if(pCol+1>=r)
                    {
                        cout << "Player may not move outside of the game world" << endl;
                        pEnergy += 1;
                        break;
                    }
                    else{
                    if(arr[pRow][pCol+1]==Space) //empty space
                    {
                        arr[pRow][pCol] = Space;
                        arr[pRow][pCol+1] = Player;
                        pCol+=1;
                        pEnergy -= 1;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Energy_units) //energy unit
                    {
                        arr[pRow][pCol+1] = Player;
                        arr[pRow][pCol] = Space;
                        pCol+=1;
                        pEnergy -= 1;
                        pEnergy += 5;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Mines) //Mines
                    {
                        cout << "Player lost, Player entered a mine at Row " <<pRow<< " ,column " << pCol+1<< "." << endl;
                        Gamecontinue = false;
                        break;
                    }
                    else if(arr[pRow][pCol+1]==Imm_obstacles)
                    {
                        arr[pRow][pCol] = Player;
                        break;
                    }
                    }
                break;

                case 'q': //option for player to quit the game.
                case 'Q':
                    cout << "You quit the game, better luck next time" << endl;
                    Gamecontinue = false;
                    break;

                default:
                    cerr << "Invalid input. " << endl;
                    Pause();
            }
            }
         }while(Gamecontinue);


     }
}

