/*
Егошин Игорь, ПС-22, VS 2017
4.2. Треугольник (5)
Ниже изображен пример треугольника из чисел. Найти наибольшую сумму чисел,
расположенных на пути из верхней точки треугольника до основания.

7
3 8
8 1 6
4 2 3 0

Каждый шаг на пути происходит в направлении вниз по диагонали (влево или вправо). Число
строк в треугольнике от 1 до 100. Треугольник составлен из целых чисел от 0 до 99.
Ввод из файла INPUT.TXT. Первое число определяет количество строк треугольника N
(N ≤ 300). Далее задаются строки треугольника.
Вывод в файл OUTPUT.TXT. В первой строке выводится единственное число – наибольшая
сумма. Во второй строке выдаются через пробел числа от вершины треугольника до основания,
дающие наибольшую сумму. Если решений несколько, вывести любое из них.
Пример
Ввод
4
7
3 8
8 1 6
4 2 3 0
Вывод
24
7 8 6 3
*/

#include "stdafx.h"
#pragma optimize( "", off )

using namespace std;

struct tringle
{
	int value;
	int sum;
	char direction;
};

void fillTringleMatrix(ifstream& inFile, tringle** tringleMatrix, int tringleDepth);
void findMaxSum(tringle** tringleMatrix, int tringleDepth);
void printPath(ofstream& outFile, tringle** tringleMatrix, int tringleDepth);

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

	int tringleDepth = 0;
	inFile >> tringleDepth;
	tringle** tringleMatrix;
	tringleMatrix = new tringle* [tringleDepth];
	for (int i = 0; i < tringleDepth; ++i)
		tringleMatrix[i] = new tringle[i + 1];

	fillTringleMatrix(inFile, tringleMatrix, tringleDepth);

	findMaxSum(tringleMatrix, tringleDepth);
	outFile << tringleMatrix[0][0].sum << "\n";
	printPath(outFile, tringleMatrix, tringleDepth);
    return 0;
}

void fillTringleMatrix(ifstream& inFile, tringle** tringleMatrix, int tringleDepth)
{
	int value;
	int tringleChecker = 0;
	for (int i = 0; i < tringleDepth; ++tringleChecker , ++i)
		for (int j = 0; j <= tringleChecker; ++j)
		{
			inFile >> value;
			tringleMatrix[i][j].value = value;
			if (i == tringleDepth - 1)
				tringleMatrix[i][j].sum = tringleMatrix[i][j].value;
			else
				tringleMatrix[i][j].sum = 0;
		}
}

void findMaxSum(tringle** tringleMatrix, int tringleDepth)
{
	int tempValue;
	int tringleChecker = tringleDepth;
	for (int i = tringleDepth - 1; i > 0; --tringleChecker, --i)
		for (int j = 0; j < tringleChecker; ++j)
		{
			if (j != 0 && j != tringleChecker - 1)
			{
				tempValue = tringleMatrix[i - 1][j].value + tringleMatrix[i][j].sum;
				if (tringleMatrix[i - 1][j].sum < tempValue)
				{
					tringleMatrix[i - 1][j].sum = tempValue;
					tringleMatrix[i - 1][j].direction = 'l';
				}
				tempValue = tringleMatrix[i - 1][j - 1].value + tringleMatrix[i][j].sum;
				if (tringleMatrix[i - 1][j - 1].sum < tempValue)
				{
					tringleMatrix[i - 1][j - 1].sum = tempValue;
					tringleMatrix[i - 1][j - 1].direction = 'r';
				}
			} 
			else if (j == 0)
			{
				tempValue = tringleMatrix[i - 1][j].value + tringleMatrix[i][j].sum;
				if (tempValue > tringleMatrix[i - 1][j].sum)
				{
					tringleMatrix[i - 1][j].sum = tempValue;
					tringleMatrix[i - 1][j].direction = 'l';
				}
			}
			else if (j == tringleChecker - 1)
			{
				tempValue = tringleMatrix[i - 1][j - 1].value + tringleMatrix[i][j].sum;
				if (tempValue > tringleMatrix[i - 1][j - 1].sum)
				{
					tringleMatrix[i - 1][j - 1].sum = tempValue;
					tringleMatrix[i - 1][j - 1].direction = 'r';
				}
			}
		}
}

void printPath(ofstream& outFile, tringle** tringleMatrix, int tringleDepth)
{
	int i = 0;
	int j = 0;
	outFile << tringleMatrix[i][j].value << ' ';
	while (i != tringleDepth - 1)
	{
		if (tringleMatrix[i][j].direction == 'l')
			++i;
		else
		{
			++i;
			++j;
		}
		outFile << tringleMatrix[i][j].value;
		if (i != tringleDepth - 1)
			outFile << " ";
		else
			outFile << "\n";
	}
}