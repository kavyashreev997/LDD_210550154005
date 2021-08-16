#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
int main()
{
	int fd;
	fd=open("/dev/MyCharDevice",O_RDWR,0777);
	if(fd<0)
	{
		printf("\n error in opening the file\n");
		exit(1);

	}
        close(fd);
}

