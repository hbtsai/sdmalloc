#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <time.h> 



#define BUF_LEN 1024


/*
 * list of CMD_ID (4 bytes)
 * ==============
 * 0x00 - 0x0F   : system command
 * 0x10 - 0x1F	 : memory allocation command
 * 0x20 - 0x2F   : get policy command
 * 0x30 - 0x3F   : set policy command
 */


#define CMD_SYS_1		0x01

#define CMD_MA_ALLOC		0x11 // select on policy, return address
#define CMD_MA_RAMALLOC		0x1A // force malloc() on RAM and swap, return address
#define CMD_MA_SSDALLOC		0x1B // force mmap() on SSD, return address


#define CMD_GET_POL_1	0x21

#define CMD_SET_POL_1	0x31
