#pragma once

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>

constexpr int MAX_ARRIVAL_TIME = 15;
constexpr int BURST_ARR_SIZE = 8;
constexpr int MAX_BURST_DURATION = 20;

struct Process {
	int pid;
	int arrival_time = rand() % MAX_ARRIVAL_TIME;
	int total_exec_time = 0;
	bool ready_to_execute = true;
	bool completed = false;

	int burst_index = 0;
	std::array<int, BURST_ARR_SIZE> cpu_io_bursts;

	Process(int p) {
		this->pid = p;

		for (int i = 0; i < BURST_ARR_SIZE; i++)
			cpu_io_bursts[i] = 1 + rand() % MAX_BURST_DURATION;
	}

	void increment_burst_index() { this->burst_index += 2; }

	void print() {
		std::cout << "[PID: " << std::setw(3) << this->pid << "] | ";
		std::cout << "Arrival Time: " << std::setw(2) << this->arrival_time << " | ";
		std::cout << "Completed: " << std::boolalpha << std::setw(5) << completed << " | ";
		std::cout << "Bursts: [ ";

		std::for_each(cpu_io_bursts.begin(), cpu_io_bursts.end(), [&](int x) { std::cout << x << ' '; });

		std::cout << "] | ";

		std::cout << "Execution Time: " << this->total_exec_time << std::endl;
	}
};