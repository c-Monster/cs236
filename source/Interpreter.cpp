//
//  Interpreter.cpp
//  
//
//  Created by Clark Richard Green on 7/20/16.
//
//

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Interpreter.h"
#include "Predicate.h"
#include "Scheme.h"
#include "Tuple.h"
//#define RULES

using namespace std;

void Interpreter::createRelations(){
    for (Predicate scheme : input.getSchemes()) {
        Scheme s;
        for (string str : scheme.getStrings()) s.push_back(str);
        string n = scheme.getName();
        Relation temp(n,s);
        database.addRelation(temp);
    }
}

void Interpreter::fillRelations(){
    for (Predicate fact : input.getFacts()) {
        string n = fact.getName();
        Tuple t;
        for (string str : fact.getStrings()) t.push_back(str);
        database.editRelation(t, n);
    }
}

void Interpreter::interpret(){
    vector<Rule> ruleList = input.getRules();
    Relation relation;
    stringstream ss;
    ss << "Scheme Evaluation\n\nFact Evaluation\n";
    createRelations();
    fillRelations();
    ss << database.printRelations();
    ss << "\nRule Evaluation\n\n";
    
    
    //build dependency graph and reverse graph
    ss << database.buildGraphs(ruleList);
    
    //run dfsForest and create SCCs
    ss << database.evaluateRules(ruleList);
    
    //lab 4 code
    /**
    bool change = true;
    int size = 0;
    int itr = 0;

    
    while (change) {
        //count the number of tuples in the database
        size = database.getSize();
        
        //Evaluate all the rules once
        for (Rule rule : ruleList) {
            relation = database.evaluateRule(rule);
            ss << rule.toString() << endl;
            ss << relation.toString();
        }
        
         //count the number of tuples in the database again
        if ((database.getSize() - size) == 0) change = false;
        
        //keep track of iterations
        itr++;
        
    }
    ss << "\nConverged after " << itr << " passes through the Rules.\n\n";
    */
    
    ss << "\nRule Evaluation Complete\n";

    ss << database.printRelations();

    ss << "\nQuery Evaluation\n";
    for (Predicate query : input.getQueries()){
        database.evaluateQuery(query);
        ss << database.getResults();
    }
    ss << endl;
    output = ss.str();
}

void Interpreter::printResults(string fileName){
    ofstream outFile;
    outFile.open(fileName);
    outFile << output;
    outFile.close();
}