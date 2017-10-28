#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<arpa/inet.h>
#include <unistd.h>

int main(int argc, char* argv[])
{

	if(argc != 3)
	{
		printf("- Invalid parameters!!!\n");
		printf("- Usage %s <source hostname/IP> <target hostname/IP>\n", argv[0]);
		exit(-1);
	}

	int udp_socket;
	struct sockaddr_in peer;
	struct send_tcp
	{
	struct iphdr ip;
	struct udphdr udp;
	} packet;

	packet.ip.version = 4;
	packet.ip.ihl = 5;
	packet.ip.tos = 0;
	packet.ip.tot_len = htons(40);
	packet.ip.id = 1;
	packet.ip.frag_off = 0;
	packet.ip.ttl = 255;
	packet.ip.protocol = IPPROTO_UDP;
	packet.ip.check = 14536;
	packet.ip.saddr = inet_addr(argv[1]);
	packet.ip.daddr = inet_addr(argv[2]);

	packet.udp.source = htons(1234);
	packet.udp.dest = htons(80);
	packet.udp.len = htons(sizeof(struct udphdr));

	peer.sin_family = AF_INET;
	peer.sin_port = htons(80);
	peer.sin_addr.s_addr = inet_addr(argv[1]);
	udp_socket = socket(AF_INET, SOCK_RAW,IPPROTO_RAW);
	if(udp_socket < 0){
		perror("Socket Failed");
		return 1;
	}
	puts("Socket creates");
	while(1) {
		if(sendto (udp_socket, &packet,sizeof(packet),0,(struct sockaddr*)&peer,sizeof(peer))<0){
			perror("Send Failed");
			sleep(1);
		}
		else {
			printf("Sent\n");
			sleep(1);
		}
	}

	return 0;
}
