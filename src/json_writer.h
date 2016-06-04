//---------------------------------------------------------------------------
#ifndef JSON_SRC_WRITER_H_
#define JSON_SRC_WRITER_H_
//---------------------------------------------------------------------------
#include <string>
//---------------------------------------------------------------------------
namespace json
{

class Value;

class JsonWriter
{
public:
    JsonWriter()
    {
    }
    ~JsonWriter()
    {
    }

    static std::string ToString(const Value& value, bool format=false);

private:
    static void ToString        (const Value& value, std::string& str, bool format, int deep);
    static void ObjectToString  (const Value& value, std::string& str, bool format, int deep);
    static void ArrayToString   (const Value& value, std::string& str, bool format, int deep);

    static void AddTab(std::string& str, int deep)
    {
        for(int i=0; i<deep; i++)
            str.push_back('\t');
    }

    static void AddString(const std::string& from, std::string& str);
};

}//namespace json

//---------------------------------------------------------------------------
#endif //JSON_SRC_WRITER_H_
