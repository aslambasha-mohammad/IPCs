#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int pipefd[2];
	int pid = 0;
	int read_len = 0, write_len = 0;
	char buff[1024] = {'\0'};
	char *msg1 = "Hello child, I am ur parent";
	char *msg2 = "Hello parent, I am ur child";

	if(pipe(pipefd) == -1)
	{
		printf("Failed to created the unnamed pipe\n");
		return -1;
	}

	pid = fork();
	if(pid == -1)
	{
		printf("Failed to create the child process\n");
		return -1;
	}
	else if(pid == 0)
	{
		printf("This is the child process\n");
		read_len = read(pipefd[0], buff, 1024);
		printf("Read: %d\tReceived '%s' msg from parent\n", read_len, buff);
		write_len = write(pipefd[1], msg2, strlen(msg2));
		printf("Successfully send the msg2 to parent with len: %d\n", write_len);
	}
	else
	{
		printf("This is the parent process\n");
		write_len = write(pipefd[1], msg1, strlen(msg1));
		sleep(1);
		printf("Successfully send the msg1 to child with len: %d\n", write_len);
		read_len = read(pipefd[0], buff, 1024);
		printf("Read: %d\tReceived '%s' msg from child\n", read_len, buff);
	}
	return 0;
}
