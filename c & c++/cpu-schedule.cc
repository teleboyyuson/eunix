#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, burst;
};

int main() {
    vector<Process> p = {{1, 5}, {2, 2}, {3, 8}, {4, 3}};

    sort(p.begin(), p.end(),
         [](Process a, Process b) { return a.burst < b.burst; });

    int time = 0;
    cout << "Process Execution Order:\n";
    for (auto &x : p) {
        time += x.burst;
        cout << "P" << x.id << " completed at " << time << endl;
    }

    return 0;
}

