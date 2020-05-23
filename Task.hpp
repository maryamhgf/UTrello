#ifndef __TASK_HPP__
#define __TASK_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<algorithm>
#include<bits/stdc++.h> 

using namespace std;

class Task {
public:
	Task(string listName, string name, unsigned int neededTime, unsigned int priorityOfTask, string descriptionOfTask);
	void setTask(string name, string listName, unsigned int neededTime, unsigned int priorityOfTask, string descriptionOfTask, 
			string owner, string state, string stateOfAssign);
	void editnameOfTask(string newName);
	void editeNameOfList(string newNameOFList);
	void editEstimatedTime(unsigned int newEstimatedTime);
	void editPriority(unsigned int newPriority);
	void editDescriotion(string newDescription);
	void editinvolvedUser(string newOwner);
	void editStateOfTask(string newState); 
	void editStateOfAssignTask(string newStateOfAssign);
	string getTaskName();
	string getListName();
	unsigned int getTime();
	unsigned int getPriority();
	string getDescription();
	string getInvolvedUser();
	string getStateOfTask();
	string getStateOfAssignTask(); 
	void assignTaskToUser(string username);
private:
	string nameOfTask;
	string nameOfList;
	unsigned int estimatedTime;
	unsigned int priority;
	string description;
	string involvedUser;
	string stateOfTask;
	string stateOfAssigneTask;
};

#endif