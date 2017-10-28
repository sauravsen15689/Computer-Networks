import java.io.*;
import java.net.*;
import java.util.*;

class CliMulti
{
	Socket socket;
	BufferedReader in;
	BufferedReader stdIn;
	PrintWriter out;
	private static String hostname;
	private static  int port;
	static String name;

	CliMulti(){}

	void connect()
	{
		try
		{
		socket = new Socket(hostname,port);
		System.out.println("Connected . . .");
		in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
		stdIn = new BufferedReader(new InputStreamReader(System.in));
		out = new PrintWriter(socket.getOutputStream(),true);
		System.out.print("Enter the screen name : ");
		name = stdIn.readLine();
		out.println(name +" joined the chat");
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
						System.out.println(in.readLine());
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
					synchronized(socket)
					{
						while((data=stdIn.readLine())!=null)
					    {
					    	out.println(name+ " : "+data);
					     }
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
		CliMulti chat = new CliMulti();
		chat.connect();
		chat.readThread();
		chat.writeThread();

	}
}