/*
 * TaskMessage.cc
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#include "TaskMessage.h"

using namespace omnetpp;

TaskMessage::TaskMessage(const char * name) : cMessage(name) { }

bool operator<(const TaskMessage &a, const TaskMessage &b)
{
    return a.task.mips < b.task.mips;
}

bool operator>(const TaskMessage &a, const TaskMessage &b)
{
    return a.task.mips > b.task.mips;
}
