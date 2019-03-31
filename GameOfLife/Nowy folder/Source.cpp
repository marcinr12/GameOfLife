#include <iostream>
#include <chrono>
#include "Cell.h"
#include "Grid.h"
#include "InitialCondition.h"

// TO DO 
// #include <ncurses.h>

// README
// WASD navigation
// G change status of blinking cell
// V start game


using namespace std;

int main()
{
	//InitialCondition ic;
	//Grid grid(ic.getSizeX(), ic.getSizeY());
	//grid.navigate();
	//grid.start(500, ic.getVerticalCongition(), ic.getHorizontalCondition());

	Grid t(5, 5);
	shared_ptr<Cell> cell = t.getCell(3, 3);
	t.getCell(3,3)->setStatus(1);

	t.getCells()[3][4].setStatus(1);
	t.getCells()[3][5].setStatus(1);
	t.printGrid();
	cout << t.cells[3][3].getStatus() << endl;
	cout << t.getCell(3, 3)->getStatus() << endl;

	system("pause");

	return 0;
}