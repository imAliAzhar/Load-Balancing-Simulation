/*
 * Node.h
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#ifndef OBJECTS_NODE_NODE_H_
#define OBJECTS_NODE_NODE_H_

#include<string>
#include<ostream>
#include<omnetpp.h>

using namespace omnetpp;


class Node
{
    public:
    int mips, storage, ram;
    cModule* module;
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
    friend bool operator<(const Node &a, const Node &b);
    friend bool operator>(const Node &a, const Node &b);
};



#endif /* OBJECTS_NODE_NODE_H_ */
