//---------------------------------------------------------------------------
#ifndef JSON_TEST_BASE_H_
#define JSON_TEST_BASE_H_
//---------------------------------------------------------------------------
#define MY_ASSERT(EXPRESSION) {if(true != (EXPRESSION)) { assert(0); return false;}}
//---------------------------------------------------------------------------
namespace test
{

class TestBase
{
public:
    TestBase()
    {
    }

    virtual ~TestBase()
    {
    }

    virtual bool DoTest() =0;
};

}// namespace test

//---------------------------------------------------------------------------
#endif// JSON_TEST_BASE_H_

