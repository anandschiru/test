
/* Author : Subhash.K.U ( www.subhashku.com )
 * Copyright (C) MindSculptor Systems Pvt. Ltd (www.mindsculptorsys.com)
 */

/* SEMAPHORE OPERATION FUNCTIONS */

/* 
     -semget(2)
     -semctl(2)
     -semop(2)
*/




#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int SemID, i, nsem;
	key_t key;
	
	key = (key_t)0x50;

	for(i = 0; ; i++)
	{
		nsem = i + 1;
		
		if((SemID = semget(key, nsem, IPC_CREAT | 0666)) == -1)
		{
			perror("SEMGET: 1");
			printf("Maximum number of Semaphores in one set = %d\n", i);

			exit(0);
		}

		printf("Semaphore with ID : %d created\n", SemID);
		semctl(SemID, IPC_RMID, 0);
	}

	return 0;

}
