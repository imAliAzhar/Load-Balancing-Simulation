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

#ifndef __LOADBALANCER_GENERATOR_H_
#define __LOADBALANCER_GENERATOR_H_

#include <omnetpp.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../Objects/Task/Task.h"
#include "../../Objects/TaskMessage/TaskMessage.h"


using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Generator : public cSimpleModule
{
  private:
    cMessage *timerMessage;
    int tasksCount;
    int counter;
    std::vector<Task> tasks;
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    void readTasks();
    void finish();
};

#endif
