#include "sem_pv.h"

int semid = -1;

int init_semaphore()
{
	key_t key = ftok("sem_pv.h", 11);
	if(key == -1) 
	{
		perror("error ftok");
		return -2;
	}
	semid = semget(IPC_PRIVATE, N_SEM, IPC_CREAT|700);	
	if(semid < 0) perror("error semid init");
	int i;
	int retour;
	printf("smid : %d", semid);
	for(i = 0; i < N_SEM; i++) {
		retour = val_sem(i, 0);
		}

	if(semid > 0 && retour > 0 ) return 0;
	return -2;
}


int detruire_semaphore(void)
{
	if( semid < 0) 
	{	
		fprintf(stderr, "Semaphore non initialisé");
		return -1;
	}
	return semctl(semid, 0, IPC_RMID);
}


int val_sem(int sem, int val)
{
	if( semid < 0) 
	{
		fprintf(stderr, "Semaphore non initialisé");
		return -1;
	}
	if ( sem > N_SEM) 
	{
		fprintf(stderr, "Nombre de sem incorrect");
		return -2;
	}
	union semun init;
	init.array = malloc(5*sizeof(unsigned int));
	int i;
	for(i = 0; i < N_SEM; i++) //initialisation du tableau pour chaque sem
	{
	init.array[i] = val;
	}
	init.val = val;
	int retour = semctl(semid, sem, SETVAL, init.val);
	if(retour < 0) perror("error semctl val_sem");
	return retour;
}


int P(int sem)
{
	if( semid < 0) 
	{
		fprintf(stderr, "Semaphore non initialisé");
		return -1;
	}
	if ( sem > N_SEM) 
	{
		fprintf(stderr, "Nombre de sem incorrect");
		return -2;
	} //sem -1 car 0 a 4 sémaphores
	struct sembuf P;
	P.sem_op = -1; //pour action p
	P.sem_num = sem; // pour viser le bon sémaphore
	int retour = semop( semid, &P, 1); // 1 sémaphore => 1 opération
	if(retour < 0) perror("error semop P");
	return retour;
}

int V(int sem)
{
	if( semid < 0) 
	{
		fprintf(stderr, "Semaphore non initialisé");
		return -1;
	}
	if ( sem > N_SEM) 
	{
		fprintf(stderr, "Nombre de sem incorrect");
		return -2;
	} //sem -1 car 0 a 4 sémaphores
	struct sembuf V;
	V.sem_op = 1; //pour action V
	V.sem_num = sem; // pour viser le bon sémaphore
	int retour = semop( semid, &V, 1); // 1 sémaphore => 1 opération
	if(retour < 0) perror("error semop V");
	return retour;
}
