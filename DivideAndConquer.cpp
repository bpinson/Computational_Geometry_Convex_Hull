#include "ConvexHull.h"

std::vector<std::vector<int>> ConvexHull::DivideAndConquer(std::vector<std::vector<int>> input)
{
	int size = input[0].size();
	if (size < 5) // if there are less than four points polygon function returns
    {   
        return input;
    }

	std::vector<std::vector<int>> lowerHalf; // contains lower bounds
	lowerHalf.resize(2, std::vector<int>(size/2, 0));
	std::vector<std::vector<int>> upperHalf; // contains upper bounds
	upperHalf.resize(2, std::vector<int>(size-size/2, 0));


	int i = 0;
	for (i = 0; i < size/2; i++)
	{
		lowerHalf[0][i] = input[0][i];
		lowerHalf[1][i] = input[1][i];
	}
	
	for (int n = 0; i < size; i++, n++)
	{
		upperHalf[0][n] = input[0][i];
		upperHalf[1][n] = input[1][i];
	}


	DivideAndConquer(lowerHalf);
	DivideAndConquer(upperHalf);


	return merger(lowerHalf, upperHalf);
}
