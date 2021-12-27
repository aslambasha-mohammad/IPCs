#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define	PIPE_NAME	"/tmp/my_pipe"

int main(int agrc, char **argv)
{
	int pipe_fd = 0, len = 0;
	char *msg = "Produced data";

	pipe_fd = open(PIPE_NAME, O_WRONLY);
	if(pipe_fd < 0)
	{
		printf("Failed to open the '%s' pipe\n", PIPE_NAME);
		return -1;
	}

	len = write(pipe_fd, msg, strlen(msg));
	printf("Sent '%d' bytes of data via pipe\n", len);

	close(pipe_fd);
	return 0;
}
