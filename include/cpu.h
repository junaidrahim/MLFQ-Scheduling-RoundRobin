#pragma once

#include "process.hpp"
#include <vector>

constexpr int MAX_EXECUTION_TIME = 20;

struct CPU {
	int64_t time = 0;
	std::vector<Process*> io_wait;

	void load(Process& p, int quantum_time);
	void tick();
	void reset();	
};

