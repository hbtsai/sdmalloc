#include "sdmad.h"

void *connection_handler(void *);

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr, client_addr; 

    char send_buf[BUF_LEN] = "";
	int conn_len=0;
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(&client_addr, '0', sizeof(client_addr));
    memset(send_buf, '0', sizeof(send_buf)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 
	int *new_sock = NULL;

    while(connfd = accept(listenfd, (struct sockaddr*)&client_addr, NULL))
    {

		fprintf(stderr, "%s:%d connection established!\n", __FILE__, __LINE__);
	         
			//recv(connfd, recv_buf, sizeof(recv_buf), 0);


		pthread_t thread_id;
		new_sock = malloc(sizeof(int));
		*new_sock = connfd;
	
		if(pthread_create(&thread_id, NULL, connection_handler, (void*)new_sock) < 0)
		{
			perror("could not create thread");
			return -1;
		}
		
			/*
	        ticks = time(NULL);
	        snprintf(send_buf, sizeof(send_buf), "%.24s\r\n", ctime(&ticks));
	        write(connfd, send_buf, strlen(send_buf)); 
			*/
	
	        close(connfd);
	        //sleep(1);
	}

	if(connfd < 0)
	{
		perror("accept() failed");
		return -1;
	}

	close(listenfd);
	close(connfd);

	return 0;
}


void *connection_handler(void *socket_desc)
{

	int sock = *(int*)socket_desc;
	int recv_len=0;

	char send_buf[BUF_LEN] ="";
	char recv_buf[BUF_LEN] ="";
	
	int cmd_id = 0;

	fprintf(stderr, "%s:%d connection thread created!\n", __FILE__, __LINE__);

	while(1)
	{

		if(recv_len = recv(sock, recv_buf, sizeof(recv_buf), 0)>0)
		{
			fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
			if(recv_len > BUF_LEN)
			{
				perror("insufficient buffer!");
				exit(-1);
			}

			recv_buf[recv_len] = '\0';
			cmd_id = (int)recv_buf;

		fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
			switch(cmd_id)
			{
				case CMD_SYS_1:
					sprintf(send_buf, "CMD_SYS_1 invoked!\n");
					send(sock, send_buf, strlen(send_buf), 0);
					break;
				case CMD_MA_ALLOC:
					break;
				case CMD_MA_RAMALLOC:
					break;
				case CMD_MA_SSDALLOC:
					break;
				case CMD_GET_POL_1:
					break;
				case CMD_SET_POL_1:
					break;
				default:
					perror("command identifier not recognized");
					exit(-1);
					break;
			};

		fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
			if(recv_len == 0)
			{
				perror("client disconnected");
				fflush(stdout);
			}
			else if(recv_len == -1)
			{
				perror("recv error");
			}
		}

	}

	fprintf(stderr, "%s:%d thread finished!\n", __FILE__, __LINE__);

	close(sock);
	free(sock);

	return 0;
}

