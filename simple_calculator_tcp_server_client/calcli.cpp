/* of.seekg(0,of.end);
            length = is.tellg();
             of.seekg (0, of.beg);
             while(!of.eof())
             {
             	of.get(ch);
             	send(client_socket,&ch,sizeof(char),0);
             }*/

#include<bits/stdc++.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
using namespace std;

int main()
{
	int client_socket;
	struct sockaddr_in ser;
	char msg[2000]={};
	char server_reply[2000]={};
	double number,result;
	int trigchoice;
   
    ifstream file;

    if((client_socket = socket(AF_INET,SOCK_STREAM,0))<0)
    {
    	cout<<"\nsocket creation failed";
    	return 0;
    }
    cout<<"\nsocket created";
    ser.sin_family=AF_INET;
    ser.sin_addr.s_addr=INADDR_ANY;
    ser.sin_port=htons(8000);

    if(connect(client_socket,(struct sockaddr*)&ser,sizeof(ser))<0)
    {
    	cout<<"\nconnection failed";
    	return 0;
    }
     cout<<"\nconnected...";

     while(1)
     {
     	char word[2000];
     	//char ch;
     	cout<<"\n1.say hello\n2.File Transfer\n3.Trigonometric Calculator\n\nenter choice : ";
     	int x,len=0;
     	cin>>x;
         send(client_socket,&x,sizeof(int),0);
     	switch(x)
     	{
     		fflush(stdin);
     		fflush(stdout);
     		case 1:
                strcpy(word,"hello");
               if(send(client_socket,word,strlen(word),0) < 0)
               {
               	cout<<"\nsend failed";
               	return 0;
               }

               if(recv(client_socket,word,6,0)<0)
               {
               	cout<<"\nreceive failed";
               	return 0;
               }
               cout<<"\nServer  : "<<word;
     		  break;
     		case 2:
                  file.open("ques.txt");
                  while(file.get()!=EOF)len++;
                  send(client_socket,&len,sizeof(int), 0 );
                  file.close();
                  file.open("ques.txt");
                  while(!file.eof())
                  {
                  	 char ch;
                  	if(file.eof())
						break;
                  	file.get(ch);
                    cout<<ch;
                  

                  	if( send(client_socket,&ch,1, 0 ) < 0)
					{
						puts("\nSend Failed");
						break;
					}

                  }
                  file.close();
     		  break;
     		case 3:
     		   cout<<"\nEnter the Value : ";
     		   cin>>number;
     		   
     		   cout<<"\n\t1.sin\n\t2.cos\n\t3.tan\n\tenter the Trigonometric function : \n\t";
               cin>>trigchoice;
               send(client_socket,&trigchoice,sizeof(int),0);
               send(client_socket,&number,sizeof(double),0);
               recv(client_socket,&result,sizeof(double),0);
               cout<<"\nresult : "<<result;
     		  break;
     	}
     }



    close(client_socket);
	return 0;
}