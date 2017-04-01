#include "coordinates.h"
#include <vector>
#include <iostream>

#ifndef NODE_H
#define NODE_H

class node
{
    public:
        node(){}
        node(int name, coordinates coordinates);
        ~node(){}
        bool operator==(const node& other)const;
        int get_id(){return id;}
        coordinates get_position(){return position;}
        std::vector<node*> get_connections(){return connections;}
        void connecting(node * node_ptr){connections.push_back(node_ptr);}
        void print(std::ostream & out);
        int find_distance(const node& other)const;
        int get_connections_size(){return connections.size();}
        std::vector<node*>::iterator get_connections_begin(){return connections.begin();}


    private:
        int id;
        coordinates position;
        std::vector<node*> connections;
};

#endif // NODE_H
