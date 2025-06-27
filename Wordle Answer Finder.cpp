#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;



string findMostValuableWord(const vector<string>& words, const map<char, int>& charCount) {
    int bestScore = -1;
    string bestWord;

    for (const auto& word : words) {
        set<char> uniqueLetters;
        int score = 0;

        for (char c : word) {
            if (uniqueLetters.find(c) == uniqueLetters.end()) {
                uniqueLetters.insert(c);
                auto it = charCount.find(c);
                if (it != charCount.end()) {
                    score += it->second;
                }
            }
        }

        if (score > bestScore) {
            bestScore = score;
            bestWord = word;
        }
    }

    return bestWord;
}


int main() {
    map<char, int> charCount;  // Count of each character
    vector<string> words;
    string word;

    std::cout << "Reading words from file..." << endl;
    std::cout << "=========================" << endl;

    fstream file("words.txt");
    if (file.is_open()) {
        while (file >> word) {
            for (int i = 0; i < word.length() && i < 5; i++) {
                charCount[word[i]]++;
            }
            words.push_back(word);
        }
        file.close();
    }
    else {
        std::cout << "Error: Failed to open file 'words.txt'." << endl;
        return 1;
    }

    std::cout << "Loaded " << words.size() << " words." << endl;

    int basesize = words.size();
    std::cout << "Character frequencies:" << endl;
    for (const auto& entry : charCount) {
        std::cout << entry.first << ": " << entry.second << endl;
    }
    charCount.clear();
    string result;
    string guess;
    string best;
    std::cout << "Now lets start the wordle. I recommend to start with ADIEU, as it has the most common letters." << endl;
    std::cout << "W - wrong, gray letter" << endl;
    std::cout << "G - green, correct letter on correct spot" << endl;
    std::cout << "Y - yellow, correct letter, but on wrong spot" << endl;
    guess = "adieu";


        while (result != "GGGGG") {
            std::cout << "Please enter the result (USE CAPITAL LETTERS):" << endl;
            cin >> result;
            //result = wordle(guess, winword);
            if (result == "GGGGG") {
                break;
            }
            for (int i = 0; i < 5; i++) {
                switch (int(result[i])) {
                case 87: { // Gray (not in word)
                    for (int j = 0; j < words.size();) {
                        if (words[j].find(guess[i]) != string::npos) {
                            words.erase(words.begin() + j);
                        }
                        else {
                            ++j;
                        }
                    }
                    break;
                }

                case 71: { // Green (correct position)
                    for (int j = 0; j < words.size();) {
                        if (words[j][i] != guess[i]) {
                            words.erase(words.begin() + j);
                        }
                        else {
                            ++j;
                        }
                    }
                    break;
                }

                case 89: { // Yellow (in word but wrong position)
                    for (int j = 0; j < words.size();) {
                        if (words[j].find(guess[i]) == string::npos || words[j][i] == guess[i]) {
                            words.erase(words.begin() + j);
                        }
                        else {
                            ++j;
                        }
                    }
                    break;
                }
                }
            }

            std::cout << basesize - words.size() << " words eliminated. " << words.size() << " remaining." << endl;
            basesize = words.size();


            for (const string& w : words) {
                for (int i = 0; i < 5; i++) {
                    charCount[w[i]]++;
                }
            }
            //for (const auto& entry : charCount) {
            //    std::cout << entry.first << ": " << entry.second << endl;
            //}

            best = findMostValuableWord(words, charCount);
            std::cout << "best word to guess is: " << best << endl;
            guess = best;
            charCount.clear();

        }

    
    std::cout << "Congrats, we did it!!!";
    return 0;
}
