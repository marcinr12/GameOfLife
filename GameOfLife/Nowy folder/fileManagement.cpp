#include "fileManagement.h"

vector<string> fileManagement::encode(Grid g)
{
	vector<string> toReturn(g.getCells().size());
	for (int i = 0; i < g.getCells().size(); i++)
	{
		if (g.getCells()[i].size() == 0)
			continue;
		if (g.getCells()[i].size() == 1)
			toReturn[i] = g.getCells()[i][0].getStatus();

		int j = 0;
		int k = 1;
		while (k < g.getCells()[i].size())
		{
			if (g.getCells()[i][j].getStatus() == g.getCells()[i][k].getStatus())
			{
				toReturn[i] += to_string(k - j);
				if (g.getCells()[i][j].getStatus() == true)
					toReturn[i] += 'T';
				else
					toReturn[i] += 'F';

				j = k;
			}
			k++;
		}
		toReturn[i] += to_string(k - j);
		if (g.getCells()[i][j].getStatus() == true)
			toReturn[i] += 'T';
		else
			toReturn[i] += 'F';

	}


	/*string toReturn = "";
	if (w.size() == 0)
		return toReturn;
	if (w.size() == 1)
	{
		toReturn = w[0];
		return toReturn;
	}
	int i = 0;
	int j = 1;
	while (j < w.size())
	{
		if (w[i] != w[j])
		{
			toReturn += to_string(j - i);
			if (w[i] == true)
				toReturn += 'T';
			else
				toReturn += 'F';
			i = j;
		}
		j++;
	}
	toReturn += to_string(j - i);
	if (w[i] == true)
		toReturn += 'T';
	else
		toReturn += 'F';*/




	return toReturn;
}

void fileManagement::saveStateToFile(Grid g)
{

}
