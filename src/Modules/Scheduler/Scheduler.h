//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __LOADBALANCER_SCHEDULER_H_
#define __LOADBALANCER_SCHEDULER_H_

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include <algorithm>
#include<vector>
#include <omnetpp.h>

#include"../../Objects/Node/Node.h"
#include "../../Objects/TaskMessage/TaskMessage.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Scheduler : public cSimpleModule
{
  private:
    cMessage *timerMessage;
    std::vector<Node> nodes;
//    std::vector<cModule*> nodePtrs;
    std::vector<TaskMessage*> queue;
    bool* nodeFree;
    int numNodes;
    int counter;
    double sumTaskTime;
    int totalTasks;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void readNodes();
    void initiateWorkers();
    void schedule();
    void finish();
};

#endif
