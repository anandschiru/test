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
	
	for(i = 0; ; i++)
	{
		if((SemID = semget((key_t)i, 3, IPC_CREAT | 0666)) == -1)
		{
			perror("SEMGET");
			printf("Maximum number of Semaphores in one set = %d\n", i);

			exit(0);
		}

		printf("Semaphore with ID : %d created with key : %d\n", SemID, i);
		
	}

	return 0;

}
