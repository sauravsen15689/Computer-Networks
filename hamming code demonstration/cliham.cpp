#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>

using namespace std;

int main()
{
  int client_sock;
  struct sockaddr_in ser;
  client_sock=socket(AF_INET,SOCK_STREAM,0);
  if(client_sock<0)
  {
    cout<<"Socket Creation Failed\n";
    return 0;
  }
  cout<<"Socket created\n";

    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=INADDR_ANY;
    ser.sin_port=htons(8888);

   if(connect(client_sock,(struct sockaddr*)&ser,sizeof(ser))<0)
   {
     printf("Connect Failed");
 		return 0;
 	}
 	puts("Connected\n");

 while(1)
  {
    int data[20],datarecv[20];
    char message[200]={};
    char server_reply[200]={};
    char charac;
    cout<<"\nenter the character : ";
    cin>>charac;
    int ch=(int)charac;

    data[11] = ch%2;
    ch=ch/2;
    data[10]=ch%2;
    ch=ch/2;
    data[9]=ch%2;
    ch=ch/2;
    data[7]=ch%2;
    ch=ch/2;
    data[6]=ch%2;
    ch=ch/2;
    data[5]=ch%2;
    ch=ch/2;
    data[3]=ch%2;
    ch=ch/2;

    data[1] = data[3] ^ data[5] ^ data[7] ^ data[9] ^ data[11];
    data[2] = data[3] ^ data[6] ^ data[7] ^ data[10] ^ data[11];
    data[4] = data[5] ^ data[6] ^ data[7] ;
    data[8] = data[9] ^ data[10] ^ data[11];

    int j,i;
    for(i=0,j=11;j>0;j--,i++)
      message[i]=data[j]+48;
      message[i]='\0';

    if(send(client_sock,message,strlen(message),0)<0)
    {
      cout<<"\nmessage send failed";
      return 0;
    }

    if(recv(client_sock,server_reply,2000,0)<0)
    {
      cout<<"\nreceived failed";
      return 0;
    }

    for(i=0,j=11;j>0;j--,i++)
    {
      datarecv[j]=server_reply[i]-48;
    }
  
     cout<<"\n Received Character : ";
     char a[2];
     a[0]=(char)(datarecv[11])+(datarecv[10]*2)+(datarecv[9]*4)+(datarecv[7]*8)+(datarecv[6]*16)+(datarecv[5]*32)+(datarecv[3]*64);
     a[1]='\0';
     cout<<a;
     char temp = getchar();


  }


  close(client_sock);
  return 0;
}