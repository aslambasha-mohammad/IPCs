#include <stdio.h>
#include <unistd.h>
#include <string.h>	//strlen
#include <sys/msg.h>	//msg queue sys calls

#define	MSG_QUEUE_KEY	111

int main()
{
	int msgId = 0, res = 0;
	char *msg = "Hello I am Msg Queue";

	msgId = msgget(MSG_QUEUE_KEY, 0666 | IPC_CREAT);
	if(msgId < 0)
	{
		printf("Failed to create the msg queue with %d key\n", MSG_QUEUE_KEY);
		return -1;
	}

	res = msgsnd(msgId, (void *)msg, strlen(msg), 0);
	if(res < 0)
	{
		printf("Failed to send the msg through msg queue\n");
		return -1;
	}

	//If we remove the msgId then the receiver side it will need to create the new id and wait for msg from sender
	/*res = msgctl(msgId, IPC_RMID, NULL);
	if(res < 0)
	{
		printf("Failed to remove the msg queue\n");
	}*/
	return 0;
}
