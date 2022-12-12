#include "../headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(Array2D<int> &src,int &pnumThrshold, int &handlingType, int &neighbourType,int pixelThreshold,int &rows,int &cols)  {
   

    int RemoveCount=0;       

    Mat Pointlabel(rows,cols, CV_8UC1,Scalar::all(255) );  

 

	#pragma omp parallel for 
        for(int i = 0; i < rows; ++i)  {    
    
             #pragma omp parallel for 
            for(int j = 0; j < cols; ++j) {    
                 if(src(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 
               
                 }
      
            }    
        }  



   if (!contours.empty() && !hierarchy.empty())	{

           #pragma omp parallel for      
	   for(int z=0;z<contours.size();z++){
		
		       cv::Rect countourposition = cv::boundingRect(Mat(contours.at(z)));      	
		       double area = contourArea(contours.at(z));
			
			if (area < pnumThrshold) 
			{
						
				#pragma omp parallel for
				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
		
				{
					//uchar *output_data = dst.ptr<uchar>(i);
					#pragma omp parallel for
         
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
			
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
