#include "sem_pv.h"

int main()
{
int get;
get = init_semaphore();
if (get == -1 || get == -1) printf("erreur init\n");
get = val_sem(2,1);
get = P(2);
sleep(30);
get = V(2);
get = detruire_semaphore();
return 0;
}
