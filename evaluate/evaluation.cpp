#include<iostream>
#include <cstdlib>
#include<cmath>
#include<vector>
#include <cstring>
const int MAX = 100;
const int MAXCOST = 0x7fffffff;
double dis[MAX][MAX];//distance between ij,also travel time
using namespace std;

int pos[MAX];//position of task
double q[MAX] = {0};//demand of task i accumulated at time t
double rate[MAX];//inherent increment rate of task i
double ct[100];
double last[MAX] = {0};//rate updatad time
int sol[MAX][MAX] = {0};//solutions
int sollen[MAX] = {0};//length of each solution
int ability[MAX];//ability of each rob
int robtask[MAX];//task's index of rob 
int ROBNUM;
int TASKNUM;
vector<int>r;

//input
void input()
{
	int n = 0;
	//init dis
	cin >> n;
	int start = 0;
	int end = 0;
	int weight = 0;
	for(int i = 0;i<n;i++){
		cin >> start >> end >> weight;
		dis[start][end] = weight;
		dis[end][start] = weight;
	}
	cout << "dis input successfully" << endl;

	//input task
	cin >> n;
	TASKNUM = n;
	for (int i = 1;i <= TASKNUM;i++) {
		cin >> pos[i] >> rate[i] >> q[i];
		ct[i] = MAX;
	}
	cout << "task input successfully" << endl;
	//input robot ability
	cin >> n;
	ROBNUM = n;
	for (int i = 0;i < ROBNUM;i++) {
		cin >> ability[i];
	}
	cout << "rob input successfully" << endl;
	//input solutions

	for (int i = 0;i < ROBNUM;i++) {
		cin >> n;
		sollen[i] = n;
		for (int j = 0;j < n;j++) {
			cin >> sol[i][j];
		}
	}
	cout << "sol input successfully" << endl;
}

int main() {
	input();
	double fit = 0;
	int k = 0;
	int cnt = 0;//total solutions
	double cur = 0;
	while (sollen[k] != 0) {
		cnt += sollen[k];
		k++;
	}
	for (int i = 0;i < ROBNUM;i++) {
		//assign first tasks to each robot
		int pre = 0;
		cur = dis[0][pos[sol[i][0]]];
		robtask[i] = 0;//updata rob's current task
		q[sol[i][0]] += rate[sol[i][0]] * (cur - pre);//updata task's demand in period (pre,cur)
		rate[sol[i][0]] -= ability[i];//updata task's inherent increment rate
		ct[sol[i][0]] = cur + abs(q[sol[i][0]] / rate[sol[i][0]]);
		last[sol[i][0]] = cur;
		//cout << cur << endl;
		fit = max(fit, cur);
		cnt--;
	}
	while(cnt >= 0) {
		int min = MAXCOST;
		int minid = 0;
		//find nearest complete task
		for (int j = 1;j <= TASKNUM;j++) {
			if (ct[j] < min) {
				min = ct[j];
				minid = j;
			}
		}
		//find corresponding robs 
		for (int j = 0;j < ROBNUM;j++) {
			if (sol[j][robtask[j]] == minid) {
				r.push_back(j);//if all the task of this robot is completed
			}
		}
		while (r.size() != 0) {
			//cur = completion time of the robot's last task + travel time between two tasks
			int robot = r[0];
			if (sol[robot][robtask[robot] + 1] != 0) {
				int next = robtask[robot] + 1;//next task to be executed by robot
				cur = ct[minid] + dis[pos[minid]][pos[sol[robot][next]]];
				double pre = last[sol[robot][next]];
				robtask[robot] = next;
				q[sol[robot][next]] += rate[sol[robot][next]] * (cur - pre);
				rate[sol[robot][next]] -= ability[robot];
				ct[sol[robot][next]] = cur + abs(q[sol[robot][next]] / rate[sol[robot][next]]);
				last[sol[robot][next]] = cur;
				//cout << cur << endl;
				fit = max(fit, cur);
			}
			else {
				cur = ct[minid];
				fit = max(fit, cur);
			}
			r.erase(r.begin());
			cnt--;
		}
	ct[minid] = MAX;//task minid is completed
	}
	cout << fit << endl;
}
