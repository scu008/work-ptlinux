
// Header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

// Physical memory map
#define reg_0 0x43c00000
#define reg_offset 0x43c0ffff

// UDP information
#define PORT 5555
#define BUFF_SIZE 100

// Main function
int main(int argc, char **argv)
{

    // Main variables
    int fd, i;
    float *value;
    int client_socket;
    struct sockaddr_in serverAddress;
    int server_addr_size;
    float buff[BUFF_SIZE];


    // UDP socket setup
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    inet_aton("192.168.0.2", (struct in_addr*) &serverAddress.sin_addr.s_addr);
    serverAddress.sin_port = htons(PORT);

    // Socket creation
    if ((client_socket = socket(PF_INET, SOCK_DGRAM, 0)) == -1)
    {
        printf("Creation is failed \n");
        exit(0);
    }
    


    // call mmap function
    if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		perror( "ERROR: could not open \"/dev/mem\", " );
		exit(EXIT_FAILURE);
	}

    // allocate physical memory to virtual memory;
    value = (float *)mmap(NULL, reg_offset, (PROT_READ|PROT_WRITE), MAP_SHARED, fd, reg_0);
    if( value == MAP_FAILED ) {
		perror( "ERROR: mmap() failed, " );
		close( fd );
		exit(EXIT_FAILURE);
	}

    // Repeatly send the register value
    while(1){
        for(i = 0; i < BUFF_SIZE; i++){
            buff[i] = *value;
        }
        sendto(client_socket, buff, sizeof(buff), 0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    }
    


    // Exit instruction
    if( munmap( (void *)value, reg_offset ) != 0 )
		perror("ERROR: munmap() failed, ");
	close(fd);
    return 0;
}
