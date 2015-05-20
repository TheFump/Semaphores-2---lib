#include "sem_pv.h"


int main()
{
key_t key; 
int shmid;
int* data; 
pid_t pid;

int mutex;
mutex = init_semaphore();
val_sem(mutex, 1);


//récupération de la clé
key = ftok("sem1.c", 11);
if(key == -1) perror("error ftok");
//creation smp et allocation mémoire
shmid=shmget(key,5*sizeof(int), 0666|IPC_CREAT|IPC_EXCL) ; 
if(shmid== -1) perror("Création échoue error shmid)") ;
//get adresse smp
E = shmat(shmid, (void*)0, 0);
if(E == -1) perror("error shmat");
int i;
int A;
E = 0; //initialisation de l'entier a 0;

pid = fork();
switch(pid){
case -1 : perror("Error fork");
	exit(0);
	break;

case 0 : //fils 
	printf("Fils !");	
	for(i = 0; i < 100; i++)
	{
	P(mutex);
	A = E;
	usleep(rand()%80+20);
	A++;
	E = A;
	usleep(rand()%80+20);
	V(mutex);
	}
	exit(1);
	break;

default : //père
	printf("Père !");
	while(1)
	{
	i= (i+1)%5;
	A = rand()%100
	
	}
	break;
}

}
