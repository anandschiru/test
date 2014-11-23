
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
int main()
{
	int SemID1, SemID2, SemID3;
	key_t key;
	
	key = ftok(".", 'S');

	if((SemID1 = semget(key, 3, IPC_CREAT | 0666)) == -1)
	{
		perror("SEMGET: 1");
	}
	printf("Identifier for SEMAPHORE-1: %d\n", SemID1);

	if((SemID2 = semget(key, 3, IPC_CREAT | IPC_EXCL | 0666)) == -1)
	{
		perror("SEMGET: 2");
        }
        printf("Identifier for SEMAPHORE-2: %d\n", SemID2);

	if((SemID3 = semget(IPC_PRIVATE, 3, 0666)) == -1)
        {
                perror("SEMGET: 3");
        }
        printf("Identifier for SEMAPHORE-3: %d\n", SemID3);

	return 0;

}
