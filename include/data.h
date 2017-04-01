#include <iostream>

#ifndef DATA_H
#define DATA_H

class data
{
    public:
        data();
        data(int ID, int D);
        ~data();
        int get_id() { return id; }
        void set_id(int val) { id = val; }
        int get_distance() { return distance; }
        void set_distance(int val) { distance = val; }
        void print(std::ostream & out);
        bool operator<(const data& other)const;

    private:
        int id;
        int distance;
};

#endif // DATA_H
