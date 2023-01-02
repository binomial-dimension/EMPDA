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

const int MAXN = 100;
const int MAXM = 100;
const double eps = 1e-6;

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

int dis(int x1, int x2, int y1, int y2){
    return int(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}

int xpos[MAXN], ypos[MAXN], inc[MAXN], inh[MAXN], ability[MAXM];
int diss[MAXN][MAXN];
int main(){
    cout << "Please Input point numbers and robot numbers: m, n\n";
    int n = read(),m = read();
    if (n>=MAXN||m>=MAXM) return 0;
    srand(time(0));
    for (re i=0;i<n;i++){
        xpos[i] = rand() % 17;
        ypos[i] = rand() % 17;
        inc[i] = rand() % (2 * m);
        inh[i] = rand() % 5;
    }
    for (re i=0;i<m;i++){
        ability[i] = rand() % 14 + 1;
    }
    for (re i=0;i<n;i++){
        for (re j=0;j<n;j++){
            diss[i][j] = dis(xpos[i],xpos[j],ypos[i],ypos[j]);
        }
    }
    inh[0] = 0;
    inc[0] = 0;

    cout<<n<<' '<<m;
    for (re i=0;i<n;i++){
        for (re j=0;j<n;j++){
            cout<<diss[i][j]<<' ';
        }
        cout<<endl;
    }
    for (re i=0;i<n;i++){
        cout<<inc[i]<<' ';
    }
    cout<<endl;
    for (re i=0;i<n;i++){
        cout<<inh[i]<<' ';
    }
    cout<<endl;
    for (re i=0;i<m;i++){
        cout<<ability[i]<<' ';
    }
    cout<<endl;
    cout<< "1 0"<<endl;
    system("pause");
    return 0;
}