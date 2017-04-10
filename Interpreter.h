//
//  Interpreter.h
//  
//
//  Created by Clark Richard Green on 7/20/16.
//
//

#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include "DatalogProgram.h"
#include "Database.h"

using namespace std;

class Interpreter {
    /** holds a DatalogProgram object to be interpreted
     */
    DatalogProgram input;
    /** stores a Database object
     */
    Database database;
    /** stores the string to be printed to the output file
     */
    string output;
public:
    /** Interpreter constructor
        @param input a valid Datalog Program from the parser stored in a DatalogProgram object
     */
    Interpreter(DatalogProgram& input) : input(input) {}
    /** creates Relation objects and stores them in the Database map
     */
    void createRelations();
    /** adds Tuple objects to relation objects
     */
    void fillRelations();
    /** interprets a Datalog program by creating relation objects
     */
    void interpret();
    /** prints the results of the interpret function
        @param fileName the name of the file to print the results to
     */
    void printResults(string fileName);
};

#endif /* Interpreter_h */
