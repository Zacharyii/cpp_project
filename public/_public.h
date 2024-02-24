/****************************************************************************************/
/*   程序名：_public.h，此程序是公共函数和类的声明文件。                                            */                                                                                                           */
/****************************************************************************************/
#ifndef __PUBLIC_HH
#define __PUBLIC_HH 1

#include "_cmpublic.h"    // C/C++、Linux编程常用的头文件，新的头文件请在_cmpublic.h中添加。

using namespace std;

namespace idc
{

///////////////////////////////////// /////////////////////////////////////
// C++风格字符串操作的若干函数。
// 删除字符串左边指定的字符。
// str：待处理的字符串。
// cc：需要删除的字符，缺省删除空格。
char*     deletelchr(char* str, const int cc=' ');  //c
string& deletelchr(string &str, const int cc=' ');  //c++

// 删除字符串右边指定的字符。
// str：待处理的字符串。
// cc：需要删除的字符，缺省删除空格。
char*     deleterchr(char *str,const int cc=' ');   //c
string& deleterchr(string &str,const int cc=' ');   //c++

// 删除字符串左右两边指定的字符。
// str：待处理的字符串。
// chr：需要删除的字符，缺省删除空格。
char*     deletelrchr(char *str,const int cc=' ');
string& deletelrchr(string &str,const int cc=' ');   //c++

// 把字符串中的小写字母转换成大写，忽略不是字母的字符。
// str：待转换的字符串。
char*     toupper(char *str);
string& toupper(string &str);   //c++

// 把字符串中的大写字母转换成小写，忽略不是字母的字符。
// str：待转换的字符串。
char*     tolower(char *str);
string& tolower(string &str);   //c++

// 字符串替换函数。
// 在字符串str中，如果存在字符串str1，就替换为字符串str2。
// str：待处理的字符串。
// str1：旧的内容。
// str2：新的内容。
// bloop：是否循环执行替换。
// 注意：
// 1、如果str2比str1要长，替换后str会变长，所以必须保证str有足够的空间，否则内存会溢出（C++风格字符串不存在这个问题）。
// 2、如果str2中包含了str1的内容，且bloop为true，这种做法存在逻辑错误，replacestr将什么也不做。
// 3、如果str2为空，表示删除str中str1的内容。
bool replacestr(char *str   ,const string &str1,const string &str2,const bool bloop=false);
bool replacestr(string &str,const string &str1,const string &str2,const bool bloop=false);

// 从一个字符串中提取出数字、符号和小数点，存放到另一个字符串中。
// src：原字符串。
// dest：目标字符串。
// bsigned：是否提取符号（+和-），true-包括；false-不包括。
// bdot：是否提取小数点（.），true-包括；false-不包括。
// 注意：src和dest可以是同一个变量。
char*     picknumber(const string &src,char *dest,const bool bsigned=false,const bool bdot=false);
string& picknumber(const string &src,string &dest,const bool bsigned=false,const bool bdot=false);   //c++
string    picknumber(const string &src,           const bool bsigned=false,const bool bdot=false); //  没有目标字符串参数

// 正则表达式，判断一个字符串是否匹配另一个字符串。
// str：需要判断的字符串，是精确表示的，如文件名"_public.cpp"。
// rules：匹配规则的表达式，用星号"*"代表任意字符，多个表达式之间用半角的逗号分隔，如"*.h,*.cpp"。
// 注意：1）str参数不需要支持"*"，rules参数支持"*"；2）函数在判断str是否匹配rules的时候，会忽略字母的大小写。
bool matchstr(const string &str,const string &rules);
///////////////////////////////////// /////////////////////////////////////

///////////////////////////////////// /////////////////////////////////////
// ccmdstr类用于拆分有分隔符的字符串。
// 字符串的格式为：字段内容1+分隔符+字段内容2+分隔符+字段内容3+分隔符+...+字段内容n。
// 例如："messi,10,striker,30,1.72,68.5,Barcelona"，这是足球运动员梅西的资料。
// 包括：姓名、球衣号码、场上位置、年龄、身高、体重和效力的俱乐部，字段之间用半角的逗号分隔。
class ccmdstr
{
private:
    vector<string> m_cmdstr;  // 存放拆分后的字段内容。

    ccmdstr(const ccmdstr &) = delete;                      // 禁用拷贝构造函数。
    ccmdstr &operator=(const ccmdstr &) = delete;  // 赋值函数=delete：禁用。
public:
    ccmdstr()  { } // 构造函数。
    ccmdstr(const string &buffer,const string &sepstr,const bool bdelspace=false);

