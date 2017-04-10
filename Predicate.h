//
//  Predicate.h
//  
//
//  Created by Clark Richard Green on 7/4/16.
//
//

#ifndef Predicate_h
#define Predicate_h

#include <stdio.h>
#include <vector>
#include <string>
#include "Parameter.h"

using namespace std;

class Predicate{
    
public:
    /** Predicate constructor
     */
    Predicate(){}
    /** Predicate destructor
     */
    ~Predicate(){}
    /** prints the Predicate as a string to the outputfile
     */
    string toString() const;
    /** sets the name of the Predicate
     */
    void setName(string name) {
        this->name = name;
    }
    /** allows the client to add Paramter objects to parameterList
     */
    void addParameters(vector<Parameter> p) {
        parameterList.insert(parameterList.end(), p.begin(), p.end());
    }
    /** creates a vector of strings from parameterList
     */
    vector<string> getStrings();
    /** allows the client to access the name
     */
    string getName() const {
        return name;
    }
private:    
    /** a vector that holds the parameters of the predicate
     */
    vector<Parameter> parameterList;
    /** holds the name of the predicate
     */
    string name;
};

#endif /* Predicate_h */
