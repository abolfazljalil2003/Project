#include <iostream>
#include <string>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

void showMatrix(int *matrix,int n);
int * GetNeighbours(int *matrix,int n,int row, int col,int level=1);
void saveToFile(string name,int score);
string readFile();
int main()
{
    cout<<"Maximum score from:"<<readFile()<<endl;
    cout<<"1)play"<<endl;
    cout<<"2)How to play"<<endl;
    cout<<"3)Quit Game!"<<endl;

    int menu;
    string user="";
    cin>>menu;

    switch (menu) {
        case 1:
            cout<<"Player name:";
            cin>>user;

            break;
        case 2:
            cout<<"more information: https://minesweeperonline.com";
            return 0;
            break;
        case 3:
            cout<<"Good bay!";
            return 0;
            break;
    }



    int n=6; //n*n matrix default value=6
    int count=10; // number of mine default value=6

    int type;
    cout<<"Game Level:1=>easy,2=>medium,3=>hard:";
    cin>>type;
    int score=0;

    switch (type) {
        case 1:
            n=6;
            count=10;
            break;
        case 2:
            n=8;
            count=12;
            break;
        case 3:
            n=10;
            count=16;
            break;
        default:
            n=6;
            count=10;
    }

    int matrix[n][n];

    int matrix1d[n*n];

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j]=-2;
                                       }

        }

    cout<<"Generating random mine Matrix..."<<endl;
    int countn=count;
    while(countn>0){
        int c,r;
        srand (time(NULL));
        c=rand() % n;
        srand (time(NULL));
        r=rand() % n;
        if(matrix[r][c]!=-1){
            matrix[r][c]=-1;

         countn--;

            }

    }
    cout<<"random mine Matrix generated."<<endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
             matrix1d[j+n*i]=matrix[i][j];
        }

    }

    showMatrix(matrix1d,n);

    int *mt=matrix1d;


bool fail=false;
    int progress=0;
    int progress_count=0;
while(!fail){

    cout<<" enter row\n";
    int r,c;
    cin>>r;
    cout<<" enter col\n";
    cin>>c;

    int counte=0;
    r=r-1;
    c=c-1;

    if(matrix1d[r*n+c]==-1){fail=true;cout<<"\nGame Over!!!"<<endl;break;}
    else
        progress++;

    mt=GetNeighbours(matrix1d,n,r,c);

    showMatrix(mt,n);

    if (progress==n*n-count)
    {
        cout<<"Win!!"<< endl;
        cout<<"Your score="<<100*type<<endl;
        saveToFile(user,100*type);
        break;
    }
    else
        cout<<"progress:"<<(progress*100.0)/float((n*n)-count)<<endl;

    }


}

void showMatrix(int *matrix,int n){

    for (int j=0;j<n+1;j++)
{
     for (int i=0;i<n+1;i++){
         if(i==0 && j>0)
         cout<<j;
         if(j==0 && i>0)
         cout<<"\t"<<i;
         if (i>0 && j>0)
         {
             if(matrix[(j-1)*n+i-1]==-1)
             cout<<"\t"<<'#';

             if(matrix[(j-1)*n+i-1]>=0)
             cout<<"\t"<<matrix[(j-1)*n+i-1];
             if(matrix[(j-1)*n+i-1]==-2)
             cout<<"\t"<<'#';


             }
                        }
                        cout<<"\n\n";

}
    }

int  *GetNeighbours(int *matrix,int n,int row, int col,int level){
    int* arr = matrix;
    int count_bomb=0;

        int imax=row<n-1?1:0;
        int imin=row>0?-1:0;
        int jmin=col>0?-1:0;
        int jmax=col<n-1?1:0;
        for (int i=imin;i<=imax;i+=1)
        for (int j=jmin;j<=jmax;j+=1){

            int rown=row+i;
            int coln=col+j;
          int  index=(rown*n+coln);

            if (i!=0 || j!=0){

                if (arr[index]==-1)
                count_bomb++;

                }



            }

    arr[row*n+col]=count_bomb;

    if(count_bomb==0 && level==1){

                for (int i=-1;i<2;i+=1)
        for (int j=-1;j<2;j+=1){
            int rown=row+i,coln=col+j;

            arr=GetNeighbours(arr,n,rown,coln,0);

            }

        }
    return arr;



}

void saveToFile(string name,int score){

    ofstream outfile;

    outfile.open("data.txt", ios_base::app); // append instead of overwrite

    if (outfile.is_open()) {
        // Write data to the file
        outfile << name<<"-"<<score << endl;


        // Close the file
        outfile.close();

    }

}

string readFile(){
    string myText;


    ifstream MyReadFile("data.txt");
    string name="";
    int max=0;
    while (getline (MyReadFile, myText)) {
       if(max<stoi(myText.substr(myText.find(" ")+1,myText.length()-1))){
           max=stoi(myText.substr(myText.find(" ")+1,myText.length()-1));
           name=myText.substr(0,myText.find(" ")+1);

       }
    }
    name=name+":"+ to_string(max);
    MyReadFile.close();
    return name;

}



