#include <stdio.h>
#include <fcntl.h>

void main ( )
 {
        int i,fd;
        char ch, write_buf[100], read_buf[100];
        fd = open("/dev/chardev2", O_RDWR);
        if (fd == -1)
        {
                printf("Error in opening file \n");
                exit(-1);
        }
	printf("using device 3:");
        printf ("Press r to read from device3 or w to write the device 3");
        scanf ("%c", &ch);

        switch (ch) {
                case 'w':
                       printf (" Enter the data to be written into device");
                        scanf (" %[^\n]", write_buf);
                        write(fd, write_buf, sizeof(write_buf));
                        break;
                case 'r':
                        read(fd, read_buf, sizeof(read_buf));
                        printf ("The data in the device is %s\n", read_buf);
                        break;
                default:
                        printf("Wrong choice \n");
                        break;
        }
        close(fd);
}
