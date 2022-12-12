#include "../headerspace/WatershedAlg.h"
#include <queue>
#include <cstdlib> 
#include <vector>
#include <string.h>
#define NUMSIZE 8
#define NSIZE 4

using namespace cv;

Array2D<int> &WatershedAlg::distanceTransform(Array2D<int>& matArr, Array2D<int> &markers,int &rows,int &cols,Array2D<int> &plots,Array2D<bool>& visArr,Array1D &plotx,Array1D &ploty,int**** arr4D,int**** mat4D,Bool2D &visBool) {

       // queue<int> qx, qy;
        int dx[NUMSIZE]={-1, 1, 0, 0, -1, -1, 1, 1};
        int dy[NUMSIZE]={0, 0, -1, 1, -1,  1, 1, -1};
        int pixelThreshold=55;


        

//******It makes the nearest piexel along 0 point sohow up and become the edge pixel
//          //#pragma omp simd
       //
     /*   #pragma omp parallel for
        for(int i = 0; i < rows; i++) {
         #pragma omp parallel for
	   for(int j = 0; j < cols; j++) {
                if(matArr(i,j)!= ZERO) {
                    continue;
                }
                //this is the part that sepreated from the edge
                #pragma omp simd 
                for(int h = 0; h < NSIZE; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols ) {
                        continue;
                    }

                    if( !visArr(nextX,nextY) && matArr(nextX,nextY)== ONE){ //(int) image.at<uchar>(nextX, nextY) == ONE ) {
                        visArr(nextX,nextY) = true;

			matArr(nextX,nextY)=pixelThreshold;
			plots(nextX,nextY)=1;
			// it would be more efficient too set pcounter here already and plotx, ploty if possible???

                    }
                }
                
        }
        
     }

*/






//************new changes*********************





/*

  #pragma omp parallel for
        for(int i = 0; i < rows; i++) {
        // #pragma omp parallel for
           for(int j = 0; j < cols; j++) {
                if(matArr(i,j)== ZERO && matArr(i,j)!=pixelThreshold) {
                    continue;
                }
                //this is the part that sepreated from the edge
                //#pragma omp simd 
                for(int h = 0; h < NSIZE; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols ) {
                        continue;
                    }
                 // if(matArr(i,j)!=pixelThreshold){
                    if( matArr(nextX,nextY)==ZERO){ //(int) image.at<uchar>(nextX, nextY) == ONE ) {
                       // visArr(nextX,nextY) = true;

                        matArr(i,j)=pixelThreshold;
                        plots(i,j)=1;
                        // it would be more efficient too set pcounter here already and plotx, ploty if possible???

                    }
               // }
               }
        }

     }
*/

//************************updated new changes*****************
//int vcounter=0;
int boundcounter=0;
int zerocounter=0;

#pragma omp parallel for reduction(+:boundcounter,zerocounter)	   
for(int i=0;i<rows;i++){
   for(int j=0;j<cols;j++){
     if(matArr(i,j)==ZERO){
  
             visArr(i,j)=true; 
            // zerocounter+=1;
	     continue;
            }

        for(int k=0;k<NSIZE;k++){
	   // if(!visArr(arr4D[i][j][0][k],arr4D[i][j][1][k])){
            if(arr4D[i][j][0][k]>-1 && arr4D[i][j][1][k]>-1 && arr4D[i][j][0][k]<rows && arr4D[i][j][1][k]<cols){
                
	       if(!visArr(arr4D[i][j][0][k],arr4D[i][j][1][k])) {  
            
                    if(matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])==ZERO){ //!visArr(arr4D[i][j][0][k],arr4D[i][j][0][k])){  
                       matArr(i,j)=pixelThreshold;
                       visArr(i,j)=true;
		      // boundcounter+=1;
		       plots(i,j)=1;

                     //  mat4D[i][j][0][k]=i;
                     //  mat4D[i][j][1][k]=j;
                      // vcounter++;
                 }
	       }
	    }
             // }
	 }
       }
    }



// cout<<"zero :"<<zerocounter<<endl;

//cout<<"boundary :"<<boundcounter<<endl;



 //string filename21="/opt/test21new.txt";
   //      ofstream fout21(filename21);


/*


for(int i = 0; i < rows; i++) {
   for(int j = 0; j < cols; j++) {
       fout21<<((int)matArr(i,j))<<",";
         }
          fout21<<endl;
			          }
     fout21.close();
*/
    //******It makes the nearest piexel along 0 point sohow up and become the edge pixel
    
//edge is equal to 50
      
 
 
   int maxVal=0;
        int pcounter=0;
