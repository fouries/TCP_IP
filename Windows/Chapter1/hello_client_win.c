#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
void Error_Handling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAddr;

	char message[30];
	int strLen;
	if(argc != 3)
	{
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}

	if( WSAStartup(MAKEWORD(2, 2), &wsaData) != 0 ) // ��ʼ��Winsock�⡣
		Error_Handling("WSAStartup() error");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);		 // �����׽��֣���32��ͨ�����׽�����������˷�����������
	if(hSocket == INVALID_SOCKET)
		Error_Handling("socket() error");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr(argv[1]);
	servAddr.sin_port = htons(atoi(argv[2]));

	if(connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) // ����ͬ��
		Error_Handling("connet() error!");

	strLen = recv(hSocket, message, sizeof(message)-1, 0);  // ����recv�������շ��������������ݡ�
	if(strLen == -1)
		Error_Handling("read() error!");
	printf("Message from server : %s \n", message);
	
	closesocket(hSocket);
	WSACleanup();											 // ע����20���г�ʼ����Winsock�⡣
	return 0;
}

void Error_Handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}