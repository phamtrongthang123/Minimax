#include <iostream>

using namespace std;
#define X 500
#define O 100
#define MAX_DEPTH 8
int a[3][3]{};
int buoc = 0;
struct Move{
	int bestScore, bestRow, bestCol;
};
bool KiemTra()
{

	int n1[] = { a[0][0], a[0][1], a[0][2] };
	int n2[] = { a[1][0], a[1][1], a[1][2] };
	int n3[] = { a[2][0], a[2][1], a[2][2] };
	int d1[] = { a[0][0], a[1][0], a[2][0] };
	int d2[] = { a[0][1], a[1][1], a[2][1] };
	int d3[] = { a[0][2], a[1][2], a[2][2] };
	int c1[] = { a[0][0], a[1][1], a[2][2] };
	int c2[] = { a[0][2], a[1][1], a[2][0] };


	return ((n1[0] == n1[1] && n1[1] == n1[2] && n1[1] != 0)
		|| (n2[0] == n2[1] && n2[1] == n2[2] && n2[1] != 0)
		|| (n3[0] == n3[1] && n3[1] == n3[2] && n3[1] != 0)
		|| (d1[0] == d1[1] && d1[1] == d1[2] && d1[1] != 0)
		|| (d2[0] == d2[1] && d2[1] == d2[2] && d2[1] != 0)
		|| (d3[0] == d3[1] && d3[1] == d3[2] && d3[1] != 0)
		|| (c1[0] == c1[1] && c1[1] == c1[2] && c1[1] != 0)
		|| (c2[0] == c2[1] && c2[1] == c2[2] && c2[1] != 0));
}
void NguoiChoi() {
	cout << "Danh o nao? ";
	int x, y;
	cin >> x >> y;
	a[x][y] = X;
}
int evalLine(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int score =0;
	if (a[x1][y1]==X)
	{
		score = -1;
	}
	else if (a[x1][y1] == O) { score = 1; }
	if (a[x2][y2] == O)
	{
		if (score==1)
		{
			score = 10;
		}
		else if (score==-1)
		{
			return 0;
		}
		else
		{
			score = 1;
		}
	}
	else if (a[x2][y2] == X)
	{
		if (score == -1)
		{
			score = -10;
		}
		else if (score == 1)
		{
			return 0;
		}
		else
		{
			score = -1;
		}
	}
	if (a[x3][y3] == O)
	{
		if (score==10)
		{
			score = 100;
		}
		else if (score<0)
		{
			return 0;
		}
		else score = 1;
	}
	else if (a[x3][y3] == X)
	{
		if (score==-10)
		{
			score = -100;
		}
		else if (score>0)
		{
			return 0;
		}
		else score = -1;
	}
	return score;
}
int eval()
{
	int score = 0;
	score += evalLine(0, 0, 0, 1, 0, 2);  // row 0
	score += evalLine(1, 0, 1, 1, 1, 2);  // row 1
	score += evalLine(2, 0, 2, 1, 2, 2);  // row 2
	score += evalLine(0, 0, 1, 0, 2, 0);  // col 0
	score += evalLine(0, 1, 1, 1, 2, 1);  // col 1
	score += evalLine(0, 2, 1, 2, 2, 2);  // col 2
	score += evalLine(0, 0, 1, 1, 2, 2);  // diagonal
	score += evalLine(0, 2, 1, 1, 2, 0);  // alternate diagonal
	return score;
}
Move minimax(int depth, int player)
{
	Move bestMove;
	bestMove.bestScore = (player == O) ? int(-1e9) : int(1e9);
	bestMove.bestCol = -1;
	bestMove.bestRow = -1;
	int currentScore =-1;
	if (depth == 0 || KiemTra() || buoc + (MAX_DEPTH-depth+1) == 9)
	{
		bestMove.bestScore = eval();
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				//try every move
				if (a[i][j] == 0)//isEmpty ?
				{					
					a[i][j] = player;
					if (player == O)
					{
						currentScore = minimax(depth - 1, X).bestScore;
						if (currentScore>bestMove.bestScore)
						{
							bestMove.bestScore = currentScore;
							bestMove.bestCol = j;
							bestMove.bestRow = i;
						}
					}
					else
					{
						currentScore = minimax(depth - 1, O).bestScore;
						if (currentScore<bestMove.bestScore)
						{
							bestMove.bestScore = currentScore;
							bestMove.bestCol = j;
							bestMove.bestRow = i;
						}
					}
					a[i][j] = 0;
				}
			}
		}
	}
	return bestMove;
}
void MayChoi()
{
	Move res = minimax(MAX_DEPTH, O);
	a[res.bestRow][res.bestCol] = O;
}

void Draw()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (a[i][j] == 0)
			{
				cout << " . ";
			}
			else if (a[i][j] == X)
			{
				cout << " X ";
			}
			else
			{
				cout << " O ";
			}
		}
		cout << endl;
	}
}

int main()
{
	bool b = true;
	while (b)
	{
		Draw();
		NguoiChoi(); buoc++; system("cls"); Draw();
		if (buoc < 9) {
			MayChoi(); buoc++;
		}
		system("cls"); Draw();
		b=!KiemTra();
		if (buoc == 9) b = false;
		system("cls");
	}
	cout << "game dung.";
	system("pause");
	return 0;
}