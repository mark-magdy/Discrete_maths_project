//
// Created by marka on 11/26/2024.
//

#ifndef PROJECT_EQUATION_H
#define PROJECT_EQUATION_H

#include <bits/stdc++.h>
#define print(x) for(auto &ij:x) cout << ij.second <<" "

using namespace std;
using ll = long long;

class Equation {
private:
    string input, postfix;
    int no_of_operands{};
    set<char> operands;

    bool func(char c, bool a, bool b); //it does the xor , or , -> , minus

    ll get_number_of_operands(string s);

    int prec(char c);//priority of operations

    string change_to_postfix(string &input);

    void clean(string &s);

public:
    Equation();

    Equation(string in);

    bool calc(map<char, bool> in);

    vector<char> getVariables();

    int getNoOfOperands() const;

    string getEquation();
};


#endif //PROJECT_EQUATION_H


















/*

unordered_set <char> operands ;
bool func(char c , bool a, bool b) {
    if (c=='^')return a&b;
    if (c=='|')return a|b;
    if (c=='>') return (!a)|b;
    if (c=='-') return (!a|b)&(a|!b);
}
ll get_number_of_operands (string s ){
    for ( auto &i: s) if (isalpha(i)) operands.insert(i);
    return operands.size();
}
int prec(char c) {
    if (c == '~')
        return 3;
    else if (c == '|' || c == '^')
        return 2;
    else if (c == '>' || c == '-')
        return 1;
    else
        return -1;
}
string change_to_postfix (string &input ) {
    string postfix;
    stack<char> st ;

    for (int i = 0; i < input.size(); ++i) {
        char c=input[i];
        if (isalpha(c)) {
            postfix += c;
        }else if (c=='(') st.push (c);
        else if (c==')') {
            while (st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            st.pop();
        }else {
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
void clean(string &s) {
    string nw;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'v') nw += '|';
        else if (s[i] == '<') {
            nw += '-';
            i++;
        }else {
            nw += s[i];
        }
    }
    s = nw;
}
bool calc(string s , map <char,bool> in ){
    stack <bool> operands ;
    for(int i = 0;i<s.size();i++){
        if (s[i]=='~'){
            operands.top() = !operands.top();
        }else if (!isalpha(s[i])){
            bool x=operands.top();
            operands.pop();
            bool y = operands.top();
            operands.pop();
            operands.push(func(s[i],y,x));
        }else
        operands.push(in[s[i]]);
    }

    return operands.top();

}
 */