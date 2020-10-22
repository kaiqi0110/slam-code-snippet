/*************************************************

Copyright:bupt
Author:kaiqi
email:kaiqigu0110@163.com
Date:2020-10-22
Description:根据两帧图像对应的匹配点计算基础矩阵，并利用该矩阵绘制出前10个特征点对应的极线
            题目来源： 计算机视觉life

**************************************************/

#include<iostream>
#include <vector>
#include<algorithm>
#include <unistd.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;


//自定义排序函数
bool sortFun(const  DMatch &p1, const  DMatch &p2) {
    return p1.distance < p2.distance;//升序排列
}

int main( int argc, char** argv )
{

    Mat image1 = imread( "./euroc1.png");
    Mat image2 = imread( "./euroc2.png");

    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();

    vector< KeyPoint > kp1, kp2;
    detector->detect( image1, kp1 );
    detector->detect( image2, kp2 );

    // 计算描述子
    Mat desp1, desp2;
    descriptor->compute( image1, kp1, desp1 );
    descriptor->compute( image2, kp2, desp2 );

    // 匹配描述子
    vector< DMatch > matches;
    BFMatcher matcher;
    matcher.match( desp1, desp2, matches );
    cout<<"Find total "<<matches.size()<<" matches."<<endl;
    Mat img_mathes;

    drawMatches(image1, kp1, image2, kp2, matches, img_mathes);

    // 筛选匹配对
    //冒泡排序法根据描述匹配距离排序
    sort(matches.begin(), matches.end(), sortFun);
    //选最相似的前30个点
    vector< DMatch > goodMatches;
    for ( int i=0; i<30; i++ ){
        goodMatches.push_back( matches[i] );
    }

    Mat img_goodmathes;
    drawMatches(image1, kp1, image2, kp2, goodMatches, img_goodmathes);
    imshow("goodMatches", img_goodmathes);


    vector< Point2f > pts1, pts2;
    for (size_t i=0; i<goodMatches.size(); i++)
    {
        pts1.push_back(kp1[goodMatches[i].queryIdx].pt);
        pts2.push_back(kp2[goodMatches[i].trainIdx].pt);
    }
    cout<<"Find total "<<goodMatches.size()<<" matches."<<endl;
    // 计算基础矩阵
    Mat F = findFundamentalMat(pts1, pts2, CV_FM_RANSAC);
    std::vector<Vec<float, 3>> epilines1, epilines2;
    //极线epilines 方程ax+by+c=0;
    computeCorrespondEpilines(pts1, 1, F, epilines1);
    computeCorrespondEpilines(pts2, 2, F, epilines2);

    //绘制出30个匹配点对应的对极线
    RNG rng;
    for (uint i = 0; i < 30; i++)
    {
        Scalar color = Scalar(rng(256), rng(256), rng(256));//随机产生颜色
        //在视图2中把关键点用圆圈画出来，然后再绘制在对应点处的外极线
        circle(image2, pts2[i], 3, color, 2);
        line(image2, Point(0, -epilines1[i][2] / epilines1[i][1]), Point(image2.cols, -(epilines1[i][2] + epilines1[i][0] * image2.cols) / epilines1[i][1]), color);

        //绘制外极线的时候，选择两个点，一个是x=0处的点，一个是x为图片宽度处
        circle(image1, pts1[i], 3, color, 2);
        line(image1, Point(0, -epilines2[i][2] / epilines2[i][1]), Point(image1.cols, -(epilines2[i][2] + epilines2[i][0] * image1.cols) / epilines2[i][1]), color);
    }


    // ----------- 结束你的代码 --------------//
    imshow("epiline1", image1);
    imshow("epiline2", image2);
    waitKey(0);
    return 0;
}

