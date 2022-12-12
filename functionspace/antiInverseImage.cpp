
#include "../headerspace/WatershedAlg.h"
using namespace cv;

Array2D<int> &WatershedAlg::antiInverseImage(Array2D<int>&antimat,int &rows,int &cols) {
     
      //clock_t start2,end2;
    // double start3,end3;
      //start2=clock();
     // start3=omp_get_wtime();
       #pragma omp parallel for 
	for(int i = 0; i < rows; i++) {
       //   #pragma omp parallel for  
            for(int j = 0; j < cols; j++) {
                if( antimat(i,j) == ZERO ) {
                    antimat(i,j) = ZERO;
                } else {
                    antimat(i,j) = ONE;
                }
            }
        }

//	end2=clock();
  //      cout<<"The total time the algorithm used is :"<<(double)(end2 - start2)/CLOCKS_PER_SEC<<endl;

      //   end3=omp_get_wtime();
        // cout<<"The total time the parallel  algorithm used is :"<<(double)(end3 - start3)<<"s"<<endl;
        return antimat;
    }
