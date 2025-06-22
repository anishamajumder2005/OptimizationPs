#include <bits/stdc++.h>
using namespace std;

// Represents a building on the grid
struct Building {
    int x, y, w; // Coordinates (x, y) and associated weight w
};

// Fenwick Tree (Binary Indexed Tree) to support range queries on count and weight
struct FenwickTree {
    int size;
    vector<int> countTree;         // Tracks count of points
    vector<long long> weightTree;  // Tracks sum of weights

    FenwickTree(int n) : size(n), countTree(n + 2), weightTree(n + 2) {}

    // Point update: Add 'cnt' and 'w' at index i
    void update(int i, int cnt, int w) {
        for (++i; i <= size + 1; i += i & -i) {
            countTree[i] += cnt;
            weightTree[i] += w;
        }
    }

    // Prefix sum queries
    int getCount(int i) {
        int res = 0;
        for (++i; i > 0; i -= i & -i) res += countTree[i];
        return res;
    }

    long long getWeight(int i) {
        long long res = 0;
        for (++i; i > 0; i -= i & -i) res += weightTree[i];
        return res;
    }

    // Range queries
    int rangeCount(int l, int r) {
        return getCount(r) - getCount(l - 1);
    }

    long long rangeWeight(int l, int r) {
        return getWeight(r) - getWeight(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int N, K;
    cin >> N >> K;

    vector<Building> A(N);
    set<int> ySet;

    // Input all buildings and collect unique y-values for compression
    for (int i = 0; i < N; ++i) {
        cin >> A[i].x >> A[i].y >> A[i].w;
        ySet.insert(A[i].y);
    }

    // Coordinate compression for y-values
    vector<int> yList(ySet.begin(), ySet.end());
    unordered_map<int, int> yComp;
    for (int i = 0; i < yList.size(); ++i)
        yComp[yList[i]] = i;

    // Sort buildings by x-coordinate to allow sliding window
    sort(A.begin(), A.end(), [](const Building &a, const Building &b) {
        return a.x < b.x;
    });

    double minCost = 1e18;
    vector<double> bestRect(4);  // x1, y1, x2, y2 of the optimal rectangle

    int nY = yList.size();
    FenwickTree tree(nY);
    int left = 0;

    // Right pointer expands the sliding window along x
    for (int right = 0; right < N; ++right) {
        int yIndex = yComp[A[right].y];
        tree.update(yIndex, 1, A[right].w);

        // Try shrinking left of the window while preserving at least K buildings
        while (left <= right) {
            int l = 0, r = 0;
            int bestL = -1, bestR = -1;

            // Binary-like search on y-coordinates to find vertical range containing at least K buildings
            while (r < nY) {
                while (r < nY && tree.rangeCount(l, r) < K) r++;
                if (r < nY && tree.rangeCount(l, r) >= K) {
                    if (bestL == -1 || yList[r] - yList[l] < yList[bestR] - yList[bestL]) {
                        bestL = l;
                        bestR = r;
                    }
                    l++;
                } else break;
            }

            if (bestL != -1) {
                int x1 = A[left].x, x2 = A[right].x;
                int y1 = yList[bestL], y2 = yList[bestR];

                int perim = 2 * ((x2 - x1) + (y2 - y1));
                long long wsum = tree.rangeWeight(bestL, bestR);
                double cost = perim + wsum;

                if (cost < minCost) {
                    minCost = cost;
                    bestRect = {static_cast<double>(x1), static_cast<double>(y1),
                                static_cast<double>(x2), static_cast<double>(y2)};
                }
            }

            // Limit window width to control complexity
            if (right - left > 3000) {
                int removeIndex = yComp[A[left].y];
                tree.update(removeIndex, -1, -A[left].w);
                left++;
            } else break;
        }
    }

    // Output results
    cout << fixed << setprecision(6) << minCost << "\n";
    double x1 = bestRect[0], y1 = bestRect[1], x2 = bestRect[2], y2 = bestRect[3];
    
    // Print rectangle in clockwise order
    cout << x1 << " " << y1 << " " << x2 << " " << y1 << "\n";
    cout << x2 << " " << y1 << " " << x2 << " " << y2 << "\n";
    cout << x2 << " " << y2 << " " << x1 << " " << y2 << "\n";
    cout << x1 << " " << y2 << " " << x1 << " " << y1 << "\n";

    return 0;
}

