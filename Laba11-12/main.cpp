#include <iostream>
#include <string>
using namespace std;

template <class type1>
class massive  //объявления класса массива
{
	int size;
	type1* p;
public:
	massive(int size)//конструктор по умолчнию
	{
		this->size = size;
		p = new type1[size];
	}

	~massive()//деструктор
	{
		delete[] p;
	}

	massive(const massive& r)//конструктор копирования
	{
		size = r.size;
		p = new type1[size];
		for (int i = 0; i < r.size; i++)
		{
			p[i] = r.p[i];
		}
	}

	void input(int pos, type1 element)// функция ввода элемента
	{
		p[pos] = element;
	}

	void show()//функция вывода массива на экран
	{
		for (int i = 0; i < size; i++)
		{
			cout << p[i] << endl;
		}
		cout << endl;
	}

	int Get_size()// функция возращающая размер массива
	{
		return size;
	}

	type1 operator[](int i)
	{
		return p[i];
	}

	massive& operator=(const massive& right) // перегрузка оператора присваивания
	{

		for (int i = 0; i < right.size; i++)
		{
			p[i] = right.p[i];
		}
		return *this;
	}

	massive&  operator-(massive l)//перегрузка оператора вычитания массива
	{
		for (int i = 0; i < l.size; i++)
		{
			p[i] = p[i] - l.p[i];
		}
		return *this;
	}

	massive& operator-(type1 i)// перегрузка оператора вычитания элемента из массива
	{
		p[size - 1] = p[size - 1] - i;
		return *this;
	}

};

class Point//пользовательский класс 
{
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}//конструктор по умолчнию

	Point(const Point& copy)//конструктор копирования
	{
		x = copy.x;
		y = copy.y;
	}
	
	void Show() const//функция показа точки
	{
		cout << " (" << x << "," << y << ")"<< endl;
	}

	Point& operator =(const Point& a)//перезрузка оператора присваивания
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	const Point operator -(const Point& a)//перезрузка оператора вычитания
	{
		
		return Point(x - a.x, y - a.y);
	}
	int x, y;

	friend ostream& operator<< (ostream& out, const Point& point);
};

ostream& operator<< (ostream& out, const Point& point)// перегрузка оператора вывода для класса Point
{
	out << " (" << point.x << "," << point.y << ")";
	return out;
}

int main()
{
	setlocale(LC_ALL, "rus");
	massive <double> b(10);
	cout << "massive b(10) заполненый числами." << endl;
	for (int i = 0; i < 10; i++)
	{
		b.input(i, i + 1);
	}
	b.show();
	cout << "massive a = b " << endl;
	massive <double> a = b;
	a.show();
	cout << "massive c = a - b " << endl;
	massive <double> c(10);
	c = a - b;
	c.show();
	cout << "massive c = c - 4 " << endl;
	c = c - 4;
	c.show();

	massive <Point> b1(10);
	cout << "massive b1(10) заполненый объектами класса Point." << endl;
	for (int i = 0; i < 10; i++)
	{
		b1.input(i, Point(i+1, i));
	}
	b1.show();
	cout << "massive a1 = b1 " << endl;
	massive <Point> a1 = b1;
	a1.show();
	cout << "massive c1 = a1 - b1 " << endl;
	massive <Point> c1(10);
	c1 = a1 - b1;
	c1.show();
	cout << "massive c1 = c1 - Point(100, 100) " << endl;
	c1 = c1 - Point(100, 100);
	c1.show();
}
