
#include "stdafx.h"
using namespace std;

int **matrix, n, k;

void CreateMatrix();
void FindFirstTree(int indexes[]);
void FenceBuilding(int i, int j, int &fenceAmount, string side);

int main() 
{
	int indexes[2];
	int fenceAmount = 0;
	CreateMatrix();
	FindFirstTree(indexes);
	FenceBuilding(indexes[0], indexes[1], fenceAmount, "none");
	cout << fenceAmount;
	ofstream outFile("output.txt");
	for (int i = 0; i < n; outFile << "\n", ++i)
		for (int j = 0; j < k; ++j)
			outFile << matrix[i][j];
}

void FindFirstTree(int indexes[]) 
{
	indexes[0] = -1;
	indexes[1] = -1;
	for (int i = 1; i < n - 1; ++i)
		for (int j = 1; j < k - 1; ++j)
			if (matrix[i][j] == 1) {
				indexes[0] = i;
				indexes[1] = j;
				return;
			}
}

void FenceBuilding(int i, int j, int &fenceAmount, string side) 
{
	if (matrix[i][j] == 1) 
	{
		matrix[i][j] = 0;
		FenceBuilding(i, j - 1, fenceAmount, "left");
		FenceBuilding(i + 1, j, fenceAmount, "down");
		FenceBuilding(i, j + 1, fenceAmount, "right");
		FenceBuilding(i - 1, j, fenceAmount, "up");
	}
	else if (matrix[i][j] == 0) 
	{
		++fenceAmount;
	}
}

void CreateMatrix() {
	const char *fileName = "input.txt";
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile) {
		cerr << "Error: file " << fileName << " is not open\n";
		exit(0);
	}
	string line;
	inFile >> n >> k;
	n = n + 2; //Барьер
	k = k + 2;
	getline(inFile, line);
	getline(inFile, line);
	matrix = new int *[n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new int[k];
	for (int i = 0; i < n; ++i) 
	{
		matrix[i][k - 1] = 0;
		matrix[i][0] = 0;
	}
	for (int j = 1; j < k - 1; ++j) 
	{
		matrix[0][j] = 0;
		matrix[n - 1][j] = 0;
	}
	for (int i = 1; i < n - 1; ++i, getline(inFile, line))
		for (int j = 1; j < k - 1; ++j)
			if (line[j - 1] == '1')
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
}