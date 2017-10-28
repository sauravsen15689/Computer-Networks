#include<bits/stdc++.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUFLEN 503
#define PORT 8885

using namespace std;
int main()
{
	int sock,client_sock,c,read_size;
	struct sockaddr_in ser,cli;
	c =sizeof(ser);
	char msg[503];
	
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
     if(sock < 0)
     {
      cout<<"socket creation failed";
      return 0;
     }
     
     memset((char*)&ser,0,sizeof(ser));
     ser.sin_family = AF_INET;
     ser.sin_port = 8888;
     ser.sin_addr.s_addr=htonl(INADDR_ANY);
     
     if(bind(sock,(struct sockaddr *)&ser,sizeof(ser)) < 0)
     {
      cout<<"Binding failed..";
      return 0;
     }
     
    
     
      char fname[20];
      recvfrom(sock,fname,20,0,(struct sockaddr *)&cli,(socklen_t*)&c);
     cout<<fname<<"\n";
     
     
     int filesize;
     recvfrom(sock,&filesize,sizeof(int),0,(struct sockaddr *)&cli,(socklen_t*)&c);
     cout<<filesize;
     
     fname[0]='v';
     
     fstream fout;
     fout.open(fname,ios::out | ios::binary);
     int itr=1;
     while(itr*503 < filesize)
     {
      recvfrom(sock,msg,503,0,(struct sockaddr *)&cli,(socklen_t*)&c);
      fout.write(msg,503);
      memset(&msg[0],0,503);
      itr++;
     }
     recvfrom(sock,msg,filesize%503,0,(struct sockaddr *)&cli,(socklen_t*)&c);
      fout.write(msg,filesize%503);
     fout.close();     
	return 0;
}
