#include "Packet.h"



Packet::Packet(MPI_Status& status){
	if(status.MPI_ERROR != MPI_SUCCESS){}
	from = status.MPI_SOURCE;
	tag = status.MPI_TAG;
}

void Packet::sendPacket(int timestamp, int to, int tag){
	MPI_Send(&timestamp,1,MPI_INT,to,tag,MPI_COMM_WORLD);
}
