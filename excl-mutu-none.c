 #include "sem_pv.h"

int main()
{
key_t key; 
int shmid;
int E; 
pid_t pid;



//récupération de la clé
key = ftok("sem1.c", 11);
if(key == -1) perror("error ftok");
//creation smp et allocation mémoire
shmid=shmget(key,sizeof(int), 0666|IPC_CREAT|IPC_EXCL) ; 
if(shmid== -1) perror("Création échoue error shmid)") ;
//get adresse smp
E = shmat(shmid, (void*)0, 0);
if(E == -1) perror("error shmat");
int i;
int A = 0;
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
	A = E;
	usleep(rand()%80+20);
	A++;
	E = A;
	usleep(rand()%80+20);
	}
	exit(1);
	break;

default : //père
	printf("Père !");
	for(i = 0; i < 100; i++)
	{	
	A = E;
	usleep(rand()%80+20);
	A++;
	E = A;
	usleep(rand()%80+20);
	printf(" E = %d, ", E); fflush(stdout);
	}
	wait(1);
	shmdt(E);
	shmctl(shmid, IPC_RMID, 0);
	exit(2);
	break;
}

}
