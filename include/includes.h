#pragma once
#include <string>

/*
*******
*/
#define createImage system("dot -Tpng mygraph.dot -o mygraph.png");

void createShortestPath(int id1,int id2) //overwrite graph.dot
{
 /*******************************************************/
 createImage;
}

void mutualConnectionGraph(int id1,int id2) //overwrite graph.dot
{
 /*******************************************************/
 createImage;
}

void createGraph(int id1) //overwrite graph.dot //for 2 traversals(starting from id1)
{
 /*******************************************************/
 createImage;
}

std::string generateStatistics(int id1)
{
    /*******************************************************/
    return "Degree: 26 Clustering: 0.430769 Influence: 99";
}