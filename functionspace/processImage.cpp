#include "../headerspace/WatershedAlg.h"
using namespace cv;
void WatershedAlg::processImage(Mat &image,Mat &duplImage,Array2D<int> &threshmat0,Array2D<int> & markers,Array2D<bool> &visArr,Array1D &plotx,Array1D &ploty,Array2D<int>& plots,Array2D<bool> &inprioq,Array2D<int> &markerMap,Array2D<int> &temp,Array2D<int>& nextSet,int**** arr4D,int**** mat4D,Bool2D &visBool) {

       image = makeImageGrayScale(image);


       vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
       image = erosion(image, erosionTargetThree);

       // int** __restrict threshmat;
       
        threshmat0= thresholdMeasure(image,threshmat0);

       //int** __restrict antimat;
       threshmat0=antiInverseImage(threshmat0,image.rows,image.cols);

	//int** __restrict matimage;
       threshmat0=distanceTransform(threshmat0,markers,image.rows,image.cols,plots,visArr,plotx,ploty,arr4D,mat4D,visBool);
       image = watershed(threshmat0, markers,duplImage,image.rows,image.cols,inprioq,markerMap,temp,nextSet);
  //    cv::imshow("watershed result",image);
  // cv::waitKey(0);

    }
