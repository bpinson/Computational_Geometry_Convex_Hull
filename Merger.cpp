#include "ConvexHull.h"

std::vector<std::vector<int>> ConvexHull::merger(std::vector<std::vector<int>> left, std::vector<std::vector<int>> right)
{

	int leftSize = left[0].size();
	int rightSize = right[0].size();


	// Merges the left and right convex hulls
	std::vector<std::vector<int>> merged;
	merged.clear();
	merged.resize(2, std::vector<int>(leftSize + rightSize, 0));
	int mergeSize = merged[0].size();

	int m = 0;
	for (m = 0; m < leftSize; m++)
	{
		merged[0][m] = left[0][m];
		merged[1][m] = left[1][m];
	}
	for (int n = 0; n < rightSize; m++, n++)
	{
		merged[0][m] = right[0][n];
		merged[1][m] = right[1][n];
	}

    int tangentUpL = 0;
    int tangentUpR = 0;
    int tangentLoL = 0;
    int tangentLoR = 0; 




    bool foundUpper = false;
    bool foundLower = false;



	for (int i = 0; i < leftSize; i++)
	{
		for (int j = 0; j < rightSize; j++)
		{
		bool above = false;
		bool below = false;
		bool parallelOutside = false;
			for (int k = 0; k < mergeSize; k++)
			{
				if (k != i && k != j+leftSize)
				{
					if (left[0][i] - right[0][j] == 0) //this is to avoid dividing by zero when calculating slope
					{
						if (merged[0][k] < left[0][i])
							above = true;
						else if (merged[0][k] > left[0][i])
							below = true;
						else if (merged[1][k] < left[1][i] || merged[1][k] > right[1][j])  // calculates if point k is outside of line segment (i,j)
							parallelOutside = true;

					}
					else
					{
						double m = (left[1][i] - right[1][j]) / ((double)(left[0][i] - right[0][j])); // slope 
						double b = left[1][i] - m * left[0][i]; // y-intercept

						if (merged[1][k] > (m * merged[0][k] + b))
							above = true;
						else if (merged[1][k] < (m * merged[0][k] + b))
							below = true;
						else if (merged[0][k] < left[0][i] || merged[0][k] > right[0][j])
							parallelOutside = true;
					}
				}
			}
			if (!above && below && !parallelOutside) // successfully found a convex hull coordinate
			{
				foundUpper = true;

                tangentUpL = i;
                tangentUpR = j+leftSize;

		
			}
			else if (above && !below && !parallelOutside) // successfully found a convex hull coordinate
			{
        		foundLower = true;
                tangentLoL = i;
                tangentLoR = j+leftSize; 
			}
			above = false;
			below = false;
			parallelOutside = false;
		}
    if(foundUpper && foundLower)
    break;
	}



//	std::cout << "found upper tangent: (" << merged[0][tangentUpL] << ", " << merged[1][tangentUpL] << "), (" << merged[0][tangentUpR] << ", " << merged[1][tangentUpR] << ")" << std::endl;
//	std::cout << "found lower tangent: (" << merged[0][tangentLoL] << ", " << merged[1][tangentLoL] << "), (" << merged[0][tangentLoR] << ", " << merged[1][tangentLoR] << ")" << std::endl;
  
	// tangent deleter

for(int i = 0; i < mergeSize; i++)
    {
    bool deleteThis = false;
    if(merged[0][i] == merged[0][tangentUpL] && merged[0][i] == merged[0][tangentLoL] && merged[0][i] == merged[0][tangentUpR] && merged[0][i] == merged[0][tangentLoR]) //everything is a straight line
        deleteThis = true;
    else if(merged[1][i] == merged[1][tangentUpL] && merged[1][i] == merged[1][tangentLoL] && merged[1][i] == merged[1][tangentUpR] && merged[1][i] == merged[1][tangentLoR]) //everything is a straight line
        deleteThis = true;
    else if(i != tangentUpL && i != tangentUpR && i != tangentLoL && i != tangentLoR) // avoiding deleting upper and lower tangent points
    {
        float areaQuad = 0.5 *(merged[0][tangentLoL] * merged[1][tangentUpL] + merged[0][tangentUpL] * merged[1][tangentUpR] + 
                        merged[0][tangentUpR] * merged[1][tangentLoR] + merged[0][tangentLoR] * merged[1][tangentLoL] -
                        merged[0][tangentUpL] * merged[1][tangentLoL] - merged[0][tangentUpR] * merged[1][tangentUpL] -
                         merged[0][tangentLoR] * merged[1][tangentUpR] - merged[0][tangentLoL] * merged[1][tangentLoR]);

    float tri1 = 0.5 *(merged[0][i] * (merged[1][tangentLoL] - merged[1][tangentUpL]) + merged[0][tangentLoL] * (merged[1][tangentUpL] - merged[1][i]) + merged[0][tangentUpL] * (merged[1][i] - merged[1][tangentLoL]));
    float tri2 = 0.5 *(merged[0][i] * (merged[1][tangentUpL] - merged[1][tangentUpR]) + merged[0][tangentUpL] * (merged[1][tangentUpR] - merged[1][i]) + merged[0][tangentUpR] * (merged[1][i] - merged[1][tangentUpL]));
    float tri3 = 0.5 *(merged[0][i] * (merged[1][tangentUpR] - merged[1][tangentLoR]) + merged[0][tangentUpR] * (merged[1][tangentLoR] - merged[1][i]) + merged[0][tangentLoR] * (merged[1][i] - merged[1][tangentUpR]));
    float tri4 = 0.5 *(merged[0][i] * (merged[1][tangentLoR] - merged[1][tangentLoL]) + merged[0][tangentLoR] * (merged[1][tangentLoL] - merged[1][i]) + merged[0][tangentLoL] * (merged[1][i] - merged[1][tangentLoR]));
    float triSum = tri1 + tri2 + tri3 + tri4;

    if(triSum == areaQuad)
    {
        deleteThis = true;
    }
    
   if(deleteThis)
    {   
                merged[0].erase(merged[0].begin() + i);
				merged[1].erase(merged[1].begin() + i);
                if(tangentUpL > i) 
                tangentUpL--;
                if(tangentUpR > i) 
                tangentUpR--;
                if(tangentLoL > i) 
                tangentLoL--;
                if(tangentLoR > i) 
                tangentLoR--;
                i--;
                mergeSize--;
        }
    }
}





	return merged;
}
