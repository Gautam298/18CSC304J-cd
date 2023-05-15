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
    // Check if Follow set for the symbol is already calculated
    if (followSet.find(symbol) != followSet.end()) {
        return;
    }

    // Initialize an empty set for the Follow set of the symbol
    std::unordered_set<std::string> follow;

    // If the symbol is the starting symbol, add the end marker ($) to its Follow set
    if (symbol == "<start>") {
        follow.insert("$");
    }

    // Iterate through each production
    for (const auto& entry : productions) {
        const std::string& nonTerminal = entry.first;
        const std::vector<std::vector<std::string>>& nonTerminalProductions = entry.second;

        // Iterate through each production for the non-terminal symbol
        for (const std::vector<std::string>& production : nonTerminalProductions) {
            for (size_t i = 0; i < production.size(); ++i) {
                if (production[i] == symbol) {
                    // Case 1: A -> αBβ, where β is a string of symbols
                    if (i + 1 < production.size()) {
                        const std::string& nextSymbol = production[i + 1];

                        // If the next symbol is a terminal, add it to the Follow set
                        if (!isupper(nextSymbol[0])) {
                            follow.insert(nextSymbol);
                        } else {
                            // If the next symbol is a non-terminal, add the First set of the next symbol
                            // (excluding epsilon) to the current symbol's Follow set
                            const std::unordered_set<std::string>& nextSymbolFirst = firstSet.at(nextSymbol);
                            for (const std::string& terminal : nextSymbolFirst) {
                                if (terminal != "epsilon") {
                                    follow.insert(terminal);
                                }
                            }

                            // If epsilon is in the First set of the next symbol, add the Follow set of the
                            // non-terminal to the current symbol's Follow set
                            bool hasEpsilon = (nextSymbolFirst.find("epsilon") != nextSymbolFirst.end());
                            if (hasEpsilon) {
                                calculateFollow(nonTerminal, productions, firstSet, followSet);
                                const std::unordered_set<std::string>& nonTerminalFollow = followSet.at(nonTerminal);
                                follow.insert(nonTerminalFollow.begin(), nonTerminalFollow.end());
                            }
                        }
                    }
                    // Case 2: A -> αB or A -> αBβ, where β is epsilon
                    else {
                        // If the non-terminal symbol is different from the current symbol, recursively calculate
                        // Follow set for the non-terminal and add it to the current symbol's Follow set
                        if (nonTerminal != symbol) {
                            calculateFollow(nonTerminal, productions, firstSet, followSet);
                            const std::unordered_set<std::string>& nonTerminalFollow = followSet.at(nonTerminal);
                            follow.insert(nonTerminalFollow.begin(), nonTerminalFollow.end());
                        }
                    }
                }
            }
        }
    }

    // Add the calculated Follow set to the map
    followSet[symbol] = follow;
}

