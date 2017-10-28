import java.util.*;
import java.io.*;
import java.net.*;

class CliPeer
{
	BufferedReader stdIn;
	DatagramPacket packet;
	DatagramSocket socket;
	byte buf[];
	private static int port=3000;
	private static String hostname="localhost";
	InetAddress address;

	CliPeer()
	{}

	void connect()
	{
		try
		{
		socket =new DatagramSocket();
		address = InetAddress.getByName(hostname);
		buf = new byte[256];
		stdIn = new BufferedReader(new InputStreamReader(System.in));
		packet = new DatagramPacket(buf,buf.length,address,port);
		socket.send(packet);
		}
				catch(Exception e)
				{
					System.out.println(e);
				}
	}

	void readThread()
	{
		Thread read = new Thread()
		{
			public void run()
			{
				String data;
				try
				{
					while(true)
					{
						buf =new byte[256];
						packet = new DatagramPacket(buf,buf.length);
						socket.receive(packet);
						data = new String(packet.getData(),0,packet.getLength());
						System.out.println("Server : "+data);
						data=null;
					}
				}
				catch(Exception e)
				{
					System.out.println(e);
				}
			}
		};
		read.start();
	}
	void writeThread()
	{
		Thread write = new Thread()
		{
			public void run()
			{
				String data;
				try
				{
					while(true)
					{
						buf =new byte[256];
						data = stdIn.readLine();
						buf = data.getBytes();
						packet = new DatagramPacket(buf,buf.length,address,port);
						socket.send(packet);
					}
				}
				catch(Exception e)
				{
					System.out.println(e);
				}
			}
		};
		write.start();
	}

public static void main(String args[])
	{
		CliPeer chat =new CliPeer();
		chat.connect();
		chat.readThread();
		chat.writeThread();
	}
}