// 24labrab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
#include <iostream>
#include <windows.h>


using namespace std;

HANDLE Mutex;
HANDLE Events[4], EndEvent;

DWORD WINAPI Employee(LPVOID lpParam) {
	char input;
	if (WaitForSingleObject(Mutex, INFINITE) != 0) {
		cout << "Не удалось занять мьютекс" << endl;
		return 1;
	}
	if (WaitForSingleObject(EndEvent, 10) == WAIT_TIMEOUT) {
		cout << "Введите одну из цифр: 0, 1, 2, 3\n";
		cout << "Ваш выбор: ";
		cin >> input;
		if (cin.fail() || (input < '0' || input>'3'))
			cout << "Введены неправильные данные" << endl;
		else if (SetEvent(Events[(unsigned int)(input - '0')]) == 0)
			cout << "Не удалось установить событие" << endl;
		ReleaseMutex(Mutex);
		return 0;
	}
	else {
		ReleaseMutex(Mutex);
		return 1;
	}
}

void main() {
	setlocale(LC_ALL, ".1251");
	cout << "Задайте кол-во потоков: ";
	unsigned int n;
	cin >> n;
	if (cin.fail()) {
		cout << "Введены неправильные данные" << endl;
		ExitProcess(1);
	}
	cout << "Будет создано потоков: " << n << endl;
	for (unsigned int i = 0; i < 4; i++)
		if ((Events[i] = CreateEventA(0, 0, 0, 0)) == 0) {
			cout << "Не удалось создать событие \"" << i << "\"" << endl;
			ExitProcess(1);
		}
	if ((EndEvent = CreateEventA(0, 1, 0, 0)) == 0) {
		cout << "Не удалось создать событие" << endl;
		ExitProcess(1);
	}
	Mutex = CreateMutexA(0, 1, 0);
	HANDLE* Threads = new HANDLE[n];
	for (unsigned int i = 0; i < n; i++)
		if ((Threads[i] = CreateThread(0, 0, Employee, 0, 0, 0)) == 0) {
			cout << "Не удалось создать поток №" << i + 1 << endl;
			ExitProcess(1);
		}
	cout << "Потоков создано: " << n << endl;
	ReleaseMutex(Mutex);
	for (unsigned int i = 0; i < 3; i++) {
		WaitForMultipleObjects(4, Events, 0, INFINITE);
		cout << "Принято сообщение №" << i + 1 << endl;
	}
	SetEvent(EndEvent);
	WaitForSingleObject(Mutex, INFINITE);
	ResetEvent(EndEvent);
	cout << "Программа успешно завершается" << endl;
	delete[] Threads;
	ExitProcess(0);
}
