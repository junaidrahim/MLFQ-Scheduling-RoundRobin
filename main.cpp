#include "include/scheduler.h"
#include "include/process.hpp"

#include <memory>

int main(){
	Scheduler s;

	for(int i=0; i<30; i++) {
		auto p = std::make_shared<Process>(i);
		s.insert_new_process(p);
	}

	s.print_queue(0);

	s.run();

	s.print_queue(0);
	s.print_queue(1);
	s.print_queue(2);
	s.print_queue(3);

	s.print_completed();

	return 0;
}