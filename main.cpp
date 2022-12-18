#include <iostream>
#include <deque>
#include <conio.h>
#include <thread>
#include <windows.h>

using std::cout, std::string, std::deque, std::this_thread::sleep_for, std::chrono::milliseconds, std::thread;

// written by chapel1337
// made on 12/18/2022
// not much to say about this, it's just a crappy piano program
// i've attempted to fix the same refresh error that duplicates all of the characters and makes the screen look awful, but nothing has worked

char keyPressed{};
bool showHelp{ true };

deque<deque<char>> map
{
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
	{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', },
};
deque<deque<int>> colorMap
{
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
	{ 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, },
};

int main();

void title(const string& input)
{
	SetConsoleTitleA(input.c_str());
}

void setTextColor(const int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void clear()
{
	system("cls");
}

void help()
{
	clear();

	cout << "\n	help\n\n";

	cout << "	this program functions like your average piano\n";
	cout << "	press a key ranging from q-l on your keyboard to press a piano key\n\n";

	cout << "	written by chapel1337\n";
	cout << "	made on 12/18/2022\n\n";

	cout << "	> okay <\n";

	_getch();
	main();
}

void refresh()
{
	clear();

	/*
	cout << "map y: " << map.size() << '\n';
	cout << "map x: " << map[0].size() << "\n\n";
	*/

	if (showHelp)
	{
		cout << "\n	press esc + help for help\n\n";
		cout << "	key pressed: " << keyPressed << "\n\n";

		showHelp = false;
	}
	else
	{
		cout << "\n\n\n	key pressed: " << keyPressed << "\n\n";
	}

	for (int i{}; i < 8; ++i)
	{
		cout << '\n';
	}

	for (int i{}; i < map.size(); ++i)
	{
		for (int o{}; o < 18; ++o)
		{
			cout << ' ';
		}

		for (int o{}; o < map[i].size(); ++o)
		{
			setTextColor(colorMap[i][o]);

			cout << "  " << map[i][o] << map[i][o];

			resetTextColor();
		}

		cout << '\n';
	}
}

void pressKey(const DWORD frequency, const DWORD duration, const unsigned int key)
{	
	for (int i{}; i < colorMap.size(); ++i)
	{
		colorMap[i][key] = 8;
	}

	refresh();
	Beep(frequency, duration);

	for (int i{}; i < colorMap.size(); ++i)
	{
		colorMap[i][key] = 7;
	}

	refresh();
}

void getInput()
{
	const int keyInput{ _getch() };
	thread playSound{};

	if (keyInput == 'Q' || keyInput == 'q')
	{
		playSound = thread(pressKey, 150, 500, 0);
	}
	else if (keyInput == 'W' || keyInput == 'w')
	{
		playSound = thread(pressKey, 175, 500, 1);
	}
	else if (keyInput == 'E' || keyInput == 'e')
	{
		playSound = thread(pressKey, 200, 500, 2);
	}
	else if (keyInput == 'R' || keyInput == 'r')
	{
		playSound = thread(pressKey, 225, 500, 3);
	}
	else if (keyInput == 'T' || keyInput == 't')
	{
		playSound = thread(pressKey, 250, 500, 4);
	}
	else if (keyInput == 'Y' || keyInput == 'y')
	{
		playSound = thread(pressKey, 275, 500, 5);
	}
	else if (keyInput == 'U' || keyInput == 'u')
	{
		playSound = thread(pressKey, 300, 500, 6);
	}
	else if (keyInput == 'I' || keyInput == 'i')
	{
		playSound = thread(pressKey, 325, 500, 7);
	}
	else if (keyInput == 'O' || keyInput == 'o')
	{
		playSound = thread(pressKey, 350, 500, 8);
	}
	else if (keyInput == 'P' || keyInput == 'p')
	{
		playSound = thread(pressKey, 375, 500, 9);
	}
	else if (keyInput == 'A' || keyInput == 'a')
	{
		playSound = thread(pressKey, 400, 500, 10);
	}
	else if (keyInput == 'S' || keyInput == 's')
	{
		playSound = thread(pressKey, 425, 500, 11);
	}
	else if (keyInput == 'D' || keyInput == 'd')
	{
		playSound = thread(pressKey, 450, 500, 12);
	}
	else if (keyInput == 'F' || keyInput == 'f')
	{
		playSound = thread(pressKey, 475, 500, 13);
	}
	else if (keyInput == 'G' || keyInput == 'g')
	{
		playSound = thread(pressKey, 500, 500, 14);
	}
	else if (keyInput == 'H' || keyInput == 'h')
	{
		playSound = thread(pressKey, 525, 500, 15);
	}
	else if (keyInput == 'J' || keyInput == 'j')
	{
		playSound = thread(pressKey, 550, 500, 16);
	}
	else if (keyInput == 'K' || keyInput == 'k')
	{
		playSound = thread(pressKey, 575, 500, 17);
	}
	else if (keyInput == 'L' || keyInput == 'l')
	{
		playSound = thread(pressKey, 600, 500, 18);
	}
	else if (keyInput == 27)
	{
		const int secondKeyInput{ _getch() };

		if (secondKeyInput == 'H' || secondKeyInput == 'h')
		{
			help();
		}
	}
	else
	{
		getInput();
	}

	playSound.detach();
	keyPressed = keyInput;

	getInput();
}

int main()
{
	refresh();
	getInput();
}