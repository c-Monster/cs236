//
//  Parameter.h
//  
//
//  Created by Clark Richard Green on 7/5/16.
//
//

#ifndef Parameter_h
#define Parameter_h

#include <stdio.h>
#include <string>

using namespace std;

class Parameter {
    /** the name of the Parameter
     */
    string name;
    
public:
    /** @return the name of the Parameter
     */
    string getName() const {
        return name;
    }
    /** @param the name of the Parameter
     */
    void setName(string name) {
        this->name = name;
    }
};

#endif /* Parameter_h */
