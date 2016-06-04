//---------------------------------------------------------------------------
#include "test_main.h"
#include "test_base.h"
#include "test_json.h"
#include <iostream>
//---------------------------------------------------------------------------
using namespace test;
//---------------------------------------------------------------------------
TestMain::TestMain()
{
#define TEST_ADD(TypeName)   test_obj_list_[#TypeName]=std::shared_ptr<TestBase>(dynamic_cast<TestBase*>(new TypeName))

   TEST_ADD(TestJson);
    
#undef TEST_ADD
}
//---------------------------------------------------------------------------
TestMain::~TestMain()
{
    test_obj_list_.clear();
}

void TestMain::StartTest()
{
    std::cout << "验证没有bug后请使用 查看是否有内存问题: valgrind --tool=memcheck --leak-check=full ./test" << std::endl;
    std::cout << "lsof -p pid 验证句柄" << std::endl;

    for(auto iter=test_obj_list_.begin(); test_obj_list_.end()!=iter; ++iter)
    {
        std::cout <<"----------------------------------------------------------->"<< std::endl;
        std::cout << "test:" << iter->first << " start..." << std::endl;
        bool result = iter->second->DoTest();
        //todo count time
        std::cout << "test:" << iter->first << " end, result:" << result << std::endl;
    }
}
//---------------------------------------------------------------------------
