find_package(Eyestack REQUIRED)

find_package(GaoCe REQUIRED)

find_package(Qt5 REQUIRED COMPONENTS PrintSupport Charts)
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

find_package(PCL 1.10 REQUIRED)
find_package(VTK REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
add_definitions(${PCL_DEFINITIONS})
