#ifndef LIDAROUTLIERFILTERING_H
#define LIDAROUTLIERFILTERING_H

#include "FilterBase.h"
#include "filters/filter_chain.h"

class LidarOutlierFiltering : public FilterBase
{
public:
    //using class constructor just to initialize ros related variables
    LidarOutlierFiltering(std::string name,
                          ros::NodeHandle nh,
                          ros::NodeHandle nhPrivate);

    ~LidarOutlierFiltering();
    //put initialization of class members here
    virtual void initialize();
protected:
    //put all filter processing code here and call the function in laser scan subscriber
    virtual void process(sensor_msgs::LaserScanPtr data);

private:
    void laserScanSubscriberCallback(const sensor_msgs::LaserScanConstPtr& msg);

private:
    filters::FilterChain<sensor_msgs::LaserScan> m_filterChain;
    ros::Subscriber m_scanSub;
    ros::Publisher  m_filteredScanPub;

};

#endif // LIDAROUTLIERFILTERING_H
