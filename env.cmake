# Eyestack 搜索目录，按需修改为不同的配置版本
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(Eyestack_DIR "D:/IICT/build-Eyestack-Desktop_Qt_5_15_2_MSVC2019_64bit-Debug/cmake")
else()
  set(Eyestack_DIR "D:/IICT/build-Eyestack-Desktop_Qt_5_15_2_MSVC2019_64bit-Release/cmake")
endif()

# OpenCV 搜索目录
set(OpenCV_DIR "F:/QT/OpenCv/opencv/build")

# Boost 搜索目录
set(BOOST_ROOT "D:/ICAC/boost_1_76_0")
set(Boost_INCLUDE_DIR "D:/ICAC/boost_1_76_0")

# 算法库搜索目录
set(GaoCeV3_DIR "D:/IICT/GaoCeV3-0.0.0-win64(3)/cmake")

# PCL
set(PCL_ROOT "D:/Program Files/PCL1.10.1")
