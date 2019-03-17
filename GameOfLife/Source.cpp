#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"
#include "InitialCondition.h"

// TO DO 
// #include <ncurses.h>


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