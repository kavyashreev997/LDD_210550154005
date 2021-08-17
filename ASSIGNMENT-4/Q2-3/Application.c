
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int8_t write_buf[1024];
int8_t read_buf[1024];

int main()
{
        int file;
        char choice;
        file = open("/dev/my_chardevice", O_RDWR);
        if(file < 0) 
	{
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) 
        {
                printf("Enter the choice\n");
                printf("1. Write\n");
                printf("2. Read \n");
                printf("3. Exit \n");
                scanf(" %c", &choice);
                printf("Your choice = %c\n", choice);
                
                switch(choice) 
		{
                        case '1':
                                printf("Enter the string to be writeen into the driver :");
                                scanf(" %[^\t\n]s", write_buf);
                                printf("Data Writing ");
                                write(file, write_buf, strlen(write_buf)+1);
                                printf("\nSuccessfully data written .\n");
                                break;
                        case '2':
                                printf("Data Reading ");
                                read(file, read_buf, 1024);
                                printf("\nSuccessfully data read.\n");
                                printf("Data = %s\n\n", read_buf);
                                break;
                        case '3':
                                close(file);
                                exit(1);
                                break;
                        default:
                                printf("Invalid choice entered = %c\n",choice);
                                break;
                }
        }
        close(file);
}
