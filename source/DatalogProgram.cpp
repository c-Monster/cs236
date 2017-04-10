//
//  DatalogProgram.cpp
//  
//
//  Created by Clark Richard Green on 7/1/16.
//
//

#include <vector>
#include <string>
#include <sstream>
#include "DatalogProgram.h"
#include "Token.h"

string DatalogProgram::toString() const {
    stringstream ss;
    ss << "Schemes(" << schemeList.size() << "):\n";
    for (int i = 0; i < schemeList.size(); i++) {
        ss << "  " << schemeList[i].toString() << endl;
    }
    ss << "Facts(" << factList.size() << "):\n";
    for (int i = 0; i < factList.size(); i++) {
        ss << "  " << factList[i].toString() << endl;
    }
    ss << "Rules(" << ruleList.size() << "):\n";
    for (int i = 0; i < ruleList.size(); i++) {
        ss << "  " << ruleList[i].toString() << endl;
    }
    ss << "Queries(" << queryList.size() << "):\n";
    for (int i = 0; i < queryList.size(); i++) {
        ss << "  " << queryList[i].toString() << endl;
    }
    ss << "Domain(" << domain.size() << "):\n";
    for (string s : domain){
        ss << "  " << s << endl;
    }
    return ss.str();
}

void DatalogProgram::addDomain(string s){
    domain.insert(s);
}
