#ifndef CONVEXHULL_H
#define CONVEXHULL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <ctime>

class ConvexHull
{
public:
	explicit ConvexHull();
	~ConvexHull();

	void setFilename();
	std::string getFilename() const;
	std::vector<std::vector<int>> buildVertexList(const std::string &);
	void numericallyOrganize(std::vector<std::vector<int>> &);
	void deleteDuplicates(std::vector<std::vector<int>> &);
	std::vector<std::vector<int>> DivideAndConquer(std::vector<std::vector<int>>);
	std::vector<std::vector<int>> bruteConvexHull(std::vector<std::vector<int>>);
	std::vector<std::vector<int>> merger(std::vector<std::vector<int>>, std::vector<std::vector<int>>);
	void clockwise(std::vector<std::vector<int>> &);
	void printConvexHull(std::vector<std::vector<int>>);


	void xycoordinates(std::string, int &, int &); // changes int x and y to the values found on the current line of the textfile 
	bool its_a_number(char); // returns true if a number is present
	bool its_a_number_exp(char); // returns true if a number, decimal, or minus char is present

private:
	std::string filename;
	std::vector<std::vector<int>> coordinates; // 2-d vector holds coordinates for all points
	std::vector<std::vector<int>> convex_hull; // 2-d vector holds coordinates for the convex hull

};


#endif
