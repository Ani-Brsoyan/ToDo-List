#include "todo.h"
#include <iostream>

int todo::doneCount;
int todo::notStCount;
int todo::expCount;

todo::todo()
{
	std::cout << "This is a daily ToDo list, so every input belongs to today\n";
}

void todo::addTask(const std::string& newTask)
{
	Task tmp;
	tmp.tText = newTask;
	tmp.tStatus = status::notStarted;
	tmp.setDeadline();
	std::cin.ignore();
	list.push_back(tmp);
	notStCount++;
}

void todo::markAsDone(int index)
{
	index--;
	if(index >= 0 && index < list.size() && list[index].tStatus != status::expired){
		list[index].tText += " [completed]";
		notStCount--;
		doneCount++;
	}else{
		std::cout << "Invalid index\n";
	}
}

void todo::removeTask(int index)
{
	index--;
	if(index >= 0 && index < list.size()){
		std::cout << std::endl;
		std::cout << list[index].tText << " :task removed\n";
		list.erase(list.begin() + index);
		if(list[index].tStatus == status::done){
			doneCount--;
		}else if(list[index].tStatus == status::notStarted){
			notStCount--;
		}else{
			expCount--;
		}
	}else{
		std::cout << "Invalid index\n";
	}
}

void todo::printTasks()
{
	std::cout << "***********\n";
	std::cout << "To-Do List:\n";
	if(list.empty()){
		std::cout << "No Tasks\n";
	}else{
		int i = 1;
		for(const Task& task : list){
			std::cout << i << ") " << task.tText;
			if(this->littleLeft(i - 1)){
				std::cout << " //less than 1 hour left";
			}
			else if(this->expired(i - 1)){
				std::cout << " [ops, missing time management]";
				notStCount--;
				expCount++;
			}
			std::cout << std::endl;
			i++;
		}
	}
}

void Task::setDeadline()
{
	std::cout << "Enter deadline\n";
	int hour;
	int minutes;
	do{
		std::cout << "Hour: ";
		std::cin >> hour;
	}while(hour < 0 || hour >= 24);
	do{
		std::cout << "Minute: ";
		std::cin >> minutes;
	}while(minutes < 0 || minutes >= 60);
	this->deadH = hour;
	this->deadM = minutes;
}

int todo::getDone()
{
	return doneCount;
}

int todo::getNotStarted()
{
	return notStCount;
}

int todo::getExpired()
{
	return expCount;
}

std::chrono::duration<double> todo::getDuration(int index)
{
	auto currentTime = std::chrono::system_clock::now();
	auto currentDate = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm userTime = *std::localtime(&currentDate);
	userTime.tm_hour = list[index].deadH;
	userTime.tm_min = list[index].deadM;
	auto userTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&userTime));
	std::chrono::duration<double> duration = userTimePoint - currentTime;
	return duration;
}

bool todo::littleLeft(int index)
{
	return (getDuration(index) > std::chrono::seconds(0) && getDuration(index) < std::chrono::hours(1));	
}

bool todo::expired(int index)
{
	return getDuration(index) < std::chrono::seconds(0);	
}
