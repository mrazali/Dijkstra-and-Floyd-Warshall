#include <iostream>
#include <conio.h>
using namespace std;

void floyds(int** b,int n,int f,int s,int *col,int c)
{
    int i, j, k;
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < n; j++)
            {
                if ((b[i][k] * b[k][j] != 0) && (i != j))
                {
                    if ((b[i][k] + b[k][j] < b[i][j]) || (b[i][j] == 0))
                    {
                        b[i][j] = b[i][k] + b[k][j];
                    }
                }
            }
        }
    }
   // for (i = 0; i < n; i++)
    {
        cout<<endl<<endl<<"               FloydWarshall"<<endl<<endl<<"First Vertex\t\tShortest path \t\tSecond Vertex "<<endl;
        //for (j = 0; j < n; j++)
        {
            cout<<f<<"\t\t\t"<<b[f][s]<<"\t\t\t"<<s<<endl;
        }
 
    }
}
//int main()
//{
//    int b[7][7];
//    cout<<"ENTER VALUES OF ADJACENCY MATRIX\n\n";
//    for (int i = 0; i < 7; i++)
//    {
//        cout<<"enter values for "<<(i+1)<<" row"<<endl;
//        for (int j = 0; j < 7; j++)
//        {
//            cin>>b[i][j];
//        }
//    }
//    floyds(b);
//    getch();
//}
