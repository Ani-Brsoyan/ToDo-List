#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>

enum class status
{
	done,
	notStarted,
	expired
};

struct Task
{
	std::string tText;
	status tStatus;	
	int deadH;
	int deadM;
	void setDeadline();
};

class todo
{
	public:
		todo();
		void addTask(const std::string& newTask);
		void markAsDone(int index);
		void removeTask(int index);	
		void printTasks();
		static int getDone();
		static int getNotStarted();
		static int getExpired();

	private:
		std::vector<Task> list;
		static int doneCount;
		static int notStCount;
		static int expCount;
		std::chrono::duration<double> getDuration(int index);
		bool littleLeft(int index);
		bool expired(int index);
};
