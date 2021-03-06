/*
Егошин Игорь, ПС-22, VS 2017
2.8. Калькулятор (7)
Одна фирма выпускает в продажу странные калькуляторы. Они могут выполнять лишь три
операции:
. ввести число 1;
. удвоить текущее число;
. поменять в текущем числе первую и последнюю цифры.
Калькулятор умеет работать лишь с целыми числами от 1 до L (1 ≤ L ≤ 10 5 ). Незначащие нули в
начале числа отбрасываются. Написать программу, которая проверяет, можно ли на данном
калькуляторе получить число N (1 ≤ N ≤ 10 5 ). Если это возможно, выдать самую короткую
последовательность преобразований.
Ввод. В единственной строке находятся через пробел значения число L и N.
Вывод. В первой строке вывести Yes или No. Если значение N достижимо, во второй строке
выдать количество значений в цепочке преобразований от 1 до N, а в третьей строке через пробел
сами эти значения.
Примеры
Ввод 1			Ввод 2
100 61			100 3
Вывод 1			Вывод 2
Yes				No
6
1 2 4 8 16 61
*/

#include "stdafx.h"

using namespace std;

int ChangeLastAndFirstDigit(int i);
int CountsOfDigit(int i);
bool GetNumber(int& i, int needNumber, int maxNumber, unordered_map<int, int>& digitsMap);
vector<int> GetPath(int i, unordered_map<int, int> digitsMap);
void PrintPath(vector<int> path, ofstream& outFile);

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

	int i = -1;
	int needNumber;
	int maxNumber;
	inFile >> maxNumber >> needNumber;
	unordered_map<int, int> digitsMap;
	if (GetNumber(i, needNumber, maxNumber, digitsMap))
	{
		outFile << "Yes\n";
		vector<int> path = GetPath(i, digitsMap);
		outFile << path.size() << "\n";
		PrintPath(path, outFile);
	}
	else
		outFile << "No\n";
	inFile.close();
	outFile.close();
	return 0;
}

int ChangeLastAndFirstDigit(int i)
{
	if (i < 10)
		return i;
	int delimeter = static_cast<int>(pow(10, CountsOfDigit(i) - 1));
	int lastDigit = i % 10;
	int firstDigit = i / delimeter;
	return (lastDigit * delimeter) + (((i % delimeter) / 10) * 10) + firstDigit;
}

int CountsOfDigit(int i)
{
	int count = (i == 0) ? 1 : 0;
	while (i != 0)
	{
		count++;
		i /= 10;
	}
	return count;
}

bool GetNumber(int& i, int needNumber, int maxNumber, unordered_map<int, int>& digitsMap)
{
	int doubledI;
	int reversedI;
	digitsMap.insert(pair<int, int>(1, -1));
	queue<int> q;
	q.push(1);
	while (!q.empty())
	{
		i = q.front();
		q.pop();
		if (i != needNumber)
		{
			reversedI = ChangeLastAndFirstDigit(i);
			doubledI = i * 2;
			if (digitsMap.find(doubledI) == digitsMap.end() && doubledI <= maxNumber)
			{
				q.push(doubledI);
				digitsMap.insert(pair<int, int>(doubledI, i));
			}
			if (digitsMap.find(reversedI) == digitsMap.end() && reversedI <= maxNumber)
			{
				q.push(reversedI);
				digitsMap.insert(pair<int, int>(reversedI, i));
			}
		}
		else
			break;
	}
	return i == needNumber;
}

vector<int> GetPath(int i, unordered_map<int, int> digitsMap)
{
	vector<int> path;
	path.push_back(i);
	while (digitsMap[i] != -1)
	{
		i = digitsMap[i];
		path.push_back(i);
	}
	reverse(path.begin(), path.end());
	return path;
}

void PrintPath(vector<int> path, ofstream& outFile)
{
	size_t pathElementsAmount = path.size();
	for (size_t i = 0; i < pathElementsAmount; ++i)
	{
		outFile << path[i];
		if (i + 1 != pathElementsAmount)
			outFile << " ";
	}
	outFile << "\n";
}