enable_testing()

include(CTest)

# 本项目使用 Boost 的单元测试框架
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

if (NOT Boost_USE_STATIC_LIBS)
  add_compile_definitions(BOOST_TEST_DYN_LINK)
endif()



add_executable(Test_1 test_1.cpp GaoCeSkeleton.hpp GaoCeSkeleton.cpp)

target_link_libraries(Test_1 PUBLIC
  _PCH Boost::unit_test_framework APP
)

target_precompile_headers(Test_1 REUSE_FROM _PCH)

add_test(Test_1 Test_1)



add_executable(Test_2 test_2.cpp)

target_link_libraries(Test_2 PRIVATE
  _PCH Boost::unit_test_framework APP
)

target_precompile_headers(Test_2 REUSE_FROM _PCH)

add_test(Test_2 Test_2)
