#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"
#include "InitialCondition.h"
#include "fileManagement.h"

// TO DO 
// #include <ncurses.h>

// README
// WASD navigation
// G change status of blinking cell
// V start game
// P pause / start
// -> F save to file
// -> L load from file
// -> C clear grid


using namespace std;

int main()
{
	InitialCondition ic;
	Grid grid(ic.getSizeX(), ic.getSizeY());
	grid.navigate();
	grid.start(500, ic.getVerticalCongition(), ic.getHorizontalCondition());

	system("pause");

	return 0;
}