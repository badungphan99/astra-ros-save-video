#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
	
cv::VideoWriter videoC("outColor.avi",CV_FOURCC('X','2','6','4'),30, cv::Size(640,480),true);

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    cv::Mat imageColor;
    try
    {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        imageColor = cv_ptr->image;
        videoC.write(imageColor);
        cv::imshow("View", imageColor);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "video_save_color");
    ros::NodeHandle nh;
    
    cv::namedWindow("View");
    
    cv::startWindowThread();

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("/camera/rgb/image_raw", 1, imageCallback);
    
    ros::spin();
    cv::destroyWindow("View");
}
