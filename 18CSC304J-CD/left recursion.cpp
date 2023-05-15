#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Function to check if a string is a prefix of another string
bool isPrefix(const std::string& str1, const std::string& str2) {
    return (str2.compare(0, str1.length(), str1) == 0);
}

// Function to perform left factoring on a production
void leftFactoring(std::string& production) {
    // Split the production into options
    size_t arrowPos = production.find("->");
    if (arrowPos != std::string::npos) {
        std::string lhs = production.substr(0, arrowPos);
        std::string rhs = production.substr(arrowPos + 2);

        std::vector<std::string> options;
        size_t pipePos = rhs.find("|");
        while (pipePos != std::string::npos) {
            std::string option = rhs.substr(0, pipePos);
            options.push_back(option);
            rhs = rhs.substr(pipePos + 1);
            pipePos = rhs.find("|");
        }
        options.push_back(rhs);

        // Find common prefixes among the options
        std::vector<std::string> commonPrefixes;
        for (size_t i = 0; i < options.size() - 1; i++) {
            for (size_t j = i + 1; j < options.size(); j++) {
                std::string prefix;
                size_t k = 0;
                while (k < options[i].length() && k < options[j].length() && options[i][k] == options[j][k]) {
                    prefix += options[i][k];
                    k++;
                }
                if (!prefix.empty()) {
                    commonPrefixes.push_back(prefix);
                    options[i] = options[i].substr(k);
                    options[j] = options[j].substr(k);
                }
            }
        }

        // Print the left-factored production
        std::cout << "Production after left factoring:" << std::endl;
        std::cout << lhs << " -> ";

        if (commonPrefixes.empty()) {
            // No common prefixes found, print the original options
            for (size_t i = 0; i < options.size(); i++) {
                std::cout << options[i];
                if (i < options.size() - 1) {
                    std::cout << " | ";
                }
            }
        } else {
            // Print the common prefixes and factored options
            for (size_t i = 0; i < commonPrefixes.size(); i++) {
                std::cout << commonPrefixes[i] << " ";
                std::vector<std::string> matchingOptions;
                matchingOptions.push_back(options[0]);

                // Find options with matching prefix
                for (size_t j = 1; j < options.size(); j++) {
                    if (isPrefix(commonPrefixes[i], options[j])) {
                        matchingOptions.push_back(options[j].substr(commonPrefixes[i].length()));
                    }
                }

                // Print the matching options
                for (size_t j = 0; j < matchingOptions.size(); j++) {
                    std::cout << matchingOptions[j];
                    if (j < matchingOptions.size() - 1) {
                        std::cout << " | ";
                    }
                }

                if (i < commonPrefixes.size() - 1) {
                    std::cout << " | ";
                }
            }
        }

        std::cout << std::endl;
    }
}

int main() {
    std::string production;
    std::string nonTerminal;

    std::cout << "Enter the production: ";
    std::getline(std::cin, production);

    std::cout << "Enter the non-terminal symbol: ";
    std::cin >> nonTerminal;

    // Check if the production contains the non-terminal symbol
    if (production.find(nonTerminal) == std::string::npos) {
        std::cout << "Error: The non-terminal symbol is not present in the production." << std::endl;
        return 0;
    }

    // Perform left factoring
    leftFactoring(production);

    return 0;
}
