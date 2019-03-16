#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"

// TO DO 
// #include <ncurses.h>


using namespace std;

int main()
{

	const unsigned int sizeX = 30;
	const unsigned int sizeY = 30;

	Grid grid(sizeX, sizeY);

	//grid.cells[2][1].setStatus(true);
	//grid.cells[2][2].setStatus(true);
	//grid.cells[2][3].setStatus(true);
	grid.navigate();
	grid.printGrid();


	grid.start(500);

	

	system("pause");

	return 0;
}