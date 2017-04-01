#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <list>
#include <queue>
#include "coordinates.h"
#include "node.h"
#include "data.h"

using namespace std;

int main()
{
    default_random_engine random_engine(time(NULL));
    uniform_int_distribution<int> connectivity_dist(0,6);
    int * userNodes = new int;

    cout<<"******************************"<<endl;
    cout<<"-------  WELCOME!!!  ---------"<<endl;
    cout<<"******************************"<<endl;
    cout<<"\n------------------------------"<<endl;
    cout<<"This is a Djikstra Mesh Solver"<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"\nAll output will be generated to"<<endl;
    cout<<"text files as well as to the   "<<endl;
    cout<<"screen.                        "<<endl;
    cout<<"\nPlease enter the number of"<<endl;
    cout<<"nodes to generate: ";
    cin>>*(userNodes);
    cout<<"Thank you"<<endl;

    if (*(userNodes) < 5 )
    {
        *(userNodes)=5;
    }

    uniform_int_distribution<int> id_dist(1, *(userNodes)+2);
    uniform_int_distribution<int> coordinate_dist(-(*(userNodes)+100),*(userNodes)+100);

    list<node> djikstras_nodes;
    list<node>::iterator djikstras_nodes_itr;

    for(int i=0;i<(*userNodes);i++)
    {
        coordinates * coordinates_ptr = new coordinates;
        coordinates_ptr->setX(coordinate_dist(random_engine));
        coordinates_ptr->setY(coordinate_dist(random_engine));

        node * node_ptr = new node(i+1,*coordinates_ptr);
        djikstras_nodes.push_back(*node_ptr);
        delete coordinates_ptr;
    }
    delete userNodes;

    djikstras_nodes_itr=djikstras_nodes.begin();
    while(djikstras_nodes_itr!=djikstras_nodes.end())
    {
        for(int i=0;i<connectivity_dist(random_engine);i++)
        {
            int neighbor=id_dist(random_engine);
            while(neighbor==djikstras_nodes_itr->get_id())
            {
                neighbor=id_dist(random_engine);
            }
            list<node>::iterator connection_itr=djikstras_nodes.begin();
            while(connection_itr!=djikstras_nodes.end())
            {
                if(neighbor==connection_itr->get_id())
                {
                    djikstras_nodes_itr->connecting(&*(connection_itr));
                }
                connection_itr++;
            }
        }
        djikstras_nodes_itr++;
    }

    fstream djikstras_node_list;
    djikstras_node_list.open("djikstras_nodes.txt", ios::out);

    fstream djikstras_solution;
    djikstras_solution.open("djikstras_solution.txt", ios::out);

    djikstras_node_list<<"------------------------------"<<endl;
    djikstras_node_list<<"List of Djikstra Nodes by ID"<<endl;
    djikstras_node_list<<"------------------------------"<<endl;
    cout<<"\n------------------------------"<<endl;
    cout<<"List of Djikstra Nodes by ID"<<endl;
    cout<<"------------------------------"<<endl;
    djikstras_nodes_itr=djikstras_nodes.begin();
    while(djikstras_nodes_itr!=djikstras_nodes.end())
    {
        djikstras_nodes_itr->print(cout);
        djikstras_nodes_itr->print(djikstras_node_list);
        djikstras_nodes_itr++;
    }
    djikstras_node_list.close();

    int * points = new int[2];

    cout<<"\n------------------------------"<<endl;
    cout<<"    Find Djikstra Solution    "<<endl;
    cout<<"------------------------------"<<endl;
    cout<<"\nPlease Enter Start and End Point IDs"<<endl;
    cout<<"Starting Point ID: ";
    cin>>points[0];
    cout<<"Ending Point ID: ";
    cin>>points[1];
    cout<<"Thank You"<<endl;

    if(points[0] > djikstras_nodes.size() || points[1] > djikstras_nodes.size())
    {
        delete [] points;
        cout<<"\nAn Invalid Node Id was Entered"<<endl;
        cout<<"Program is exiting..."<<endl;
        return 1;
    }






    list<data> solution_path;
    list<data>::iterator solution_path_itr;
    priority_queue<data> solution_queue;
    data temp_data;

    djikstras_nodes_itr=djikstras_nodes.begin();
    while(djikstras_nodes_itr!=djikstras_nodes.end())
    {
        if(points[0]==djikstras_nodes_itr->get_id())
        {
            temp_data.set_distance(0);
            temp_data.set_id(djikstras_nodes_itr->get_id());
        }
        djikstras_nodes_itr++;
    }

    solution_path.push_back(temp_data);

    djikstras_nodes_itr=djikstras_nodes.begin();
    while(djikstras_nodes_itr->get_id()!=solution_path.front().get_id())
    {
        djikstras_nodes_itr++;
    }

    vector<node*>::iterator node_itr=djikstras_nodes_itr->get_connections_begin();
    for(int i=0;i < djikstras_nodes_itr->get_connections_size();i++)
    {
        temp_data.set_distance((*node_itr)->find_distance(*djikstras_nodes_itr));
        temp_data.set_id((*node_itr)->get_id());
        solution_queue.push(temp_data);
        node_itr++;
    }

    int target_id=points[1];
    bool found_target_id=false;

    while(!solution_queue.empty())
    {
        found_target_id=false;
        solution_path_itr=solution_path.begin();

        while(solution_path_itr!=solution_path.end())
        {
            if(target_id==solution_path_itr->get_id())
            {
                found_target_id=true;
                solution_queue.pop();
            }
            solution_path_itr++;
        }

        if(found_target_id==false)
        {
            temp_data=solution_queue.top();
            solution_path.push_back(temp_data);
            solution_queue.pop();

            djikstras_nodes_itr=djikstras_nodes.begin();
            while(djikstras_nodes_itr!=djikstras_nodes.end())
            {
                if(djikstras_nodes_itr->get_id()==temp_data.get_id())
                {
                    found_target_id=true;
                    break;
                }
                djikstras_nodes_itr++;
            }

            if(found_target_id==true)
            {
                node_itr=djikstras_nodes_itr->get_connections_begin();
                for(int i=0;i < djikstras_nodes_itr->get_connections_size();i++)
                {
                    temp_data.set_distance((*node_itr)->find_distance(*djikstras_nodes_itr));
                    temp_data.set_id((*node_itr)->get_id());
                    solution_queue.push(temp_data);
                    node_itr++;
                }
            }
        }
    }

    delete [] points;

    djikstras_solution<<"------------------------------"<<endl;
    djikstras_solution<<"        Solution Nodes        "<<endl;
    djikstras_solution<<"------------------------------"<<endl;
    cout<<"\n------------------------------"<<endl;
    cout<<"        Solution Nodes        "<<endl;
    cout<<"------------------------------"<<endl;

    if(found_target_id==false)
    {
        cout<<"\nNo Solution from Starting Point to End Point"<<endl;
        cout<<endl;
        djikstras_solution<<"\nNo Solution from Starting Point to End Point"<<endl;
        djikstras_solution<<endl;
    }
    if(found_target_id==true)
    {
        cout<<"\nNode"<<"\tDistance"<<endl;
        djikstras_solution<<"\nNode"<<"\tDistance"<<endl;

        solution_path_itr=solution_path.begin();
        while(solution_path_itr!=solution_path.end())
        {
            solution_path_itr->print(cout);
            solution_path_itr->print(djikstras_solution);
            solution_path_itr++;
        }
    }

    djikstras_solution.close();

    return 0;
}
