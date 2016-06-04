//---------------------------------------------------------------------------
#include <string>
#include "token_reader.h"
//---------------------------------------------------------------------------
namespace json
{

TokenReader::TokenType TokenReader::ReadNextToken()
{
    SkipWhitespace();

    if(!char_reader_.HasMore())
        return DOCUMENT_END;

    char c = char_reader_.Peek();
    switch(c)
    {
        case '{':
            char_reader_.Next();
            return OBJECT_BEGIN;

        case '}':
            char_reader_.Next();
            return OBJECT_END;

        case '[':
            char_reader_.Next();
            return ARRAY_BEGIN;

        case ']':
            char_reader_.Next();
            return ARRAY_END;

        case ':':
            char_reader_.Next();
            return SEP_COLON;

        case ',':
            char_reader_.Next();
            return SEP_COMMA;

        case '\"':
            char_reader_.Next();
            return STRING;

        case 'n':
//            char_reader_.Next();
            return NUL;

        case 't':
        case 'f':
//           char_reader_.Next();
            return BOOLEAN;

        case '-':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
//            char_reader_.Next();
            return NUMBER;
    }

    return INVALID;
}
//---------------------------------------------------------------------------
bool TokenReader::ReadString(std::string& str)
{
    std::string value;
    for(;;)
    {
        if(!char_reader_.HasMore())
            break;

        char c = char_reader_.Next();
        switch(c)
        {
            case '\\'://转义字符
                {
                if(!char_reader_.HasMore())
                    break;

                char esc = char_reader_.Next();
                switch(esc)
                {
                    case '\"':
                        str.push_back('\"');
                        break;

                    case '\\':
                        str.push_back('\\');
                        break;

                    case '/':
                        str.push_back('/');
                        break;

                    case 'b':
                        str.push_back('\b');
                        break;

                    case 'f'://换页
                        str.push_back('\f');
                        break;

                    case 'n':
                        str.push_back('\n');
                        break;

                    case 'r':
                        str.push_back('\r');
                        break;

                    case 't':
                        str.push_back('\t');
                        break;

                    case 'u'://unicode字符
                        //todo
                        break;

                    default:
                        return false;
                }
                }
                break;

            case '\"':  //结束
                return true;
            
            default:    //普通字符
                str.push_back(c);
                break;
        }
    }

    //不是从 case '\"'返回的,说明字符串读取不完整,返回失败
    return false;
}
//---------------------------------------------------------------------------
bool TokenReader::ReadNumber(std::string& number, Value::ValueType& type)
{
    //数值分为2个部分构成
    //整数部分和小数部分(不支持指数表示)
    
    char        c;
    bool        has_sign    = false;
    bool        has_decimal = false;
    for(;;)
    {
        if(char_reader_.HasMore())
        {
            c = char_reader_.Peek();

            //检查是否是数字,如果不是数字,则有可能该数字不是正确的数字(例如:123a),这种情况留給上一层处理
            if(false == CheckNumber(c))
                break;
        }
        else
            break;

        switch(c)
        {
            case '-':
                //符号位不是第0位
                if(0 < number.size())
                    return false;

                has_sign = true;
                number.push_back(c);
                char_reader_.Next();
                break;

            case '.':
                //已经出现过.了
                if(has_decimal)
                    return false;

                has_decimal = true;
                number.push_back(c);
                char_reader_.Next();
                
                break;

            case 'E':
            case 'e':
                //todo 指数
                break;

            default:
                number.push_back(c);
                char_reader_.Next();
                break;
        }
    }

    //如果是有符号,则str值必须大于1才表示有值
    if(true == has_sign)
    {
        if(1 >= number.size())
            return false;
    }
    else
    {
        if(number.empty())
            return false;
    }

    //值是小数
    if(true == has_decimal)
    {
        type = Value::TYPE_REAL;
        return true;
    }

    if(true == has_sign)    //值是有符号整数
    {
        //数字不能以0开头
        if((2<number.size()) && ('0'==number[1]))
            return false;

        type = Value::TYPE_INT;
    }
    else                    //无符号整数
    {
        //数字不能以0开头
        if((1<number.size()) &&('0'==number[0]))
            return false;

        type = Value::TYPE_UINT;
    }

    return true;
}
//---------------------------------------------------------------------------
bool TokenReader::ReadBoolean(bool& boolean)
{
    //第一个字符必须是't' or 'f'

    char c = char_reader_.Peek();
    switch(c)
    {
        case 't':   //"true"=4
            {
            if(4 > char_reader_.Remain())
                return false;

            std::string value = char_reader_.Next(4);
            if("true" != value)
                return false;

            boolean = true;
            }

            break;

        case 'f':   //"false"=5
            {
            if(5 > char_reader_.Remain())
                return false;

            std::string value = char_reader_.Next(5);
            if("false" != value)
                return false;

            boolean = false;
            }

            break;

        default:
            return false;
    }

    return true;
}
//---------------------------------------------------------------------------
bool TokenReader::ReadNull()
{
    //"null"=4
    if(4 > char_reader_.Remain())
        return false;

    std::string value = char_reader_.Next(4);
    if("null" != value)
        return false;

    return true;
}
//---------------------------------------------------------------------------
void TokenReader::SkipWhitespace()
{
    for(;;)
    {
        if(!char_reader_.HasMore())
            break;

        char c = char_reader_.Peek();
        if(!IsWhitespace(c))
            break;

        char_reader_.Next();
    }

    return;
}
//---------------------------------------------------------------------------
}//namespace json
