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
#define consume 1

const int MAXN = 100;
const int MAXM = 100;
const double eps = 1e-6;
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

int xpos[MAXN], ypos[MAXN], inc[MAXN], inh[MAXN], ability[MAXM];
int diss[MAXN][MAXN];
int n, m;
vector<int> solution[MAXM];

void readProblem(){
    n = read(),m = read();
    if (n>=MAXN||m>=MAXM) return;
    for (re i=0;i<n;i++){
        for (re j=0;j<n;j++){
            diss[i][j] = read();
        }
    }
    for (re i=0;i<n;i++){
        inc[i] = read();
    }
    for (re i=0;i<n;i++){
        inh[i] = read();
    }
    for (re i=0;i<m;i++){
        ability[i] = read();
    }
}
void coutProblem(){
    for (re i = 0; i < m;i++){
        cout << solution[i].size() << ' ';
        for (re j = 0; j < solution[i].size(); j++){
            cout << solution[i][j] << ' ';
        }
        cout << endl;
    }
}
int nearPoint(int pos, bool visited[]){
    int minn = 1000, minid = -1;
    for (re i = 0; i < n;i++){
        if (i==pos||visited[i])
            continue;
        if(diss[pos][i] < minn){
            minn = diss[pos][i];
            minid = i;
        }
    }
    return minid;
}

bool greedy1(){
    int elc = 100;
    int abl = 0;
    int now = 0;
    int t = 0;
    bool visited[MAXM];
    ms(visited, 0);
    for (re i = 0; i < m;i++){
        abl += ability[i];
    }
    int counter = 100000;
    while (nearPoint(0, visited) != -1)
    {
        counter--;
        if (counter<0){
            cout << "FATAL: no solution" << endl;
            return false;
        }
        if (t * inc[now] + inh[now] < 0)
            visited[now] = true;
        int to = nearPoint(now, visited);
        if (to == -1)
            break;
        if ((diss[now][to] + diss[to][0]) * consume > elc){
            to = 0;
        }
        if (t * inc[now] + inh[now] + diss[now][0] * consume <= elc / consume){
            visited[now] = true;
            t += (t * inc[now] + inh[now]) / abl;
        }else if (diss[now][0] <= elc / consume){
            int frag = elc/consume - diss[now][0];
            t += frag;
            inh[now] -= frag * abl;
            to = 0;
        }else{
            to = 0;
        }
        elc -= diss[now][to] * consume;
        for (re j = 0; j < m;j++){
            solution[j].push_back(to);
        }
        now = to;
        t += diss[now][to];
        if (to == 0){
            t += (100 - elc) / charge;
            elc = 100;
        }
    }
    cout << "\ntime consume: " << t << endl;
    return true;
}

bool greedy2(int membernum){

}

int main(){
    readProblem();
    if(greedy1()){
        coutProblem();
    };
    
    system("pause");
    return 0;
}