//
//  Scheme.h
//  
//
//  Created by Clark Richard Green on 7/20/16.
//
//

#ifndef Scheme_h
#define Scheme_h

#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>

class Scheme : public std::vector<std::string> {
public:
    int find(const std::string& s) const {
        auto itr = std::find(begin(), end(), s);
        if (itr == end()) return -1;
        else return itr - begin();
    }
};

#endif /* Scheme_h */
