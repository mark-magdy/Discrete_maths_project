#include <bits/stdc++.h>
#include "Equation.h"
#include "multEqsSolution.h"
using namespace std ;
using ll= long long ;




int main () {
    int no_eq; string eq ;
    cout << "specify the number of premises equations: \n";
    cin >> no_eq;
    multEqsSolution task  ;
    for (int i = 0; i < no_eq; ++i) {
         cin >> eq ;
        task.addNewPremisesEquation(eq);
    }
    cout <<"add your conclusion" <<endl ;
    cin >> eq ;
    task.addConclusionEquation(eq);
    task.solve() ;
    cout <<"Here is your Truth Table : " << endl ;
    task.printTable();

    if (task.getSatsfiable()) {
        cout <<"your equations are satsfiable"  <<endl ;
    }else {
        cout <<"OOPS! your equations are not satsfiable"  <<endl ;
    }
    if (task.getValid()) {
        cout <<"HORRAI! yes it is valid :) "  <<endl ;
    }else {
        cout <<"OOPS! your equations are not valid "  <<endl ;
    }
}



/*
int main() {
    int no_eq;
    cout << "specify the number of equations: \n";
    cin >> no_eq ;
    vector<string>inputs_str(no_eq);
    vector<Equation> eqs(no_eq);
    vector <char> vars;
    set <char> vars_set;
    cout << "enter no of equations: \n";
    for ( auto &i: inputs_str) cin >> i ;
    for (int i = 0; i < no_eq ; i++ ) {
        Equation tmp(inputs_str[i]);
        eqs[i]=tmp;
        auto ret= tmp.getVariables();
        for(auto &j:ret ) vars_set.insert(j);
    }
    for ( auto &i:vars_set) vars.push_back(i);
    for (auto &i: vars) cout << i <<" " ;
    cout << endl ;
    for (int i = 0; i < (1<<vars.size()); ++i) {
        map<char, bool> mp ;
        int tmp = i , shft = 0 ;
        for (auto &j: vars){
            mp[j]= (tmp>>shft++)%2;
        }
        print(mp)
        cout << " : ";
        for ( auto &j: eqs) cout<< j.calc(mp)<<" ";
        cout<< endl ;
    }
    return 0;
}
*/



//class Equation {
//private:
//    string input ,postfix;
//    int no_of_operands;
//    set <char> operands ;
//    bool func(char c , bool a, bool b) {
//        if (c=='^')return a&b;
//        if (c=='|')return a|b;
//        if (c=='>') return (!a)|b;
//        if (c=='-') return (!a|b)&(a|!b);
//    }
//    ll get_number_of_operands (string s ){
//        for ( auto &i: s) if (isalpha(i)) operands.insert(i);
//        return operands.size();
//    }
//    int prec(char c) {
//        if (c == '~')
//            return 3;
//        else if (c == '|' || c == '^')
//            return 2;
//        else if (c == '>' || c == '-')
//            return 1;
//        else
//            return -1;
//    }
//    string change_to_postfix (string &input ) {
//        string postfix;
//        stack<char> st ;
//
//        for (int i = 0; i < input.size(); ++i) {
//            char c=input[i];
//            if (isalpha(c)) {
//                postfix += c;
//            }else if (c=='(') st.push (c);
//            else if (c==')') {
//                while (st.top() != '(') {
//                    postfix += st.top();
//                    st.pop();
//                }
//                st.pop();
//            }else {
//                while (!st.empty() && prec(c) < prec(st.top()) ||
//                       !st.empty() && prec(c) == prec(st.top())) {
//                    postfix += st.top();
//                    st.pop();
//                }
//                st.push(c);
//            }
//        }
//        while (!st.empty()) {
//            postfix += st.top();
//            st.pop();
//        }
//        return postfix;
//    }
//    void clean(string &s) {
//        string nw;
//        for (int i = 0; i < s.size(); ++i) {
//            if (s[i] == 'v') nw += '|';
//            else if (s[i] == '<') {
//                nw += '-';
//                i++;
//            }else {
//                nw += s[i];
//            }
//        }
//        s = nw;
//    }
//public:
//    Equation(){};
//    Equation(string in){
//        this->input=in;
//        clean(input);
//        postfix = change_to_postfix(input) ;
//        no_of_operands = get_number_of_operands(input);
//    }
//    bool calc(map <char,bool> in ){
//        stack <bool> operands ;
//        for(int i = 0;i<postfix.size();i++){
//            if (postfix[i]=='~'){
//                operands.top() = !operands.top();
//            }else if (!isalpha(postfix[i])){
//                bool x=operands.top();
//                operands.pop();
//                bool y = operands.top();
//                operands.pop();
//                operands.push(func(postfix[i],y,x));
//            }else
//                operands.push(in[postfix[i]]);
//        }
//        return operands.top();
//    }
//    vector<char> get_variables(){
//        vector<char> ret(no_of_operands) ; int j = 0 ;
//        for ( auto &i:operands )ret[j++]=i;
//        return ret;
//    }
//
//    int getNoOfOperands() const {
//        return no_of_operands;
//    }
//};