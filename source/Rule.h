//
//  Rule.h
//  
//
//  Created by Clark Richard Green on 7/5/16.
//
//

#ifndef Rule_h
#define Rule_h

#include <stdio.h>
#include <string>
#include <vector>
#include "Predicate.h"

using namespace std;

class Rule {
    
private:
    /** contains the predicates in the Rule
     */
    vector<Predicate> predicateList;
    /** contains the head Predicate of the rule
     */
    Predicate name;
    /** allows DatalogProgram to push predicate objects into predicateList
     */
    friend class DatalogProgram;
    
public:
    /** @return the Rule as a string
     */
    string toString() const;
    /** @param the head predicate of the rule
     */
    void setName(Predicate name) {
        this->name = name;
    }
    /** allows the user to access the Rule head
     */
    Predicate getName() const {
        return name;
    }
    /** allows the user to add Prediate objects to predicateList
     */
    void addPredicates(vector<Predicate> p) {
        predicateList.insert(predicateList.end(), p.begin(), p.end());
    }
    /** gives the client access to the Rule body
     */
    vector<Predicate> getPredicates() const {
        return predicateList;
    }
};

#endif /* Rule_h */
