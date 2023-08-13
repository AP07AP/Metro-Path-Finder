#include <bits/stdc++.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, string> P;

unordered_map<string, unordered_map<string, int>> metroGraph;

vector<string> dijkstra(const string& start, const string& end) {
    priority_queue<P, vector<P>, greater<P>> pq;
    unordered_map<string, int> distances;
    unordered_map<string, string> previous;
    vector<string> path;

    for (const auto& station : metroGraph) {
        distances[station.first] = numeric_limits<int>::max();
    }

    distances[start] = 0;
    pq.push(make_pair(0, start));

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        string currentStation = pq.top().second;
        pq.pop();

        if (currentDistance > distances[currentStation]) {
            continue;
        }

        for (const auto& neighbor : metroGraph[currentStation]) {
            string nextStation = neighbor.first;
            int weight = neighbor.second;
            int distance = currentDistance + weight;

            if (distance < distances[nextStation]) {
                distances[nextStation] = distance;
                previous[nextStation] = currentStation;
                pq.push(make_pair(distance, nextStation));
            }
        }
    }

    string current = end;
    while (!current.empty()) {
        path.push_back(current);
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

int main() {
    metroGraph["A"] = {{"B", 5}, {"C", 2}};
    metroGraph["B"] = {{"A", 5}, {"C", 1}, {"D", 3}};
    metroGraph["C"] = {{"A", 2}, {"B", 1}, {"D", 6}};
    metroGraph["D"] = {{"B", 3}, {"C", 6}};

    string start = "A";
    string end = "D";

    vector<string> shortestPath = dijkstra(start, end);

    cout << "Shortest path from " << start << " to " << end << ": ";
    for (const auto& station : shortestPath) {
        cout << station << " ";
    }
    
    cout << endl;

    return 0;
}
