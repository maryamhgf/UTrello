#include "UTrelloInterface.hpp"

using namespace std;

#define UNCOMPLETE "Uncompleted"
#define UNASSIGNED "Unassigned"
#define EMPTY_STRING ""
#define ASSIGNED "Assigned"
#define COMPLETE "Complete"
#define NO_LIST_ERROR "There is no list"
#define USER_EXISTS "User already exists"
#define TASK_EXISTS "Task already exists"
#define LIST_EXISTS "List already exists"
#define LIST_DOES_NOT_EXIST "List does not exist"
#define TASK_DOES_NOT_EXIST "Task does not exist"
#define USER_DOES_NOT_EXIST "User does not exist"
#define SUCCESS "Success"
#define NEXT_LINE "\n"

bool existedTask(vector<Task> tasks, string taskName) {
	for(int i = 0; i < tasks.size(); i++) {
		if(tasks[i].getTaskName() == taskName)
			return 1;
	}	
	return 0;
}

bool existedList(vector<List> lists, string listName) {
	for(int i = 0; i < lists.size(); i++) {
		if(lists[i].getListName() == listName) 
			return 1;
	}	
	return 0;
}

int findIndexOfListName(vector<List> lists, string listName) {
	if(lists.size() == 0)
		perror(NO_LIST_ERROR);
	for(int i = 0; i < lists.size(); i++) {
		if(lists[i].getListName() == listName) 
			return i;
	}	
}

UTrelloInterface::UTrelloInterface() {
	lists.push_back(List(EMPTY_STRING));
	tasks.push_back(Task(EMPTY_STRING, EMPTY_STRING, 0, 0, EMPTY_STRING));
	users.push_back(User(EMPTY_STRING));
}

void UTrelloInterface::modifyUsersBeforeAddUser(){
	if(users.size() == 1 && users[0].getName() == EMPTY_STRING)
		users.pop_back();	
}

bool existedUser(vector<User> users, string username) {
	for(int i = 0; i < users.size(); i++) {
		if(users[i].getName() == username) 
			return 1;
	}
	return 0;
}

string UTrelloInterface::addUser(string username) {
	modifyUsersBeforeAddUser();
	if(existedUser(users, username))
		return USER_EXISTS;
	users.push_back(User(username));
	return "Success";
}

void  UTrelloInterface::modifyTaskssBeforeAddTask(){
	if(tasks.size() == 1 && tasks[0].getTaskName() == EMPTY_STRING && tasks[0].getListName() == EMPTY_STRING && tasks[0].getTime() == 0 &&
		 tasks[0].getPriority()== 0 && tasks[0].getDescription() == EMPTY_STRING)
		tasks.pop_back();
}

string UTrelloInterface::addTask(string list, string name, unsigned int estimatedTime, unsigned int priority, string description) {
	modifyTaskssBeforeAddTask();
	if(existedTask(tasks, name)) 
		return TASK_EXISTS;
	if(!existedList(lists, list))
		return LIST_DOES_NOT_EXIST;
	tasks.push_back(Task(list, name, estimatedTime, priority, description));
	int indexOfListInLists = findIndexOfListName(lists, list);
	lists[indexOfListInLists].addTaskToList(name);
	return SUCCESS;
}

void  UTrelloInterface::modifyListsBeforeAddList() {
	if(lists.size() == 1 && lists[0].getListName() == EMPTY_STRING)
		lists.pop_back();
}

string UTrelloInterface::addList(string name) {
	modifyListsBeforeAddList();
	if(existedList(lists, name))
		return LIST_EXISTS;
	lists.push_back(List(name));
	return SUCCESS;
}

int findIndexOfTaskInTasks(vector<Task> tasks, string taskName) {
	if(tasks.size() == 0)
		perror("There is no task");
	for(int i = 0; i < tasks.size(); i++) {
		if(tasks[i].getTaskName() == taskName)
			return i;
	}
}

string UTrelloInterface::editTask(string task, unsigned int estimatedTime, unsigned int priority, string description) {
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	int indexOfTaskInTasks = findIndexOfTaskInTasks(tasks, task);
	tasks[indexOfTaskInTasks].editEstimatedTime(estimatedTime);
	tasks[indexOfTaskInTasks].editPriority(priority);
	tasks[indexOfTaskInTasks].editDescriotion(description);
	return SUCCESS;
}

int findIndexOfUserInUsers(vector<User> users, string username) {
	if(users.size() == 0)
		perror("There is no user");
	for(int i = 0; i < users.size(); i++) {
		if(users[i].getName() == username)
			return i;
	}	
}

