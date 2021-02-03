INCLUDEDIR=include/
CPPC=g++
CFLAGS=--std=c++17 -I $(INCLUDEDIR)

mlfq-scheduler: main.cpp src/cpu.cpp src/scheduler.cpp include/cpu.h include/process.hpp include/scheduler.h
	$(CPPC) -o mlfq-scheduler $(CFLAGS) main.cpp src/cpu.cpp src/scheduler.cpp

run: mlfq-scheduler
	./mlfq-scheduler