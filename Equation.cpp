#include "Equation.h"
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool Equation::func(char c, bool a, bool b) {
    if (c == '^')return a & b;
    if (c == '|')return a | b;
    if (c == '>') return (!a) | b;
    if (c == '-') return (!a | b) & (a | !b);
}

ll Equation::get_number_of_operands(string s) {
    for (auto &i: s) if (isalpha(i)) operands.insert(i);
    return operands.size();
}

int Equation::prec(char c) {
    if (c == '~')
        return 3;
    else if (c == '|' || c == '^')
        return 2;
    else if (c == '>' || c == '-')
        return 1;
    else
        return -1;
}

string Equation::change_to_postfix(string &input) {
    string postfix;
    stack<char> st;

    for (int i = 0; i < input.size(); ++i) {
        char c = input[i];
        if (isalpha(c)) {
            postfix += c;
        } else if (c == '(') st.push(c);
        else if (c == ')') {
            while (st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        } else {
            while (!st.empty() && prec(c) < prec(st.top()) ||
                   !st.empty() && prec(c) == prec(st.top())) {
                postfix += st.top();
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        postfix += st.top();
        st.pop();
    }
    return postfix;
}

void Equation::clean(string &s) {
    string nw;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'v') nw += '|';
        else if (s[i] == '<') {
            nw += '-';
            i++;
        } else {
            nw += s[i];
        }
    }
    s = nw;
}
Equation::Equation() = default;
Equation::Equation(string in) {
    this->input = in;
    clean(input);
    postfix = change_to_postfix(input);
    no_of_operands = get_number_of_operands(input);
}

bool Equation::calc(map<char, bool> in) {
    stack<bool> operands;
    for (int i = 0; i < postfix.size(); i++) {
        if (postfix[i] == '~') {
            operands.top() = !operands.top();
        } else if (!isalpha(postfix[i])) {
            bool x = operands.top();
            operands.pop();
            bool y = operands.top();
            operands.pop();
            operands.push(func(postfix[i], y, x));
        } else
            operands.push(in[postfix[i]]);
    }
    return operands.top();
}

vector<char> Equation::getVariables() {
    vector<char> ret(no_of_operands);
    int j = 0;
    for (auto &i: operands)ret[j++] = i;
    return ret;
}

int Equation::getNoOfOperands() const {
    return no_of_operands;
}

string Equation::getEquation() {
    return input;
}