//        #pragma omp parallel for reduction(+:pcounter)
// this is very inefficient on GPU (reduction kernel!) and serial on CPU !!!
	for(int i=0;i<rows;i++){
  //         #pragma omp parallel for
           for(int j=0;j<cols;j++){
             if(plots(i,j)==1){
                  plotx(pcounter)=i;
		  ploty(pcounter)=j;
                 // qx.push(i);
		 // qy.push(j);
		  pcounter++;
	     }
              

	   }


	}



//for(int i=0;i<)
	


int qcounter=0;
  

int i=0;
while(plotx(i)!=-1){
            //int crtX = qx.front(); qx.pop();
            //int crtY = qy.front(); qy.pop();

            int crtX=plotx(i);
            int crtY=ploty(i);
             i++;
             qcounter++;
            bool isBigger = true;//check
          // #pragma omp simd
            for(int h = 0; h < NUMSIZE; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= rows || nextY >= cols || matArr(nextX,nextY) == ZERO ) {
                    continue;
                }

                if( matArr(crtX,crtY) <= matArr(nextX,nextY)) {
                    isBigger = false;

                }
                //pick the max local value of some regions

                if( matArr(crtX,crtY) +1< matArr(nextX,nextY)) {
                    visArr(nextX,nextY) = true;
                    matArr(nextX,nextY) =  min((matArr(crtX,crtY)+1), 254);

                    //to get max value for difference between max value image and image
                    if(maxVal<=matArr(nextX,nextY)){
                       maxVal=matArr(nextX,nextY);

                    }
                     //to get max value for difference between max value image and image
 
                    plotx(pcounter)=nextX;
                    ploty(pcounter)=nextY;
                    pcounter++;

                }
                //fout4<<endl;
            }
           //find the max value in local area
            if(isBigger) {
                markers(crtX,crtY)=2;
             }
          }


/*
int allPixel=rows*cols;
int maxvalue=0;
//bool tmpVal=true;
//while((allPixel-boundcounter-zerocounter)!=0){
bool sign=true;
for(int h=0;h<6;h++){
bool isBigger = true;
//tmpVal=true;
#pragma omp parallel for
for(int i=0;i<rows;i++){
  for(int j=0;j<cols;j++){

   if(matArr(i,j)!=ZERO){
    for(int k = 0; k < 4; k++){
     if(arr4D[i][j][0][k]>-1 && arr4D[i][j][1][k]>-1 && arr4D[i][j][0][k]<rows && arr4D[i][j][1][k]<cols){
       if(visArr(arr4D[i][j][0][k],arr4D[i][j][1][k])==true&&sign&&matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])!=0&&matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])!=254&&!visArr(i,j)){//&&*visBool(i,j)){
               //if( matArr(i,j) > matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])) {
                 //   isBigger = false;

              //  }
              
              //tmptr=&tmpVal;
             if(matArr(i,j)> matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])){
  //              tmpVal=false;
                isBigger = false;
                //visBool(i,j) = &tmpVal;
		//visArr(i,j)=true;
		if(maxvalue<=matArr(arr4D[i][j][0][k],arr4D[i][j][1][k])){
                   maxvalue=matArr(arr4D[i][j][0][k],arr4D[i][j][1][k]);

		}
                matArr(i,j)=min((maxvalue+1), 254);
                boundcounter+=1;
                //curthreshold=matArr(i,j);
                }
            // if(maxVal<=matArr(i,j){
                  //     maxVal=matArr(i,j);

                  //  }
               else{
                     //isBigger = true;
                     markers(arr4D[i][j][0][k],arr4D[i][j][1][k])=2;
                  }
                
          
         }
       }
     }

//      if(isBigger) {
  //      markers(arr4D[i][j][0][k],arr4D[i][j][1][k])=2;
    //   }


      }
    }
    
  }

}

*/

//cout<<"left point:"<<allPixel-boundcounter-zerocounter<<endl;

//}

  //      string filename5="/opt/test5new.txt";
   //     ofstream fout5(filename5);
      /*  string filename21="/opt/test21.txt";
        ofstream fout21(filename21);
        string filename24="/opt/test24.txt";
        ofstream fout24(filename24);
        string filename25="/opt/test25.txt";
        ofstream fout25(filename25);
        */


/*
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {

             fout5<<((int)matArr(i,j))<<",";
             

        }
         fout5<<endl;
     }
     fout5.close();



*/



   pixelThreshold=pixelThreshold-1;

   int pnumThrshold=30;
   int handlingType=0;
   int neighbourType=0;
   removeholesopt(matArr,pnumThrshold,  handlingType, neighbourType, pixelThreshold,rows,cols);

      return matArr;
    }
