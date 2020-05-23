#include "User.hpp"

using namespace std;

#define NO_TASK_ERROR "There is no task to remove"
#define NOT_FOUND -1

int findUserIndexInVectorOfString(vector<string> vectorOfString, string element) {
	for(int i = 0; i < vectorOfString.size(); i++) {
		if(vectorOfString[i] == element)
			return i;
	}
	return NOT_FOUND;	
}

User::User(string name) {
	setUser(name);
}

void User::setUser(string name) {
	nameOfUser = name;
}

void User::addTask(string taskName) {
	allTasks.push_back(taskName);
}

void User::removeTask(string taskName) {
	if(allTasks.size() == 0) {
		cout<< NO_TASK_ERROR<< endl;
		return;
	}
	int indexOfTask = findUserIndexInVectorOfString(allTasks, taskName);
	if(indexOfTask != NOT_FOUND)
		allTasks.erase(allTasks.begin() + indexOfTask);	
}

string User::getName() { 
	return nameOfUser; 
}

vector<string> User::getTasks() { 
	return allTasks; 
}