
// 0 - Floor   1 - Wall

#include<iostream>
#include<Windows.h>
using namespace std;

#define size 150

int createGrid() {
	int grid[size][size] = { 1 };

	return 1;
}

void dispGrid(int grid[][size]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			if(grid[i][j] == 1)
				SetConsoleTextAttribute(hConsole, 9);
			else
				SetConsoleTextAttribute(hConsole, 10);
			cout << grid[i][j];
		}
		cout << "\n";
	}
	SetConsoleTextAttribute(hConsole, 7);
}

void makeNoise(int grid[][size],int density) {
	srand(time(0));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			int random = rand() % 100;
			if (random > density)
				grid[i][j] = 0;
			else
				grid[i][j] = 1;
		}
		cout << "\n";
	}
}

void cellularAutomata(int grid[][size]) {
	int temp[size][size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int wallCount = 0;
			for (int k = i - 1; k <= i + 1; k++) {
				for (int l = j - 1; l <= j + 1; l++) {
					if (k < 0 || k>size-1 || l < 0 || l>size-1 || (k==i && l==j))
						continue;
					wallCount += grid[k][l];
				}
			}

			if (wallCount > 4)
				temp[i][j] = 1;
			else
				temp[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			grid[i][j] = temp[i][j];
		}
	}
}

int main() {
	int density = 50,iteration = 3;
	cout << "Enter Noise density: \n";
	cin >> density;
	cout << "Enter Iterations: \n";
	cin >> iteration;
	int grid[size][size] = { 0 };
	makeNoise(grid, density);
	dispGrid(grid);
	cout << "\n\n\n";
	for (int i = 0; i < iteration; i++) {
		cellularAutomata(grid);
		dispGrid(grid);
		cout << "\n\n\n";
	}
}