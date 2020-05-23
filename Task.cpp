#include "Task.hpp"

using namespace std;

#define UNCOMPLETE "Uncompleted"
#define UNASSIGNED "Unassigned"
#define EMPTY_STRING ""

Task::Task(string listName, string name, unsigned int neededTime, unsigned int priorityOfTask, string descriptionOfTask) {
	nameOfTask = name;
	nameOfList = listName;
	estimatedTime = neededTime;
	priority = priorityOfTask;
	description = descriptionOfTask;
	involvedUser = EMPTY_STRING;
	stateOfTask = UNCOMPLETE;
	stateOfAssigneTask = UNASSIGNED;
}

void Task::setTask(string name, string listName, unsigned int neededTime, unsigned int priorityOfTask, 
		string descriptionOfTask, string owner, string state, string stateOfAssign) {
	nameOfTask = name;
	nameOfList = listName;
	estimatedTime = neededTime;
	priority = priorityOfTask;
	description = descriptionOfTask;
	involvedUser = owner;
	stateOfTask = state;
	stateOfAssigneTask = stateOfAssign;
}

string Task::getTaskName() { 
	return nameOfTask; 
}

string Task::getListName() { 
	return nameOfList; 
}

unsigned int Task::getTime() { 
	return estimatedTime; 
}

unsigned int Task::getPriority() { 
	return priority; 
}

string Task::getDescription() { 
	return description; 
}

string Task::getInvolvedUser() { 
	return involvedUser; 
}

string Task::getStateOfTask() { 
	return stateOfTask; 
}

string Task::getStateOfAssignTask() { 
	return stateOfAssigneTask;
}

void Task::assignTaskToUser(string username) { 
	involvedUser = username; 
}

void Task::editnameOfTask(string newName) { 
	nameOfTask = newName; 
}

void Task::editeNameOfList(string newNameOFList) { 
	nameOfList = newNameOFList; 
}

void Task::editEstimatedTime(unsigned int newEstimatedTime) { 
	estimatedTime = newEstimatedTime; 
}

void Task::editPriority(unsigned int newPriority) { 
	priority = newPriority; 
}

void Task::editDescriotion(string newDescription) { 
	description = newDescription; 
}

void Task::editinvolvedUser(string newOwner) { 
	involvedUser = newOwner; 
}

void Task::editStateOfTask(string newState) { 
	stateOfTask = newState; 
}

void Task::editStateOfAssignTask(string newStateOfAssign) { 
	stateOfAssigneTask = newStateOfAssign; 
}