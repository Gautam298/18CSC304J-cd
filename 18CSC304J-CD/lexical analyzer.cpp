#include <iostream>
#include <string>
#include <vector>

// Token structure to store token information
struct Token {
    std::string lexeme;
    std::string tokenType;
};

// Function to perform lexical analysis
std::vector<Token> lexicalAnalyzer(const std::string& input) {
    std::vector<Token> tokens;
    std::string lexeme = "";
    std::string tokenType = "";

    for (size_t i = 0; i < input.length(); i++) {
        char ch = input[i];

        if (ch == ' ') {
            if (!lexeme.empty()) {
                tokens.push_back(Token());
                tokens.back().lexeme = lexeme;
                tokens.back().tokenType = tokenType;
                lexeme.clear();
            }
        }
        else if (isalpha(ch)) {
            lexeme += ch;
            tokenType = "IDENTIFIER";
        }
        else if (isdigit(ch)) {
            lexeme += ch;
            tokenType = "NUMBER";
        }
        else {
            if (!lexeme.empty()) {
                tokens.push_back(Token());
                tokens.back().lexeme = lexeme;
                tokens.back().tokenType = tokenType;
                lexeme.clear();
            }
            lexeme += ch;
            tokenType = "SYMBOL";
            tokens.push_back(Token());
            tokens.back().lexeme = lexeme;
            tokens.back().tokenType = tokenType;
            lexeme.clear();
        }
    }

    if (!lexeme.empty()) {
        tokens.push_back(Token());
        tokens.back().lexeme = lexeme;
        tokens.back().tokenType = tokenType;
    }

    return tokens;
}

// Function to display tokens
void displayTokens(const std::vector<Token>& tokens) {
    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];
        std::cout << "Lexeme: " << token.lexeme << ", Token Type: " << token.tokenType << std::endl;
    }
}

int main() {
    std::string input;
    std::cout << "Enter the input string: ";
    std::getline(std::cin, input);

    std::vector<Token> tokens = lexicalAnalyzer(input);
    displayTokens(tokens);

    return 0;
}

