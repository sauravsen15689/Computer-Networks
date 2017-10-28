import java.util.*;
import java.io.*;
import java.net.*;

class CliMulti
{
	MulticastSocket socket;
	DatagramPacket packet;
	BufferedReader stdIn;
	private static int port = 3000;
	InetAddress addrbroad,addrserver;
	String name;
	byte buf[];
	private static String hostname="224.0.0.1";

	CliMulti(){}

	void connect()
	{
		try
		{
		socket = new MulticastSocket(3001);
		addrbroad=InetAddress.getByName(hostname);
		socket.joinGroup(addrbroad);
		stdIn = new BufferedReader(new InputStreamReader(System.in));
		System.out.print("enter screen name : ");
		buf = new byte[256];
		name = stdIn.readLine();
		String sent = name + " joined the chat";
		buf = sent.getBytes();
		addrserver = InetAddress.getByName("localhost");
		packet = new DatagramPacket(buf,buf.length,addrserver,port);
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
						buf=new byte[256];
						packet = new DatagramPacket(buf,buf.length);
						socket.receive(packet);

						data = new String(packet.getData(),0,packet.getLength());
						System.out.println(data);
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
						data=stdIn.readLine();
						data = name + " : "+data;
						buf=new byte[256];
						buf = data.getBytes();
						packet = new DatagramPacket(buf,buf.length,addrserver,port);
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

	  	public static void main(String[] args) throws Exception {
		
        CliMulti chatClient = new CliMulti();
        chatClient.connect();

        chatClient.writeThread();
        chatClient.readThread();
	}
}