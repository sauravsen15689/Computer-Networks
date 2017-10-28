#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

using namespace std;

int main()
{
	int client_socket;
	struct sockaddr_in ser;
	char message[2000]={};
	char server_reply[2000]={};
	client_socket=socket(AF_INET,SOCK_STREAM,0);
	if(client_socket<0)
	{
		cout<<"\nsocket create failed";
		return 0;
	}
  
     ser.sin_family = AF_INET;
     ser.sin_addr.s_addr = INADDR_ANY;
     ser.sin_port = htons(8888);

	if(connect(client_socket,(struct sockaddr *)&ser,sizeof(ser))<0)
	{
		cout<<"\nconnect failed";
		return 0;
	}
	cout<<"\nconnected . . .";
	while(1)
	{
		cout<<"\nenter the message : ";
		cin>>message;
		send(client_socket,message,strlen(message),0);
		recv(client_socket,server_reply,2000,0);
		cout<<"Server : "<<server_reply;
	}

    close(client_socket);
	return 0;
}