//
//  token.h
//  Scanner
//
//  Created by Clark Richard Green on 6/23/16.
//  Copyright © 2016 Clark Richard Green. All rights reserved.
//

#ifndef Token_h
#define Token_h

#include <stdio.h>
#include <string>
#include "tokenType.h"

using std::string;

class Token {
public:
    /** constructor of Token objects
     */
    Token(tokenType type, string value,  int line):
    type(type), line(line), value(value) {}
    /** destructor of Token objects
     */
    ~Token(){}
    /** @return the token as a the type, the value, and the line number in parenthesis
     */
    string toString();
    /** @return the token's type
    */
    tokenType getType() const {
        return type;
    }
    /** @return the token's value
     */
    string getValue() const {
     return value;   
    }
private:
    /** stores the name of the token
     */
    tokenType type;
    /** stores the line number of the token
     */
    int line;
    /** stores the literal token as a string
     */
    string value;
    
};

#endif /* token_h */
