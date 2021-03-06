/*
Егошин Игорь, ПС-22, VS2017
10.12. Последовательность 4 (6)
Имеется последовательность целых чисел x 1 , x 2 , …, x n . Найти количество троек чисел, в каждой
из которых одно из чисел равно сумме двух других.
Ввод из файла INPUT.TXT. В первой строке содержится значение n (3 ≤ n ≤ 2000). Во второй
строке заданы через пробел значения x 1 , x 2 , …, x n (1  x i  10 5 ).
Вывод в файл OUTPUT.TXT. В единственной строке выводится количество указанных троек
чисел (x i , x j , x k ).
*/

#include "stdafx.h"

void WriteNumbersInVector(std::istream& input, std::vector<int>& numbersArr);
std::unordered_map<int, int> FillMap(std::vector<int> numbersArr);
int CountTriplets(std::vector<int>& numbersArr, std::unordered_map<int, int> numbersMap, size_t numbersAmount);

int main()
{
	const std::string inFileName = "input.txt";
	const std::string outFileName = "output.txt";
	std::ifstream inFile(inFileName);
	std::ofstream outFile(outFileName);
	if (!inFile.is_open())
	{
		std::cerr << "File " << inFileName << " can't be opened\n";
		return 1;
	}
	if (!outFile.is_open())
	{
		std::cerr << "File " << outFileName << " can't be opened\n";
		return 1;
	}
	std::vector<int> numbersArr;
	size_t numbersAmount;
	inFile >> numbersAmount;
	numbersArr.reserve(numbersAmount * 4);
	WriteNumbersInVector(inFile, numbersArr);
	std::sort(numbersArr.rbegin(), numbersArr.rend(), [](int a, int b) {return a > b; });
	std::unordered_map<int, int> numbersMap = FillMap(numbersArr);
	int tripletsAmount = CountTriplets(numbersArr, numbersMap, numbersAmount);
	outFile << tripletsAmount << std::endl;
	return 0;
}

void WriteNumbersInVector(std::istream& input, std::vector<int>& numbersArr)
{
	int number;
	while (input >> number)
	{
		numbersArr.push_back(number);
	}
}

std::unordered_map<int, int> FillMap(std::vector<int> numbersArr)
{
	std::unordered_map<int, int> numbersMap;
	for (auto i : numbersArr)
	{
		++numbersMap[i];
	}
	return numbersMap;
}

int CountTriplets(std::vector<int>& numbersArr, std::unordered_map<int, int> numbersMap, size_t numbersAmount)
{
	int tripletsAmount = 0;
	int twoNumbersSum;
	int maxNumber = numbersArr[numbersAmount - 1];
	for (size_t i = 0; i < numbersAmount; ++i)
	{
		if ((i != numbersAmount - 1) && ((numbersArr[i] + numbersArr[i + 1])) > maxNumber)
		{
			break;
		}
		for (size_t j = i + 1; j < numbersAmount; ++j)
		{
			twoNumbersSum = numbersArr[i] + numbersArr[j];
			if (twoNumbersSum > maxNumber)
			{
				break;
			}
			auto result = numbersMap.find(twoNumbersSum);
			if (result != numbersMap.end())
			{
				tripletsAmount += result->second;
			}
		}
	}
	return tripletsAmount;
}
