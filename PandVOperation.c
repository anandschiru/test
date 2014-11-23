
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

int main(int argc, char *argv[])
{
	int i, semid;
	key_t key;
	char *Data = "Subhash\n";
	union semun arg;
	struct sembuf P = {0, -1, SEM_UNDO};
	struct sembuf V = {0,  1, SEM_UNDO};

	srand((unsigned int)getpid());

	if((key = ftok(".", 'S')) == -1)
	{
		perror("FTOK");
		exit(1);
	}
	
	if((semid = semget(key, 1, IPC_CREAT | 0666)) == -1)
	{
		perror("SEMGET");
		exit(2);
	}

	/*Setting Initial Semaphore Value*/
	if(argc > 1)
	{
		arg.val = 1;
		if(semctl(semid, 0, SETVAL, arg) == -1)
		{
			perror("SEMCTL: SETVAL");
			exit(3);
		}
		Data = "TGF\n";
		sleep(2);
	}
	
	for(i = 0; i < 10; i++)
	{
		if(semop(semid, &P, 1) == -1)
		{
			perror("SEMOP: P");
			exit(4);
		}
		printf("%s", Data);
		fflush(stdout);
		printf("%s", Data);
                fflush(stdout);
		
		if(semop(semid, &V, 1) == -1)
                {
                        perror("SEMOP: V");
                        exit(5);
                }
		
		sleep(1);
	}	
	printf("\n%d - Finished\n", getpid());

	if(argc > 1)
	{
		sleep(10);
		if(semctl(semid, 0, IPC_RMID, arg) == -1)
        	{
                	perror("SEMCTL: IPC_RMID");
                	exit(6);
		}
        }

	return 0;

}
