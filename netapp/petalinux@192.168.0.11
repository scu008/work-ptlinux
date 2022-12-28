
// Header files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Memory map
#define reg_0 0x43c00000
#define reg_offset 0x43c0ffff


// Main function
int main(int argc, char **argv)
{

    // Main variables
    int fd;
    int *value;

    // call mmap function
    if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		perror( "ERROR: could not open \"/dev/mem\", " );
		exit(EXIT_FAILURE);
	}

    // allocate physical memory to virtual memory;
    value = (int *)mmap(NULL, reg_offset, (PROT_READ|PROT_WRITE), MAP_SHARED, m_fd, reg_0);
    if( value == MAP_FAILED ) {
		perror( "ERROR: mmap() failed, " );
		close( fd );
		exit(EXIT_FAILURE);
	}

    // Repeatly print the register value
    while(1){
        printf("%d", *value);
    }
    
    // Exit instruction
    if( munmap( (void *)value, reg_offset ) != 0 )
		perror("ERROR: munmap() failed, ");
	close(fd);
    return 0;
}
