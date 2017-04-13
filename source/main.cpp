//
//  main.cpp
//  Scanner
//
//  Created by Clark Richard Green on 6/23/16.
//  Copyright © 2016 Clark Richard Green. All rights reserved.
//

#include <iostream>
#include <string>
#include "Scanner.h"
#include "DatalogProgram.h"
#include "Parse.h"
#include "Interpreter.h"

using namespace std;

int main(int argc, char* argv[]) {
    Scanner scanner;
    scanner.scan(argv[1]);
//    scanner.printTokens(argv[2]);
    vector<Token> inputTokens = scanner.getTokens();
    Parser parser(inputTokens);
    DatalogProgram inputDatalogProgram = parser.parse();
//    parser.printStructures(argv[2]);
    Interpreter interpreter(inputDatalogProgram);
    interpreter.interpret();
    interpreter.printResults(argv[2]);
	cout << "Execution complete";
    return 0;
}

