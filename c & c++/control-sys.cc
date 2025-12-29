#include <iostream>
#include <stack>
using namespace std;

class VersionControl {
    stack<string> versions;

public:
    void commit(string data) {
        versions.push(data);
        cout << "Committed\n";
    }

    void undo() {
        if (!versions.empty()) {
            versions.pop();
            cout << "Last commit undone\n";
        }
    }

    void show() {
        if (!versions.empty())
            cout << "Current version: " << versions.top() << endl;
        else
            cout << "No versions available\n";
    }
};

int main() {
    VersionControl vcs;
    vcs.commit("Initial code");
    vcs.commit("Added feature");
    vcs.show();
    vcs.undo();
    vcs.show();
}
