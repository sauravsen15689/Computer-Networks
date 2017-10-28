#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>

using namespace std;

int main()
{
	int client_socket,ser_socket;
	struct sockaddr_in ser,cli;
	char message[2000]={};
	if((ser_socket = socket(AF_INET,SOCK_STREAM,0))<0)
	{
		cout<<"\nsocket creation failed";
		return 0;
	}
     cout<<"\nsocket created";
	ser.sin_family = AF_INET;
	ser.sin_addr.s_addr = INADDR_ANY;
	ser.sin_port = htons(8888);

	if(bind(ser_socket,(struct sockaddr *)&ser,sizeof(ser))<0)
	{
		cout<<"\nbind failed";
		return 0;
	}
    cout<<"\nbind successful";
    listen(ser_socket,3);

     int addrlen = sizeof(cli);
    client_socket = accept(ser_socket,(struct sockaddr*)&cli,(socklen_t *)&addrlen);
    if(client_socket < 0)
    {
    	cout<<"\nconnection failed";
		return 0;
    }
    cout<<"\nclient connected";
    while(recv(client_socket,message,2000,0)>0)
    {
    	write(client_socket,message,strlen(message));
    	fflush(stdout);
    	cout<<message;
    }
    close(client_socket);
	return 0;
}