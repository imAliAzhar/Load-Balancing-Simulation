/*
 * Task.h
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#ifndef OBJECTS_TASK_TASK_H_
#define OBJECTS_TASK_TASK_H_

#include<string>
#include<ostream>


class Task
{
    public:
    int mips, storage, ram;
    friend std::ostream& operator<<(std::ostream& os, const Task& task);
};


#endif /* OBJECTS_TASK_TASK_H_ */
