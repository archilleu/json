//---------------------------------------------------------------------------
#ifndef JSON_TEST_MAIN_H_
#define JSON_TEST_MAIN_H_
//---------------------------------------------------------------------------
#include <unordered_map>
#include <memory>
//---------------------------------------------------------------------------
namespace test
{

class TestBase;

class TestMain
{
public:
    TestMain();
    ~TestMain();

    void StartTest();

private:
    typedef std::unordered_map<std::string, std::shared_ptr<TestBase>> TestObj;
    TestObj test_obj_list_;
};

}//namespace test

//---------------------------------------------------------------------------
#endif// JSON_TEST_MAIN_H_
