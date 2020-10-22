/*************************************************

Copyright:bupt
Author:kaiqi
email:kaiqigu0110@163.com
Date:2020-10-22
Description:实现倾斜角度重投影到正视平面效果
            题目来源： 计算机视觉life
            
**************************************************/

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct userdata{
    Mat im;
    vector<Point2f> points;
};


void mouseHandler(int event, int x, int y, int flags, void* data_ptr)
{
    static int x_last,y_last;
    if  ( event == EVENT_LBUTTONDOWN )
    {
        userdata *data = ((userdata *) data_ptr);
        circle(data->im, Point(x,y),50,Scalar(0,255,255), 50, CV_AA);
        if (data->points.size() < 4)
        {
            data->points.push_back(Point2f(x,y));
        }
        if (data->points.size() == 4){
            line(data->im, data->points[0],data->points[1], Scalar(0,0,255),20);
            line(data->im, data->points[1],data->points[2], Scalar(0,0,255),20);
            line(data->im, data->points[2],data->points[3], Scalar(0,0,255),20);
            line(data->im, data->points[3],data->points[0], Scalar(0,0,255),20);
        }
        imshow("Image", data->im);

    }
}



int main( int argc, char** argv)
{
    // Destination image
    //Mat im_dst = imread("times-square.jpg");
    Mat im_dst = imread("./paper.jpg");

    // Set data for mouse handler
    Mat im_temp = im_dst.clone();
    userdata data;
    data.im = im_temp;

    //show the image
    namedWindow("Image",0);
    imshow("Image", im_temp);

    cout << "Click on four corners of a billboard and then press ENTER" << endl;
    //set the callback function for any mouse event
    setMouseCallback("Image", mouseHandler, &data);
    waitKey(0);

    Mat im_src_per;
    im_src_per = Mat::zeros(im_dst.rows*1.5, im_dst.cols, im_dst.type());

    Size size = im_src_per.size();
    int height = size.height;
    int width = size.width;
    // Create a vector of points.
    vector<Point2f> pts_src;
    pts_src.push_back(Point2f(0,0));
    pts_src.push_back(Point2f(width - 1, 0));
    pts_src.push_back(Point2f(width - 1, height -1));
    pts_src.push_back(Point2f(0, height - 1 ));

    // 计算原图四个角点和目标图区域对应角点的 Homography
    Mat Homography = findHomography(data.points, pts_src);

    // 用H对原图做变换
    warpPerspective(im_dst, im_src_per, Homography,im_src_per.size());
    namedWindow("warpPerspective",0);
    imshow("warpPerspective", im_src_per);
    waitKey(0);

    // Display image.
    imshow("Image", im_dst);
    waitKey(0);

    return 0;
}
