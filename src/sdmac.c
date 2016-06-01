#include "sdmad.h"


int main()
{
    int sock_desc;
    struct sockaddr_in serv_addr;
    int* sbuff=NULL;
	char rbuff[BUF_LEN];

	sbuff = (char*)malloc(BUF_LEN);

    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        printf("Failed creating socket\n");

    bzero((char *) &serv_addr, sizeof (serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(5000);

    if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
	        printf("Failed to connect to server\n");
	        return -1;
	    }

    printf("Connected successfully - Please enter string\n");

	*sbuff = CMD_SYS_1;

	fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);

	send(sock_desc,sbuff,strlen(sbuff),0);
	
	if(recv(sock_desc,rbuff,BUF_LEN,0)==0)
		printf("Error");
	else
		fprintf(stderr, "%s:%d %s\n", __FILE__, __LINE__, rbuff);
	
	       bzero(rbuff,BUF_LEN);

    close(sock_desc);
	free((void*)sbuff);
    return 0;


}
