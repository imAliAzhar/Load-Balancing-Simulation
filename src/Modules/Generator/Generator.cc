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

#include "Generator.h"

Define_Module(Generator);

void Generator::initialize()
{
    readTasks();
    counter = 0;
    tasksCount = tasks.size();
    timerMessage = new cMessage("timer");
    scheduleAt(simTime()+0.1, timerMessage);
}

void Generator::finish()
{
//    delete timerMessage;
    tasks.clear();
}

void Generator::handleMessage(cMessage *msg)
{
    std::string display = ": <" + std::to_string(tasks[counter].mips) + ","
            + std::to_string(tasks[counter].storage) + "," + std::to_string(tasks[counter].ram) + ">";
    std::string taskID = "T# " + std::to_string(counter) + display;
    TaskMessage *taskMessage = new TaskMessage(taskID.c_str());
    taskMessage->task = tasks[counter];
    taskMessage->status = TaskStatus::INITIATED;
    send(taskMessage, "out");

    counter++;

    if(counter < tasksCount )
            scheduleAt(simTime()+ 1.0, timerMessage);
}

void Generator::readTasks()
{
    std::ifstream inputFile ("/home/imaliazhar/projects/Omnet/test/LoadBalancer/src/Data/tasks");

    if(!inputFile)
        std::cerr << "Error: " << strerror(errno);

    while(inputFile.good())
    {
        std::string line;
        getline(inputFile, line, '\n');
        std::stringstream lineStream(line);
        std::string tupple;
        while(lineStream.good())
        {
            std::string m,s,r;
            getline(lineStream, tupple, ' ');
            tupple = tupple.substr(1, tupple.size() - 2);
            std::stringstream tuppleStream(tupple);
            Task task = Task();
            getline(tuppleStream, m, ',');
            getline(tuppleStream, s, ',');
            getline(tuppleStream, r, ',');
            task.mips = std::stoi(m);
            task.storage = std::stoi(s);
            task.ram = std::stoi(r);
            tasks.push_back(task);
        }
    }
}

