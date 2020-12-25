#include <iostream>

class Disjoint{
    public:
    long *rank, *parent, num;
    Disjoint(long a);
    ~Disjoint();
    void union_set(long a, long b);
    long find(long a);
};

Disjoint::~Disjoint(){
    delete [] rank;
    delete [] parent;
}

Disjoint::Disjoint(long a){
    rank = new long[a];
    parent = new long[a];
    num = a;
    for (long i = 0; i < num; i++){
        parent[i] = i;
    } 
}

long Disjoint::find(long a){
    if (parent[a] != a){
        parent[a] = find(parent[a]);
    }
    return parent[a];
}

void Disjoint::union_set(long a, long b){
    long set_one = find(a);
    long set_two = find(b);
    if (set_one == set_two) return;
    if(rank[set_one] < rank[set_two]){
        parent[set_one] = set_two;      
    }
    else if (rank[set_one] > rank[set_two]){
        parent[set_two] = set_one;
    }
    else {
        parent[set_two] = set_one;
        rank[set_one]++;
    }
}
