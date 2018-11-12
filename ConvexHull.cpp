#include "ConvexHull.h"




ConvexHull::ConvexHull() // Constructor for ConvexHull class
{
	setFilename();
	buildVertexList(getFilename());
	numericallyOrganize(coordinates);
    convex_hull = DivideAndConquer(coordinates);
	printConvexHull(convex_hull);


}

ConvexHull::~ConvexHull()
{

}


void ConvexHull::setFilename() // asks user to input filename or defaults to "input.txt"
{
	std::getline(std::cin, filename);

	if (filename == "q")
		exit(1);
	else
	{
		if (filename == "\0")
		{
filename = "input.txt";
		}
	}
}



std::string ConvexHull::getFilename() const // returns filename
{
	return filename;
}


std::vector<std::vector<int>> ConvexHull::buildVertexList(const std::string &input) // opens file or will report error message
{

	std::fstream textfile;
	textfile.open(input);
	if (textfile.is_open())
	{
		std::string line;
		std::getline(textfile, line); //skips to next line
		int vertices = std::stoi(line); //number of vertices
		int x = 0; //x axis coordinate
		int y = 0; //y axis coordinate


		coordinates.resize(2, std::vector<int>(vertices, 0));


		for (int i = 0; i < vertices; i++) //loop scans through each line of textfile and creates a linked list;
		{
			std::getline(textfile, line); //skips to next line
			xycoordinates(line, x, y); // changes int x and y to the values found on the current line of the textfile
			coordinates[0][i] = x;
			coordinates[1][i] = y;
		}

  		return coordinates;
	}
	else
	{
		std::cout << "\nError file not found" << std::endl;
		std::cout << "Input name of text file or press \'enter\' if filename is: input.txt" << std::endl;
		std::cout << "Type 'q' to quit program\n" << std::endl;
		setFilename();
		buildVertexList(getFilename());
	}

	textfile.close();
	return coordinates;
}

void ConvexHull::numericallyOrganize(std::vector<std::vector<int>> &input)
{
	int size = input[0].size();
	int tempX;
	int tempY;

	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (input[0][j] < input[0][i] || (input[0][j] == input[0][i] && input[1][j] < input[1][i]))
			{
				tempX = input[0][i];
				tempY = input[1][i];
				input[0][i] = input[0][j];
				input[1][i] = input[1][j];
				input[0][j] = tempX;
				input[1][j] = tempY;
			}
		}
	}
}

void ConvexHull::deleteDuplicates(std::vector<std::vector<int>> &input)
{
    int size = input[0].size();
	for (int i = 0; i < size; i++)
	{
		if (i < size - 1)
		{
			if (input[0][i] == input[0][i + 1] && input[1][i] == input[1][i + 1])
			{
				input[0].erase(input[0].begin() + i);
				input[1].erase(input[1].begin() + i);
				i--;
                size--;
			}
		}
	}
}



void ConvexHull::printConvexHull(std::vector<std::vector<int>> input)
{
    int size = input[0].size();
	std::cout << size << std::endl;

	for (int i = 0; i < size; i++) // prints out coordinates
	{
		std::cout << input[0][i] << ", " << input[1][i] << std::endl;
	}
}





void ConvexHull::xycoordinates(std::string line, int &x, int &y) // changes int x and y to the values found on the current line of the textfile
{
	x = 0;
	y = 0;
	int start = 0; // marks the first char in the line that contains a number or decimal point
	int i = 0; // loop control

	int size = line.length();

	for (; i < size; i++) //scans for end of numerical value and calculates x
	{
		if (!its_a_number_exp(line[i]))
		{
			x = std::stoi(line.substr(start, i));
			break;
		}
	}

	i++;
    start = i;

	for(; i < size; i++) //scans for end of numerical value and calculates y
	{

		if ( i+1 == size)
		{
			y = std::stoi(line.substr(start, i));
			break;
		}
	}
}



bool ConvexHull::its_a_number_exp(char a) // returns true if a number, decimal, or minus char is present
{
	if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' ||
		a == '6' || a == '7' || a == '8' || a == '9' || a == '-')
		return true;
	else
		return false;
}

bool ConvexHull::its_a_number(char a) // returns true if there is a number present
{
	if (a == '0' || a == '1' || a == '2' || a == '3' || a == '4' || a == '5' ||
		a == '6' || a == '7' || a == '8' || a == '9')
		return true;
	else
		return false;
}



		
