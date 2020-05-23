#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<algorithm>
#include<bits/stdc++.h> 

using namespace std;

class List {
public:
	List(string name);
	void setList(string name);
	void addTaskToList(string taskName);
	void removeTaskInList(string taskName);
	string getListName();
	vector<string> getTasksInList();
private:
	string nameOfList;
	vector<string> tasksInList;
};

#endif