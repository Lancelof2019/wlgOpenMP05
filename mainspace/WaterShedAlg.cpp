 #include "../headerspace/WatershedAlg.h"
 #include<iostream>
 #define NUMSIZE 8
 using namespace std;
 using namespace cv;
 #include <time.h>
 int main(){



    cv::Mat srcImg=cv::imread("../image/pexels-sagui-andrea-618833.jpg");
    int rows=srcImg.rows;
    int cols=srcImg.cols;

     cv::Mat duplImage(srcImg.rows,srcImg.cols,CV_8UC3,Scalar::all(0));
     srcImg.copyTo(duplImage);

     if(!srcImg.data){

        cout<<"The file is not loaded or does not exist"<<endl;
        return -1;


     }

Array2D<int> threshmat(rows,cols,0);     
Array2D<int> markers(rows,cols,0);
Array2D<bool> visArr(rows,cols,false);
Array2D<int> plots(rows,cols,0);
Array2D<int> markerMap(rows,cols,0);
Array2D<bool> inprioq(rows,cols,false);
Array2D<int> temp(rows*cols,3,0);
Array2D<int> nextSet(rows*cols*9,3,0);
Bool2D visBool(rows,cols);

#pragma omp parallel for
for(int i=0;i<rows;i++){
  for(int j=0;j<cols;j++){
   visBool(i,j)=&visArr(i,j);
   
  }


}


//cout<<*visBool(3,7)<<endl;

/*
bool bVal=false;
bool* __restrict visArr[rows][cols]={NULL};
for(int i=0;i<rows;i++){
  for(int j=0;j<cols;j++){
    visArr[i][j]=&bVal;

  }
}
*/


//Array2D<int> boundmat(rows,cols*8,0);
//
//
//
//
/*
int ***arr3D=new int**[rows*cols];
for(int i=0;i<rows*cols;i++){
    arr3D=new int*[2];
    //for(int j=0;j<2;j++){
     arr3D[i*cols][0]=new int[8];
     arr3D[i*cols][1]=new int[8];
     arr3D[i*cols][0][0]=i
     arr3D[i*cols][0][1]=i
     


    }



}
*/





int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};

int nrows=2;
int ncols=8;
int ****arr4D=new int***[rows];
for(int i=0;i<rows;i++){
   arr4D[i]=new int**[cols];
     for(int j=0;j<cols;j++){
       arr4D[i][j]=new int*[nrows];
       for(int m=0;m<nrows;m++){
        arr4D[i][j][m]=new int[ncols];
	for(int n=0;n<ncols;n++){

	   arr4D[i][j][m][n]=0;

	}

       }
     }
}

#pragma omp parallel for
for(int i=0;i<rows;i++){

	for(int j=0;j<cols;j++){

          for(int z=0;z<8;z++){
           arr4D[i][j][0][z]=i+dx[z];
           arr4D[i][j][1][z]=j+dy[z];

	  }
	}
}


int ****mat4D=new int***[rows];
for(int i=0;i<rows;i++){
   mat4D[i]=new int**[cols];
     for(int j=0;j<cols;j++){
       mat4D[i][j]=new int*[nrows];
       for(int m=0;m<nrows;m++){
        mat4D[i][j][m]=new int[ncols];
        for(int n=0;n<ncols;n++){

           mat4D[i][j][m][n]=0;

        }

       }
     }
}



/*
for(int i=0;i<5;i++){

  for(int j=0;j<4;j++){

        for(int z=0;z<8;z++){
          cout<<"("<< arr4D[i][j][0][z]<<","<<arr4D[i][j][1][z]<<") ";

          }
	cout<<"|";
  }
cout<<endl;

}
*/




//for(int i=0;i<rows;i++){

  //for(int j=0;j<cols)




//}


Array1D plotx(rows,cols,-1);
Array1D ploty(rows,cols,-1);
//memset(plotx,-1,sizeof(int)*rows*cols);
//memset(ploty,-1,sizeof(int)*rows*cols);


//  bool** __restrict inprioq=new bool*[rows];
  //     int** __restrict markerMap=new int*[rows];
/****Buffer allocation****/
/*   int **threshmat=new int*[rows];
   for(int i=0;i<rows;i++){

      threshmat[i]=new int[cols];
   }
   //Array2D markers(rows,cols); // creates markers and initializes values to 0 in constructor
   //markers(i,j) = 5; // uses overloaded operator() to access markers[i][j]
   // this avoids code duplication and makes codes safer because allocation is only in constructor and deallocation is done in destructor 
   // exercise 1 in AdvPT

  int **markers=new int*[rows];
          for(int i=0;i<rows;i++){
              markers[i]=new int[cols];

          }


   #pragma omp parallel for
        for(int i=0;i<rows;i++){
         #pragma omp parallel for
           for(int j=0;j<cols;j++){
  :             markers[i][j]=0;

                }
        }




        bool** visArr=new bool*[rows];
       // #pragma omp parallel for
        for(int i=0;i<rows;i++){
             visArr[i]=new bool[cols];
        }


        int* plotx=new int[rows*cols];
        int* ploty=new int[rows*cols];



        memset(plotx,-1,sizeof(int)*rows*cols);
        memset(ploty,-1,sizeof(int)*rows*cols);




   int **plots=new int*[rows];
   for(int i=0;i<rows;i++){
     plots[i]=new int[cols];
   }



       bool** __restrict inprioq=new bool*[rows];
       int** __restrict markerMap=new int*[rows];
      // #pragma omp parallel for
      for(int i=0;i<rows;i++){
          inprioq[i]=new bool[cols];
         // markerMap[i]=new int[cols];
       }

           for(int i=0;i<rows;i++){
           markerMap[i]=new int[cols];
          // markerMap[i]=new int[cols];
       }





     #pragma omp parallel for
        for(int i=0;i<rows;i++){
         #pragma omp parallel for
         for(int j=0;j<cols;j++){
           inprioq[i][j]=false;
          markerMap[i][j]=0;

           }
          }

int **temp=new int*[rows*cols];

for(int i=0;i<rows*cols;i++){

     temp[i]=new int[3];

}


int **nextSet= new int*[rows*cols*9];
for(int i=0;i<rows*cols*9;i++){

 nextSet[i]=new int[3];

}
*/
/****Buffer allocation****/






   clock_t start1,end1;
    double start,end;
    start1=clock();
    start=omp_get_wtime();
     WatershedAlg *walg=new WatershedAlg();
     walg->processImage(srcImg,duplImage,threshmat,markers,visArr,plotx,ploty,plots,inprioq,markerMap,temp,nextSet,arr4D,mat4D,visBool);
     end=omp_get_wtime();
     end1=clock();
     //cout<<"CLOCKS_PER_SEC :"<<CLOCKS_PER_SEC<<endl;
     cout<<"The total time the parallel  algorithm used is :"<<(double)(end - start)<<"s"<<endl;
     cout<<"The total time the algorithm used is :"<<(double)(end1 - start1)/CLOCKS_PER_SEC<<endl;
     delete walg;
     return 0;
   } 
