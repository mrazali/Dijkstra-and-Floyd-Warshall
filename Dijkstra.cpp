#include<iostream>
#include<climits> 
using namespace std;
int vertex= 7;  
int s;  
int minimumDist(int dist[], bool Dset[])
{
	int min=INT_MAX,index;    
	for(int v=0;v<vertex;v++)
	{
		if(Dset[v]==false && dist[v]<=min)      
		{
			min=dist[v];
			index=v;
		}
	}
	return index;
}
void dijkstra(int** graph,int vertex,int src,int f,int* col,int c)
{
	s=f;
	int dist[vertex];                             
	bool Dset[vertex];
	for(int i=0;i<vertex;i++)           
	{
		dist[i]=INT_MAX;
		Dset[i]=false;	
	}
	dist[src]=0;                    
	for(int c=0;c<vertex;c++)                           
	{
		int u=minimumDist(dist,Dset);     
		Dset[u]=true;                           
		for(int v=0;v<vertex;v++)                  
		{
			if(!Dset[v] && graph[u][v] && dist[u]!=INT_MAX && dist[u]+graph[u][v]<dist[v])
			dist[v]=dist[u]+graph[u][v];
		}
	}
	cout<<endl<<endl<<"               DIJKSTRA"<<endl<<endl<<"First Vertex\t\tShortest path \t\tSecond Vertex "<<endl;
	for(int i=0; i<vertex; i++){
		if(i==c){
			cout<<src<<"\t\t\t"<<dist[i]<<"\t\t\t"<<f<<endl;	
		}
			
	}
	return;
	
}


