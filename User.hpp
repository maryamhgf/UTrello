#ifndef __USER_HPP__
#define __USER_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include<algorithm>
#include<bits/stdc++.h> 
using namespace std;


class User {
public:
	User(string name);
	void setUser(string name);
	void addTask(string taskName);
	void removeTask(string taskName);
	string getName();
	vector<string> getTasks();
private:
	string nameOfUser;
	vector<string> allTasks;
};

#endif