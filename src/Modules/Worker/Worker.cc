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

#include "Worker.h"

Define_Module(Worker);

void Worker::initialize()
{
    getNodeInfo();
}

void Worker::handleMessage(cMessage *msg)
{
    TaskMessage *taskMessage = check_and_cast<TaskMessage *> (msg);
    cDisplayString& dispStr = getDisplayString();

    if(msg->isSelfMessage())
    {
        taskMessage->status = TaskStatus::PROCESSED;
        taskMessage->endTime = simTime().dbl();
        dispStr.parse("i=old/ball");
        send(taskMessage, "out");
    }
    else
    {
        if(taskMessage->task.ram > node.ram)
            std::cerr << "ABORT! Task ran > Node ram";
        if(taskMessage->task.storage > node.storage)
            std::cerr << "ABORT! Task storage > Node storage";

        double processTime = taskMessage->task.mips /(double) node.mips;
        taskMessage->status = TaskStatus::PROCESSING;
        dispStr.parse("i=old/ball2");
        scheduleAt(simTime()+processTime, taskMessage);
    }
}

void Worker::getNodeInfo()
{
    std::stringstream nameStream(getName());
    std::string tupple;
    std::string m,s,r;

    getline(nameStream, tupple, '<');
    nodeName = tupple;
    getline(nameStream, tupple, '>');
    std::stringstream tuppleStream (tupple);

    getline(tuppleStream, m, ',');
    getline(tuppleStream, s, ',');
    getline(tuppleStream, r, ',');

    node.mips = std::stoi(m);
    node.storage = std::stoi(s);
    node.ram = std::stoi(r);
}
