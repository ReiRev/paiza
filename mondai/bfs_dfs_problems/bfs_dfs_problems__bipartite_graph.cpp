#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// 幅優先探索でチェック
bool check_bipartite(vector<bool> &searched, vector<bool> &color, vector<vector<int>> &e, int n, int start)
{
    searched[start] = true;
    // 隣接するものに対して、色づけてしていく
    // すでに探しているもので、二部グラフと矛盾するものがないかチェック
    for (int v : e[start])
    {
        if (searched[v] && color[v] == color[start])
        {
            // cout << "not same color" << endl;
            return false;
        }
        else
        {
            color[v] = !color[start];
        }
    }

    // 隣接するものに対して、同じことを繰り返す。
    for (int v : e[start])
    {
        if (!searched[v])
        {
            if (!check_bipartite(searched, color, e, n, v))
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++)
    {
        int _a, _b;
        cin >> _a >> _b;
        _a--;
        _b--;
        e[_a].push_back(_b);
        e[_b].push_back(_a);
    }
    // searched, color(0or1)
    vector<bool> searched(n, false);
    vector<bool> color(n, false);
    bool is_bipartite = true;
    // 木が連結していないかもしれないので注意！
    for (int i = 0; i < n; i++)
    {
        if (!searched[i])
        {
            is_bipartite = check_bipartite(searched, color, e, n, i);
        }
        if (!is_bipartite)
        {
            break;
        }
    }

    if (is_bipartite)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
}