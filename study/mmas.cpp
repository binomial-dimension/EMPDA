#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#define ms(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define iv inline void
#define re int
#define MAXN 100
#define ANTS 48
#define alpha 2
#define beta 3
#define maxpheno 10000
#define maxepoch 1000
#define rho 0.1
#define Q 1
using namespace std;

int read()
{
	int x = 0, w = 0;
	char ch = 0;
	while (!isdigit(ch))
	{
		w |= ch == '-';
		ch = getchar();
	}
	while (isdigit(ch))
		x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
	return w ? -x : x;
}
pair<double, double> pos[MAXN];
double dis[MAXN][MAXN];		 // dis between i and j
int n;						 // total nodes
double pheno[MAXN][MAXN];	 // pheno between i and j
double prepheno[MAXN][MAXN]; // delta pheno between i and j
double heuro[MAXN][MAXN];	 // heuro between i and j
int ants[ANTS + 2][MAXN];	 // the path of ants i
int ia[ANTS + 2];			 // the path length of ants i
double lk[ANTS + 2];		 // the last path length of ants i
int asnum;					 // the number of ants
double ans;					 // answer
bool ise[MAXN][ANTS + 2];	 // taboo list
int main()
// 49 34428
{
	int seed;
	cin >> seed;
	srand(seed);
	// init and input
	ms(lk, 0);
	ms(heuro, 0);
	ms(pheno, 0);
	ms(dis, 0);
	ms(ise, 0);
	ans = 10000000;			   // init the ans
	cin >> n;				   // input n
	for (re i = 0; i < n; i++) // input position
	{
		int tmp;
		cin >> tmp >> pos[i].first >> pos[i].second;
	}
	for (re i = 0; i < n; i++) // init dis and heuro and pheno
	{
		for (re j = 0; j < n; j++)
		{
			// dis init
			double d = sqrt((pos[i].second - pos[j].second) * (pos[i].second - pos[j].second) + (pos[i].first - pos[j].first) * (pos[i].first - pos[j].first));
			dis[j][i] = d;
			dis[i][j] = d;
			// heuro = 1/d
			heuro[i][j] = 1 / d;
			heuro[j][i] = 1 / d;
			// pheno init with 1
			pheno[i][j] = 1;
		}
	}
	// ants number
	asnum = ANTS;
	// clear array
	ms(ants, 0);
	ms(ia, 0);
	// init all length of the ant's path finish its travel to 1 (/0 leads to error)
	for (re i = 0; i < asnum; i++)
	{
		lk[i] = 1;
	}

	// epoch repeat
	for (re epoch = 0; epoch < maxepoch; epoch++)
	{
		// flag that find a complete solution
		bool flag = false;

		// iterate each ant
		for (re iants = 0; iants < asnum; iants++) // the iants is just i (the counter)
		{
			// the sum of heuro and phenon with alpha and beta
			double sumheuro = 0;
			// the random number in [0,10000)
			double rndpt = (rand() % 10000);
			// input the node ants had traveled to the taboo list
			ise[ants[iants][ia[iants]]][iants] = true;
			// calculate the sumheuro
			for (re ito = 0; ito < n; ito++)
			{
				if (!ise[ito][iants])
				{
					sumheuro += pow(heuro[ants[iants][ia[iants]]][ito], beta) * pow(pheno[ants[iants][ia[iants]]][ito], alpha);
				}
			}
			// iterate next node
			for (re ito = 0; ito < n; ito++)
			{
				// don't go to itself
				if (ise[ito][iants] || ito == ants[iants][ia[iants]])
				{
					continue;
				}
				// the possibility of this node
				double p = pow(pheno[ants[iants][ia[iants]]][ito], alpha) * pow(heuro[ants[iants][ia[iants]]][ito], beta) / (sumheuro);
				// minus the p
				rndpt -= p * 10000;
				// go to the node
				if (rndpt < 0)
				{
					// plus the dis
					lk[iants] += dis[ants[iants][ia[iants]]][ito];
					// put to the taboo
					ise[ito][iants] = true;
					// record the path
					ants[iants][++ia[iants]] = ito;
					break;
				}
			}
			// the path is full
			if (ia[iants] >= n - 1)
			{
				// find iteration best ants
				int itera = 0;
				int beslk = 10000000;
				for (re i = 0; i < asnum; i++)
				{
					if (lk[i] < beslk)
					{
						beslk = lk[i];
						itera = i;
					}
				}
				// find best ans
				if (lk[iants] < ans)
				{
					cout << epoch << " " << ans << endl;
				}
				// update delta pheno
				if (prepheno[ants[itera][0]][ants[itera][1]] == 0)
				{
					for (re j = 0; j < ia[itera]; j++)
					{
						prepheno[ants[itera][j]][ants[itera][j + 1]] += Q / lk[itera];
					}
				}
				// update best ans
				ans = min(ans, lk[iants]);
				// clear taboo
				for (re ik = 0; ik < n; ik++)
				{
					ise[ik][iants] = false;
				}
				// clear the path
				for (re j = 0; j < ANTS + 2; j++)
				{
					ants[iants][j] = 0;
				}
				// clear the path
				ia[iants] = 0;
				// clear the length of the path
				lk[iants] = 0;
				// flag that find whole answer
				flag = true;
			}
		}
		// update delta pheno to the pheno and multiply with rho
		if (flag)
		{
			for (re i = 0; i < n; i++)
			{
				for (re j = 0; j < n; j++)
				{
					pheno[i][j] = max(0.0, min(pheno[i][j] * rho + prepheno[i][j], double(maxpheno)));
					prepheno[i][j] = 0;
				}
			}
		}
	}
	cout << "over";
	main();
	return 0;
}
