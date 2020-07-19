cmake_minimum_required(VERSION 2.8.3)
project(lidar_2d_filters)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    sensor_msgs
    nodelet)

catkin_package(
    INCLUDE_DIRS include
    LIBRARIES LidarFilters LidarFiltersNodelets
    CATKIN_DEPENDS roscpp nodelet pluginlib sensor_msgs
    )

include_directories(
    include
    ${catkin_INCLUDE_DIRS}
    )

add_library(LidarFilters
    src/lidar_filters/LidarOutlierFiltering.cpp)
target_link_libraries(LidarFilters ${catkin_LIBRARIES})

add_library(LidarFiltersNodelets
    nodelets/FiltersNodelets.cpp)

target_link_libraries(LidarFiltersNodelets LidarFilters ${catkin_LIBRARIES})
add_dependencies(LidarFiltersNodelets LidarFilters)

if(catkin_EXPORTED_LIBRARIES)
    add_dependencies(LidarFiltersNodelets ${catkin_EXPORTED_LIBRARIES})
endif()

add_executable(outlier_filter_node src/outlier_filter_node.cpp)
target_link_libraries(outlier_filter_node LidarFilters ${catkin_LIBRARIES})
add_dependencies(outlier_filter_node LidarFilters)

install(TARGETS LidarFilters LidarFiltersNodelets
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION})

install(FILES nodelets/nodelets.xml
    DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
