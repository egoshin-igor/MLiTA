/*
Егошин Игорь, ПС-22, VS
Найти выпуклую оболочку множества точек методом Грэхема.
Ввод из файла INPUT.TXT. В первой строке находится число N (1 ≤ N ≤ 10 5 ) , задающее
количество точек. Следующие N строк содержат пары целых чисел - координаты точек (X i , Y i ).
Вывод в файл OUTPUT.TXT. В первой строке выводится M – количество вершин минимальной
оболочки. Следующие N строк содержат пары целых чисел - координаты вершин (X i , Y i ) в порядке
обхода против часовой стрелки, начиная от самой левой из самых нижних вершин.
Ограничения: координаты целые и по модулю не превосходят 10000, время 1 с.
*/

#include "stdafx.h"

using namespace std;

const double E = 0.0001;

struct Coord
{
	int x;
	int y;
};

Coord minCoord;

vector<Coord> GetCoords(istream& input, Coord& minCoord, size_t N);
double CosAlpha(Coord currVector);
double GetZCoord(Coord a, Coord b, Coord c);
double LenBeetwenPoints(Coord a, Coord b);
vector<Coord> GetStack(vector<Coord>& points, size_t N);
void PrintPoints(ostream& output, vector<Coord>& points);
struct SortByAngle
{
	bool operator () (Coord a, Coord b)
	{
		auto zCoord = GetZCoord(minCoord, a, b);
		if (a.x == b.x && a.y == b.y) return true;
		/*Coord vectorA = { a.x - minCoord.x, a.y - minCoord.y };
		Coord vectorB = { b.x - minCoord.x, b.y - minCoord.y };
		auto angleA = acos(CosAlpha(vectorA));
		auto angleB = acos(CosAlpha(vectorB));
		if (abs(angleA - angleB) < E)
		{
			return LenBeetwenPoints(minCoord, a) < LenBeetwenPoints(minCoord, b);
		}
		return angleA < angleB;*/
		if (abs(zCoord) < E)
		{
			return LenBeetwenPoints(minCoord, a) < LenBeetwenPoints(minCoord, b);
		}
		return zCoord > 0;
	}
};

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
	size_t N;
	inFile >> N;
	vector<Coord> points;
	points = GetCoords(inFile, minCoord, N);
	sort(points.begin() + 1, points.end(), SortByAngle());
	vector<Coord> stack;
	stack = GetStack(points, N);
	PrintPoints(outFile, stack);
	return 0;
}

vector<Coord> GetCoords(istream& input, Coord& minCoord, size_t N)
{
	vector<Coord> coords;
	Coord point;
	minCoord.x = 100001;
	minCoord.y = 100001;
	size_t k;
	for (size_t i = 0; i < N; ++i)
	{
		input >> point.x >> point.y;
		if (point.y <= minCoord.y)
		{
			if (point.y < minCoord.y)
			{
				k = i;
				minCoord.y = point.y;
				minCoord.x = point.x;
			}
			else if (point.x < minCoord.x)
			{
				k = i;
				minCoord.x = point.x;
			}

		}
		coords.push_back(point);
	}
	swap(coords[0], coords[k]);
	return coords;
}

double CosAlpha(Coord currVector)
{
	double currX = (double) currVector.x;
	double currY = (double)currVector.y;
	return currX / sqrt(currX * currX + currY * currY);
}

double GetZCoord(Coord a, Coord b, Coord c)
{
	return (((double)(b.x - a.x)) * ((double)(c.y - b.y)) - ((double)(b.y - a.y)) * ((double)(c.x - b.x)));
}

double LenBeetwenPoints(Coord a, Coord b)
{
	auto ax = (double)a.x;
	auto bx = (double)b.x;
	auto ay = (double)a.y;
	auto by = (double)b.y;
	return sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
}

vector<Coord> GetStack(vector<Coord>& points, size_t N)
{
	vector<Coord> stack;
	stack.push_back(points[0]);
	stack.push_back(points[1]);
	double zCoord;
	size_t lastElem = 1;
	for (size_t i = 2; i < N; ++i)
	{
		zCoord = GetZCoord(stack[lastElem - 1], stack[lastElem], points[i]);
		while ((lastElem > 0) && (zCoord < 0 || abs(zCoord) < E))
		{
			stack.pop_back();
			--lastElem;
			zCoord = GetZCoord(stack[lastElem - 1], stack[lastElem], points[i]);
		}
		stack.push_back(points[i]);
		++lastElem;
	}
	return stack;
}

void PrintPoints(ostream& output, vector<Coord>& points)
{
	auto pointsLen = points.size();
	output << to_string(pointsLen) << '\n';
	for (size_t i = 0; i < points.size(); ++i)
	{
		output << points[i].x << ' ' << points[i].y << '\n';
	}
}