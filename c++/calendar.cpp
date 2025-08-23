#include <iostream>
#include <string>


using namespace std;

int main()
{

    int num;
    cout << "Enter a number:"; // Input a number between 1 and 12
    cin >> num;

    switch (num) {
        case 1:
            cout << "It's January\n"; 
            break;
        case 2:
            cout << "It's Februrary\n"; 
            break;
        case 3:
            cout << "It's March\n"; 
            break;
        case 4:
            cout << "It's April\n"; 
            break;
        case 5:
            cout << "It's May\n"; 
            break;
        case 6:
            cout << "It's June\n"; 
            break;
        case 7:
            cout << "It's July\n"; 
            break;
        case 8:
            cout << "It's August\n"; 
            break;
        case 9:
            cout << "It's September\n"; 
            break;
        case 10:
            cout << "It's October\n"; 
            break;
        case 11:
            cout << "It's November\n"; 
            break;
        case 12:
            cout << "It's December\n"; 
            break;
        default:
            cout << "Invalid month number!\n";
            break;
    }
    
    return 0;
    
}

