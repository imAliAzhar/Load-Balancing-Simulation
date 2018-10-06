/*
 * TaskMessage.h
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#ifndef OBJECTS_TASKMESSAGE_TASKMESSAGE_H_
#define OBJECTS_TASKMESSAGE_TASKMESSAGE_H_

#include "../../Objects/Task/Task.h"
#include <omnetpp.h>

using namespace omnetpp;

enum class TaskStatus;

class  TaskMessage : public cMessage
{
  public:
    Task task;
    TaskStatus status;
    double startTime;
    double endTime;
    TaskMessage(const char * name);
    friend bool operator<(const TaskMessage &a, const TaskMessage &b);
    friend bool operator>(const TaskMessage &a, const TaskMessage &b);
};


enum class TaskStatus
{
    INITIATED,
    WAITING,
    ASSIGNED,
    PROCESSING,
    PROCESSED
};

#endif /* OBJECTS_TASKMESSAGE_TASKMESSAGE_H_ */
