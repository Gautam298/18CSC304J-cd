#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>

void calculateFirst(const std::string& symbol,
                    const std::unordered_map<std::string, std::vector<std::vector<std::string>>>& productions,
                    std::unordered_map<std::string, std::unordered_set<std::string>>& firstSet) {
    if (firstSet.find(symbol) != firstSet.end()) {
        // First set for the symbol is already calculated
        return;
    }

    std::vector<std::vector<std::string>> symbolProductions = productions.at(symbol);

    for (const std::vector<std::string>& production : symbolProductions) {
        const std::string& firstSymbol = production.front();

        if (firstSymbol != symbol) {
            if (productions.find(firstSymbol) != productions.end()) {
                // Non-terminal symbol
                calculateFirst(firstSymbol, productions, firstSet);

                // Add first set of firstSymbol to firstSet[symbol]
                firstSet[symbol].insert(firstSet[firstSymbol].begin(), firstSet[firstSymbol].end());
            } else {
                // Terminal symbol
                firstSet[symbol].insert(firstSymbol);
            }
        }
    }
}
void calculateFollow(const std::string& symbol,
                     const std::unordered_map<std::string, std::vector<std::vector<std::string>>>& productions,
                     const std::unordered_map<std::string, std::unordered_set<std::string>>& firstSet,
                     const std::unordered_map<std::string, std::unordered_set<std::string>>& followSet) {
    // Implementation of the calculateFollow function
    // ...
}


int main() {
    // Define your productions
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> productions = {
        {"E", {{"T", "E'"}, {"T", "+", "E'"}}},
        {"E'", {{"T", "E'"}, {""}}},
        {"T", {{"F", "T'"}}},
        {"T'", {{"F", "T'"}, {""}}},
        {"F", {{"(", "E", ")"}, {"id"}}}
    };

    // Calculate the First sets
    std::unordered_map<std::string, std::unordered_set<std::string>> firstSet;
    for (const auto& production : productions) {
        const std::string& symbol = production.first;
        calculateFirst(symbol, productions, firstSet);
    }

    // Calculate the Follow sets
    std::unordered_map<std::string, std::unordered_set<std::string>> followSet;
    const std::string startSymbol = "E";
    followSet[startSymbol].insert("$"); // Add end of input marker to start symbol
    for (const auto& production : productions) {
        const std::string& symbol = production.first;
        calculateFollow(symbol, productions, firstSet, followSet);
    }

    // Print the First sets
    std::cout << "First Sets:" << std::endl;
    for (const auto& entry : firstSet) {
        const std::string& symbol = entry.first;
        const std::unordered_set<std::string>& firsts = entry.second;

        std::cout << symbol << ": ";
        for (const std::string& first : firsts) {
            std::cout << first << " ";
        }
        std::cout << std::endl;
    }

    // Print the Follow sets
    std::cout << "Follow Sets:" << std::endl;
    for (const auto& entry : followSet) {
        const std::string& symbol = entry.first;
        const std::unordered_set<std::string>& follows = entry.second;

        std::cout << symbol << ": ";
        for (const std::string& follow : follows) {
            std::cout << follow << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

