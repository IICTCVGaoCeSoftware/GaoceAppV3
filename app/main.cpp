#include <boost/thread/thread.hpp>
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl\visualization\pcl_visualizer.h>

int
main(int argc, char* argv[])
{
  //------------------------------------ 加载点云
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(
    new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::PCDReader reader;

  pcl::PolygonMesh mesh;
  if (pcl::io::loadPLYFile("bun_zipper.ply", mesh) == -1) {
    std::cerr << "can't load point cloud file" << std::endl;
    return -1;
  }
  boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(
    new pcl::visualization::PCLVisualizer("cloud"));
  viewer->addPolygonMesh(mesh, "mesh");

  ///必选
  while (!viewer->wasStopped()) {
    viewer->spinOnce(100);
    std::this_thread::sleep_for(std::chrono::microseconds(100000)); //正确
  }
  //==============================================================================

  return 0;
}

