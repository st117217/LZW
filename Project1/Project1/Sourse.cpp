#include <iostream>
#include "FileProcessor.h"

void printMenu();

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Ru");
	FileProcessor processor("text.txt");
	std::locale::global(std::locale("ru_RU.UTF-8"));

	bool exit = false;
	while (!exit)
	{
		printMenu();
		int choice;
		std::cin >> choice;

		switch (choice)
		{
		case 1:
		{
			processor.encodeFile();
			std::cout << "Нажмите Enter, чтобы продолжить...";
			std::cin.ignore();
			std::cin.get();
			break;
		}
		case 2:
		{
			processor.decodeFile();
			std::cout << "Нажмите Enter, чтобы продолжить...";
			std::cin.ignore();
			std::cin.get();
			break;
		}
		case 3:
		{
			exit = true;
			break;
		}
		default:
		{
			std::cout << "Неверный ввод. Повторите попытку. Нажмите Enter...";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.get();
			break;
		}
		}
		std::cout << std::endl;
		system("cls");
	}

	return EXIT_SUCCESS;
}

void printMenu()
{
	setlocale(LC_ALL, "ru");
	std::cout << "1. Закодировать" << std::endl;
	std::cout << "2. Декодировать" << std::endl;
	std::cout << "3. Выход" << std::endl;
	std::cout << "Введите номер опции: ";
}