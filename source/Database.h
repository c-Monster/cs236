//
//  Database.h
//  
//
//  Created by Clark Richard Green on 7/20/16.
//
//

#ifndef Database_h
#define Database_h

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "Relation.h"
#include "Predicate.h"
#include "Rule.h"
#include "Graph.h"

using namespace std;

class Database {
    /** stores the output to be printed later
     */
    string results;
    /** stores the relations
     */
    map<string, Relation> database;
    /** stores the variables in the query and keeps their occurences in a vector of ints
     */
    map<string, vector<int>> variables;
    /** maps the Rules to be evaluated to the IDs
     */
    map<int, Rule> graphID;
    /** map of postorder numbers to Node IDs
     */
    map<int, int> postOrderID;
    /** stores a dependency graph represented as an adjacency list
     */
    Graph dependencyGraph;
    /** stores a reverse dependency Graph
     */
    Graph reverseGraph;
    
public:
    /** allows the user to add relations to the map
     */
    void addRelation(Relation& r){
        database.insert(pair<string, Relation>(r.getName(),r));
    }
    /** allows the client to add a Tuple to a relation in database
     */
    void editRelation(Tuple& t, string& ID){
        database[ID].addTuple(t);
    }
    /** evaluates the query using facts
        @param ID the name of the query to be evaluated
     */
    Relation evaluateQuery(Predicate& query);
    /** finds the tuples that make a given predicate true
        @ a relation containing the solutions
     */
    string printRelations();
    /** @return a vector of int containing positions of the parameters that need to be projected and possibly renamed
     */
    vector<int> toProject(const vector<string>& parameters);
    /**
     */
    vector<int> toProj(const Scheme& a, const Scheme& b);
    /** allows the client to access the printed results
        @return a string containing the printed results
     */
    string getResults() const {
        return results;
    }
    /** Processes a Rule object
        @param the rule to be evaluated
     */
    Relation evaluateRule(const Rule& rule);
    /** assigns postorder numbers based on the dfsForest algorithm, identifies the strongly connected components, and evaluates the rules in each 
        @param ruleList the rules to be evaluated
        @return the results of each operation printed to a string
     */
    string evaluateRules(const vector<Rule>& ruleList);
    /** @return the number of Tuples in the Database object
     */
    int getSize() const {
        int size = 0;
        for (auto itr : database) size += itr.second.getSize();
        return size;
    }
    /** builds both the dependency graph and the reverse dependency graph
        @param contains the rules to be evaluated
     */
    string buildGraphs(const vector<Rule>& ruleList);
    /**
     */
    string fixedPointAlgorithm(const set<int>& component, const vector<Rule>& ruleList);
};

#endif /* Database_h */
