#define BOOST_TEST_MODULE Test_2
#include <boost/test/unit_test.hpp>

#include "StatisReport.hpp"
#include <Eyestack/Framework.hpp>

struct GlobalFixture
{
  Eyestack::Framework::Application app{ 0, nullptr };

  GlobalFixture() {}
  ~GlobalFixture() {}

  void setup() {}
  void teardown() {}
};

BOOST_TEST_GLOBAL_FIXTURE(GlobalFixture);

BOOST_AUTO_TEST_CASE(case_1)
{
  struct RecordIter : public StatisReport::RecordIter
  {
    int i = 0;

    virtual bool next(StatisReport::Record* record) noexcept override
    {
      if (++i > 100)
        return false;
      record->_timestamp = QDateTime::currentDateTime();

      static QRandomGenerator rg;
      auto size = rg.bounded(10);
      record->_results.resize(size);
      for (int i = 0; i < size; ++i) {
        auto x = rg.bounded(50), y = rg.bounded(50);
        auto w = rg.bounded(x, 100 - x), h = rg.bounded(y, 100 - y);

        record->_results[i]._rect = { x, y, w, h };
        record->_results[i]._area = rg.generateDouble();
        record->_results[i]._circumference = rg.generateDouble();
        record->_results[i]._maxLen = 3 * rg.generateDouble();
      }

      return true;
    }
  } recIter;

  StatisReport sr;
  sr.set_statistics(recIter);

  QPrintPreviewDialog dlg;
  dlg.connect(&dlg,
              &QPrintPreviewDialog::paintRequested,
              &dlg,
              [&](QPrinter* printer) { sr.print(*printer); });

  dlg.exec();
}
