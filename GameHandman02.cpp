#include <iostream>
#include "Gibbet.h"

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    char choice;
    do {
        cout << "\t\t\x1b[33mThe game is on!\x1b[0m\n\n";

        string fileName{ "wordlist.txt" };
        Gibbet g(fileName);

        cout << "\n\t\x1b[35mDo you want to play again? (y/n):\x1b[0m\n ";
        cin >> choice;

    } while (choice != 'y' || choice != 'Y');

    return 0;
}
