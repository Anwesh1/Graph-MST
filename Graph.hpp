#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "Disjoint.hpp"

class Edge{
    public:
    long source, destination;
    double weight;
    Edge(long src = 0, long dest = 0, double wei = 0){
        source = src;
        destination = dest;
        weight = wei;
    }
};

class Graph{
    public:
    double** adj;
    long num_nodes;
    void create(long use);
    ~Graph();
    void init_empty();
    bool insert(long a, long b, double weight);
    bool del(long a, long b);
    void degree(long a);
    long edge_count();
    void clear();
    void mst();
};

bool lol(Edge lhs, Edge rhs){
    return lhs.weight < rhs.weight;
}

void Graph::mst(){
    std::vector <Edge> use;
    Edge e;
    for (long i = 0; i < num_nodes; i++) { 
        for (long j = 0; j <= i; j++) {
            if (adj[i][j] != -1){
                e = Edge(i,j,adj[i][j]);
                use.push_back(e);
            }
        }
    }
    std::sort (use.begin(), use.end(), lol);
    Disjoint *set = new Disjoint(num_nodes);
    double mst;
    for(long i = 0; i < use.size(); i++){
        if ((set->find(use[i].source) != set->find(use[i].destination))){
            set->union_set(use[i].source, use[i].destination);
            mst += use[i].weight;
        }
    }
    for(long i = 0; i < num_nodes; i++){
        if(set->find(i) != set->find(0)){
            std::cout << "not connected" << std::endl;
            delete set;
            return;        
        }
    }
    std::cout << "mst " << std::fixed << std::setprecision(2) << mst << std::endl;
    mst = 0;
    delete set;
    return;
}

void Graph::create(long use){
    if (use <= 0){
        throw std::invalid_argument("lol");
        return;
    }
    num_nodes = use;
    adj = new double* [num_nodes];
    for (long i = 0; i < num_nodes; i++){
        adj[i] = new double [num_nodes];
    }
    init_empty();
    std::cout << "success" << std::endl;
}

void Graph::init_empty(){
    for (long i = 0; i < num_nodes; i++){
        for (long j = 0; j <num_nodes; j++){
            adj[i][j] = -1;
        }
    }
}

Graph::~Graph(){
    for (long i = 0; i < num_nodes; i++) {
        delete [] adj[i];
    }
    delete [] adj;
}

bool Graph::insert(long a, long b, double weight){
    if (a < 0 || a >= num_nodes || b < 0 || b >= num_nodes || weight <= 0){
        throw std::invalid_argument("lol");
        return false;
    }
    adj[a][b] = weight;
    adj[b][a] = weight;
    std::cout << "success" << std::endl;
    return true;
}

bool Graph::del(long a, long b){
    if (a < 0 || a >= num_nodes || b < 0 || b >= num_nodes){
        throw std::invalid_argument("lol");
        return false;
    }
    if (adj[a][b] == -1 && adj[b][a] == -1){
        std::cout << "failure" << std::endl;
        return false;
    }
    adj[a][b] = -1;
    adj[b][a] = -1;
    std::cout << "success" << std::endl;
    return true;
}

void Graph::degree(long a){
    if (a < 0 || a >= num_nodes){
        throw std::invalid_argument("lol");
        return;
    }
    long count = 0;
    for (long i = 0; i < num_nodes; i++){
        if (i == a){
            for (long j = 0; j < num_nodes; j++){
                if (adj[i][j] != -1) {
                    if (i == j){
                        count +=2;
                    }
                    else count++;              
                }
            }
        }
    }
    std::cout << "degree of " << a << " is " << count << std::endl;
}

long Graph::edge_count(){
    long count = 0;
    for (long i = 0; i < num_nodes; i++){
        for (long j = 0; j <= i; j++){
            if (adj[i][j] != -1) count++;
        }
    }
    return (count);
}

void Graph::clear(){
    for (long i = 0; i < num_nodes; i++) { 
        for (long j = 0; j < num_nodes; j++) { 
        adj[i][j] = -1; 
        }     
    }
}