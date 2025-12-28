#include <iostream>
using namespace std;

int main() {
    string questions[3] = {
        "What is the capital of France?",
        "2 + 2 = ?",
        "C++ is a ___ language?"
    };

    string answers[3] = {"Paris", "4", "Programming"};
    string userAnswer;
    int score = 0;

    for(int i = 0; i < 3; i++) {
        cout << questions[i] << endl;
        cin >> userAnswer;

        if(userAnswer == answers[i])
            score++;
    }

    cout << "Your score: " << score << "/3\n";

    return 0;
}
