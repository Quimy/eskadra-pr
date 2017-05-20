#include "mpi.h"
#include <stdio.h>
#include "constants.h"
#include <thread>
#include <atomic>
#include <iostream>
#include <unistd.h>
#include "Packet.h"
using namespace std;

atomic<int> state_P(NOT_INTERESTED);
atomic<int> state_S(NOT_INTERESTED);

void receive(){
	int timestamp;
	MPI_Status status;
	cout<<"OK"<<endl;
	while(true){
		MPI_Recv(&timestamp,1,MPI_INT,MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		cout<<"Odebrano"<<endl;
		Packet pck = Packet(status);
		cout<<pck.getFrom()<<"|"<<pck.getTag()<<endl;

		if(pck.getTag() == REQUEST_P){
			if(state == HELD_P)
		}

	}
}

int main( int argc, char **argv )
{
	int rank, size;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int namelen;

	MPI_Init( &argc, &argv );
	
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );

	MPI_Get_processor_name(processor_name,&namelen);
	printf( "Jestem %d z %d na %s\n", rank, size, processor_name );
	if(rank == 0){
		cout<<"Start"<<endl;
		thread(receive).detach();
		cout<<"KOniec"<<endl;
		while(true){

		}
	}else{
		int timestamp = 1;
		MPI_Send(&timestamp,1,MPI_INT,0,TAKEN_P,MPI_COMM_WORLD);
		cout<<"Wysłano"<<endl;
		while(true){

		}
	}






	MPI_Finalize();
	return 0;
}