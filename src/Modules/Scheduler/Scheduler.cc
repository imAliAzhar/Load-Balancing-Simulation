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

#include "Scheduler.h"

Define_Module(Scheduler);

void Scheduler::initialize()
{
    readNodes();
    initiateWorkers();
    nodeFree = new bool[numNodes];
    for(int i=0; i<numNodes; i++)
        nodeFree[i] = true;
    counter = 0;
    sumTaskTime = 0;
    totalTasks = 0;
}

void Scheduler::finish()
{
    delete [] nodeFree;
    nodeFree = NULL;
    nodes.clear();
    queue.clear();

    std::cout << "Total tasks:\t" << totalTasks << endl;
    std::cout << "Total time:\t" << sumTaskTime << endl;
    std::cout << "Average time:\t" << sumTaskTime/totalTasks << endl << endl;
}


void Scheduler::schedule()
{
    //////////////////////////////////////////////////////////////////////////////////////
//    std::sort(queue.begin(), queue.end());
    std::sort(queue.rbegin(), queue.rend());

    for(int tID = 0; tID < queue.size(); tID++)
    {
        bool isAssigned = false;
        for(int i = 0; i < numNodes; i++)
        {
           if(nodeFree[i] == true)
           {
               if(queue[tID]->task.ram <= nodes[i].ram && queue[tID]->task.storage <= nodes[i].storage)
               {
                   queue[tID]->status = TaskStatus::ASSIGNED;
                   send(queue[tID], "out", i);
                   std::cout << queue[tID]->task << " assigned to " << nodes[i].module->getName() << endl;

                   nodeFree[i] = false;
                   isAssigned = true;
                   break;
               }
           }
        }

       if(isAssigned == true)
       {
           queue.erase(queue.begin()+tID);
       }
    }
}


void Scheduler::handleMessage(cMessage *msg)
{
    TaskMessage *taskMessage = check_and_cast<TaskMessage *> (msg);

    if(std::strcmp(msg->getArrivalGate()->getName(), "in") == 0)
    {
        totalTasks += 1;
        taskMessage->startTime = simTime().dbl();
        queue.push_back(taskMessage);
    }
    else if(std::strcmp(msg->getArrivalGate()->getName(), "inn") == 0)
    {
        assert(taskMessage->status == TaskStatus::PROCESSED);

        std::string name = msg->getSenderModule()->getName();
        std::stringstream nameStream(name);
        std::string sID;
        int ID;

        getline(nameStream, sID, ' ');
        getline(nameStream, sID, ':');
        ID = std::stoi(sID);

        nodeFree[ID] = true;

        double completionTime = taskMessage->endTime - taskMessage->startTime;
        sumTaskTime += completionTime;

        std::cout << "[X] " << taskMessage->task << " completed in " << std::to_string(completionTime) << endl;
        std::cout << msg->getSenderModule()->getName() << " is free." << endl << endl;

        delete taskMessage;
    }

    schedule();

    cDisplayString& dispStr = getDisplayString();
    std::string queueLength = "t=" + std::to_string(queue.size());
    dispStr.parse(queueLength.c_str());
}

void Scheduler::readNodes()
{
    std::ifstream inputFile ("/home/imaliazhar/projects/Omnet/test/LoadBalancer/src/Data/nodes");
    std::string mips, storage, ram;
    if(inputFile)
    {
        while(inputFile >> mips >> storage >> ram)
        {
            Node node = Node();
            node.mips = std::stoi(mips);
            node.storage = std::stoi(storage);
            node.ram = std::stoi(ram);
            nodes.push_back(node);
        }
    }
    else
        std::cout << "Could not open file.";
    numNodes = nodes.size();

    //////////////////////////////////////////////////////////////////////////
//    std::sort(nodes.begin(), nodes.end());
    std::sort(nodes.rbegin(), nodes.rend());
}

void Scheduler::initiateWorkers()
{
    cModuleType *moduleType = cModuleType::get("loadbalancer.Modules.Worker.Worker");

    addGate("out", cGate::OUTPUT, true);
    addGate("inn", cGate::OUTPUT, true);

    setGateSize("out", numNodes);
    setGateSize("inn", numNodes);

    cModule* parentmod = getParentModule();

    for(int i = 0; i < numNodes; i++)
    {
        std::string workerID = "W# " + std::to_string(i) + ": " +
                "<" + std::to_string(nodes[i].mips) + "," + std::to_string(nodes[i].storage) + "," + std::to_string(nodes[i].ram) + ">";

        nodes[i].module = moduleType->create(workerID.c_str(), parentmod);

        gate("out",i)->connectTo(nodes[i].module->gate("in"));
        nodes[i].module->gate("out")->connectTo(gate("inn", i));

        nodes[i].module->finalizeParameters();
        nodes[i].module->buildInside();
        nodes[i].module->scheduleStart(simTime());
    }
}
