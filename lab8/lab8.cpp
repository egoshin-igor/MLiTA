/*
Егошин Игорь, ПС-22, VS 2017, 8.3
В матрице A размера NN числа от 1 до N 2 . Каждое число записано ровно один раз. Даны две
матрицы размера NN: Top и Left. Значение Top i j определяет количество чисел, больших A i j и
расположенных выше по столбцу, Left i j - количество чисел, больших A i j и расположенных левее по
строке. Найти возможные значения матрицы A. Если решений несколько, вывести любое.
Ввод из файла INPUT.TXT. В первой строке N (1 ≤ N ≤100), затем N строк матрицы Top (числа
через пробел), затем N строк матрицы Left. Числа в обеих матрицах от 0 до N.
Вывод в файл OUTPUT.TXT матрицы A – N строк, числа в строке через пробел. Если решений
нет, вывести 0.
*/

#include "stdafx.h"

using namespace std;

void InitMatrix(vector<vector<int>>& matrix, int value, int N);
vector<vector<int>> GetMatrix(istream& input, int N);
bool LocateElement(vector<vector<int>>& matrix, vector<vector<int>>& top, vector<vector<int>>& left, int elem, int N);
bool FillMatrix(vector<vector<int>>& matrix, vector<vector<int>>& top, vector<vector<int>>& left, int N);
void PrintMatrix(ostream& output, vector<vector<int>>& matrix, int N);
bool isCorrectData(vector<vector<int>>& top, vector<vector<int>>& left, int N);

int main()
{
	const string inFileName = "input.txt";
	const string outFileName = "output.txt";
	ifstream inFile(inFileName);
	ofstream outFile(outFileName);
	if (!inFile.is_open())
	{
		cerr << "File " << inFileName << " can't be opened\n";
		return 1;
	}
	if (!outFile.is_open())
	{
		cerr << "File " << outFileName << " can't be opened\n";
		return 1;
	}

	int N;
	inFile >> N;
	vector<vector<int>> top = GetMatrix(inFile, N);
	vector<vector<int>> left = GetMatrix(inFile, N);
	vector<vector<int>> matrix(N, vector<int>(N));
	InitMatrix(matrix, 0, N);
	if (!isCorrectData(top, left, N) || !FillMatrix(matrix, top, left, N))
	{
		outFile << 0 << '\n';
	}
	else
	{
		PrintMatrix(outFile, matrix, N);
	}
	return 0;
}

vector<vector<int>> GetMatrix(istream& input, int N)
{
	vector<vector<int>> matrix(N, vector<int>(N));
	for (size_t i = 0; i < static_cast<size_t>(N); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(N); ++j)
		{
			input >> matrix[i][j];
		}
	}
	return matrix;
}

void InitMatrix(vector<vector<int>>& matrix, int value, int N)
{
	for (size_t i = 0; i < static_cast<size_t>(N); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(N); ++j)
		{
			matrix[i][j] = 0;
		}
	}
}

void PrintMatrix(ostream& output, vector<vector<int>>& matrix, int N)
{
	for (size_t i = 0; i < static_cast<size_t>(N); output << '\n', ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(N); ++j)
		{
			output << matrix[i][j] << '\t';
		}
	}
}

bool LocateElement(vector<vector<int>>& matrix, vector<vector<int>>& top, vector<vector<int>>& left, int elem, int N)
{
	int freeI = 0, freeJ = 0, free;
	bool possibleToPut;
	for (size_t i = 0; i < static_cast<size_t>(N); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(N); ++j)
		{
			if (matrix[i][j] == 0)
			{
				++freeJ;
				freeI = 0;
				for (size_t k = 0; k < i; ++k)
				{
					freeI += matrix[k][j] == 0 ? 1 : 0;
				}
				possibleToPut = top[i][j] == 0 && freeI > 0 || freeI > top[i][j] ? false : true;

				if (possibleToPut)
				for (size_t k = i; k < static_cast<size_t>(N); ++k)
				{
					if (top[k][j] == 0 && elem > matrix[k][j] && matrix[k][j] != 0 ||
						top[k][j] != 0 && freeI <= top[k][j] && i != k && matrix[k][j] == 0)
					{
						possibleToPut = false;
						break;
					}
					if (matrix[k][j] == 0)
					{
						++freeI;
					}
				}
				/*
				free = 0;
				for (size_t k = 0; k < j; ++k)
				{
					free += matrix[i][k] == 0 ? 1 : 0;
				}
				*/
				free = freeJ - 1;
				possibleToPut = left[i][j] == 0 && free > 0 || free > left[i][j] ? false: possibleToPut;

				if (possibleToPut)
				for (size_t k = j; k < static_cast<size_t>(N); ++k)
				{
					if (left[i][k] == 0 && elem > matrix[i][k] && matrix[i][k] != 0 ||
						left[i][k] != 0 && free <= left[i][k] && k != j && matrix[i][k] == 0)
					{
						possibleToPut = false;
						break;
					}
					if (matrix[i][k] == 0)
					{
						++free;
					}
				}
				
				if (possibleToPut)
				{
					matrix[i][j] = elem;
					return true;
				}
			}
		}
		freeJ = 0;
	}
	return false;
}

bool FillMatrix(vector<vector<int>>& matrix, vector<vector<int>>& top, vector<vector<int>>& left, int N)
{
	for (int i = 1; i <= N * N; ++i)
	{
		if (!LocateElement(matrix, top, left, i, N))
		{
			return false;
		}
	}
	return true;
}

bool isCorrectData(vector<vector<int>>& top, vector<vector<int>>& left, int N)
{
	for (size_t i = 0; i < static_cast<size_t>(N); ++i)
	{
		for (size_t j = 0; j < static_cast<size_t>(N); ++j)
		{
			if (static_cast<size_t>(left[i][j]) > j || static_cast<size_t>(top[i][j] > i))
			{
				return false;
			}
		}
	}
	return true;
}