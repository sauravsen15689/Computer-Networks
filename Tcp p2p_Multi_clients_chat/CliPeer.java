import java.io.*;
import java.net.*;

class CliPeer
{
	Socket socket;
	BufferedReader in;
	BufferedReader stdIn;
	PrintWriter out;
	private static String hostname;
	private static int port;

	CliPeer()
	{}

	void connect()
	{
		try
		{
		socket = new Socket(hostname,port);
		System.out.println("Connected . . .");
		in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		stdIn = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(socket.getOutputStream(),true);
		System.out.println("Chat begins");
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
			 String received;
			 try
			 {
			 	while((received=in.readLine())!=null)
			 	{
			 		System.out.println("Server : "+received);
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
			 String sent;
			 try
			 {
			 	while((sent=stdIn.readLine())!=null)
			 	{
			 		out.println(sent);
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
		hostname="localhost";
		port=3000;
		CliPeer chat = new CliPeer();
		chat.connect();
		chat.readThread();
		chat.writeThread();
	}
}