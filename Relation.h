//
//  Relation.h
//  
//
//  Created by Clark Richard Green on 7/20/16.
//
//

#ifndef Relation_h
#define Relation_h

#include <stdio.h>
#include <string>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

using namespace std;

class Relation {
    /** holds the name of the relation
     */
    string name;
    /** holds the scheme of the relation
     */
    Scheme scheme;
    /** holds the tuples in the relation
     */
    set<Tuple> tuples;
    
public:
    /** default Relation constructor
     */
    Relation(){}
    /** overloaded Relation construcor
     */
    Relation(string& name, Scheme& scheme) : name(name), scheme(scheme) {}
    /** allows the client to add Tuple objects to the set
     */
    void addTuple(Tuple& t){
        tuples.insert(t);
    }
    /** allows the client to access the name member
     */
    string getName() const {
        return name;
    }
    /** allows the client to access the scheme of the relation
     */
    Scheme getScheme() const {
        return scheme;
    }
    /** allows the client to access the tuples in the relation
     */
    set<Tuple> getTuples() const {
        return tuples;
    }
    /** use this one when performing an ordinary select
     */
    void select(int position, string& ID);
    /** use this one when multiple columns must be the same
     */
    void select(const vector<int>& positions);
    /**
     */
    Relation project(const vector<int>& positions);
    /** creates a copy of the Relation object which represents a rename operation 
        @param actual the Scheme to be assigned to the Relation
     */
    Relation rename(const Scheme& actual);
    /** @return the tuples of a relation in a string
     */
    string toString();
    /**@return the number of tuples in the relation
     */
    int getSize() const {
        return tuples.size();
    }
    /** Creates a new Tuple and initializes it with a, then iterates through B. If A does not contain the value at any given index of B, the value of b at the index is appended to the output
        @param a the first Tuple
        @param A the Scheme of the first Tuple
        @param b the second Tuple
        @param B the Scheme of the second Tuple
        @return the newly joined Tuple
     */
    Tuple join(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B);
    /** @param a the first Tuple to be considered
        @param A the Scheme if a
        @param b the second Tuple to be consdiered
        @param B the Scheme of bs
     */
    bool isJoinable(const Tuple& a, const Scheme& A, const Tuple& b, const Scheme& B) const;
    /** generates a Shceme that includes the attributes of both parameters
        @param a a reference to the first Scheme
        @param b a reference to the second Scheme
        @return a Scheme that includes attributes from a and b
     */
    Scheme createScheme(const Scheme& a, const Scheme& b);
    /** @param a a reference to the first relation in the join
        @param b a reference to the second relation in the join
        @return a Relation object that represents the join of a and b
     */
    Relation join(const Relation& a, const Relation& b);
    /** adds the Tuples from the input relation to the Relation that calls the function
        @param the Relation containing the tuples to be added
     */
    Relation Union(const Relation& newTuples);
};

#endif /* Relation_h */
