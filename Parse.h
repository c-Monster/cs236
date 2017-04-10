//
//  Parse.h
//  
//
//  Created by Clark Richard Green on 7/6/16.
//
//

#ifndef Parse_h
#define Parse_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

class Parser {
    /** stores the tokens to be parsed
     */
    vector<Token> tokenList;
    /** stores the the number of matches that have been executed
     */
    int itr;
    /** stores a DatalogProgram object for future use
     */
    DatalogProgram hold;
    /** Holds the output in a string before it is printed. If an exception is thrown it is assigned the error message
     */
    string output;
public:
    /** Parser constructor
     */
    Parser(vector<Token> input): tokenList(input), itr(0) {}
    /** Parser deconstructor
     */
    ~Parser(){}
    /** calls the datalogProgram function, then attempts to match the EOF token
     */
    DatalogProgram parse();
    /** @param token the token to be matched
     if the token encountered in the tokenList matches the token, the iterator in the vector advances, otherwise throws a Token exception
     */
    void match(tokenType token);
    /** @return an object of the DatalogProgram to be stored in the hold member.
     */
    DatalogProgram datalogProgram();
    /** @return a vector of Predicates to be stored in a DatalogProgram object
     */
    vector<Predicate> schemeList();
    /** @return a Predicate object to be added to the schemeList member of DatalogProgram
     */
    Predicate scheme();
    /** @return a vector of Predicate objects to be added to the factList member of DatalogProgram
     */
    vector<Predicate> factList();
    /** @return a Predicate object to be stored in the factList member of DatalogProgram
     */
    Predicate fact();
    /** @return a vector of Predicate objects to be added to the queryList member of DatalogProgram
     */
    vector<Predicate> queryList();
    /** @return a Predicate object to be stored in the queryList member of DatalogProgram
     */
    Predicate query();
    /** @return a vector of Rule objects to be stored in the RuleList member of DatalogProgram
     */
    vector<Rule> ruleList();
    /** @return a newly created Rule object
     */
    Rule rule();
    /** @return a vector of Predicate objects to be stored in a Rule object
     */
    vector<Predicate> predicateList();
    /** @return a Predicate object to be stored in a data structure
     */
    Predicate predicate();
    /** @return a vector of Parameter objects to be stored in a Predicate object
     */
    vector<Parameter> parameterList();
    /** @return a newly created Parameter object
     instantiates and sets the name of a Parameter object
     */
    Parameter parameter();
    /** prints the final output of the Parser class
     */
    void printStructures(string fileName);

};

#endif /* Parse_h */
