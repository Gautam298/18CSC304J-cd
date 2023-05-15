#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>

// Function to calculate First set for a given non-terminal symbol
void calculateFirst(const std::string& symbol,
                    const std::unordered_map<std::string, std::vector<std::vector<std::string>>>& productions,
                    std::unordered_map<std::string, std::unordered_set<std::string>>& firstSet) {
    // Check if First set for the symbol is already calculated
    if (firstSet.find(symbol) != firstSet.end()) {
        return;
    }

    // Initialize an empty set for the First set of the symbol
    std::unordered_set<std::string> first;

    // Get the productions for the symbol
    const std::vector<std::vector<std::string>>& symbolProductions = productions.at(symbol);

    // Iterate through each production
    for (const std::vector<std::string>& production : symbolProductions) {
        const std::string& firstSymbol = production[0];

        // If the first symbol is a terminal, add it to the First set
        if (!isupper(firstSymbol[0])) {
            first.insert(firstSymbol);
        } else {
            // If the first symbol is a non-terminal, recursively calculate First set for it
            calculateFirst(firstSymbol, productions, firstSet);

            // Add the First set of the first symbol (excluding epsilon) to the current symbol's First set
            const std::unordered_set<std::string>& firstSymbolFirst = firstSet.at(firstSymbol);
            for (const std::string& terminal : firstSymbolFirst) {
                if (terminal != "epsilon") {
                    first.insert(terminal);
                }
            }

            // If epsilon is in the First set of the first symbol, continue checking the next symbol in the production
            bool hasEpsilon = (firstSymbolFirst.find("epsilon") != firstSymbolFirst.end());
            size_t i = 1;
            while (hasEpsilon && i < production.size()) {
                const std::string& nextSymbol = production[i];

                // If the next symbol is a terminal, add it to the First set and break the loop
                if (!isupper(nextSymbol[0])) {
                    first.insert(nextSymbol);
                    break;
                } else {
                    // If the next symbol is a non-terminal, recursively calculate First set for it
                    calculateFirst(nextSymbol, productions, firstSet);

                    // Add the First set of the next symbol (excluding epsilon) to the current symbol's First set
                    const std::unordered_set<std::string>& nextSymbolFirst = firstSet.at(nextSymbol);
                    for (const std::string& terminal : nextSymbolFirst) {
                        if (terminal != "epsilon") {
                            first.insert(terminal);
                        }
                    }

                    // If epsilon is not in the First set of the next symbol, break the loop
                    hasEpsilon = (nextSymbolFirst.find("epsilon") != nextSymbolFirst.end());
                    if (!hasEpsilon) {
                        break;
                    }
                }

                i++;
            }
        }
    }

    // Add the calculated First set to the map
    firstSet[symbol] = first;
}

// Function to calculate Follow set for a given non-terminal symbol
void calculateFollow(const std::string& symbol,
                     const std::unordered_map<std::string, std::vector<std::vector<std::string>>>& productions,
                     const std::unordered_map<std::string, std::unordered_set<std::string>>& firstSet,
                     std::unordered_map<std::string, std::unordered_set<std::string>>& followSet) {
    // Implementation of the calculateFollow function
    // ...
}

int main() {
    // Initialize your variables and data structures
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions;
    std::unordered_map<std::string, std::unordered_set<std::string>> firstSet;
    std::unordered_map<std::string, std::unordered_set<std::string>> followSet;

    // Call the calculateFollow function for your desired symbol
    calculateFollow("E", productions, firstSet, followSet);

    // Output the follow sets
    std::cout << "Follow Sets:" << std::endl;
    for (const auto& entry : followSet) {
        const std::string& symbol = entry.first;
        const std::unordered_set<std::string>& follow = entry.second;

        std::cout << symbol << ": ";
        for (const std::string& terminal : follow) {
            std::cout << terminal << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
