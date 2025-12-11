#include <bits/stdc++.h>
using namespace std;

// int optimizeLootSplit(int n, vector<int>& coins) {
//     // Calculate total sum
//     int total = 0;
//     for (int coin : coins) {
//         total += coin;
//     }

//     int target = total / 2;

//     // DP array: dp[i] = true if sum i is achievable
//     vector<bool> dp(target + 1, false);
//     dp[0] = true;

//     // For each coin, update possible sums
//     for (int coin : coins) {
//         for (int j = target; j >= coin; j--) {
//             dp[j] = dp[j] || dp[j - coin];
//         }
//     }

//     // Find the largest achievable sum <= target
//     int closest = 0;
//     for (int i = target; i >= 0; i--) {
//         if (dp[i]) {
//             closest = i;
//             break;
//         }
//     }

//     // Minimum difference is |closest - (total - closest)|
//     return abs(2 * closest - total);
// }

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
    int n = items.size();

    // dp[i][w] = max value using first i items with capacity w
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        int weight = items[i - 1].first;
        int value = items[i - 1].second;

        for (int w = 0; w <= capacity; w++)
        {
            // Don't take item i
            dp[i][w] = dp[i - 1][w];

            // Take item i if possible
            if (w >= weight)
            {
                dp[i][w] = max(dp[i][w], dp[i - 1][w - weight] + value);
            }
        }
    }

    return dp[n][capacity];
}

long long countStringPossibilities(string s)
{
    int n = s.length();
    if (n == 0)
        return 1;

    // dp[i] = number of ways to decode s[0...i-1]
    vector<long long> dp(n + 1, 0);
    dp[0] = 1; // Empty string has one way
    dp[1] = 1; // Single character has one way

    for (int i = 2; i <= n; i++)
    {
        // Always can decode as individual characters
        dp[i] = dp[i - 1];

        // Check if we can decode last two characters as a pair
        if (s[i - 2] == 'u' && s[i - 1] == 'u')
        {
            // "uu" can be "w" or "uu", so add alternative decodings
            dp[i] += dp[i - 2];
        }
        else if (s[i - 2] == 'n' && s[i - 1] == 'n')
        {
            // "nn" can be "m" or "nn", so add alternative decodings
            dp[i] += dp[i - 2];
        }
    }

    return dp[n];
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
    vector<string> tests = {"n", "nn", "u", "uu", "uuu", "nnuu"};
    for (const auto &t : tests)
    {
        cout << "countStringPossibilities(\"" << t << "\") = " << countStringPossibilities(t) << '\n';
    }

    return 0;
}
