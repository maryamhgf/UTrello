#include "List.hpp"

using namespace std;

int findIndexInVectorOfString(vector<string> vectorOfString, string element) {
	for(int i = 0; i < vectorOfString.size(); i++) {
		if(vectorOfString[i] == element)
			return i;
	}
	return -1;	
}

List::List(string name) {
	setList(name);
}

void List::setList(string name) {
	nameOfList = name;
}

void List::addTaskToList(string taskName) {
	tasksInList.push_back(taskName);
}

void List::removeTaskInList(string taskName) {
	int indexOfTask = findIndexInVectorOfString(tasksInList, taskName);
	if(tasksInList.size() == 0) {
		cout<< "There is no task to remove"<< endl;
		return;
	}
	if(indexOfTask != -1)
		tasksInList.erase(tasksInList.begin()+indexOfTask);
}

string List::getListName() { 
	return nameOfList; 
}

vector<string> List::getTasksInList() { 
	return tasksInList; 
}