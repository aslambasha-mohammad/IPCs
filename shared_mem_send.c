#include <stdio.h>
#include <sys/shm.h>	//shared memory sys calls

#define	SHM_KEY		24
#define	MEM_SIZE	1024

int main()
{
	int shmId = 0;
	char *memPtr = NULL;

	shmId = shmget(SHM_KEY, MEM_SIZE, 0666|IPC_CREAT);
	if(shmId < 0)
	{
		printf("Failed to get the Shared Memory Id with key '%d'\n", SHM_KEY);
		return -1;
	}

	memPtr = shmat(shmId, NULL, 0);
	if(memPtr != (void *)-1)	//on failure shmat returns (void *)-1
	{
		printf("Enter the data which need to be send via shared memory: ");
		scanf("%[^\n]s", memPtr);
		printf("'%s' written successfully into shared memory\n", memPtr);
	}
	else
		printf("Failed to get the shared memory pointer\n");

	shmdt(memPtr);
	return 0;
}
