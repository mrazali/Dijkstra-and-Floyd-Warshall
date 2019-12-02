#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Dijkstra.cpp"
#include "FloydWarshall.cpp"
using namespace std;


struct node{
	int number;
	int distance;
	node *ptr=NULL;
};

class graph{
	public:
		graph();
		~graph();
		node *root;
		int n;
		int** vertix_mtx;
		int** mtx;
		void insert_graph();
		void print_graph();
		bool repeat(int no);
		void mtxfun();
		void short_path();
		void insert_edg(int from,int to,int dis);
		void make_edg(int num,node *temp,int dis);
		void wtdAdjMat(int counter,int inner_counter,int to);
		void wtdAdjMat_zero(int counter,int inner_counter,int to);
};

graph::graph(){
	root=NULL;
}

graph::~graph(){
	delete []root;	
}

void graph::insert_graph(){
	fstream file;
	string ch;
	char filename[256];
	cout<<"Enter file 'name' or complete 'path'(with .txt):"<<endl;
	cin>>filename;
	file.open(filename);
	if(!file){
		cout<<"No such file";
	}else{
		file >>ch;
		istringstream(ch)>>n;
	}
	root=new node[n];
	
	mtx= new int*[n];
	for(int i = 0; i < n; ++i)
    	mtx[i] = new int[n];
    
	vertix_mtx= new int*[n];
	for(int i = 0; i < n; ++i)
    	mtx[i] = new int[n];
    	
	node *temp=root;
	int no;
	int counter=0;
	int to,dis,save;
	while(!file.eof()){
		if(save){
			no=save;
			save=0;
		}else{
			file >>ch;
			istringstream(ch)>>no;
		}
		//cout<<"no check : "<<no<<endl;

		temp->number=no;
		temp->ptr=NULL;
		temp++;
		to=0;
		int inner_counter=0;
		while(to!=-999){
			file >>ch;
			istringstream(ch)>>to;
			//cout<<"to val: "<<to<<endl;
			file >>ch;
			istringstream(ch)>>dis;
			//cout<<"dis val: "<<dis<<endl;
			if(to!=-999){
				//cout<<no<<" "<<to<<" "<<dis<<endl;
				insert_edg(no,to,dis);
				wtdAdjMat(counter,inner_counter,to);
				inner_counter++;
			}else{
				save=dis;
			}
		}
		wtdAdjMat_zero(counter,inner_counter,0);
		counter++;
		//cout<<"out"<<endl;
	}
	file.close();
	return;
}

bool graph::repeat(int no){
	if(root==NULL)
		return 0;
	node *temp=root;
	for(int i=0; i<n; i++){
		if(temp->number==no){
			return 1;
		}
	}
	return 0;
}

void graph::print_graph(){
	cout<<endl<<"------------------------------------"<<endl;
	cout<<endl<<"                 GRAPH"<<endl<<endl;
	node *temp=root;
	node *t;
	for(int i=0; i<n ; i++){
		cout<<" Vertix:  ";
		cout<<temp->number;
		t=temp;
		while(t->ptr!=NULL){
			t=t->ptr;
			cout<<"-->"<<t->number<<"("<<t->distance<<")";
		}
		cout<<endl;
		temp++;
	}
	cout<<"------------------------------------"<<endl;
	cout<<endl<<"              MATRIX"<<endl<<endl;
	for(int i=0; i<n ;i++){
		cout<<"    ";
		for(int j=0; j<n; j++){
			cout<<" "<<mtx[i][j]<<" ";
		}
		cout<<endl;
	}
	return;
}

void graph::make_edg(int num,node *temp,int dis){
	while(temp->ptr!=NULL){
		temp=temp->ptr;
	}
	temp->ptr=new node;
	temp=temp->ptr;
	temp->number=num;
	temp->distance=dis;
	temp->ptr=NULL;
	return;
}

void graph::insert_edg(int from,int to,int dis){
	node *temp=root;
	int done=1;
	while(done){
		if(temp->number==from){
			make_edg(to,temp,dis);
			done=0;
		}else{
			temp++;
		}
	}
	return;
}

void graph::wtdAdjMat(int counter,int inner_counter,int to){
	mtx[counter][inner_counter]=to;
}

void graph::wtdAdjMat_zero(int counter,int inner_counter,int x){
	while(inner_counter!=n){
		mtx[counter][inner_counter]=x;
		inner_counter++;
	}
}

void graph::mtxfun(){
	
	for(int i=0; i<n ;i++){
		for(int j=0; j<n; j++){
			mtx[i][j]=0;
		}
	}
	
	node *temp=root;
	node *t,*tem;
	for(int i=0; i<n; i++){
		tem=root;
		t=temp->ptr;
		int j=0;
		while(t!=0){
			
				if(tem->number==t->number){
					mtx[i][j]=t->distance;
					//cout<<t->distance<<endl;
					if(t!=0){
						t=t->ptr;
						j=0;
					}
					tem=root;
					
				}else{
					tem++;
					j++;
				}
		}
		temp++;
	}
}

void graph::short_path(){
	char ans;
	int f=0,s;
	cout<<"Find short path(y/n): "<<endl;
	cin>>ans;
	if(ans=='y'){
		cout<<"Enter First Vertex: "<<endl;
		cin>>f;
		cout<<"Enter Second Vertex: "<<endl;
		cin>>s;
		int col[n];
		int c;
		node* temp=root;
		for(int i=0; i<n; i++){
			col[i]=temp->number;
			if(i==s)
				c=i;
			temp++;
		}
		dijkstra(mtx,n,f,s,col,c);
		floyds(mtx,n,f,s,col,c);
	}
	
	cout<<endl<<endl<<"Thank you! ^_^ "<<endl;
}

int main(){
	graph obj;
	obj.insert_graph();
	obj.mtxfun();
	obj.print_graph();
	obj.short_path();

}
