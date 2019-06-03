#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
	
cv::VideoWriter videoC("outDepth.avi",CV_FOURCC('X','2','6','4'),30, cv::Size(640,480),false);

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat imageDepth,depth;
        cv_ptr = cv_bridge::toCvCopy(msg);
        depth = cv_ptr->image;
        depth.convertTo(depth, CV_8UC1,255.0f/2500.0f);
        cv::imwrite("abc.png",depth);
        cv::imshow("View", depth);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "video_save_depth");
    ros::NodeHandle nh;
    
    cv::namedWindow("View");
    
    cv::startWindowThread();

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw", 1, imageCallback);
    
    ros::spin();
    cv::destroyWindow("View");
}