string UTrelloInterface::deleteTask(string task) {
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	int indexOfTaskInTasks = findIndexOfTaskInTasks(tasks, task);
	string listName = tasks[indexOfTaskInTasks].getListName();
	int indexOfList = findIndexOfListName(lists, listName);
	string involvedUser = tasks[indexOfTaskInTasks].getInvolvedUser();
	if(involvedUser != EMPTY_STRING) {
		int indexOfUser = findIndexOfUserInUsers(users, involvedUser);
		users[indexOfUser].removeTask(task);
	}
	tasks.erase(tasks.begin()+indexOfTaskInTasks);
	lists[indexOfList].removeTaskInList(task);
	return SUCCESS;
}

string UTrelloInterface::assignTask(string task, string user) {
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	if(!existedUser(users, user))
		return USER_DOES_NOT_EXIST;
	int indexOfUser = findIndexOfUserInUsers(users, user);
	users[indexOfUser].addTask(task);
	int indexOfTask = findIndexOfTaskInTasks(tasks, task);
	if(tasks[indexOfTask].getStateOfAssignTask() != UNASSIGNED) {
		string oldOwner = tasks[indexOfTask].getInvolvedUser();
		int indexOfOldOwner = findIndexOfUserInUsers(users, oldOwner);
		users[indexOfOldOwner].removeTask(task);
	}
	tasks[indexOfTask].assignTaskToUser(user);
	tasks[indexOfTask].editStateOfAssignTask(ASSIGNED);
	return SUCCESS;
}

string UTrelloInterface::moveTask(string task, string list) {
	if(!existedList(lists, list))
		return LIST_DOES_NOT_EXIST;
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	int indexOfNewListInLists = findIndexOfListName(lists, list);
	lists[indexOfNewListInLists].addTaskToList(task);
	int indexOfTaskInTasks = findIndexOfTaskInTasks(tasks, task);
	int indexOfOldListInLists = findIndexOfListName(lists, tasks[indexOfTaskInTasks].getListName());
	lists[indexOfOldListInLists].removeTaskInList(task);	
	tasks[indexOfTaskInTasks].editeNameOfList(list);
	return SUCCESS;
}

string UTrelloInterface::completeTask(string task){
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	int indexOfTask = findIndexOfTaskInTasks(tasks, task);
	tasks[indexOfTask].editStateOfTask(COMPLETE);
	return SUCCESS;
}

string UTrelloInterface::printTask(string task) {
	string outputString = EMPTY_STRING;
	if(!existedTask(tasks, task))
		return TASK_DOES_NOT_EXIST;
	int indexOfTask = findIndexOfTaskInTasks(tasks, task);
	outputString = outputString + tasks[indexOfTask].getTaskName()  + NEXT_LINE + tasks[indexOfTask].getDescription() + NEXT_LINE;
	outputString = outputString+ "Priority: " + to_string(tasks[indexOfTask].getPriority()) + NEXT_LINE;
	outputString = outputString + "Estimated Time: " + to_string(tasks[indexOfTask].getTime()) + NEXT_LINE;
	string assignState = tasks[indexOfTask].getStateOfAssignTask();
	if(assignState == UNASSIGNED)
		outputString =  outputString + assignState + NEXT_LINE;
	else
		outputString = outputString + "Assigned to " + tasks[indexOfTask].getInvolvedUser() + NEXT_LINE;
	return outputString; 
}

string printInformaionOfTaskString(Task task) {
	string s= EMPTY_STRING;
	string invlovedUser;
	if(task.getStateOfAssignTask() == UNASSIGNED)
		invlovedUser = UNASSIGNED;
	else
		invlovedUser = task.getInvolvedUser();
	s = s + to_string(task.getPriority()) + " | " + task.getTaskName() + " | " + invlovedUser + " | " + to_string(task.getTime()) + "h" + NEXT_LINE;
	return s;
}

string UTrelloInterface::printList(string list) {
	string printString = EMPTY_STRING;
	if(!existedList(lists, list))
		return LIST_DOES_NOT_EXIST;
	printString = printString + "List " + list + NEXT_LINE;
	int indexOfList = findIndexOfListName(lists, list);
	vector<string> tasksInList = lists[indexOfList].getTasksInList();
	for(int numberOfTasks = 0; numberOfTasks < tasksInList.size(); numberOfTasks++) {
		int indexOfTask = findIndexOfTaskInTasks(tasks, tasksInList[numberOfTasks]);
		printString = printString + printInformaionOfTaskString(tasks[indexOfTask]);
	}
	return printString;
}

string UTrelloInterface::printUserTasks(string user) {
	int indexOfUser = findIndexOfUserInUsers(users, user);
	string printString;
	vector<string> tasksOfUser = users[indexOfUser].getTasks();
	for(int numberOfTask = 0; numberOfTask < tasksOfUser.size(); numberOfTask++) {
		int indexOfTask = findIndexOfTaskInTasks(tasks, tasksOfUser[numberOfTask]);
		printString = printString + printInformaionOfTaskString(tasks[indexOfTask]);
	}
	return printString;
}

