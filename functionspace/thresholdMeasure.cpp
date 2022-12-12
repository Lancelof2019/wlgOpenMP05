#include "../headerspace/WatershedAlg.h"
#include <cmath> 
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

Array2D<int> &WatershedAlg::thresholdMeasure(Mat &image,Array2D<int> &threshmat) {

 cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  5,3);

 #pragma omp parallel for
 for(int i=0;i<image.rows;i++){
     #pragma omp parallel for
	 for(int j=0;j<image.cols;j++){
         threshmat(i,j)=(int)image.at<uchar>(i,j);

	}
}
       



        return threshmat;
    }
