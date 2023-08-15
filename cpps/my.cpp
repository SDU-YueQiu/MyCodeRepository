#include "algorithm"
#include "cmath"
#include "map"
#include "set"
#include "stack"
#include "vector"
#include <iostream>

using namespace std;
// #define int long long
typedef long long ll;
const int N = 1e3 + 10;
// #define endl '\n'
typedef pair<int, int> pii;

int qipan[N][N];
int n, m;

void printQ(pii P1, pii P2)
{
	int x1 = P1.first, y1 = P1.second;
	int x2 = P2.first, y2 = P2.second;
	int mid = (y2 + y1 + 1) / 2;
	for (int i = y1 + 1; i <= mid; ++i)
		cout << "D";
	for (int i = x1 + 1; i <= x2; ++i)
		cout << "R";
	for (int i = mid + 1; i <= y2; ++i)
		cout << "D";
}

void printYZ(pii P1, pii P2)
{
	int x = P1.first, y = P1.second;
	while (x != P2.first || y != P2.second)
	{
		if (qipan[x + 1][y])
		{
			cout << "R";
			x++;
		}
		else if (qipan[x][y + 1])
		{
			cout << "D";
			y++;
		}
		else
			return;
	}
}

void printYZmap(pii P1, pii P2, map<pii, bool> &vis)
{
	{
		int x = P1.first, y = P1.second;
		while (x != P2.first || y != P2.second)
		{
			if (qipan[x + 1][y])
			{
				x++;
				vis[{x, y}] = 1;
			}
			else if (qipan[x][y + 1])
			{
				y++;
				vis[{x, y}] = 1;
			}
		}
	}
}

void printQmap(pii P1, pii P2, map<pii, bool> &vis)
{
	int x1 = P1.first, y1 = P1.second;
	int x2 = P2.first, y2 = P2.second;
	int mid = (y2 + y1 + 1) / 2;
	for (int i = y1 + 1; i <= mid; ++i)
		vis[{x1, i}] = 1;
	for (int i = x1 + 1; i <= x2; ++i)
		vis[{i, mid}] = 1;
	for (int i = mid + 1; i <= y2; ++i)
		vis[{x2, i}] = 1;
}

void qurry(pii P1, pii P2)
{
	map<pii, bool> vis;
	cout << "? ";
	printYZ({1, 1}, P1);
	printQ(P1, P2);
	printYZ(P2, {n, m});
	printYZmap({1, 1}, P1, vis);
	printQmap(P1, P2, vis);
	printYZmap(P2, {n, m}, vis);
	cout << endl;

	int x1 = P1.first, y1 = P1.second;
	int x2 = P2.first, y2 = P2.second;
	int mid = (y2 + y1 + 1) / 2;

	int num;
	cin >> num;
	for (int i = 1; i <= num; ++i)
	{
		int x, y;
		cin >> y >> x;
		qipan[x][y] = 1;
	}

	pii p1 = {0, 0};
	pii p2 = {0, 0};
	int x = x1, y = y1;
	int flag = 0;
	for (y; y <= mid; ++y)
	{
		if (qipan[x][y] == 0)
			flag = 1;
		if (qipan[x][y] && flag == 0)
			p1 = {x, y};
		if (qipan[x][y] && flag == 1)
		{
			p2 = {x, y};
			if (p2.second - p1.second == 1)
			{
				for (int i = p1.first + 1; i <= p2.first; ++i)
				{
					if (vis[{i, p1.second}])
						qipan[i][p1.second + 1] = 1;
					else
						qipan[i][p1.second] = 1;
				}
			}
			else
				qurry(p1, p2);
			p1 = {0, 0};
			p2 = {0, 0};
			flag = 0;
		}
	}
	--y, ++x;
	for (x; x <= x2; ++x)
	{
		if (qipan[x][y] == 0)
			flag = 1;
		if (qipan[x][y] && flag == 0)
			p1 = {x, y};
		if (qipan[x][y] && flag == 1)
		{
			p2 = {x, y};
			if (p2.second - p1.second == 1)
			{
				for (int i = p1.first + 1; i <= p2.first; ++i)
				{
					if (vis[{i, p1.second}])
						qipan[i][p1.second + 1] = 1;
					else
						qipan[i][p1.second] = 1;
				}
			}
			else
				qurry(p1, p2);
			p1 = {0, 0};
			p2 = {0, 0};
			flag = 0;
		}
	}
	--x, ++y;
	for (y; y <= y2; ++y)
	{
		if (qipan[x][y] == 0)
			flag = 1;
		if (qipan[x][y] && flag == 0)
			p1 = {x, y};
		if (qipan[x][y] && flag == 1)
		{
			p2 = {x, y};
			if (p2.second - p1.second == 1)
			{
				for (int i = p1.first + 1; i <= p2.first; ++i)
				{
					if (vis[{i, p1.second}])
						qipan[i][p1.second + 1] = 1;
					else
						qipan[i][p1.second] = 1;
				}
			}
			else
				qurry(p1, p2);
			p1 = {0, 0};
			p2 = {0, 0};
			flag = 0;
		}
	}
}

void print()
{
	cout << "! ";
	printYZ({1, 1}, {n, m});
	cout << endl;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin >> m >> n;
	qipan[1][1] = qipan[n][m] = 1;
	qurry({1, 1}, {n, m});
	print();
	return 0;
}
