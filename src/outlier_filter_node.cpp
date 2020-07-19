#include "lidar_filters/LidarOutlierFiltering.h"

int main(int argc, char **argv)
{
    std::string nodeName = "outlier_filter_node";
    ros::init(argc, argv, nodeName);
    ros::NodeHandle nh;
    ros::NodeHandle nhPrivate("~");

    LidarOutlierFiltering filter(nodeName, nh, nhPrivate);
    filter.initialize();

    ROS_INFO_STREAM(nodeName << " - initialized");
    ros::spin();
}
