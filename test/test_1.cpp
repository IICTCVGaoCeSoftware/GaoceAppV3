#define BOOST_TEST_MODULE Test_1
#include <boost/test/unit_test.hpp>

#include "GaoCeSkeleton.hpp"
#include "Worker.hpp"
#include "wrapper.hpp"

/**
 * @brief 全局初始化
 */
struct GlobalFixture
{
  esf::Application app{ 0, nullptr };

  GlobalFixture() {}
  ~GlobalFixture() {}

  void setup()
  {
    es::Gencom::ginit();
    es::Com_MVS::ginit();
  }

  void teardown() {}
};

BOOST_TEST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_CASE(case_1)
{
  auto& app = *esf::Application::instance();

  auto worker = new Worker();
  worker->_algo = std::make_unique<GaoCeSkeleton>();
  app.reg_worker(worker);

  std::function<cv::Mat()> getInput = []() -> cv::Mat {
    return cv::Mat::zeros(1000, 1000, CV_8UC1);
  };
  worker->_getInput = getInput;

  GaoCeConfigSubUi _cSubUi{ *worker };
  {
    _cSubUi._MVScal._getInput = _cSubUi._DLPcal._getInput =
      _cSubUi._reConWin._getInput = getInput;
  }
  app.reg_sub_ui(_cSubUi);

  BOOST_CHECK(app.exec() == 0);
}
