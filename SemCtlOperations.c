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

#define NUMSEM 3
union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int main()
{
	int sid, sem_value, i;
	key_t key;
	struct semid_ds sem_buf;
	static short sem_array[NUMSEM] = {3, 1, 4};
	union semun Arg;

	key = ftok(".", 'S');
	
	if((sid = semget(key, NUMSEM, IPC_CREAT | 0777)) == -1)
	{
		perror("SEMGET");
		exit(1);
	}
	printf("Semaphore identifier %d\n", sid);
		
	Arg.buf = &sem_buf;
	if(semctl(sid, 1, IPC_STAT, Arg) == -1)
	{
		perror("SEMCTL: IPC_STAT");
		exit(2);
	}
	printf("Created %s", ctime(&sem_buf.sem_ctime));

	Arg.array = sem_array;

	if(semctl(sid, 0, SETALL, Arg) == -1)
        {
                perror("SEMCTL: SETALL");
                exit(3);
        }
        
	for(i = 0; i < NUMSEM; i++)
	{
		if((sem_value = semctl(sid, i, GETVAL, 0)) == -1)
		{
			perror("SEMCTL: GETVAL");
			exit(4);
		}
		printf("Semaphore %d has value of %d\n", i, sem_value);
	}
	
	if(semctl(sid, 0, IPC_RMID, 0) == -1)
        {
                perror("SEMCTL: IPC_RMID");
                exit(5);
        }


	return 0;

}
