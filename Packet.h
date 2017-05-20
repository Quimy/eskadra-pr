#pragma once
#include "constants.h"
#include "mpi.h"

class Packet{
	int from;
	int timestamp;
	int tag;
public:

	Packet(MPI_Status& status);
	void sendPacket(int timestamp, int to, int tag);
	int getTag(){return tag;};
	int getFrom(){return from;};
};