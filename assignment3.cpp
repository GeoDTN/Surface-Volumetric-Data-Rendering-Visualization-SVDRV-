#include <stdio.h>
#include <iostream>
#include <vector>
#include "opencv2/opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
using namespace cv;
int main(int argc, char *argv[] )
{
//Init Module for SIFT
cv::initModule_nonfree();
//INPUT
Mat query,reference;
query = imread(argv[1],1);
reference = imread(argv[2],1);
//1.DETECTION
std::vector<KeyPoint> kp_query, kp_reference;
//CODE HERE!
//Detect SIFT keypoints on the two input images
//OPENCV Functions: FeatureDetector::create, FeatureDetector::detect
//2.DRAW KEYPOINTS
Mat img_kp_query, img_kp_reference;
//CODE HERE!
//Draw detected keypoints, showing orientation and scale. Save the images.
//OPENCV Functions: drawKeypoints, imwrite
//3.DESCRIPTORS
Mat des_query, des_reference;
//CODE HERE!
//Extract SIFT descriptors (around the previous keypoints) on the two input
images
//OPENCV Functions: DescriptorExtractor::create, DescriptorExtractor::compute
//4.MATCHING
//Understand what I'm doing!!! NNDR matches are matches which respect the
"NNDR-test" (or "ratio test")
std::vector < std::vector <DMatch> > matches;
Ptr<DescriptorMatcher> descriptorMatcher = DescriptorMatcher::create(
"BruteForce" );
descriptorMatcher->knnMatch(des_query, des_reference, matches, 2);
//Neares-Neighbour-Distance-Ratio
std::vector<DMatch> NNDR_matches;
double NNDR_ratio = 0.85;
for(unsigned int i = 0; i < matches.size(); i++)
{
if(matches[i][0].distance <= NNDR_ratio*matches[i][1].distance)
{
NNDR_matches.push_back(matches[i][0]);
}
}
std::vector<int> query_idxs( NNDR_matches.size() ) ;
std::vector<int> reference_idxs( NNDR_matches.size() );
for( int i = 0; i < NNDR_matches.size(); i++ )
{
query_idxs[i] = NNDR_matches[i].queryIdx;
reference_idxs[i] = NNDR_matches[i].trainIdx;
}
//5.GEOMETRIC FILTERING AND TRANSFORMATION ESTIMATION
std::vector<Point2f> p_query,p_reference;
std::vector<DMatch> inlier_matches;
//Estimate the model.
Mat H;
KeyPoint::convert(kp_query, p_query, query_idxs ); //convert query keypoints
(with scale, orientation...) in 2D points (only containing the 2D coordinates).
KeyPoint::convert(kp_reference, p_reference, reference_idxs); //convert
reference keypoints (with scale, orientation...) in 2Dpoints (only containing the
2D coordinates).
//CODE HERE!!!
//OPENCV FUNCTION: findHomography
//H = ...
//Transform query points according to the model H
std::vector<Point2f> p_query_transform;
//CODE HERE!!!
//OPENCV FUNCTION: perspectiveTransform
//Geometric filtering (i.e finding "inliers").
//When I project query points from to the reference image according to the
estimated model
//they must be within a range of N pixels (N=RANSAC_threshold) with respect
to the matching reference keypoints
int RANSAC_threshold = 5;
if( !H.empty() )
{
for( int i = 0; i < p_query.size(); i++ )
{
if( norm(p_query_transform[i] - p_reference[i]) <= RANSAC_threshold )
// inlier
{
inlier_matches.push_back(NNDR_matches[i]);
}
}
}
//6.DRAW MATCHES
//Uncomment the following lines.
//If everything works, you'll see two images showing you the matches. Save the
images.
//(image 1: before Geometric Filtering; image 2: after Geometric Filtering)
Mat img_matches, img_inlier_matches;
namedWindow("Matches");
drawMatches( query, kp_query, reference, kp_reference, NNDR_matches,
img_matches,Scalar::all(-1),Scalar(255, 0, 0));
imshow("Matches",img_matches);
namedWindow("Inlier Matches");
drawMatches( query, kp_query, reference, kp_reference, inlier_matches,
img_inlier_matches,Scalar(0, 255, 0),Scalar(255, 0, 0));
imshow("Inlier Matches",img_inlier_matches);
waitKey(0);
return 0;
}
