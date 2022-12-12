#include "../headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(Array2D<int> &src,int &pnumThrshold, int &handlingType, int &neighbourType,int pixelThreshold,int &rows,int &cols)  {
   
   
 //  cv::imshow("distanceTransform before remove holes",src);
 //  cv::waitKey(0);
    int RemoveCount=0;       
    //string filename33="/opt/test33.txt";
   // ofstream fout33(filename33);
 //   string filename34="/opt/test34.txt";
 //   ofstream fout34(filename34);
   //  string filename35="/opt/test35.txt";
  //  ofstream fout35(filename35);
   // vector<Point> NeihborPos;
    //queue<int> qx, qy;
    //vector<Point>pixbuffer;
    Mat Pointlabel(rows,cols, CV_8UC1,Scalar::all(255) );  
/*    int **Pointlabel=new int*[src.rows];
    for(int i=0;i<src.rows;i++){
     Pointlabel[i]=new int[src.cols];

    }
  */  
 
 
       // cout<<"removing holes start. "<<endl;  
        //#pragma omp parallel for collapse(2) simd nowait
	#pragma omp parallel for 
        for(int i = 0; i < rows; ++i)  {    
           // uchar* iData = src.ptr<uchar>(i);  
           // uchar* iLabel = Pointlabel.ptr<uchar>(i);  
             #pragma omp parallel for 
            for(int j = 0; j < cols; ++j) {    
                 if(src(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 
               
                 }
               // if (iData[j] > pixelThreshold)    
              //  {    
                   // iLabel[j] = 3;   
              //  }    
            }    
        }  

//**

 //  imshow("prepration for contours",Pointlabel);
//
  //  cv::waitKey(0);

   // Mat dulpPointlabel;
    //Pointlabel.copyTo(dulpPointlabel);
    vector<vector<Point>> contours; 
  // cout<<"The rows of contour :"<< 
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
   // Mat imageContours=Mat::zeros(Pointlabel.size(),CV_8UC1);  
   // Mat contouroutput=Mat::zeros(Pointlabel.size(),CV_8UC1);  
    Point p=Point(0,0);
//    cout<<"The rows of contour :"<<contours.size()<<endl;
  //  cout<<"The lines of contour"<<contours[67].size()<<endl;


   if (!contours.empty() && !hierarchy.empty())	{
	//	vector<vector<Point> >::const_iterator itc = contours.begin();
   // cout<<"The number of size of contours"<<contours.size()<<endl;
	
		//while (itc != contours.end()) {
           #pragma omp parallel for      
	   for(int z=0;z<contours.size();z++){

			
		//	cv::Rect countourposition = cv::boundingRect(Mat(*itc));
		        cv::Rect countourposition = cv::boundingRect(Mat(contours.at(z)));      	
		//	double area = contourArea(*itc);
		        double area = contourArea(contours.at(z));
		//	int y_ordi=countourposition.y;
		//	int h_ordi=countourposition.height;
		//	int x_ordi=countourposition.x;
		//	int w_ordi=countourposition.width;
		
			if (area < pnumThrshold) 
			{
				//#pragma omp parallel for collapse(2) simd nowait
				
				#pragma omp parallel for
				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
			
			     //  for (int i = y_ordi; i < y_ordi+h_ordi; i++)
				{
					//uchar *output_data = dst.ptr<uchar>(i);
					#pragma omp parallel for
         
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
				//	for (int j = x_ordi; j < x_ordi+w_ordi; j++) 
					{
						
						if ((int)Pointlabel.at<uchar>(i,j) == 255) 
						{
						    Pointlabel.at<uchar>(i,j) = 2;
                                                    src(i,j)=pixelThreshold;

						}
					}
				}
			}
			//itc++;
		}
	}


 }
