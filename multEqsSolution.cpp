#include "multEqsSolution.h"

void multEqsSolution::addNewPremisesEquation( string s) {
    numberOfEquations ++ ;
    Equation eq (s );
    eqs.push_back(eq);
    auto ret = eq.getVariables() ;
    bool isAdded = false ;
    for (auto &i : ret ) {
        if (!binary_search(vars.begin(), vars.end(),i)){
            vars.push_back(i) ;
            isAdded = true;
        }
        if (isAdded) {
            sort(vars.begin(), vars.end());
            isAdded= false ;
        }

    }
}

void multEqsSolution::addConclusionEquation(string s) {
    conclusion = Equation (s) ;
    auto ret = conclusion.getVariables() ;
    for (auto &i : ret ) {
        if (!binary_search(vars.begin(), vars.end(),i)){
            valid = false ;
        }
    }
}

void multEqsSolution::generateTable() {
    table = vector < vector < string >> ( (1<<numberOfVars) +1 , vector < string > (numberOfVars+numberOfEquations+1) ) ;
    for (int i = 0; i < vars.size(); ++i) {
        table[0][i] = vars[i];
    }
    for (int i = 0; i < numberOfEquations; ++i) {
        table[0][numberOfVars+i] = "     " + eqs[i].getEquation() + "     ";
    }
    table[0][numberOfVars+numberOfEquations] = conclusion.getEquation()+" (conclusion)";

    for (int row = 1; row <= varsCombinations.size(); ++row) {

        for (int col = 0; col < numberOfVars; ++col) {
            table[row][col] = (varsCombinations[row-1][vars[col]]==1?"True":"F");
        }
        for (int col = numberOfVars; col < numberOfVars+numberOfEquations; ++col) {
            table[row][col] = (eqs[col-numberOfVars].calc(varsCombinations[row-1])==1?"True" : "F");
        }
        table[row][numberOfVars+numberOfEquations] = (conclusion.calc(varsCombinations[row-1])==1?"True" : "F");

    }
}


void multEqsSolution::printTruthTable() {
    for (auto &i: vars) cout << i <<" " ;cout << endl ;
    calcAllPosVars();
    for (auto &mp :varsCombinations ){
        print(mp);
        cout << " : ";
        for ( auto &j: eqs) cout<< j.calc(mp)<<" ";
        cout << conclusion.calc(mp) <<" ";
        cout<< endl ;
    }
}
void multEqsSolution:: printTable() {
    generateTable();
    if (table.empty()) return;
    vector<int> columnWidths;
    int columns = 0;

    for ( auto& row : table) {
        columns = max(columns,(int)row.size() );
    }
    columnWidths.resize(columns, 0);
    for ( auto& row : table) {
        for (int i = 0; i < row.size(); ++i) {
            columnWidths[i] = max( (int) columnWidths[i], (int) row[i].size());
        }
    }
    auto printDivider = [&]() {
        cout << "+";
        for (size_t width : columnWidths) {
            cout << string(width + 2, '-') << "+";
        }
        cout << "\n";
    };
    printDivider();
    for (const auto& row : table) {
        cout << "|";
        for (int i = 0; i < columns; ++i) {
            string cell = (i < row.size()) ? row[i] : "";
            int padding = columnWidths[i] - cell.size();
            int leftPadding = padding / 2;
            int rightPadding = padding - leftPadding;
            cout << " " << string(leftPadding, ' ') << cell <<string(rightPadding, ' ') << " |";
        }
        cout << "\n";
        printDivider();
    }
}
multEqsSolution::multEqsSolution(){
    numberOfEquations=0;
    satsfiable = false ;
    valid= -1;
}

void multEqsSolution::calcAllPosVars() {
    varsCombinations.clear();
    numberOfVars = vars.size();
    for (int i = (1<<numberOfVars)-1; i >=0 ; --i) {
        map<char, bool> mp ;
        int tmp = i , shft = 0 ;
        for (auto &j: vars){
            mp[j]= (tmp>>shft++)%2;
        }
        varsCombinations.push_back(mp);
    }
}

bool multEqsSolution::getSatsfiable() {
    return satsfiable;
}

bool multEqsSolution::getValid() {
    return valid ;
}

void multEqsSolution::solve() {
    calcAllPosVars();
    for (auto &mp :varsCombinations ){
        bool allTrue = eqs[0].calc(mp);
        for ( auto &j: eqs) {
            allTrue &= j.calc(mp);
        }
        if (allTrue) {
             if (valid==1) valid &= conclusion.calc(mp)&allTrue ;
             else if ( valid ==-1) valid = conclusion.calc(mp)&allTrue ;
            satsfiable |=   conclusion.calc(mp)&allTrue ;
        }
    }
}



