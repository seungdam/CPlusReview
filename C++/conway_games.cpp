#include <iostream>
#include <Windows.h>

using namespace std;

const char* live_cell = "\033[1;33m¡á";
const char* dead_cell = "\033[1;31m¡à";

const int grid_row = 50;
const int grid_col = 23;


const int min_neighbours = 2;
const int max_neighbours = 3;

const int min_parents = 3;
const int max_parents = 3;


void ConsoleInit()
{
	auto cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	auto cursorInfo = CONSOLE_CURSOR_INFO{};
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(cHandle, &cursorInfo);
}
void gotoXY(const short& x, const short& y)
{
	auto cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	auto grid = COORD{ x, y };
	SetConsoleCursorPosition(cHandle, grid);
}

class Cell
{
	bool _b_alive;
public:
	Cell() : _b_alive(false) {}
	~Cell() {}

	void Create() { _b_alive = true; }
	void Erase() { _b_alive = false; }
	bool IsAlive() const { return _b_alive; }
};


class CellGrid
{
	Cell cells[grid_col + 2][grid_row + 2];
private:
	void Randomize() 
	{
		const int factor = 5;
		const int cutoff = (RAND_MAX / factor);
		time_t now;
		time(&now);

		for (int c = 1; c < grid_col + 1; ++c)
		{
			for (int r = 1; r < grid_row + 1; ++r)
			{
				if (rand() / cutoff == 0) cells[c][r].Create();
			}
		}
	}
	
public:
	CellGrid() {}
	~CellGrid() {}

	void Init()
	{
		Randomize();
	}
	bool WillSurvive(int row, int col)
	{
		if (!cells[col][row].IsAlive()) return false;

		auto neighbour =
			cells[col][row - 1].IsAlive() +
			cells[col][row + 1].IsAlive() +
			cells[col - 1][row].IsAlive() +
			cells[col - 1][row + 1].IsAlive() +
			cells[col - 1][row - 1].IsAlive() +
			cells[col + 1][row].IsAlive() +
			cells[col + 1][row + 1].IsAlive();
		cells[col + 1][row - 1].IsAlive();

		if (neighbour < min_neighbours || neighbour > max_neighbours)
		{
			return false;
		}
		return true;
	}
	bool WillCreate(int row, int col)
	{
		if (cells[row][col].IsAlive()) return false;

		auto neighbour = cells[col][row - 1].IsAlive() +
			cells[col][row + 1].IsAlive() +
			cells[col - 1][row].IsAlive() +
			cells[col - 1][row + 1].IsAlive() +
			cells[col - 1][row - 1].IsAlive() +
			cells[col + 1][row].IsAlive() +
			cells[col + 1][row + 1].IsAlive();
		cells[col + 1][row - 1].IsAlive();

		if (neighbour > max_parents || neighbour < min_parents)
		{
			return false;
		}
		return true;
	}
	
	void KillCell(int row, int col) { cells[col][row].Erase(); }
	void CreateCell(int row, int col) { cells[col][row].Create(); }
	bool GetCellStatus(int row, int col) const { return cells[col][row].IsAlive(); }

	void Update(const CellGrid& new_grid) 
	{
		for (int c = 1; c < grid_col + 1; ++c)
		{
			for (int r = 1; r < grid_row + 1; ++r)
			{
				if (new_grid.GetCellStatus(r, c)) CreateCell(r,c);
				else KillCell(r,c);
			}
		}
	}
	void Render() 
	{
		cout << "\n";
		for (int c = 0; c < grid_col + 2; ++c)
		{
			for (int r = 0; r < grid_row + 2; ++r)
			{
				cout << (GetCellStatus(r,c) ? live_cell : dead_cell);
			} 
			cout << "\n";
		}
	}
};

void Calculate(CellGrid& cur_grid, CellGrid& new_grid)
{

	for (int c = 1; c < grid_col + 1; ++c)
	{
		for (int r = 1; r < grid_row + 1; ++r)
		{
			if (cur_grid.WillSurvive(r, c))
			{
				new_grid.CreateCell(r,c);
			}
			else if (cur_grid.WillCreate(r, c))
			{
				new_grid.CreateCell(r, c);
			}
		}
	}
}

int main()
{
	CellGrid grid;
	ConsoleInit();
	grid.Init();
	grid.Render();
	while (true)
	{
		CellGrid ngrid;
		Calculate(grid, ngrid);
		cin.get();
		grid.Update(ngrid);
		grid.Render();
	}
	auto str = "Hellow World!"s;
	str += "Add Operator"s;
	
}