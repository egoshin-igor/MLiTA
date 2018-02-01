#include "stdafx.h"
#include "stack.h"

using namespace std;

int **matrix, n, k;
Stack *stackPtr;

void CreateMatrix();
void goToTree(int indexes[]);
void FenceBuilding(int i, int j, int &fenceAmount);
//Подфункции для FenceBuilding
void PushInStack(int i, int j, Stack *&stackPtr);
void PopFromStack(int i, int j, Stack *&stackPtr);
//Подфункции для FenceBuilding

int main()
{
	int indexes[2];
	int i, j;
	int fenceAmount = 0;
	CreateMatrix();
	goToTree(indexes);
	FenceBuilding(indexes[0], indexes[1], fenceAmount);
	cout << fenceAmount;
	ofstream outFile("output.txt");
	for (int i = 0; i < n; outFile << "\n", ++i)
		for (int j = 0; j < k; ++j)
			outFile << matrix[i][j];
}

void goToTree(int indexes[])
{
	indexes[0] = -1;
	indexes[1] = -1;
	for (int i = 1; i < n - 1; ++i)
		for (int j = 1; j < k - 1; ++j)
			if (matrix[i][j] == 1) 
			{
				indexes[0] = i - 1;
				indexes[1] = j - 1;
				return;
			}
}

void PushInStack(int i, int j, Stack *&stackPtr)
{
	if (matrix[i][j] == 0)
	{
		stackPtr->add(i, j, stackPtr);
		matrix[i][j] = 2;
	}

}

void PopFromStack(int &i, int &j, Stack *&stackPtr)
{
	stackPtr->pop(i, j, stackPtr);
}

void FenceBuilding(int i, int j, int &fenceAmount)
{
	Stack *stackPtr;
	stackPtr->head = NULL;
	
	while (stackPtr->head != NULL) {
		matrix[i][j] = 2;
		
	}
}

void CreateMatrix() 
{
	const char *fileName = "input.txt";
	ifstream inFile;
	inFile.open(fileName);
	if (!inFile.is_open())
	{
		cerr << "Error: file " << fileName << " is not open\n";
		exit(0);
	}
	string line;
	inFile >> n >> k;
	n = n + 4; //Барьер
	k = k + 4; //Барьер
	getline(inFile, line);
	getline(inFile, line);
	matrix = new int *[n];
	for (int i = 0; i < n; ++i)
		matrix[i] = new int[k];
	for (int i = 0; i < n; ++i)
	{
		matrix[i][k - 1] = 2;
		matrix[i][0] = 2;
		matrix[i][k - 2] = 0;
		matrix[i][1] = 0;
	}
	for (int j = 1; j < k - 1; ++j)
	{
		matrix[0][j] = 2;
		matrix[n - 1][j] = 2;
		matrix[1][j] = 0;
		matrix[n - 2][j] = 0;
	}
	for (int i = 2; i < n - 2; getline(inFile, line), ++i)
		for (int j = 2; j < k - 2; ++j)
			if (line[j - 2] == '1')
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
}