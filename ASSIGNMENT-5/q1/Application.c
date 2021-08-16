#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>


#define W_VALUE _IOW('a','a',int32_t*)
#define R_VALUE _IOR('a','b',int32_t*)


int main()
{  
 
    int fds;
    int32_t val,num1,num2,numop;
    printf("Opening the driver...\n");
    fds = open("/dev/cal_dev",O_RDWR);
    if(fds<0) 
	{
        printf("device file not opened...\n");
        return 0;
    }

    printf("Select from menu \n");
    printf("\n 1. Addition \n  2. Subtraction \n  3. Multiplication \n  4. Division \n");
    scanf("%d",&numop);   
    if(numop > 4 && numop < 1)
        {
        printf("Invalid option...try again");
        return 0;
        }

    ioctl(fds,W_VALUE,(int32_t*) &numop);
    printf("Enter num1:\n");
    scanf("%d",&num1);
    printf("Enter num2:\n");
    scanf("%d",&num2);
    ioctl(fds,W_VALUE,(int32_t*) &num1);
    ioctl(fds,W_VALUE,(int32_t*) &num2);
    printf("Read data\n");
    ioctl(fds,R_VALUE,(int32_t*)&val);
    printf("Result is %d\n",val);
    printf("Closing the driver...\n");
    close(fds);

}  