int UTrelloInterface::printTotalEstimatedTime() {
	int totalTime = 0;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if(tasks[numberOfTask].getStateOfAssignTask() != UNASSIGNED) 
			totalTime = totalTime + tasks[numberOfTask].getTime();
	}
	return totalTime;
}

int UTrelloInterface::printTotalRemainingTime() {
	int totalTime = 0;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if(tasks[numberOfTask].getStateOfAssignTask() != UNASSIGNED && tasks[numberOfTask].getStateOfTask() != COMPLETE) 
			totalTime = totalTime + tasks[numberOfTask].getTime();
	}
	return totalTime;
}

int UTrelloInterface::printUserWorkload(string user) {
	int time = 0;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if( tasks[numberOfTask].getInvolvedUser() == user)
			time = time + tasks[numberOfTask].getTime();
	}
	return time;
}

int UTrelloInterface::printUserPerformance(string user) {
	int time = 0;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if( tasks[numberOfTask].getInvolvedUser() == user && tasks[numberOfTask].getStateOfTask() == COMPLETE)
			time = time + tasks[numberOfTask].getTime();
	}
	return time;
}

string makePrintStringOfVectorOfPairs(vector<pair<int,string>> vectorOfPairs) {
	string printString = EMPTY_STRING;
	for(int i = 0; i<vectorOfPairs.size(); i++) {
		if(i!=0)
			printString = printString+ NEXT_LINE;
		printString = printString + vectorOfPairs[i].second;
	}
	return printString + NEXT_LINE;
}

string UTrelloInterface::printUsersByWorkload() {
	vector< pair<int, string> > workloadAndUser;
	for(int i = 0; i< users.size(); i++) {
		int time = printUserWorkload(users[i].getName());
		workloadAndUser.push_back(make_pair(time, users[i].getName()));
	}
	sort(workloadAndUser.begin(), workloadAndUser.end());
	return makePrintStringOfVectorOfPairs(workloadAndUser);
}

string UTrelloInterface::printUsersByPerformance() {
	vector<pair<int, string>> performanceAndUser;
	for(int i = 0; i< users.size(); i++) {
		const int time = printUserPerformance(users[i].getName());
		performanceAndUser.push_back(make_pair(time,users[i].getName()));
	}
	sort(performanceAndUser.begin(), performanceAndUser.end());
	reverse(performanceAndUser.begin(), performanceAndUser.end());
	return makePrintStringOfVectorOfPairs(performanceAndUser);	
}

string UTrelloInterface::printAllLists() {
	string outputString = EMPTY_STRING;
	for(int numberOfList = 0; numberOfList < lists.size(); numberOfList++) {
		string informationOfList = printList(lists[numberOfList].getListName());
		outputString = outputString + informationOfList + NEXT_LINE;
	}
	return outputString;
}

string UTrelloInterface::printUnassignedTasksByPriority() {
	vector<pair<int, string>> taskAndPriority;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if(tasks[numberOfTask].getStateOfAssignTask() == UNASSIGNED) {
			int priority = tasks[numberOfTask].getPriority();
			taskAndPriority.push_back(make_pair(priority, tasks[numberOfTask].getTaskName()));
		}
	}
	sort(taskAndPriority.begin(), taskAndPriority.end());
	string s= EMPTY_STRING;
	for(int numberOfTask = 0; numberOfTask < taskAndPriority.size(); numberOfTask++) {
		int indexOfTask = findIndexOfTaskInTasks(tasks, taskAndPriority[numberOfTask].second);
		s = s + printInformaionOfTaskString(tasks[indexOfTask]);
	}
	return s;
}

string UTrelloInterface::deleteList(string list) {
	if(!existedList(lists, list))
		return LIST_DOES_NOT_EXIST;
	int indexOfList = findIndexOfListName(lists, list);
	vector<string> taskInList = lists[indexOfList].getTasksInList();
	for(int i = 0; i<taskInList.size(); i++)
		deleteTask(taskInList[i]);
	lists.erase(lists.begin() + indexOfList);
	return SUCCESS;
}

string UTrelloInterface::printAllUnfinishedTasksByPriority() {
	vector<pair<int, string>> taskAndPriority;
	for(int numberOfTask = 0; numberOfTask < tasks.size(); numberOfTask++) {
		if(tasks[numberOfTask].getStateOfTask() == UNCOMPLETE) {
			int priority = tasks[numberOfTask].getPriority();
			taskAndPriority.push_back(make_pair(priority, tasks[numberOfTask].getTaskName()));
		}
	}
	sort(taskAndPriority.begin(), taskAndPriority.end());
	string s= EMPTY_STRING;
	for(int numberOfTask = 0; numberOfTask < taskAndPriority.size(); numberOfTask++) {
		int indexOfTask = findIndexOfTaskInTasks(tasks, taskAndPriority[numberOfTask].second);
		s = s + printInformaionOfTaskString(tasks[indexOfTask]);
	}
	return s;	
}