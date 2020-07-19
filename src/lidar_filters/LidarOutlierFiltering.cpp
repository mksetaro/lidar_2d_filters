#include "lidar_filters/LidarOutlierFiltering.h"

LidarOutlierFiltering::LidarOutlierFiltering(std::string name,
                                             ros::NodeHandle nh,
                                             ros::NodeHandle nhPrivate)
    : FilterBase(name,
                 nh,
                 nhPrivate),
      m_filterChain("sensor_msgs::LaserScan")
{

}

LidarOutlierFiltering::~LidarOutlierFiltering()
{
    ros::shutdown();
}

void LidarOutlierFiltering::initialize()
{

    std::string rawScanTopic;
    std::string filteredScanTopic;

    getHandle().param<std::string>("raw_scan_topic", rawScanTopic, "scan_raw");
    getHandle().param<std::string>("filtered_scan_topic", filteredScanTopic, "scan_filtered");

    bool res = m_filterChain.configure(getName(),
                                       getHandle());
    if(!res)
    {
        ROS_ERROR_STREAM("["<<__FUNCTION__<<"] -"<<"Filters Chain Initialization Fail");
        ros::shutdown();
        return;
    }

    m_scanSub = getHandle().subscribe(rawScanTopic.c_str(),
                                      1,
                                      &LidarOutlierFiltering::laserScanSubscriberCallback,
                                      this);

    m_filteredScanPub = getHandle().advertise<sensor_msgs::LaserScan>(filteredScanTopic.c_str(),
                                                                      1);
}

void LidarOutlierFiltering::process(sensor_msgs::LaserScanPtr data)
{
    m_filterChain.update (*data, *data);
    m_filteredScanPub.publish(data);
}

void LidarOutlierFiltering::laserScanSubscriberCallback(const sensor_msgs::LaserScanConstPtr& msg)
{
    if(!msg || msg->ranges.empty())
    {
        ROS_WARN_STREAM("["<<__FUNCTION__<<"] -"<<"Scan msg not valid!");
        return;
    }

    if(m_filteredScanPub.getNumSubscribers() == 0)
        return;

    sensor_msgs::LaserScanPtr filteredData(new sensor_msgs::LaserScan);
    *filteredData = *msg;
    process(filteredData);
}
