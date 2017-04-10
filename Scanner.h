//
//  Scanner.h
//  Scanner
//
//  Created by Clark Richard Green on 6/23/16.
//  Copyright © 2016 Clark Richard Green. All rights reserved.
//

#ifndef Scanner_h
#define Scanner_h

#include <stdio.h>
#include <vector>
#include "Token.h"
#include "DatalogProgram.h"

using namespace std;

class Scanner{
    
friend class DatalogProgram;
    
public:
    /** Scanner constructor
     */
    Scanner(): total(0), line (1), error(false) {}
    /** Scanner destructor
     */
    ~Scanner(){}
    /** @param the name of the input file
        @return true only if the file contains no errors
        opens an input filestream and reads each character of the file. Valid tokens are stored in tokenList
     */
    void scan(string fileName);
    /** @param inFile: a reference to the input filestream
        @param last: the last character read from the filestream in the scan function
        continues reading characters from where the scan function left off until a whitespace or non-alphanumeric character is encountered
     */
    void idReader(ifstream& inFile, char last);
    /** @param input a string containing the identifier or keyword
     */
    void stringReader(ifstream& inFile);
    /** prints the type, value, and line number of each token
     */
    void printTokens(string fileName);
    /** @return the vector containing the tokens
     */
    vector<Token> getTokens() const {
        return tokenList;
    }
    
private:
    /** stores the tokens read from the input file
     */
    vector<Token> tokenList;
    /** stores the number of tokens read from the file
     */
    int total;
    /** stores the line number while reading the input file
     */
    int line;
    /** indicates whether an error has occurred
     */
    bool error;
};

#endif /* Scanner_h */
