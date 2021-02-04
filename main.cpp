#include "include/scheduler.h"
#include "include/process.hpp"

#include <algorithm>
#include <vector>
#include <memory>

int main(){
	Scheduler s;
	std::vector<std::shared_ptr<Process>> processes;

	const int MAX_NUM_PROCESSES = 100;

	for(int i=0; i<MAX_NUM_PROCESSES; i++) {
		auto p = std::make_shared<Process>(i);
		processes.push_back(p);
	}

	std::sort(processes.begin(), processes.end(), [](std::shared_ptr<Process>& p1, std::shared_ptr<Process>& p2){
		return (p1->arrival_time < p2->arrival_time);
	});

	for(int i=0; i<MAX_NUM_PROCESSES; i++) {
		s.insert_new_process(processes[i]);
	}

	std::cout << "Loaded All Processes in Queue 0" << std::endl;
	s.print_queue(0);

	std::cout << "Starting Scheduler" << std::endl;
	s.run();
	std::cout << "Scheduler Stopped" << std::endl;

	std::cout << "\nPrinting All Scheduler Queues" << std::endl;
	s.print_queue(0);
	s.print_queue(1);
	s.print_queue(2);
	s.print_queue(3);

	s.print_completed();

	return 0;
}