#include "../include/scheduler.h"

#include <iostream>

Scheduler::Scheduler() {
	for (int i = 0; i < 4; i++) {
		Queue q_temp(this->quantum_times[i]);
		queues[i] = q_temp;
	}
}

void Scheduler::insert_new_process(std::shared_ptr<Process> p) { queues[0].q.push(p); }

void Scheduler::run() {
	while (!this->all_queues_empty()) {

		while (!this->is_queue_empty(0)) {
			std::shared_ptr<Process> p = this->queues[0].q.front();
			this->queues[0].q.pop();

			if (!p->completed) {
				if (p->total_exec_time < MAX_PROC_CPU_TIME) {
					if (p->ready_to_execute) {
						cpu.load(*p, this->queues[0].quantum_time);
					} else
						cpu.tick();

					this->queues[0].q.push(p);
				} else {
					std::cout << "Moving ";
					p->print();
					std::cout << "to Queue 1" << std::endl;
					this->move_process(p, 1);
				}
			} else {
				this->completed.push_back(p);
			}
		}

		while (!this->is_queue_empty(1)) {
			std::shared_ptr<Process> p = this->queues[1].q.front();
			this->queues[1].q.pop();

			if (!p->completed) {
				if (p->total_exec_time < MAX_PROC_CPU_TIME * 2) {
					if (p->ready_to_execute) {
						cpu.load(*p, this->queues[1].quantum_time);
					} else
						cpu.tick();

					this->queues[1].q.push(p);
				} else {
					std::cout << "Moving ";
					p->print();
					std::cout << "to Queue 2" << std::endl;
					this->move_process(p, 2);
				}
			} else {
				this->completed.push_back(p);
			}
		}

		while (!this->is_queue_empty(2)) {
			std::shared_ptr<Process> p = this->queues[2].q.front();
			this->queues[2].q.pop();

			if (!p->completed) {
				if (p->total_exec_time < MAX_PROC_CPU_TIME * 3) {
					if (p->ready_to_execute) {
						cpu.load(*p, this->queues[2].quantum_time);
					} else
						cpu.tick();

					this->queues[2].q.push(p);
				} else {
					std::cout << "Moving ";
					p->print();
					std::cout << "to Queue 3" << std::endl;
					this->move_process(p, 3);
				}
			} else {
				this->completed.push_back(p);
			}
		}

		while (!this->is_queue_empty(3)) {
			std::shared_ptr<Process> p = this->queues[3].q.front();
			this->queues[3].q.pop();

			if (!p->completed) {
				if (p->total_exec_time < MAX_PROC_CPU_TIME * 4) {
					if (p->ready_to_execute) {
						cpu.load(*p, this->queues[3].quantum_time);
					} else
						cpu.tick();

					this->queues[3].q.push(p);
				} else {
					std::cout << "Moving ";
					p->print();
					std::cout << "to Queue 4" << std::endl;
					this->move_process(p, 0);
				}
			} else {
				this->completed.push_back(p);
			}
		}
	}
}

bool Scheduler::is_queue_empty(int qidx) { return this->queues[qidx].q.empty(); }

bool Scheduler::all_queues_empty() {
	return ((is_queue_empty(0)) && (is_queue_empty(1)) && (is_queue_empty(2)) && is_queue_empty(3));
}

void Scheduler::move_process(std::shared_ptr<Process> p, int to_q) { this->queues[to_q].q.push(p); }

void Scheduler::print_queue(int idx) {
	std::cout << "Printing Scheduler Queue : " << idx << std::endl;
	std::queue<std::shared_ptr<Process>> q = this->queues[idx].q;

	while (!q.empty()) {
		q.front()->print();
		q.pop();
	}
}

void Scheduler::print_completed() {
	size_t s = completed.size();

	std::cout << "Processes that Completed Execution: " << std::endl;

	for (int i = 0; i < s; i++) {
		completed[i]->print();
	}
}