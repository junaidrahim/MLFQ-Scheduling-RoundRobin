#include "../include/cpu.h"
#include <algorithm>
#include <iostream>

void CPU::load(Process &p, int quantum_time) {
	if (!p.completed) {
		if (p.ready_to_execute) {
			// reduce the particular burst by quantum time
			// if cpu burst complete move it for io

			for (int i = 0; i < quantum_time; i++) {
				p.cpu_io_bursts[p.burst_index] -= 1;
				p.total_exec_time += 1;
				this->tick();

				if (p.cpu_io_bursts[p.burst_index] == 0) {
					p.ready_to_execute = false;
					this->io_wait.push_back(&p);
					break;
				}
			}
		} else {
			for (int i = 0; i < quantum_time; i++)
				this->tick();
		}
	}
}

void CPU::tick() {
	// decrement values of the processes waiting for IO
	// Increment time
	auto it = std::remove_if(this->io_wait.begin(), this->io_wait.end(), [](Process *p) {
		p->cpu_io_bursts[p->burst_index + 1] -= 1;

		if (p->cpu_io_bursts[p->burst_index + 1] == 0) {
			if (p->burst_index == 6) p->completed = true;

			p->ready_to_execute = true;
			p->increment_burst_index();
			return true;
		}
		
		return false;
	});

	this->io_wait.erase(it, this->io_wait.end());
	this->time++;
}

void CPU::reset() {
	this->time = 0;
	this->io_wait.clear();
}