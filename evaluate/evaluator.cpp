#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <vector>
#define ms(arr, val) memset(arr, val, sizeof(arr))
#define ll long long
#define iv inline void
#define re int

#define pos sol[i][due[i]]

const int MAXN = 100;
const int MAXM = 100;
const double eps = 1e-6;
const int consume = 1;
const int charge = 1;

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
int n, m;
int t[MAXN][MAXN];
int inhIncrement[MAXN];
double inh[MAXN];
int ability[MAXM];
int solution[MAXM][MAXN];
bool elec[MAXN];
int stayTime[MAXM][MAXN];
int solm[MAXM]; // length of each robots solution
int elc[MAXM];
//--------------------initialize-----------------
void initProblem()
{
	cout << "Input the problem\nInput n m:"; // n m
	n = read();
	m = read();

	cout << "\nInput t_ij:\n"; // t_ij
	for (re i = 0; i < n; i++)
	{
		for (re j = 0; j < n; j++)
		{
			t[i][j] = read();
		}
	}
	cout << "\nInput Increment of n quests:\n"; // Increment
	for (re i = 0; i < n; i++)
	{
		inhIncrement[i] = read();
	}
	cout << "\nInput Inherent of n quests:\n"; // Inherent
	for (re i = 0; i < n; i++)
	{
		cin >> inh[i];
	}
	cout << "\nInput ability of m robots:\n"; // ability
	for (re i = 0; i < m; i++)
	{
		cin >> ability[i];
	}
	cout << "\nInput electricity numbers and position:\n"; // elec station
	int rt = 0;
	cin>>rt;
	for (re i = 0; i < rt; i++)
	{
		int tmp;
		cin >> tmp;
		elec[tmp] = true;
	}
	cout << "\nProblem input completed\n";
	
}
void inputSolution()
{
	/*
	cout<<"\nInput electricity charge numbers and time:\n"; // stay time
	int rt;
	cin>>rt;
	for (re i=0;i<rt;i++){
		int tmp1, tmp2, tmp3;
		cin>>tmp1>>tmp2>>tmp3;
		stayTime[tmp1][tmp2] = tmp3;
	}
	*/
	cout << "Input Solution:\n";
	for (re i = 0; i < m; i++)
	{
		solm[i] = read(); // the length of path
		for (re j = 0; j < solm[i]; j++)
		{
			solution[i][j] = read(); // the path
		}
	}
	cout << "\nSolution input completed\n";
}
//-------------------initialize----------------

//evaluator
double evaluator(int sol[MAXM][MAXN], int len[])// solution[], length[] -> double
{
	set<double> timing; //离散化判断时点 存放时间点的集合
	int due[MAXM];//表示第i个机器人走到第due[i]个任务了
	double countDown[MAXM];//第i个机器人的开始任务倒计时 存在负数以实现做任务
	double iinh[MAXN];//第i个任务的紧急度
	int sum[MAXN];//第i个任务当前所有机器人的能力值之和
	memcpy(iinh, inh, sizeof(inh));//硬复制 从参数表到局部变量 防止更改参数表传进来的数组
	ms(due, 0);//初始化
	ms(sum, 0);//初始化
	for (re i = 0; i < m; i++)
	{
		timing.insert(t[0][sol[i][0]]);//0时间点整一整
		countDown[i] = t[0][sol[i][0]];//把所有机器人派往路径中第一个任务点
		sum[pos] += ability[i];//更新sum[]
		elc[i] = 100;
	}
	double ans = 0;//存储答案
	double last = 0;//存储上一个时间点
	while (!timing.empty())//遍历全部时间点
	{

		double now = *timing.begin();//当前时间
		for (re i = 0; i <= n; i++)
		{
			if (i == n)
				return now;//边界条件，全做完了
			if (iinh[i] > eps)
				break;//没做完
		}
		timing.erase(now);//pop()
		double interval = now - last;//时间间隔
		for (re i = 0; i < n; i++)
		{
			if (iinh[i] > eps) //double处理 等同于>0
			{
				iinh[i] += interval * inhIncrement[i];//紧急度增加
			}
		}
		for (re i = 0; i < m; i++)
		{
			double chargetime = 0;
			if (!elec[pos]){
				elc[i] -= interval * consume;
				//elc[i] += interval * (charge + consume);
			}else{
				chargetime = (100 - elc[i]) / charge;
				elc[i] = 100;
			}
			countDown[i] -= interval;//倒计时减少
			
			if (elc[i] < 0){
				return -1;
			}
			if (countDown[i] < eps) //等同于<=0 即到达了任务点
			{						// in double: >0 -->> >eps ; <0 -->> <-eps ; ==0 -->> <eps && >-eps
				iinh[pos] += countDown[i] * ability[i];//开始做任务 扣紧急度
				countDown[i] = 0;//清除为负的倒计时
				if (iinh[pos] < eps) //<=0
				{
					ans = max(ans, now);//最大时间
					if (due[i] < len[i] - 1)//没走完就继续走
					{
						sum[pos] -= ability[i];//更新sum[]
						countDown[i] = t[pos][sol[i][1 + due[i]]] + chargetime;//路程所需时间
						timing.insert(now + t[pos][sol[i][1 + due[i]]] + chargetime);//到达的时间点
						due[i]++;//到下一个点
						sum[pos] += ability[i];//更新sum[]
					}
				}
				timing.insert(iinh[pos] / (sum[pos] - inhIncrement[pos]) + now + chargetime);//任务完成的时间点
			}
		}
		last = now;//更新last
	}
	return ans;//返回
}

int main()
{
	initProblem();							   // init the problem
	inputSolution();						   // input the answer that should be evaluated
	cout << evaluator(solution, solm) << endl; // cout fitness
	system("pause");
	return 0;
}
