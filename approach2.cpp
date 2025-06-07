#include <bits/stdc++.h>
using namespace std;

struct Building {
    int x, y, w;
};

bool compareByWeight(const Building &a, const Building &b) {
    return a.w < b.w;
}

int main() {
    int N, K;
    cin >> N >> K;

    vector<Building> buildings(N);
    for (int i = 0; i < N; ++i) {
        cin >> buildings[i].x >> buildings[i].y >> buildings[i].w;
    }

    sort(buildings.begin(), buildings.end(), compareByWeight);

    // Select the K buildings with the least weight
    double min_x = 1e9, max_x = -1e9, min_y = 1e9, max_y = -1e9;
    long long weight_sum = 0;

    for (int i = 0; i < K; ++i) {
        min_x = min(min_x, (double)buildings[i].x);
        max_x = max(max_x, (double)buildings[i].x);
        min_y = min(min_y, (double)buildings[i].y);
        max_y = max(max_y, (double)buildings[i].y);
        weight_sum += buildings[i].w;
    }

    double eps = 1e-6;
    min_x -= eps; max_x += eps;
    min_y -= eps; max_y += eps;

    // Calculate perimeter
    double perimeter = 2.0 * ((max_x - min_x) + (max_y - min_y));
    double total_cost = perimeter + weight_sum;
    cout << fixed << setprecision(6) << total_cost << "\n";

    // Output rectangle edges in order (clockwise or counterclockwise)
    vector<tuple<double, double, double, double>> edges = {
        {min_x, min_y, max_x, min_y},
        {max_x, min_y, max_x, max_y},
        {max_x, max_y, min_x, max_y},
        {min_x, max_y, min_x, min_y}
    };

    for (auto &[x1, y1, x2, y2] : edges) {
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
    }

    return 0;
}
