import java.util.*;

class linkstate
{
	public static void main(String args[])
	{
		Scanner scan = new Scanner(System.in);
		System.out.print("enter the no of nodes : ");
		
		int n = scan.nextInt();
		System.out.println();
		System.out.print("enter the no of links : ");
		int l = scan.nextInt();
		System.out.println();

		System.out.println("enter the connections");
		int arr[][]=new int[n][n];

		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				arr[i][j]=1000;
			}
		}

		int a,b,c;
		for(int i=0;i<l;i++)
		{
			a=scan.nextInt();
			b=scan.nextInt();
			c=scan.nextInt();
			a--;
			b--;
			arr[a][b]=arr[b][a]=c;
		}
		System.out.println("...................");
		System.out.println("Routing begins...");
		System.out.println("...................");
		for(int i=0;i<n;i++)
		{
			System.out.println("Router "+(i+1)+" flooding..");
			System.out.println("...................");
			for(int j=0;j<n;j++)
			{
				System.out.print("Distance from router "+(j+1)+ " : ");
				if(i==j)
					System.out.print("0");
				else if(arr[i][j]==1000)
					System.out.print("inf");
				else
					System.out.print(arr[i][j]);
				System.out.println();

			}
		}

		System.out.println("Link state routing begins.....");

		for(int i=0;i<n;i++)
		{
			System.out.println("link state routing for router : "+(i+1));
			System.out.println(".............................");
			int distance[]=new int[n];
			int parent[]=new int[n];
			int visited[]=new int[n];
			for(int j=0;j<n;j++)
				distance[j]=1000;
			int curr=i;
			distance[curr]=0;

			for(int j=0;j<n;j++)
			{
				int min=1000;
				for(int k=0;k<n;k++)
				{
					if(visited[k]!=1 && distance[k]<min)
					{
						curr=k;
						min=distance[k];
					}
				}
				visited[curr]=1;
				for(int k=0;k<n;k++)
				{
					if(distance[k]>(arr[curr][k]+min))
					{
						parent[k]=curr;
					}
					distance[k]=Math.min(distance[k],arr[curr][k]+min);
				}
			}
			for(int j=0;j<n;j++)
			{
				System.out.print((j+1)+" . "+distance[j]+" ");

				if(parent[j]!=i && parent[j]!=0)
				{
					int pos=parent[j];
					while(parent[pos]!=i)
						pos=parent[pos];
					System.out.println((pos+1));
				}
				else
					System.out.println("-");

			}
		}

	}
}