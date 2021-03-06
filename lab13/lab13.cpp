/*
Егошин Игорь, ПС-22, VS2017
13.10. Абракадабра (9)
Строка s называется супрефиксом для строки t, если t начинается с s и заканчивается на s.
Например, «abra» является супрефиксом для строки «abracadabra». В частности, сама строка t
является своим супрефиксом. Супрефиксы играют важную роль в различных алгоритмах на
строках.
В этой задаче требуется решить обратную задачу поиска. Задан словарь, содержащий n слов t 1 ,
t 2 , …, t n и набор из m строк-образцов s 1 , s 2 , …, s m . Необходимо для каждой строки-образца из
заданного набора найти количество слов в словаре, для которых эта строка-образец является
супрефиксом.
Ввод. Первая строка входного файла содержит целое число n (1 ≤ n ≤ 200 000). Последующие n
строк содержат слова t 1 , t 2 , …, t n, по одному слову в каждой строке. Каждое слово состоит из
строчных букв латинского алфавита. Длина каждого слова не превышает 50. Суммарная длина
всех слов не превышает 10 6 . Словарь не содержит пустых слов. Затем следует строка, содержащая
целое число m (1 ≤ m ≤ 200 000). Последующие m строк содержат строки-образцы s 1 , s 2 , …, s m , по
одной на каждой строке. Каждая строка-образец состоит из строчных букв латинского алфавита:
Длина каждой строки-образца не превышает 50. Суммарная длина всех строк-образцов не
превышает 10 6 . Никакая строка-образец не является пустой строкой.
Вывод. Выходной файл должен содержать m чисел, по одному на строке. Для каждой строки-
образца в порядке, в котором они заданы во входном файле, следует вывести количество слов
словаря, для которых она является супрефиксом.
*/

#include "stdafx.h"

using namespace std;

const size_t HIGH_RANGE_PLUS_ONE = 200001;

string GetSuprString(const string& str);
vector<unsigned> GetSupremsVector(const vector<string>& wordsVector, const vector<pair<string, size_t>>& samplesVector, size_t m);
vector<string> GetVectorOfStrings(istream& input, size_t quantity);
vector<pair<string, size_t>> GetPairVectorOfStrings(istream& input, size_t quantity);
void PrintSuprsAmount(ostream& output, const vector<unsigned>& suprsAmountVector);
bool SampleAndWordCorrespondence(const string& sample, const string& word);

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

	size_t n, m;
	inFile >> n;
	auto wordsVector = GetVectorOfStrings(inFile, n);
	inFile >> m;
	auto samplesVector = GetPairVectorOfStrings(inFile, m);
	sort(wordsVector.begin(), wordsVector.end());
	sort(samplesVector.begin(), samplesVector.end(), [](pair<string, size_t> a, pair<string, size_t> b) { return a.first < b.first; });
	PrintSuprsAmount(outFile, GetSupremsVector(wordsVector, samplesVector, m));
	return 0;
}


vector<string> GetVectorOfStrings(istream& input, size_t quantity)
{
	vector<string> strVector;
	strVector.reserve(quantity);
	string str;
	for (size_t i = 0; i < quantity; ++i)
	{
		input >> str;
		str = GetSuprString(str);
		strVector.push_back(str);
	}
	return strVector;
}

vector<pair<string, size_t>> GetPairVectorOfStrings(istream& input, size_t quantity)
{
	vector<pair<string, size_t>> strVector;
	strVector.reserve(quantity);
	string str;
	for (size_t i = 0; i < quantity; ++i)
	{
		input >> str;
		str = GetSuprString(str);
		strVector.push_back({ str, i });
	}
	return strVector;
}

string GetSuprString(const string& str)
{
	string tempString = "";
	auto strSize = str.size();
	int i = 0, k = strSize == 0 ? 0 : strSize - 1;
	for (; i < strSize; ++i, --k)
	{
		tempString += str[i];
		tempString += str[k];
	}
	return tempString;
}

void PrintSuprsAmount(ostream& output, const vector<unsigned>& suprsAmountVector)
{
	for (size_t i = 0; i < suprsAmountVector.size(); ++i)
	{
		output << to_string(suprsAmountVector[i]) << '\n';
	}
}
bool SampleAndWordCorrespondence(const string& sample, const string& word)
{
	auto sampleSize = sample.size();
	auto wordSubstr = word.substr(0, sampleSize);
	return sample == wordSubstr;
}
vector<unsigned> GetSupremsVector(const vector<string>& wordsVector, const vector<pair<string, size_t>>& samplesVector, size_t m)
{
	vector<unsigned> suprsQuantityVector(m, 0);
	auto samplesVectorSize = samplesVector.size();
	auto wordsVectorSize = wordsVector.size();
	size_t i = 0, j = 0, tempIndex = 0;
	bool tempIndexIsFound = false, firstCorrespondentIsFound = false;
	int counter = 0;
	for (; i < samplesVectorSize; ++i)
	{
		j = tempIndex;
		tempIndexIsFound = false;
		while (wordsVector[j] < samplesVector[i].first)
		{
			++j;
			if (j == wordsVectorSize)
			{
				break;
			}
		}
		tempIndex = j;
		for (; j < wordsVectorSize; ++j)
		{
			if (SampleAndWordCorrespondence(samplesVector[i].first, wordsVector[j]))
			{
				if (!tempIndexIsFound && samplesVector[i].first != wordsVector[j])
				{
					tempIndexIsFound = true;
					tempIndex = j;
				}
				++counter;
			}
			else
			{
				break;
			}
		}
		if (firstCorrespondentIsFound && !tempIndexIsFound)
		{
			tempIndex = j;
		}
		suprsQuantityVector[samplesVector[i].second] = counter;
		i = i + 1;
		for (; i < samplesVectorSize; ++i)
		{
			if (samplesVector[i].first == samplesVector[i - 1].first)
			{
				suprsQuantityVector[samplesVector[i].second] = counter;
			}
			else
			{
				--i;
				break;
			}
		}
		counter = 0;
	}
	return suprsQuantityVector;
}