#include "stdafx.h"
#include "stack.h"

using namespace std;


int **matrix, n, k;
Stack *stackPtr = new Stack;


template <typename fileType>
void CheckIfFileIsOpen(fileType &file, const char *fileName);

void CreateMatrix(ifstream &inFile);

void goToTree(int indexes[]);

void FenceBuilding(int i, int j, int &fenceAmount);

//Подфункции для FenceBuilding
void PushInStack(int i, int j, int &fenceAmount);

void PopFromStack(int &i, int &j);
//Подфункции для FenceBuilding

int main()
{
	const char *inFileName = "input.txt";
	const char *outFileName = "output.txt";
	int indexes[2];
	int fenceAmount = 0;
	ifstream inFile;
	CheckIfFileIsOpen(inFile, inFileName);
	CreateMatrix(inFile);
	goToTree(indexes);
	FenceBuilding(indexes[0], indexes[1], fenceAmount);
	ofstream outFile;
	CheckIfFileIsOpen(outFile, outFileName);
	outFile << fenceAmount << "\n";
	inFile.close();
	outFile.close();
	return 0;
}

template <typename fileType>
void CheckIfFileIsOpen(fileType &file, const char *fileName)
{
	file.open(fileName);
	if (!file.is_open())
	{
		cerr << "Error: file " << fileName << " is not open\n";
		exit(0);
	}
}

void goToTree(int indexes[])
{
	indexes[0] = 0;
	indexes[1] = 0;
	for (int i = 1; i < n - 1; ++i)
		for (int j = 1; j < k - 1; ++j)
			if (matrix[i][j] == 1) 
			{
				indexes[0] = i - 1;
				indexes[1] = j - 1;
				return;
			}
}

void PushInStack(int i, int j, int &fenceAmount)
{
	if (matrix[i][j] == 0)
	{
		stackPtr->add(i, j, stackPtr);
		matrix[i][j] = 2;
	}
	else if (matrix[i][j] == 1)
		++fenceAmount;

}

void PopFromStack(int &i, int &j)
{
	stackPtr->pop(i, j, stackPtr);
}

void FenceBuilding(int i, int j, int &fenceAmount)
{
	stackPtr->head = NULL;
	PushInStack(i, j, fenceAmount);

	while (stackPtr->head != NULL) {
		PopFromStack(i, j);
		PushInStack(i, j + 1, fenceAmount);
		PushInStack(i - 1, j, fenceAmount);
		PushInStack(i, j - 1, fenceAmount);
		PushInStack(i + 1, j, fenceAmount);
	}
}

void CreateMatrix(ifstream &inFile)
{
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