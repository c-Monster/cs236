//
//  Graph.h
//  
//
//  Created by Clark Richard Green on 8/3/16.
//
//

#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Graph {
    
    struct Node {
        /** flags a node that has been visited
         */
        bool visited;
        /** stores the Nodes adjacent to the Node object
         */
        std::set<int> edges;
        /** stores the postorder number
         */
        int postOrderNumber;
        /** Node constructor
         */
        Node() :  visited(false), postOrderNumber(0) {}
        /** delegates to std::map::insert
         */
        void Insert(const int ID){
            edges.insert(ID);
        }
        /** @return the postorderNumber
         */
        int getPostOrderNumber() const {
            return postOrderNumber;
        }
    };
    
    /** in the graph an integer ID maps to a Node object
     */
    std::map<int, Node> graph;
    /** stores the current postorder Number
     */
    int currentPostOrderNumber;
    
public:
    /** allows the client to add a Node to the Graph
        @param ID the integer that represents the Node
        @param Node the Node to be inserted
     */
    void addNode(const int ID){
        Node newNode;
        graph.insert(std::pair<int, Node> (ID, newNode));
    }
    /** allows the client to add an edge to the Graph
        @param ID represents the Node to add an edge to
        @param node represents the Node the directed edge points to
     */
    void addEdge(const int node, const int adjacent){
        graph[node].Insert(adjacent);
    }
    /** @return the graph represented as a string
     */
    string toString();
    /** assigns currentPostOrderNumber 0 and calls the other dfsForest function
     */
    void dfsForest();
    /** assigns postorder traversal numbers to each node in graph
     */
    void dfsForest(const int ID);
    /**
     */
    string scComponents(int ID, set<int>& scc);
    /**
     */
    string scComponents(vector<set<int>>& components, map<int, int>& postID);
    /**
     */
    string getPostOrderNumbers(){
        stringstream output;
        for (auto itr : graph) output << "  R" << itr.first << ": " << itr.second.postOrderNumber << endl;
        return output.str();
    }
    /** maps a postorder number to a Node ID
     */
    void populateIDmap(map<int, int>& m){
        for (auto entry : graph) m[entry.second.getPostOrderNumber()] = entry.first;
    }
    /**
     */
    map<int, Node>& getGraph() {
        return graph;
    }
    /** Graph constructor
     */
    Graph(): currentPostOrderNumber(1) {}
};

#endif /* Graph_h */
