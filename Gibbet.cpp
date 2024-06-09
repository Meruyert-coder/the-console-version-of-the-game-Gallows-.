#include "Gibbet.h"

const vector<string> Gibbet::v{
    {
        "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            "\n"
            " ############################\n"
            " #                          #\n"
    },
    {
        "        ###############\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
    {
        "        ###############\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
    {
        "        ###############\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        O             #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
    {
        "        ###############\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        O             #\n"
        "      /   \\           #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
    {
        "        ###############\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        O             #\n"
        "      / | \\           #\n"
        "        |             #\n"
        "                      #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
    {
        "        ###############\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        |             #\n"
        "        O             #\n"
        "      / | \\           #\n"
        "        |             #\n"
        "       / \\            #\n"
        "                      #\n"
        "                      #\n"
        " ############################\n"
        " #                          #\n"
    },
};

Gibbet::Gibbet() : file(), word(), guess(), startTime(), endTime() {}

Gibbet::Gibbet(const string& f_) : file(f_) {
    if (!file.is_open()) {
        cerr << "Error opening file " << f_ << "\n";
        exit(EXIT_FAILURE);
    }

    vector<string> words;
    string line;
    while (getline(file, line)) {
        words.push_back(decrypt(line));
    }

    if (words.empty()) {
        cerr << "File is empty.\n";
        exit(EXIT_FAILURE);
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> uni(0, words.size() - 1);
    word = words[uni(rng)];

    Play();
}

Gibbet::~Gibbet() {
    file.close();
}

string Gibbet::decrypt(const string& input) const {
    string result = input;

    for (char& c : result) {
        if (isalpha(c)) {
            c = 'a' + (c - 'a' + 24) % 26;
        }
    }

    return result;
}

void Gibbet::Play() {
    startTime = chrono::steady_clock::now();

    bool result = false;
    char ch{};
    int countT{};

    while (true) {
        cout << "Enter a symbol: ";
        cin >> ch;

        ch = tolower(ch);

        if (word.find(ch) != string::npos && guess.find(ch) == guess.end()) {
            guess.insert(ch);

            replace_copy_if(word.cbegin(), word.cend(), ostream_iterator<char>(cout), [this](const char& cc) {
                return guess.find(cc) == guess.end();
                }, '#');

            cout << endl;

            if (all_of(word.cbegin(), word.cend(), [this](const char& cc) { return guess.find(cc) != guess.end(); })) {
                result = true;
                break;
            }
        }
        else {
            system("cls");
            displayHangman(countT);
            ++countT;
            if (countT == v.size())
                break;
        }
    }

    endTime = chrono::steady_clock::now();
    displayStatistics();
}

void Gibbet::displayStatistics() const {
    cout << "\x1b[33mGame statistics:\x1b[0m\n";
    cout << "\x1b[32mTime taken: \x1b[0m" << chrono::duration_cast<chrono::seconds>(endTime - startTime).count() << " seconds\n";
    cout << "\x1b[36mAttempts made: \x1b[0m" << guess.size() << "\n";
    cout << "\x1b[34mSecret word: \x1b[0m" << word << "\n";
    cout << "\x1b[35mGuessed letters: \x1b[0m";
    for (char letter : guess) {
        cout << letter << " ";
    }
    cout << "\n";
}

void Gibbet::displayHangman(int countT) const {
    cout << v[countT] << endl;
}
