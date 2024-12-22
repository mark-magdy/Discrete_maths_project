#ifndef PROJECT_MULTEQSSOLUTION_H
#define PROJECT_MULTEQSSOLUTION_H
#include "Equation.h"

class multEqsSolution {
    int numberOfEquations,numberOfVars;
    vector<Equation> eqs;
    vector <char> vars;
    vector<map<char,bool>> varsCombinations;
    Equation conclusion;
    int satsfiable , valid ;

public:
    vector < vector < string >> table ;

    multEqsSolution () ;
    void addNewPremisesEquation(string s );
    void addConclusionEquation(string s );

    void calcAllPosVars ();
    void printTruthTable ();
    void generateTable();

    void solve () ;

    bool getSatsfiable ();
    bool getValid();

    void printTable();
};


#endif //PROJECT_MULTEQSSOLUTION_H
