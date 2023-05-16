#include <iostream>
#include <vector>
#include <string>

struct Quadruple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

struct Triple {
    std::string op;
    std::string arg1;
    std::string arg2;
};

struct IndirectTriple {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
};

std::vector<Quadruple> quadruples;
std::vector<Triple> triples;
std::vector<IndirectTriple> indirectTriples;

void generateQuadruple(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result) {
    quadruples.push_back({ op, arg1, arg2, result });
}

void generateTriple(const std::string& op, const std::string& arg1, const std::string& arg2) {
    triples.push_back({ op, arg1, arg2 });
}

void generateIndirectTriple(const std::string& op, const std::string& arg1, const std::string& arg2, const std::string& result) {
    indirectTriples.push_back({ op, arg1, arg2, result });
}

void printQuadruples() {
    std::cout << "Quadruples:\n";
    for (const auto& quad : quadruples) {
        std::cout << quad.op << ", " << quad.arg1 << ", " << quad.arg2 << ", " << quad.result << std::endl;
    }
}

void printTriples() {
    std::cout << "Triples:\n";
    for (const auto& triple : triples) {
        std::cout << triple.op << ", " << triple.arg1 << ", " << triple.arg2 << std::endl;
    }
}

void printIndirectTriples() {
    std::cout << "Indirect Triples:\n";
    for (const auto& indirectTriple : indirectTriples) {
        std::cout << indirectTriple.op << ", " << indirectTriple.arg1 << ", " << indirectTriple.arg2 << ", " << indirectTriple.result << std::endl;
    }
}

int main() {
    generateQuadruple("+", "2", "3", "t1");
    generateQuadruple("*", "t1", "4", "t2");
    generateQuadruple("-", "t2", "5", "t3");

    generateTriple("+", "2", "3");
    generateTriple("*", "t1", "4");
    generateTriple("-", "t2", "5");

    generateIndirectTriple("+", "2", "3", "t1");
    generateIndirectTriple("*", "t1", "4", "t2");
    generateIndirectTriple("-", "t2", "5", "t3");

    printQuadruples();
    std::cout << std::endl;
    printTriples();
    std::cout << std::endl;
    printIndirectTriples();

    return 0;
}
