//---------------------------------------------------------------------------
#ifndef JSON_TEST_TEST_JSON_H_
#define JSON_TEST_TEST_JSON_H_
//---------------------------------------------------------------------------
#include "test_base.h"
//---------------------------------------------------------------------------
namespace test
{

class TestJson : public TestBase
{
public:
    TestJson()
    {
    }
    virtual ~TestJson()
    {
    }

    virtual bool DoTest();

public:
    bool Test_Value_Base();
    bool Test_Value_Obj();
    bool Test_Value_Array();
    bool Test_Value_Overload();
    bool Test_CharReader();
    bool Test_TokenReader();
    bool Test_Json_KV();
    bool Test_Json_Array();
    bool Test_Json_Object();
    bool Test_Json_ArrayObject();
    bool Test_json_Format();
};

}//namespace test
//---------------------------------------------------------------------------
#endif //JSON_TEST_TEST_JSON_H_
