//
//  DatalogProgram.h
//  
//
//  Created by Clark Richard Green on 7/1/16.
//
//

#ifndef DatalogProgram_h
#define DatalogProgram_h

#include <stdio.h>
#include <vector>
#include <string>
#include <set>
#include "Scanner.h"
#include "tokenType.h"
#include "Rule.h"
#include "Predicate.h"
#include "Parameter.h"

using namespace std;

class DatalogProgram{
    
public:
    /** DatalogProgram constructor
     */
    DatalogProgram(){}
    /** DatalogProgram destructor
     */
    ~DatalogProgram(){}
    /** inserts a Rule object into ruleList
     */
    void addRules(vector<Rule> r) {
        ruleList.insert(ruleList.end(), r.begin(), r.end());
    }
    /** @return ruleList
     */
    vector<Rule> getRules(){
        return ruleList;
    }
    /** inserts a Predicate object into schemeList
     */
    void addSchemes(vector<Predicate> p) {
        schemeList.insert(schemeList.end(), p.begin(), p.end());
    }
    /** @return the schemeList
     */
    vector<Predicate> getSchemes(){
        return schemeList;
    }
    /** inserts a Predicate object into queryList
     */
    void addQueries(vector<Predicate> p) {
        queryList.insert(queryList.end(), p.begin(), p.end());
    }
    /** @return the queryList
     */
    vector<Predicate> getQueries(){
        return queryList;
    }
    /** inserts a Predicate object into factList
     */
    void addFacts(vector<Predicate> p) {
        factList.insert(factList.end(), p.begin(), p.end());
    }
    /** @return the factList
     */
    vector<Predicate> getFacts(){
        return factList;
    }
    /** allows the client to add Parameters to domain
     */
    void addDomain(string s);
    /** prints the structures into a string
    */
    string toString() const;
    
private:
    /** stores the Rule objects created by the Parser class
     */
    vector<Rule> ruleList;
    /** stores the Predicate objects associated with Schemes
     */
    vector<Predicate> schemeList;
    /** stores the Predicate objects associated with Queries
     */
    vector<Predicate> queryList;
    /** stores the Predicate objects associated with Rules
     */
    vector<Predicate> factList;
    /** stores Parameter objects found in Parser::fact
     */
    set<string> domain;
    };

#endif /* DatalogProgram_h */

//would the program be more efficient the parameters were const references?