    const string& operator[](int ii) const     // 重载[]运算符，可以像访问数组一样访问m_cmdstr成员。
    {
        return m_cmdstr[ii];
    }

    // 把字符串拆分到m_cmdstr容器中。
    // buffer：待拆分的字符串。
    // sepstr：buffer中采用的分隔符，注意，sepstr参数的数据类型不是字符，是字符串，如","、" "、"|"、"~!~"。
    // bdelspace：拆分后是否删除字段内容前后的空格，true-删除；false-不删除，缺省不删除。
    void splittocmd(const string &buffer,const string &sepstr,const bool bdelspace=false);

    // 获取拆分后字段的个数，即m_cmdstr容器的大小。
    int size() const { return m_cmdstr.size(); }
    int cmdcount() const { return m_cmdstr.size(); }      // 兼容以前的项目。

    // 从m_cmdstr容器获取字段内容。
    // ii：字段的顺序号，类似数组的下标，从0开始。
    // value：传入变量的地址，用于存放字段内容。
    // ilen：截取字段的长度
    // 返回值：true-成功；如果ii的取值超出了m_cmdstr容器的大小，返回失败。
    bool getvalue(const int ii,string &value,const int ilen=0) const;      // C++风格字符串。视频中没有第三个参数，加上第三个参数更好。
    bool getvalue(const int ii,char *value,const int ilen=0) const;          // C风格字符串，ilen缺省值为0-全部长度。 
    bool getvalue(const int ii,int  &value) const;                                    // int整数。
    bool getvalue(const int ii,unsigned int &value) const;                     // unsigned int整数。
    bool getvalue(const int ii,long &value) const;                                  // long整数。
    bool getvalue(const int ii,unsigned long &value) const;                  // unsigned long整数。
    bool getvalue(const int ii,double &value) const;                              // 双精度double。
    bool getvalue(const int ii,float &value) const;                                  // 单精度float。
    bool getvalue(const int ii,bool &value) const;                                  // bool型。

    ~ccmdstr(); // 析构函数。
};

// 重载<<运算符，输出ccmdstr::m_cmdstr中的内容，方便调试。
ostream& operator<<(ostream& out, const ccmdstr& cc);
///////////////////////////////////// /////////////////////////////////////

///////////////////////////////////// /////////////////////////////////////
// 解析xml格式字符串的函数族。
// xml格式的字符串的内容如下：
// <filename>/tmp/_public.h</filename><mtime>2020-01-01 12:20:35</mtime><size>18348</size>
// <filename>/tmp/_public.cpp</filename><mtime>2020-01-01 10:10:15</mtime><size>50945</size>
// xmlbuffer：待解析的xml格式字符串。
// fieldname：字段的标签名。
// value：传入变量的地址，用于存放字段内容，支持bool、int、insigned int、long、
//       unsigned long、double和char[]。
// 注意：当value参数的数据类型为char []时，必须保证value数组的内存足够，否则可能发生内存溢出的问题，
//           也可以用ilen参数限定获取字段内容的长度，ilen的缺省值为0，表示不限长度。
// 返回值：true-成功；如果fieldname参数指定的标签名不存在，返回失败。
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,string &value,const int ilen=0);    // 视频中没有第三个参数，加上第三个参数更好。
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,char *value,const int ilen=0);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,bool &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,int  &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,unsigned int &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,long &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,unsigned long &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,double &value);
bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,float &value);
/////// ////////////////////////////// /////////////////////////////////////

// C++格式化输出函数模板。
template< typename... Args >    //模板声明。Args 是一个模板参数包，可以接受零个或多个类型参数。
bool sformat(string &str,const char* fmt, Args... args ) 
{
    int len = snprintf( nullptr, 0, fmt, args... );      // 得到格式化输出后字符串的总长度。
                                                         //snprintf(目标缓冲区的指针,目标缓冲区的大小,格式化字符串,要格式化的数据)
    if (len < 0) return false;                                  // 如果调用snprintf失败，返回-1。
    if (len == 0) { str.clear(); return true; }            // 如果调用snprintf返回0，表示格式化输出的内容为空。

    str.resize(len);                                                 // 为string分配内存。
    snprintf(&str[0], len + 1, fmt, args... );           // linux平台第二个参数是len+1，windows平台是len。
    return true;
}

