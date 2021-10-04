#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#include <iostream>
#include <math.h>
#include <iomanip>
#include <cstring>
#include <string.h>

using namespace std;
class Triangle;
enum ORIENT
{
	LEFT, RIGHT, AHEAD, BEHIND, BETWEEN
};


class Point
{
public:
	// Конструктор 
	Point(double _x = 0, double _y = 0)
	{
		x = _x;
		y = _y;
	}
	// Другие методы 
	void Show() const;
	Point operator +(Point&);
	Point operator -(Point&);
	double Length() const;
	ORIENT Classify(Point beg_p, Point end_p) 
	{
		Point p0 = *this; Point a = end_p - beg_p; Point b = p0 - beg_p; double sa = a.x * b.y -
			b.x * a.y;
		if (sa > 0.0) 
			return LEFT;
		if (sa < 0.0)
			return RIGHT;
		if ((a.x * b.x < 0.0) || (a.y * b.y < 0.0)) 
			return BEHIND;
		if (a.Length() < b.Length())
			return AHEAD;
		return BETWEEN;
	}
	bool InTriangle(Triangle& tria);
	
public:
	double x, y;
};

void Point::Show() const 
{
	cout << " (" << x << ","<< y << ")"; 
}
Point Point::operator +(Point& p)
{
	return Point(x + p.x, y + p.y);
}
Point Point::operator -(Point& p)
{
	return Point(x - p.x, y - p.y);
}
double Point::Length() const
{
	return sqrt(x * x + y * y);
}


class Triangle {
public:
	Triangle(Point, Point, Point, const char*);
	// конструктор 
	Triangle(const char*);
	// конструктор пустого (нулевого) треугольника 
	~Triangle();
	// деструктор 
	Point Get_v1() const
	{
		return vl;
	}
	// Получить значение vl 
	Point Get_v2() const
	{
		return v2;
	}
	// Получить значение v2 
	Point Get_v3() const
	{
		return v3;
	}
	// Получить значение v3 
	char* GetName() const
	{
		return name;
	}
	// Получить имя объекта 
	void Show() const;
	// Показать объект 
	void ShowSideAndArea() const;
	// Показать стороны и площадь объекта 
	bool TriaInTria(Triangle trial, Triangle tria2);
	
public:
	int count = 0;
	// кол-во созданных объектов 
private:

	char* objID;
	// идентификатор объекта 
	char* name;
	// наименование треугольника 
	Point vl, v2, v3;
	// вершины 
	double a;
	// сторона, соединяющая vl и v2 
	double b;
	// сторона, соединяющая v2 и v3 
	double c;
	// сторона, соединяющая vl и v3 
};

Triangle::Triangle(Point _v1, Point _v2, Point _v3, const char* ident)
{
	char buf[16];
	objID = new char[strlen(ident) + 1];
	strcpy(objID, ident);
	count++;
	sprintf(buf, "Треугольник %d", count);
	a = sqrt((vl.x - v2.x) * (vl.x - v2.x) + (vl.y - v2.y) * (vl.y - v2.y));
	b = sqrt((v2.x - v3.x) * (v2.x - v3.x) + (v2.y - v3.y) * (v2.y - v3.y));
	c = sqrt((vl.x - v3.x) * (vl.x - v3.x) + (vl.y - v3.y) * (vl.y - v3.y));
	cout << "Constructor_1 for: " << objID << " (" << name << ")" << endl; //отладочный вывод
}

// Конструктор пустого (нулевого) треугольника 
Triangle::Triangle(const char* ident)
{
	char buf[16];
	objID = new char[strlen(ident) + 1];
	strcpy(objID, ident);
	count++;
	sprintf(buf, "Треугольник %d", count);
	name = new char[strlen(buf) + 1];
	strcpy(name, buf);
	a = b = c = 0;
	cout << "Constructor_2 for: " << objID << " (" << name << ")" << endl; //отладочный вывод 
}
Triangle::~Triangle()
{ 
	cout << "Destructor for: " << objID << endl; 
	delete[] objID;
	delete[] name; 
}

void Triangle::Show() const
{
	cout << name << ":";
	vl.Show();
	v2.Show();
	v3.Show(); 
	cout << endl;
}

void Triangle::ShowSideAndArea() const
{
	double p = (a + b + c) / 2;
	double s = sqrt(p * (p - a) * (p - b) * (p - c));
	cout << " " << endl; cout << name << ":";
	cout.precision(4);
	cout << " a= " << setw(5) << a;
	cout << ", b= " << setw(5) << b;
	cout << ", c= " << setw(5) << c;
	cout << ":\ts= " << s << endl;
}

bool Triangle::TriaInTria(Triangle trial, Triangle tria2)
{
	Point v1 = trial.Get_v1();
	Point v2 = trial.Get_v2();
	Point v3 = trial.Get_v3();
	return
		(vl.InTriangle(tria2) && v2.InTriangle(tria2) && v3.InTriangle(tria2));
	return 
		true;
}


bool Point::InTriangle(Triangle& tria)
{
	ORIENT orl = Classify(tria.Get_v1(), tria.Get_v2());
	ORIENT or2 = Classify(tria.Get_v2(), tria.Get_v3());
	ORIENT or3 = Classify(tria.Get_v3(), tria.Get_v1());
	if ((orl == RIGHT || orl == BETWEEN) && (or2 == RIGHT || or2 == BETWEEN) && (or3 == RIGHT || or3 == BETWEEN))
		return true;
	else
		return false;
}
int GetNumber(int min, int max);
int Menu()
{
	cout << "\n===== Главное меню =====" << endl;
	cout << "1 - вывести все объекты\t 3 - найти максимальный" << endl;
	cout << "2 - переместить\t\t 4 - определить отношение включения" <<endl;
	cout << "\t\t 5 - выход" << endl;
	return GetNumber(1, 5);
}

int GetNumber(int min, int max)
{
	int number = min - 1;
	while (true)
	{
		cin >> number;
		if ((number >= min) && (number <= max) && (cin.peek() == '\n'))
			break;
		else
		{
			cout << "Повторите ввод (ожидается число от " << min << " до " << max <<
				"):" << endl; cin.clear();
			while (cin.get() != '\n') {};
		}
	}
	return number;
}

int main()
{

}
