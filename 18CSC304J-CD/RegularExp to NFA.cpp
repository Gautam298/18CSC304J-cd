#include <iostream>
#include <stack>
#include <vector>

// NFA state structure
struct State {
    char symbol;
    State* next1;
    State* next2;
};

// NFA class
class NFA {
private:
    State* startState;
    State* acceptState;

public:
    NFA(State* start, State* accept) : startState(start), acceptState(accept) {}

    State* getStartState() {
        return startState;
    }

    State* getAcceptState() {
        return acceptState;
    }
};

NFA regexToNFA(const std::string& regex) {
    std::stack<NFA> nfaStack;

    for (char ch : regex) {
        if (ch == '*') {
            NFA nfa = nfaStack.top();
            nfaStack.pop();

            State* acceptState = new State();
            State* startState = new State();
            acceptState->next1 = nfa.getAcceptState();
            acceptState->next2 = nullptr;
            startState->next1 = nfa.getStartState();
            startState->next2 = acceptState;
            nfa.getAcceptState()->next1 = nfa.getStartState();
            nfa.getAcceptState()->next2 = acceptState;

            nfaStack.push(NFA(startState, acceptState));
        }
        else if (ch == '|') {
            NFA nfa2 = nfaStack.top();
            nfaStack.pop();
            NFA nfa1 = nfaStack.top();
            nfaStack.pop();

            State* acceptState = new State();
            State* startState = new State();
            startState->next1 = nfa1.getStartState();
            startState->next2 = nfa2.getStartState();
            nfa1.getAcceptState()->next1 = acceptState;
            nfa2.getAcceptState()->next1 = acceptState;

            nfaStack.push(NFA(startState, acceptState));
        }
        else if (ch == '.') {
            NFA nfa2 = nfaStack.top();
            nfaStack.pop();
            NFA nfa1 = nfaStack.top();
            nfaStack.pop();

            nfa1.getAcceptState()->next1 = nfa2.getStartState();

            nfaStack.push(NFA(nfa1.getStartState(), nfa2.getAcceptState()));
        }
        else {
            State* acceptState = new State();
            State* startState = new State();
            startState->symbol = ch;
            startState->next1 = acceptState;
            startState->next2 = nullptr;

            nfaStack.push(NFA(startState, acceptState));
        }
    }

    NFA finalNFA = nfaStack.top();
    nfaStack.pop();

    return finalNFA;
}

int main() {
    std::string regex;
    std::cout << "Enter a regular expression: ";
    std::cin >> regex;

    NFA nfa = regexToNFA(regex);
    std::cout << "NFA constructed successfully!" << std::endl;

    return 0;
}

