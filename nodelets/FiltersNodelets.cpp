#include <nodelet/nodelet.h>
#include <pluginlib/class_list_macros.h>

#include "lidar_filters/LidarOutlierFiltering.h"

namespace nodelet_helper {

template<typename T>
class TNodelet : public nodelet::Nodelet
{
public:
    TNodelet(){}

    virtual void onInit()
    {
        m_nodeletInterface =  std::unique_ptr<T>(new T(getName(), getNodeHandle(), getPrivateNodeHandle()));
        m_nodeletInterface->initialize();
    }
private:
    std::unique_ptr<T> m_nodeletInterface;
};
}


namespace lidar_filters {
    using OutlierFilter = nodelet_helper::TNodelet<LidarOutlierFiltering>;
}

PLUGINLIB_EXPORT_CLASS(lidar_filters::OutlierFilter, nodelet::Nodelet)
