/*
 * Task.cc
 *
 *  Created on: Oct 2, 2018
 *      Author: imaliazhar
 */

#include "Task.h"

std::ostream& operator<<(std::ostream& os, const Task& task)
{
    os << "TASK: " << "\tMIPS: " << task.mips << "\tStorage: " << task.storage << "\tRAM: " << task.ram;
    return os;
}





