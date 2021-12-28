#include <stdio.h>
#include <string.h>
#include <sys/msg.h>

#define MSG_QUEUE_KEY	111

int main()
{
	int msgId = 0, len = 0;
	char buff[256] = {'\0'};

	msgId = msgget(MSG_QUEUE_KEY, 0666);	//no need of IPC_CREAT since sender already generated the msgId with same key
	if(msgId < 0)
	{
		printf("Failed to create the msg queue with key %d\n", MSG_QUEUE_KEY);
		return -1;
	}

	len = msgrcv(msgId, (void *)buff, 256, 0, 0);
	if(len < 0)
	{
		printf("Failed to receive the msg from queue\n");
		return -1;
	}
	printf("Received '%s' from queue with len '%d'\n", buff, len);

	//Need to remove the msgId after receiving the data since sender won't remove this
	if(msgctl(msgId, IPC_RMID, NULL) < 0)
	{
		printf("Failed to remove the msg queue\n");
	}
	return 0;
}
