#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>

using namespace std;

int main()
{
	 int ser_socket,client_socket;
	 struct sockaddr_in ser;
	 char msg[2000]={};
     int trigchoice;
     double number,result;
     ofstream of;

	 if((ser_socket = socket(AF_INET,SOCK_STREAM,0))<0)
	 {
	 	cout<<"\nsocket creation failed";
	 	return 0;
	 }
      cout<<"\nSocket Created...";
	 ser.sin_family=AF_INET;
	 ser.sin_addr.s_addr=INADDR_ANY;
	 ser.sin_port = htons(8000);

	 if(bind(ser_socket,(struct sockaddr *)&ser,sizeof(ser))<0)
	 {
	 	cout<<"\nbind failed";
	 	return 0;
	 }
	 cout<<"\nbind successful";

	 listen(ser_socket,3);

    int addrlen = sizeof(ser_socket);
	 client_socket = accept(ser_socket,(struct sockaddr*)&ser,(socklen_t *)&addrlen);
	 if(client_socket<0)
	 {
	 	 cout<<"\nfailed to connect";
	 	 return 0;
	 }

	 cout<<"\nclient connected";
int choice;
  while(recv(client_socket,&choice,sizeof(int),0)>0)
  {
  	char msg[200]={};
  	int len,i;
  	char ch;
  	fflush(stdin);
  	fflush(stdout);
  	switch(choice)
  	{
  		case 1:
  		  recv(client_socket,msg,200,0);
  		  cout<<"\nclient Says : "<<msg;
  		  write(client_socket,msg,strlen(msg));
  		   break;
  		case 2:
  		    of.open("receive.txt",ios::out);
  		    i=0;
  		    recv(client_socket,&len,sizeof(int),0);
  		    while(i!=len)
  		    {
  		    	recv(client_socket,&ch,sizeof(ch),0);
  		    	of.put(ch);
  		    	i++;
  		    }
  		    of.close();
  		   break;
  		case 3:
  		   recv(client_socket,&trigchoice,sizeof(int),0);
  		   recv(client_socket,&number,sizeof(double),0);
  		     switch(trigchoice)
  		     {
  		     	case 1:
  		     	  result = sin(number);
  		     	  send(client_socket,&result,sizeof(double),0);
  		     	  break;
  		        case 2:
  		     	  result = cos(number);
  		     	  send(client_socket,&result,sizeof(double),0);
  		     	  break;
  		     	case 3:
  		     	  result = cos(number);
  		     	  send(client_socket,&result,sizeof(double),0);
  		     	  break;
  		     }
  		   break;

  	}

  }
	 close(ser_socket);
	 return 0;


}