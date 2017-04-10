//
//  Database.cpp
//  
//
//  Created by Clark Richard Green on 7/21/16.
//
//

#include <sstream>
#include <iostream>
#include "Database.h"
//#define DEBUG
//#define PROJECT
//#define P

Relation Database::evaluateQuery(Predicate& query){
    variables.clear();
    stringstream hold;
    stringstream output;
    string ID = query.getName();
    Relation relation = database[ID]; //makes a copy of the relation
    vector<string> parameters = query.getStrings(); //allows the function to acces the parameters in the query
    vector<int> positions = toProject(parameters);//holds the positions of the first occurrence of each variable in the query body
    Scheme finalScheme;
    set<string> toRename;
    hold << "\nselect";
    for (unsigned int i = 0; i < parameters.size(); i++) {
        if (parameters[i][0] == '\'') relation.select(i,parameters[i]); //if the parameter is a literal select the literal from the relation
        else {
            variables[parameters[i]].push_back(i);
            if (!toRename.count(parameters[i])) {
                toRename.insert(parameters[i]);
                finalScheme.push_back(parameters[i]);
            }
        }
    }
    for (auto itr : variables) {
        relation.select(itr.second);
    }
    hold << relation.toString();
    Relation projected = relation.project(positions);
    hold << "\nproject" << projected.toString();
    Relation renamed = projected.rename(finalScheme);
    hold << "\nrename" << renamed.toString() << endl;
    if (relation.getSize() > 0) output << endl << query.toString() << "? Yes(" << relation.getSize() << ')' << hold.str();
    else output << endl << query.toString() << "? No\n\n";
    results = output.str();
    return renamed;
}

string Database::printRelations(){
    stringstream output;
    for (auto itr : database){
        output << endl << itr.first;
//        if (itr.second.getSize() == 0) output << endl;
        output << itr.second.toString();
        output << endl;
    }
    return output.str();
}

vector<int> Database::toProject(const vector<string>& parameters){
    vector<int> positions;
    set<string> variables;
    for (unsigned int i = 0; i < parameters.size(); i++){
        if (parameters[i][0] != '\'')//if the parameter is a variable and not in the set, push its index into the vector
            if (!variables.count(parameters[i])){
                positions.push_back(i);
                variables.insert(parameters[i]);
            }
    }
    return positions;
}

vector<int> Database::toProj(const Scheme& a, const Scheme& b){
    vector<int> positions;
    for (unsigned int i = 0; i < a.size(); ++i) {
        for (unsigned int j = 0; j < b.size(); ++j) {
            if (a[i] == b[j]) {
                positions.push_back(j);
            }
        }
    }
    return positions;
}

Relation Database::evaluateRule(const Rule& rule){
    
    
    //data structures
    vector<Relation> intermediateResults;
    vector<Predicate> ruleBody = rule.getPredicates();
    vector<int> toProject;
    vector<string> ruleParameters = rule.getName().getStrings();
    Scheme intermediateScheme, ruleScheme, factScheme;
    Relation intermediate, projected, renamed, unioned;
    string factName = rule.getName().getName();

    
    //create a Scheme object for the rule
    for (string parameter : ruleParameters) ruleScheme.push_back(parameter);
    
    //process input
    
    //select, project, and rename all the predicates in the rule body
    for(Predicate predicate : ruleBody) intermediateResults.push_back(evaluateQuery(predicate));
    
    
    //join intermediate results
    if (intermediateResults.size() > 1) {
        intermediate = intermediateResults[0];
        for (unsigned int i = 1; i < intermediateResults.size(); ++i) intermediate = intermediate.join(intermediate, intermediateResults[i]);
    } else intermediate = intermediateResults[0];
    
    //project intermediate relation
    intermediateScheme = intermediate.getScheme();
    toProject = toProj(ruleScheme, intermediateScheme);
    projected = intermediate.project(toProject);
    
    //rename projected relation
    factScheme = database[factName].getScheme();
    renamed = projected.rename(factScheme);
    
    //add renamed relation to database
    unioned = database[factName].Union(renamed);
    
    //return only the new Tuples
    return unioned;
}

string Database::evaluateRules(const vector<Rule>& ruleList){
    
    //data structures
    stringstream output;
    vector<set<int>> components;
    
    //dfs Forest
    reverseGraph.dfsForest();
    
    //print postOrder numbers
    output << "Postorder Numbers\n";
    output << reverseGraph.getPostOrderNumbers() << endl;
    
    //print depth-first search order and strongly connected components
    output << "SCC Search Order";
    
    //populate map of postorder numbers to node IDs
    reverseGraph.populateIDmap(postOrderID);
    
    //use the map to create strongly connected components
    output << dependencyGraph.scComponents(components, postOrderID) << endl;
    


    //use the fixed-point algorithm to evaluate strongly connected components
    for(set<int> component : components){
        
        //print each component to the output stream
        output << "\nSCC:";
        for (int i : component) output << ' ' << 'R' << i;
        output << endl;
        
        output << fixedPointAlgorithm(component, ruleList);
    
    }
        
    //return output stream
    return output.str();
}

string Database::fixedPointAlgorithm(const set<int>& component, const vector<Rule>& ruleList){
    stringstream output;
    bool change = true;
    Relation relation;
    
    if (component.size() == 1 && !dependencyGraph.getGraph()[*component.begin()].edges.count(*component.begin())){
        relation = evaluateRule(ruleList[*component.begin()]);
        output << ruleList[*component.begin()].toString();
        output << relation.toString() << endl;
    } else {
        
        while (change) {
            
            
            //count the number of tuples in the component
            int size = 0;
            
            for (int i : component) size += database[ruleList[i].getName().getName()].getSize();
            
            //Evaluate all the rules in the component once
            for (int i : component) {
                relation = evaluateRule(ruleList[i]);
                output << ruleList[i].toString();
                output << relation.toString() << endl;
            }
            
            //count the number of tuples in the component again
            int newSize = 0;
            
            for (int i : component) newSize += database[ruleList[i].getName().getName()].getSize();
            
            if (size == newSize) change = false;
            
        }
        
    }
    return output.str();
}

string Database::buildGraphs(const vector<Rule>& ruleList){
    
    //create output stream
    stringstream output;
    
    vector<Predicate> predicateList;
    string predicateName, ruleName;
    
    for (unsigned int i = 0; i < ruleList.size(); i++) {
        
        //add each Rule to both graphs
        dependencyGraph.addNode(i);
        reverseGraph.addNode(i);

        predicateList = ruleList[i].getPredicates();
        
        for (unsigned int j = 0; j < predicateList.size(); j++) {
            
            for (unsigned int k = 0; k < ruleList.size(); k++) {
                
                predicateName = predicateList[j].getName();
                ruleName = ruleList[k].getName().getName();
                
                if (predicateName == ruleName) {
                    
                    // insert edges into both maps
                    dependencyGraph.addEdge(i, k);
                    reverseGraph.addEdge(k, i);
                    
                }
            }
        }
    }
    
    //concatenate output
    output << "Dependency Graph\n" << dependencyGraph.toString() << endl;
    output << "Reverse Graph\n" << reverseGraph.toString() << endl;
    return output.str();
}

