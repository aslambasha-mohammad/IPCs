#include <stdio.h>
#include <unistd.h>	//close
#include <string.h>	//strlen
#include <sys/types.h>	//open
#include <sys/stat.h>
#include <fcntl.h>

#define	PIPE_NAME	"/tmp/my_pipe"

int main(int argc, char **argv)
{
	int pipe_fd = 0, res = 0, len = 0;
	char buff[1024] = {'\0'};

	if(access(PIPE_NAME, F_OK) == -1)
	{
		//res = mkfifo(PIPE_NAME, 0777);
		res = mknod(PIPE_NAME, S_IFIFO|0777, 0);	//last argument indicates dev name useful for device driver files
		if(res != 0)
		{
			printf("Failed to create the named Pipe\n");
			return -1;
		}
	}

	pipe_fd = open(PIPE_NAME, O_RDONLY);
	if(pipe_fd < 0)
	{
		printf("Failed to open the named pipe file\n");
		return -1;
	}

	len = read(pipe_fd, buff, 1024);
	if(len)
		printf("Received '%s' msg from client via pipe\n", buff);
	else
		printf("No msg got received from client via pipe\n");

	close(pipe_fd);
	return 0;
}
