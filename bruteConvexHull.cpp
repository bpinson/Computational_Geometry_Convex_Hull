#include "ConvexHull.h"


std::vector<std::vector<int>> ConvexHull::bruteConvexHull(std::vector<std::vector<int>> input)
{
	
	int n = 0;
	int size = input[0].size();
	std::vector<std::vector<int>> output;
	output.resize(2, std::vector<int>(size, 0));
	if (size < 4)
	{

		for (int i = 0; i < size; i++)
		{

			output[0][i] = input[0][i];
			output[1][i] = input[1][i];
		}
		numericallyOrganize(output); // after finding all convex hull input the list is numerically organized from the x-coordinate
		deleteDuplicates(output); // after numerically organizing all duplicate input are deleted
		return output;
	}






	for (int i = 0; i < size; i++) // scans through all points
	{
		for (int j = i + 1; j < size; j++) // scans through all other points to form a line
		{
			bool above = false;
			bool below = false;
			bool parallelOutside = false;
			for (int k = 0; k < size; k++) // compares the line to this point
			{
				if (k != i && k != j)
				{
					if (input[0][i] - input[0][j] == 0) //this is to avoid dividing by zero when calculating slope
					{
						if (input[0][k] < input[0][i])
							above = true;
						else if (input[0][k] > input[0][i])
							below = true;
						else if(input[1][k] < input[1][i] || input[1][k] > input[1][j])  // calculates if point k is outside of line segment (i,j)
								parallelOutside = true;
	
					}
					else
					{
						float m = (input[1][i] - input[1][j]) / ((float)(input[0][i] - input[0][j])); // slope 
						float b = (input[1][i] - m * input[0][i]); // y-intercept

						if (input[1][k] > (m * input[0][k] + b))
							above = true;
						else if (input[1][k] < (m * input[0][k] + b))
							below = true;
						else if (input[0][k] < input[0][i] || input[0][k] > input[0][j])
							parallelOutside = true;
					}
				//	std::cout << "(" << input[0][i] << ", " << input[1][i] << ") (" << input[0][j] << ", " << input[1][j] << ") compared to: (" << input[0][k] << ", " << input[1][k] << ") is above: " << above << " below: " << below << " parrallelBetween: "<< parallelOutside << std::endl;
				}
			}
			if (((above && !below) || (!above && below)) && !parallelOutside) // successfully found a convex hull coordinate
			{
//				std::cout << "found: (" << input[0][i] << ", " << input[1][i] << ") (" << input[0][j] << ", " << input[1][j] << ")" << std::endl;

				output[0].push_back(0);
				output[1].push_back(0);
				output[0][n] = input[0][i];
				output[1][n] = input[1][i];
				n++;
				output[0].push_back(0);
				output[1].push_back(0);
				output[0][n] = input[0][j];
				output[1][n] = input[1][j];
				n++;
			}
		}
	}

	numericallyOrganize(output); // after finding all convex hull input the list is numerically organized from the x-coordinate
    deleteDuplicates(output); // after numerically organizing all duplicate input are deleted



	return output;
}




