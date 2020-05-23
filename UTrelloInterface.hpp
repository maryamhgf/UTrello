#ifndef __UTrelloInterface_HPP__
#define __UTrelloInterface_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<algorithm>
#include<bits/stdc++.h> 
#include "List.hpp"
#include "User.hpp"
#include "Task.hpp"

class User;
class List;
class Task;

class UTrelloInterface {
public:
	UTrelloInterface();

	void modifyUsersBeforeAddUser();
	void modifyTaskssBeforeAddTask();
	void modifyListsBeforeAddList();

	std::string addUser(std::string username);
	std::string addTask(std::string list, std::string name, unsigned int estimatedTime, unsigned int priority, std::string description);
	std::string editTask(std::string task, unsigned int estimatedTime, unsigned int priority, std::string description);
	
	std::string deleteTask(std::string task);
	
	std::string assignTask(std::string task, std::string user);
	std::string moveTask(std::string task, std::string list);
	std::string completeTask(std::string task);
	std::string printTask(std::string task);

	std::string addList(std::string name);
	
	std::string deleteList(std::string list);
	
	std::string printList(std::string list);

	std::string printUserTasks(std::string user);
	std::string printUserUnfinishedTasks(std::string user);

	int printTotalEstimatedTime();

	int printTotalRemainingTime();

    int printUserWorkload(std::string user);
    int printUserPerformance(std::string user);

	std::string printUsersByWorkload();
	
	std::string printUsersByPerformance();

    std::string printAllLists();
    std::string printUnassignedTasksByPriority();
	std::string printAllUnfinishedTasksByPriority();
private:
	std::vector<List> lists;
	std::vector<Task> tasks;
	std::vector<User> users;
};

#endif