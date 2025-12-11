#include <bits/stdc++.h>
using namespace std;

int optimizeLootSplit(int n, vector<int> &coins)
{

    int total = 0;
    for (int c : coins)
        total += c;

    int target = total / 2;

    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int c : coins)
    {
        for (int s = target; s >= c; s--)
        {
            if (dp[s - c])
                dp[s] = true;
        }
    }

    int best = 0;
    for (int s = target; s >= 0; s--)
    {
        if (dp[s])
        {
            best = s;
            break;
        }
    }

    int other = total - best;
    return abs(other - best);
}


int maximizeCarryValue(int capacity, vector<pair<int, int>> &items)
{
    int R = items.size();  //total rows
    int C = capacity;  //total columns
    vector<vector<int>> dp(R + 1, vector<int>(C + 1, 0));

    for (int r = 1; r <= R; r++)
    {
        int weight = items[r - 1].first;
        int value = items[r - 1].second;

        for (int c = 1; c <= C; c++)
        {
            dp[r][c] = dp[r - 1][c];

            if (c >= weight)
            {
                dp[r][c] = max(dp[r][c], dp[r - 1][c - weight] + value);
            }
        }
    }

    return dp[R][C];
}


long long countStringPossibilities(string s)
{
    const long long MOD = 1e9 + 7;
    int n = s.size();

    map<string, long long> dp;
    dp[""] = 1LL;
    dp["n"] = 1LL;
    dp["u"] = 1LL;
    dp["nn"] = 2LL;
    dp["uu"] = 2LL;

    //------------------------------------------

    queue<char> q;
    for (int i = 0 ; i < n; i++)
    {
        q.push(s[i]);
    }

    long long count = 1;   

    while (!q.empty())
    {
        char ch1 = q.front();
        q.pop();

        if (q.empty())
        {
            string single = "";
            single += ch1;

            if (dp.find(single) != dp.end())
                count *= dp[single];
            else
                count *= dp[""] ;

            break;
        }

        //------------------------------------------
        char ch2 = q.front();
        
        string comb = "";
        comb += ch1;
        comb += ch2;

        if (dp.find(comb) != dp.end())
        {
            count *= dp[comb];
            q.pop();
        }
        else
        {
            string single = "";
            single += ch1;

            if (dp.find(single) != dp.end())
                count *= dp[single];
            else
                count *= dp[""] ;
        }
    }

    return count % MOD;
}


int main()
{
    // Test optimizeLootSplit
    vector<int> coins = {1, 2, 4};
    cout << "optimizeLootSplit({1,2,4}) = " << optimizeLootSplit((int)coins.size(), coins) << '\n';

    // Test maximizeCarryValue
    vector<pair<int, int>> items = {{3, 4}, {4, 5}, {2, 3}};
    cout << "maximizeCarryValue(cap=7) = " << maximizeCarryValue(7, items) << '\n';

    // Test countStringPossibilities
    vector<string> tests = {"n", "nn", "u", "uu", "uuu", "nnuu","mnuu"};
    for (const auto &t : tests)
    {
        cout << "countStringPossibilities(\"" << t << "\") = " << countStringPossibilities(t) << '\n';
    }

    return 0;
}
