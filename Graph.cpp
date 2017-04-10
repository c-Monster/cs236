//
//  Graph.cpp
//  
//
//  Created by Clark Richard Green on 8/3/16.
//
//

#include "Graph.h"

string Graph::toString(){
    
    stringstream ss;
    for (auto i : graph){
        ss << "  R" << i.first << ':';
        for (int j : i.second.edges) {
            ss << " R" << j;
        }
        ss << endl;
    }
    return ss.str();
}

void Graph::dfsForest(){
    currentPostOrderNumber = 1;
    for (auto itr : graph)
        if (!itr.second.visited) {
//            cout << "Calling dfsForest on R" << itr.first << endl;
            dfsForest(itr.first);
//            cout << ", assigning postorder number: " << itr.second.postOrderNumber << endl;
        }
}

void Graph::dfsForest(const int ID){
    
    
    //mark the Node as visited
    graph[ID].visited = true;
    
    //for each adjacent Node
    for (int i : graph[ID].edges){
      
        //if the node has not been visited
        if (!graph[i].visited) dfsForest(i);
        
    }
    
    //assign a postorder number (the algorithm is coming out of recursion
    graph[ID].postOrderNumber = currentPostOrderNumber;
    currentPostOrderNumber++;
    
}

string Graph::scComponents(int ID, set<int>& scc){
    
    stringstream output;
    
    output << "  R" << ID << endl;
    
    Node& x = graph[ID];
    
    x.visited = true;
    
    for (int i : x.edges) if (!graph[i].visited) output << scComponents(i, scc);
    
    scc.insert(ID);
    
    return output.str();
}

string Graph::scComponents(vector<set<int>>& components, map<int, int>& postID){
    
    //output stream
    stringstream output;
    
    //begin the searches based on postorder priority
    for (unsigned int i = graph.size(); i > 0; i--){
        
        //represent a component as a set of int
        set<int> component;
        
        //begin at the first rule ID
        int begin = postID[i];
        
        output << endl << "  R" << begin;
        
        //if the rule has not been visited, begin a new search there
        if (!graph[begin].visited) {
            scComponents(begin, component);
            components.push_back(component);
        }
    }
    
    return output.str();
}
