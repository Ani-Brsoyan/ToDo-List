#include <iostream>
#include "todo.h"

int main()
{
/*	todo t;
	t.addTask("Finish project");
	t.addTask("Do classes");
	std::cout << todo::getNotStarted() << std::endl;
	t.printTasks();
	t.removeTask(1);
	t.markAsDone(1);
	t.printTasks();
	std::cout << todo::getDone() << std::endl;*/
	todo myList;
	std::cout << "Enter your ToDo\n";
	std::cout << "Press e if you are done\n";
	std::string myStr;
	while(true){
		//std::cin.ignore();
		std::cout << "Task- ";
		getline(std::cin, myStr);
		if(myStr == "e"){
			break;
		}
		myList.addTask(myStr);
	}
	myList.printTasks();
	std::cout << "\nReport:\n";
	std::cout << "Done - " << todo::getDone() << "\n";
	std::cout << "Undone - " << todo::getNotStarted() << "\n";
	std::cout << "Expired - " << todo::getExpired() << "\n";
	return 0;
}
