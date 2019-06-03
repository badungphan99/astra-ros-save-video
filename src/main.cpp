#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
	
cv::VideoWriter videoD("outDepth.avi",CV_FOURCC('X','2','6','4'),30, cv::Size(640,480),false);
cv::VideoWriter videoC("outColor.avi",CV_FOURCC('X','2','6','4'),30, cv::Size(640,480),true);

void imageDepth(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat imageDepth,depth;
        cv_ptr = cv_bridge::toCvCopy(msg);
        depth = cv_ptr->image;
        depth.convertTo(depth, CV_8UC1,255.0f/2500.0f);
        videoD.write(depth);
        cv::imshow("Depth", depth);
}

void imageColor(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat imageColor;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        imageColor = cv_ptr->image;
        videoC.write(imageColor);
        cv::imshow("Color", imageColor);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "video_save");
    ros::NodeHandle nh;
    //ros::NodeHandle d;
    
    cv::namedWindow("Depth");
    
    cv::startWindowThread();

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/camera/depth/image_raw", 1, imageDepth);
    
    cv::namedWindow("Color");
    
    cv::startWindowThread();
    // image_transport::ImageTransport it(d);
    image_transport::Subscriber subd = it.subscribe("/camera/rgb/image_raw", 1, imageColor);

    ros::spin();
    cv::destroyWindow("Depth");
    cv::destroyWindow("Color");
}