template< typename... Args >    //C++格式化输出重载版本模板
string sformat(const char* fmt, Args... args )  
{
    string str;

    int len = snprintf( nullptr, 0, fmt, args... );      // 得到格式化后字符串的长度。args...参数包展开语法
    if (len < 0) return str;              // 如果调用snprintf失败，返回-1。
    if (len == 0) return str;           // 如果调用snprintf返回0，表示格式化输出的内容为空。;

    str.resize(len);                                                // 为string分配内存。
    snprintf(&str[0], len + 1, fmt, args... );          // linux平台第二个参数是len+1，windows平台是len。
    return str;
}

///////////////////////////////////// /////////////////////////////////////
// 时间操作的若干函数。
/*
  取操作系统的时间（用字符串表示）。
  strtime：用于存放获取到的时间。
  timetvl：时间的偏移量，单位：秒，0是缺省值，表示当前时间，30表示当前时间30秒之后的时间点，-30表示当前时间30秒之前的时间点。
  fmt：输出时间的格式，fmt每部分的含义：yyyy-年份；mm-月份；dd-日期；hh24-小时；mi-分钟；ss-秒，
  缺省是"yyyy-mm-dd hh24:mi:ss"，目前支持以下格式：
  "yyyy-mm-dd hh24:mi:ss"
  "yyyymmddhh24miss"
  "yyyy-mm-dd"
  "yyyymmdd"
  "hh24:mi:ss"
  "hh24miss"
  "hh24:mi"
  "hh24mi"
  "hh24"
  "mi"
  注意：
    1）小时的表示方法是hh24，不是hh，这么做的目的是为了保持与数据库的时间表示方法一致；
    2）以上列出了常用的时间格式，如果不能满足你应用开发的需求，请修改源代码timetostr()函数增加更多的格式支持；
    3）调用函数的时候，如果fmt与上述格式都匹配，strtime的内容将为空。
    4）时间的年份是四位，其它的可能是一位和两位，如果不足两位，在前面补0。
*/
string& ltime(string &strtime,const string &fmt="",const int timetvl=0);
char *  ltime(char *strtime  ,const string &fmt="",const int timetvl=0);
// 为了避免重载的岐义，增加ltime1()函数。
string  ltime1(               const string &fmt="",const int timetvl=0);

// 把整数表示的时间转换为字符串表示的时间。
// ttime：整数表示的时间。
// strtime：字符串表示的时间。
// fmt：输出字符串时间strtime的格式，与ltime()函数的fmt参数相同，如果fmt的格式不正确，strtime将为空。
string& timetostr(const time_t ttime,string &strtime,const string &fmt="");
char*   timetostr(const time_t ttime,char   *strtime,const string &fmt="");
// 为了避免重载的岐义，增加timetostr1()函数。
string timetostr1(const time_t ttime,const string &fmt="");

// 把字符串表示的时间转换为整数表示的时间。
// strtime：字符串表示的时间，格式不限，但一定要包括yyyymmddhh24miss，一个都不能少，顺序也不能变。
// 返回值：整数表示的时间，如果strtime的格式不正确，返回-1。
time_t strtotime(const string &strtime);

// 把字符串表示的时间加上一个偏移的秒数后得到一个新的字符串表示的时间。
// in_stime：输入的字符串格式的时间，格式不限，但一定要包括yyyymmddhh24miss，一个都不能少，顺序也不能变。
// out_stime：输出的字符串格式的时间。
// timetvl：需要偏移的秒数，正数往后偏移，负数往前偏移。
// fmt：输出字符串时间out_stime的格式，与ltime()函数的fmt参数相同。
// 注意：in_stime和out_stime参数可以是同一个变量的地址，如果调用失败，out_stime的内容会清空。
// 返回值：true-成功，false-失败，如果返回失败，可以认为是in_stime的格式不正确。
bool addtime(const string &in_stime,char   *out_stime,const int timetvl,const string &fmt="");
bool addtime(const string &in_stime,string &out_stime,const int timetvl,const string &fmt="");
///////////////////////////////////// /////////////////////////////////////

///////////////////////////////////// /////////////////////////////////////
// 这是一个精确到微秒的计时器。
class ctimer
{
private:
    struct timeval m_start;    // 计时开始的时间点。
    struct timeval m_end;     // 计时结束的时间点。
public:
    ctimer();          // 构造函数中会调用start方法。

    void start();     // 开始计时。

    // 计算已逝去的时间，单位：秒，小数点后面是微秒。
    // 每调用一次本方法之后，自动调用start方法重新开始计时。
    double elapsed();
};
///////////////////////////////////////////////////////////////////////////////////////////////////
