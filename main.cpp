#include <iostream>
#include "UTrelloInterface.hpp"

using namespace std;

int main()
{
	UTrelloInterface interface;

	cout << interface.addUser("Zhivar") << endl;
	cout << interface.addUser("Amir") << endl;
	cout << interface.addUser("Bardia") << endl;

	cout << interface.addList("Code") << endl;
	cout << interface.addList("Description") << endl;
	cout << interface.addList("Misc") << endl;

    cout << interface.addTask("Code", "Do Everything", 12, 1, "Write the whole code") << endl;
    cout << interface.editTask("Do Everything", 12, 10, "Write the whole code") << endl;
    cout << interface.assignTask("Do Everything", "Bardia") << endl;
    cout << interface.printTask("Do Everything") << endl;

    cout << interface.addTask("Code", "Destroy code formatting", 1, 2, "Rewrite the whole code in a worse format") << endl;
	cout << interface.assignTask("Destroy code formatting", "Zhivar") << endl;

	cout << interface.addTask("Description", "Write Description", 3, 1, "Write the damn description") << endl;
	cout << interface.assignTask("Write Description", "Amir") << endl;
	cout << interface.addTask("Misc", "Upload Assignment", 1, 1, "Upload it") << endl;

	cout << interface.completeTask("Do Everything") << endl;
	cout << interface.printUsersByPerformance() << endl;
    cout << interface.printUsersByWorkload() << endl;

    cout << interface.printUnassignedTasksByPriority() << endl;
	cout << interface.deleteTask("Upload Assignment") << endl;
	cout << interface.printAllUnfinishedTasksByPriority() << endl;

	cout << interface.addTask("Misc", "Have fun", 10, 2, "Just do it") << endl;
	cout << interface.moveTask("Have fun", "Code") << endl;
	cout << interface.printTask("Have fun") << endl;

    cout << interface.printList("Code") << endl;

    cout << interface.printAllLists() << endl;

    cout << interface.printUserTasks("Amir") << endl;

    cout << interface.printUnassignedTasksByPriority() << endl;

    cout << interface.printAllUnfinishedTasksByPriority() << endl;
    return 0;
}
