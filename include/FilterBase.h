#ifndef IFILTERBASE_H
#define IFILTERBASE_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class FilterBase
{

public:
    FilterBase(std::string filterName,
                ros::NodeHandle& nh,
                ros::NodeHandle& nhPrivate)
                : m_filterName(filterName),
                  m_nh(nh),
                  m_nhPrivate(nhPrivate){}

    virtual ~FilterBase(){}

    ros::NodeHandle& getHandle() {return m_nh;}
    ros::NodeHandle& getPrivateHandle(){return m_nhPrivate;}
    const std::string getName(){return m_filterName;}

    virtual void initialize() = 0;

protected:
    virtual void process(sensor_msgs::LaserScanPtr data) = 0;

private:
    std::string m_filterName;
    ros::NodeHandle m_nh;
    ros::NodeHandle m_nhPrivate;
};
#endif // IFILTERBASE_H
