/*
Brian Pinson
U91813366
Convex Hull Project
09/13/2017
*/


#include "ConvexHull.h"




int main()
{
	while (1)
	{
		std::cout << "\n******************************************" << std::endl;
		std::cout << "Convex Hull Calculator" << std::endl;
		std::cout << "Input name of text file or press \'enter\' if filename is: input.txt" << std::endl;
		std::cout << "Type 'q' to quit program" << std::endl;
		std::cout << "******************************************\n" << std::endl;


        clock_t start = std::clock();   
		ConvexHull convexhull;
        clock_t finish = std::clock();
        double time = double(finish - start) / CLOCKS_PER_SEC;
        std::cout << time << std::endl;
	}
	
	return 0;
}


