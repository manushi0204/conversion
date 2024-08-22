#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Helper function to get precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else if (op == '^') {
        return 3;
    }
    return 0;
}

// Helper function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Helper function to check if a character is an operand
bool isOperand(char c) {
    return isalpha(c) || isdigit(c);
}

string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";

    for (char &c : infix) {
        if (isOperand(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop(); // remove '('
        } else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }

    return postfix;
}
string infixToPrefix(string infix) {
    // Reverse the infix expression
    reverse(infix.begin(), infix.end());

    // Replace '(' with ')' and vice versa
    for (char &c : infix) {
        if (c == '(') {
            c = ')';
        } else if (c == ')') {
            c = '(';
        }
    }

    // Convert to postfix
    string postfix = infixToPostfix(infix);

    // Reverse postfix to get prefix
    reverse(postfix.begin(), postfix.end());

    return postfix;
}
string postfixToInfix(string postfix) {
    stack<string> s;

    for (char &c : postfix) {
        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op2 = s.top(); s.pop();
            string op1 = s.top(); s.pop();
            string temp = "(" + op1 + c + op2 + ")";
            s.push(temp);
        }
    }

    return s.top();
}
string prefixToInfix(string prefix) {
    stack<string> s;

    // Traverse from right to left
    for (int i = prefix.length() - 1; i >= 0; i--) {
        char c = prefix[i];

        if (isOperand(c)) {
            s.push(string(1, c));
        } else if (isOperator(c)) {
            string op1 = s.top(); s.pop();
            string op2 = s.top(); s.pop();
            string temp = "(" + op1 + c + op2 + ")";
            s.push(temp);
        }
    }

    return s.top();
}
int main() {
    string infix = "(A-B/C)*(A/K-L)";
    cout << "Infix: " << infix << endl;

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    string prefix = infixToPrefix(infix);
    cout << "Prefix: " << prefix << endl;

    string infixFromPostfix = postfixToInfix(postfix);
    cout << "Infix from Postfix: " << infixFromPostfix << endl;

    string infixFromPrefix = prefixToInfix(prefix);
    cout << "Infix from Prefix: " << infixFromPrefix << endl;

    return 0;
}
