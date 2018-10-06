/*
 * Node.cc
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#include"Node.h"

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    os << "NODE: " << "\tMIPS: " << node.mips << "\tStorage: " << node.storage << "\tRAM: " << node.ram;
    return os;
}

bool operator<(const Node &a, const Node &b)
{
    return a.mips < b.mips;
}

bool operator>(const Node &a, const Node &b)
{
    return a.mips > b.mips;
}
