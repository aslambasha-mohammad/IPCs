#include <stdio.h>
#include <sys/shm.h>

#define	SHM_KEY		24
#define MEM_SIZE	1024

int main()
{
	int shmId = 0;
	char *memPtr = NULL;

	shmId = shmget(SHM_KEY, 0 /*MEM_SIZE*/, 0);	//No need of permission and mem size since shm is already created by sender
	if(shmId < 0)
	{
		printf("Failed to get shared memory id for key '%d'\n", SHM_KEY);
		return -1;
	}

	memPtr = shmat(shmId, NULL, 0);
	if(memPtr != (void *)-1)	//on failure shmat returns (void *)-1
	{
		printf("Read '%s' from the shared memory\n", memPtr);
	}
	else
		printf("Failed to read the data from shared memory\n");

	shmdt(memPtr);
	return 0;
}
