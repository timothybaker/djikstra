#include "data.h"

data::data()
{
    id=0;
    distance=0;
    //ctor
}

data::data(int ID, int D)
{
    id=ID;
    distance=D;
    //ctor
}

data::~data()
{
    //dtor
}

void data::print(std::ostream& out)
{
    out<<id<<"\t"<<distance<<std::endl;

}

bool data::operator<(const data& other)const
{
    if(this->distance < other.distance)
    {
        return true;
    }
    return false;
}
