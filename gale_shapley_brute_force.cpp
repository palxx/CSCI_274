#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if a matching is stable
bool isStable(const vector<vector<int>>& menPreferences, const vector<vector<int>>& womenPreferences, const vector<int>& matching, int n) {
    // matching[i] gives the woman that the ith man is paired with
    for (int i = 0; i < n; ++i) {
        int currentWoman = matching[i];
        // Go through all women to see if there is instability
        for (int j = 0; j < n; ++j) {
            if (j == currentWoman) continue;
            int preferredWoman = j;
            int manIndexInPreferredWomanList = find(womenPreferences[preferredWoman].begin(), womenPreferences[preferredWoman].end(), i) - womenPreferences[preferredWoman].begin();
            int manIndexInCurrentWomanList = find(womenPreferences[preferredWoman].begin(), womenPreferences[preferredWoman].end(), matching[preferredWoman]) - womenPreferences[preferredWoman].begin();

            if (manIndexInPreferredWomanList < manIndexInCurrentWomanList) {
                return false;
            }
        }
    }
    return true;
}

void bruteForceStableMarriage(int n, const vector<vector<int>>& menPreferences, const vector<vector<int>>& womenPreferences) {
    // Initialize men matching (first pairing)
    vector<int> matching(n);
    for (int i = 0; i < n; ++i) matching[i] = i;
    
    do {
        // Check if the current matching is stable
        if (isStable(menPreferences, womenPreferences, matching, n)) {
            cout << "Stable Matching Found:\n";
            for (int i = 0; i < n; ++i) {
                cout << "Man " << i << " is matched with Woman " << matching[i] << "\n";
            }
            return;
        }
    } while (next_permutation(matching.begin(), matching.end()));

    cout << "No stable matching found.\n";
}

int main() {
    int n = 3;

    // Men preferences (3 men)
    vector<vector<int>> menPreferences = {
        {0, 1, 2}, // Man 0 prefers Woman 0 > Woman 1 > Woman 2
        {1, 0, 2}, // Man 1 prefers Woman 1 > Woman 0 > Woman 2
        {2, 0, 1}  // Man 2 prefers Woman 2 > Woman 0 > Woman 1
    };

    // Women preferences (3 women)
    vector<vector<int>> womenPreferences = {
        {0, 1, 2}, // Woman 0 prefers Man 0 > Man 1 > Man 2
        {2, 0, 1}, // Woman 1 prefers Man 2 > Man 0 > Man 1
        {1, 0, 2}  // Woman 2 prefers Man 1 > Man 0 > Man 2
    };

    bruteForceStableMarriage(n, menPreferences, womenPreferences);

    return 0;
}
