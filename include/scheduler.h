#pragma once

#include "process.hpp"
#include "cpu.h"

#include <queue>
#include <vector>
#include <array>
#include <memory>

struct Queue {
	int quantum_time;
	std::queue<std::shared_ptr<Process>> q;

	Queue() = default;

	Queue(int qtime) {
		this->quantum_time = qtime;
	}
};

struct Scheduler {
	const int MAX_PROC_CPU_TIME = 20;

	const std::array<int, 4> quantum_times = {3, 5, 7, 9};
	std::array<Queue, 4> queues;

	CPU cpu;
	std::vector<std::shared_ptr<Process>> completed;

	Scheduler();
	void insert_new_process(std::shared_ptr<Process> p);
	void run();
	bool is_queue_empty(int qidx);
	bool all_queues_empty();
	void move_process(std::shared_ptr<Process> p, int to_q);
	void print_queue(int idx);
	void print_completed();
};