#include "node.h"

node::node(int name, coordinates coordinates )
{
    id=name;
    position=coordinates;
}

bool node::operator==(const node& other)const
{
    if(this->id == other.id)
    {
        return true;
    }
    return false;
}

void node::print(std::ostream& out)
{
    out<<"\nNode ID: "<<id<<std::endl;
    out<<"\n\tPoints to"<<"\tDistance"<<std::endl;
    for(int i=0;i<connections.size();i++)
    {
        out<<"\t"<<connections.at(i)->get_id()<<"\t\t"<<position.find_distance(connections.at(i)->get_position())<<std::endl;
    }
    out<<std::endl;

}

int node::find_distance(const node& other)const
{
    return this->position.find_distance(other.position);
}
