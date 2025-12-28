#include <iostream>
using namespace std;

double balance = 0;

void deposit(double amount) {
    balance += amount;
}

void withdraw(double amount) {
    if(amount <= balance)
        balance -= amount;
    else
        cout << "Insufficient balance\n";
}

int main() {
    int choice;
    double amount;

    do {
        cout << "\n1. Deposit\n2. Withdraw\n3. Check Balance\n4. Exit\n";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter amount: ";
                cin >> amount;
                deposit(amount);
                break;
            case 2:
                cout << "Enter amount: ";
                cin >> amount;
                withdraw(amount);
                break;
            case 3:
                cout << "Balance: " << balance;
                break;
        }
    } while(choice != 4);

    return 0;
}