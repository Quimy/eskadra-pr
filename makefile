files=src/main.cpp src/Process.cpp src/Responses.cpp src/ThreadSafeVector.cpp

LIBS=-lpthread

message="Run run script to launch program"

out: $(files) $(LIBS)
	mpicxx $(files) -o main.out -std=c++14 $(LIBS)
	
	@echo $(message)