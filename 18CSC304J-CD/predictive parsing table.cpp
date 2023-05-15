#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Function to initialize the predictive parsing table
void initializePredictiveParsingTable(unordered_map<string, unordered_map<string, vector<string>>>& parsingTable,
                                      const vector<string>& nonTerminals,
                                      const vector<string>& terminals) {
    // Prompt for production rules and generate entries in the predictive parsing table
    for (const string& nonTerminal : nonTerminals) {
        parsingTable[nonTerminal] = {};
        for (const string& terminal : terminals) {
            string production;
            cout << "Enter the production for " << nonTerminal << " and " << terminal << " (use space-separated symbols, enter 'e' for epsilon): ";
            getline(cin, production);
            parsingTable[nonTerminal][terminal] = {}; // Initialize with an empty production rule
            if (production != "e") {
                size_t startPos = 0;
                size_t endPos = production.find(" ");
                while (endPos != string::npos) {
                    string symbol = production.substr(startPos, endPos - startPos);
                    parsingTable[nonTerminal][terminal].push_back(symbol);
                    startPos = endPos + 1;
                    endPos = production.find(" ", startPos);
                }
                string lastSymbol = production.substr(startPos, endPos);
                parsingTable[nonTerminal][terminal].push_back(lastSymbol);
            }
        }
    }
}

// Function to print the predictive parsing table
void printPredictiveParsingTable(const unordered_map<string, unordered_map<string, vector<string>>>& parsingTable,
                                 const vector<string>& nonTerminals,
                                 const vector<string>& terminals) {
    cout << "Predictive Parsing Table:" << endl;

    // Print the table header
    cout << "\t";
    for (const string& terminal : terminals) {
        cout << terminal << "\t";
    }
    cout << endl;

    // Print the table contents
    for (const string& nonTerminal : nonTerminals) {
        cout << nonTerminal << "\t";
        for (const string& terminal : terminals) {
            const vector<string>& production = parsingTable.at(nonTerminal).at(terminal);
            if (!production.empty()) {
                // Print the production rule
                for (const string& symbol : production) {
                    cout << symbol << " ";
                }
            } else {
                cout << "e"; // Print "e" for epsilon (empty) entry
            }
            cout << "\t";
        }
        cout << endl;
    }
}

int main() {
    // Define your non-terminals and terminals
    vector<string> nonTerminals{"E", "T", "E'"};
    vector<string> terminals{"id", "+", "*"};

    // Define your predictive parsing table
    unordered_map<string, unordered_map<string, vector<string>>> parsingTable;

    // Initialize the predictive parsing table
    initializePredictiveParsingTable(parsingTable, nonTerminals, terminals);

    // Print the predictive parsing table
    printPredictiveParsingTable(parsingTable, nonTerminals, terminals);

    return 0;
}
