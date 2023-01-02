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
void coutSolution(){
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
    int elc[MAXM];
    int abl[MAXM];
    int now[MAXM];
    vector<int> tasks[MAXM];
    int done[MAXM];
    ms(done, 0);
    ms(abl, 0);
    ms(now, 0);
    int t = 0;
    int tk[MAXM];
    ms(tk, 0);
    bool visited[MAXM];
    ms(visited, 0);
    for (re i = 0; i < m;i++){
        elc[(i) / membernum] = 100;
        abl[(i) / membernum] += ability[i];
    }
    int teams = (int)((m-1) / membernum) + 1;
    for (re i = 0; i < teams;i++){
        tasks[i].push_back(0);
    }
    int turn = 0;
    visited[0] = true;
    while(nearPoint(0, visited) != -1){
        int tmp = nearPoint(now[turn], visited);
        tasks[turn].push_back(tmp);
        visited[tmp] = true;
        now[turn] = tmp;
        turn++;
        turn %= teams;
    }
    ms(visited, 0);
    ms(now, 0);
    int counter = 100000;
    
    while (nearPoint(0, visited) != -1)
    {
        counter--;
        if (counter<0){
            cout << "FATAL: no solution" << endl;
            return false;
        }
        for (re k = 0; k < teams;k++){
            if (done[k] >= tasks[k].size()) continue;
            if (tk[k] * inc[now[k]] + inh[now[k]] < 0)
                visited[now[k]] = true;
            int to = tasks[k][done[k]];
            if (to == -1)
                break;
            if ((diss[now[k]][to] + diss[to][0]) * consume > elc[k])
            {
                to = 0;
            }
            if (tk[k] * inc[now[k]] + inh[now[k]] + diss[now[k]][0] * consume <= elc[k] / consume){
                if (!visited[now[k]]){
                    
                    tk[k] += (tk[k] * inc[now[k]] + inh[now[k]]) / abl[k];
                }
                if (tasks[k][done[k]] == now[k] && visited[now[k]]) done[k]++;
                visited[now[k]] = true;
            }else if (diss[now[k]][0] <= elc[k] / consume){
                int frag = elc[k]/consume - diss[now[k]][0];
                tk[k] += frag;
                inh[now[k]] -= frag * abl[k];
                to = 0;
            }else{
                to = 0;
            }
            elc[k] -= diss[now[k]][to] * consume;
            for (re j = 0; j < m;j++){
                if (solution[j].size() > 0 && to == 0 && solution[j][solution[j].size()-1] == 0){
                    continue;
                }
                solution[j].push_back(to);
            }
            now[k] = to;
            tk[k] += diss[now[k]][to];
            if (to == 0){
                tk[k] += (100 - elc[k]) / charge;
                elc[k] = 100;
            }
            t = max(t, tk[k]);
        }
    }
        
    cout << "\ntime consume: " << t << endl;
    return true;
}

int main(){
    readProblem();
    if (true){
        if(greedy1()){
            coutSolution();
        };
    }else{
        if (greedy2(5)){
            coutSolution();
        }
    }
    
    
    
    system("pause");
    return 0;
}