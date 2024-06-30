#ifndef Terrain_h
#define Terrain_h

#include <iostream>
#include <sstream>
#include <random>
#include <cstdlib>
// #include <string>

using namespace std;

namespace TerrainSpace
{
    // Rangechecking
    const int minRow = 2, maxRow = 10, minCol = 2, maxCol = 10;

    // Error codes.
    const int ERR_ARGC = -1;
    const int ERR_Range = -2;
    const int ERR_Exit = -3;
    const int Quit = -4;

    // Game pieces
    const char Space = '.';
    const char Player = 'P';
    const char Imm_obstacles = '#';
    const char Energy_units = 'T';
    const char Mines = 'M';

    int string_to_int(std::string str);
    int gen_rand(int low, int high);

    typedef char *One_D_Array;
    typedef char **Two_D_Array;

    // setting up the game world
    Two_D_Array alloc2D(int row, int col);
    void Dealloc(Two_D_Array &arr, int row);
    void Display(Two_D_Array &arr, int row, int col, int playerE);
    void inarr(Two_D_Array &arr, int row, int col);
    void placepiece(Two_D_Array &arr, int row, int col, const char feature, int num);
    void placeplayer(Two_D_Array &arr, int row, int col, char feature, int &pCol);

    // Play the game.
    void Play_Game(Two_D_Array &arr, int &pRow, int &pCol, int pEnergy, int r, int c, bool Gamecontinue);
    void Pause();
    void check_Energy(int energy, bool resume);

}

#endif
