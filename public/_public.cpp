/*****************************************************************************************/
/*   程序名：_public.cpp，此程序是公共函数和类的定义文件。                       */                                                                     */
/*****************************************************************************************/

#include "_public.h"  

namespace idc
{

char *deletelchr(char* str, const int cc)
{
    if (str == nullptr) return nullptr;		// 如果传进来的是空地址，直接返回，防止程序崩溃。
	
    char* p = str;				   // 指向字符串的首地址。
    while (*p == cc)			// 遍历字符串，p将指向左边第一个不是cc的字符。
        p++;		

    memmove(str, p, strlen(str) - (p - str)+1);  // 把结尾标志0也拷过来。

    return str;
}

string& deletelchr(string &str, const int cc)   //c++
{
    auto pos=str.find_first_not_of(cc);    // 从字符串的左边查找第一个不是cc的字符的位置。

    if (pos!= 0) str.replace(0,pos,"");       // 把0-pos之间的字符串替换成空(不是空格)。

    return str;
}

char* deleterchr(char *str,const int cc)
{
    if (str == nullptr) return nullptr;	// 如果传进来的是空地址，直接返回，防止程序崩溃。
	
    char* p = str;				// 指向字符串的首地址。
    char* piscc = 0;		  // 右边全是字符cc的第一个位置。

    while (*p != 0)			   // 遍历字符串。
    {
        if (*p == cc && piscc == 0) piscc = p;		  // 记下字符cc的第一个位置。
        if (*p != cc) piscc = 0;								  // 只要当前字符不是cc，清空piscc。
        p++;		
	  }

	  if (piscc != 0) *piscc = 0;	// 把piscc位置的字符置为0，表示字符串已结束。

    return str;
}

string& deleterchr(string &str,const int cc)   //c++
{
    auto pos=str.find_last_not_of(cc);     // 从字符串的右边查找第一个不是cc的字符的位置。

    if (pos!= 0) str.erase(pos+1);            // 把pos之后的字符删掉。

    return str;
}

char* deletelrchr(char *str,const int cc)
{
    deletelchr(str,cc);
    deleterchr(str,cc);

    return str;
}

string& deletelrchr(string &str,const int cc)   //c++
{
    deletelchr(str,cc);
    deleterchr(str,cc);

    return str;
}

char* toupper(char *str)
{
    if (str == nullptr) return nullptr;

    char* p = str;				// 指向字符串的首地址。
    while (*p != 0)			  // 遍历字符串。
    {
        if ( (*p >= 'a') && (*p <= 'z') ) *p=*p - 32;
        p++;
    }

    return str;
}

string& toupper(string &str)   //c++    -32转大写
{
    for (auto &cc:str)  //遍历字符串str，将当前字符引用赋值给cc
    {
        if ( (cc >= 'a') && (cc <= 'z') ) cc=cc - 32;
    }

    return str;
}

char* tolower(char *str)
{
    if (str == nullptr) return nullptr;

    char* p = str;				// 指向字符串的首地址。
    while (*p != 0)			  // 遍历字符串。
    {
        if ( (*p >= 'A') && (*p <= 'Z') ) *p=*p + 32;
        p++;
    }

    return str;
}

string& tolower(string &str)   //c++    +32转小写
{
    for (auto &cc:str)
    {
        if ( (cc >= 'A') && (cc <= 'Z') ) cc=cc + 32;
    }

    return str;
}

bool replacestr(string &str,const string &str1,const string &str2,bool bloop)   //c++
{
    // 如果原字符串str或旧的内容str1为空，没有意义，不执行替换。
    if ( (str.length() == 0) || (str1.length() == 0) ) return false;
  
    // 如果bloop为true并且str2中包函了str1的内容，直接返回，因为会进入死循环，最终导致内存溢出。
    //string::npos和find()连用，找到了返回str1位置（不等）条件成立，没找到返回std::string::npos条件为假。
    if ( (bloop==true) && (str2.find(str1)!=string::npos) ) return false;   
                                        
    int pstart=0;      // 如果bloop==false，下一次执行替换的开始位置。
    int ppos=0;        // 本次需要替换的位置。

    while (true)
    {
        if (bloop == true)
            ppos=str.find(str1);                      // 每次从字符串的最左边开始查找子串str1。
        else
            ppos=str.find(str1,pstart);            // 从上次执行替换的位置后开始查找子串str1。

        if (ppos == string::npos) break;       // 如果没有找到子串str1。

        str.replace(ppos,str1.length(),str2);   // 把str1替换成str2。第二个参数是要替换的子字符串的长度

        if (bloop == false) pstart=ppos+str2.length();    // 下一次执行替换的开始位置往右移动。
    }

    return true;
}

bool replacestr(char *str,const string &str1,const string &str2,bool bloop)
{
    if (str == nullptr) return false;
  
    string strtemp(str);

    replacestr(strtemp,str1,str2,bloop);

    strtemp.copy(str,strtemp.length());
    str[strtemp.length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。

    return true;
}

char* picknumber(const string &src,char *dest,const bool bsigned,const bool bdot)
{
    if (dest==nullptr) return nullptr;    // 判断空指针。

    string strtemp=picknumber(src,bsigned,bdot);
    strtemp.copy(dest,strtemp.length());
    dest[strtemp.length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。

    return dest;
}

string& picknumber(const string &src,string &dest,const bool bsigned,const bool bdot)   //c++
{
    // 为了支持src和dest是同一变量的情况，定义str临时变量。
    string str;

    for (char cc:src)//逐个迭代 src 中的元素，并将每个元素赋值给变量 cc
    {
        // 判断是否提取符号。
        if ( (bsigned==true) && ( (cc == '+') || (cc == '-') ))
        {
            str.append(1,cc); continue; //append(追加字符数量，追加的字符)
        }

        // 判断是否提取小数点。
        if ( (bdot==true) && (cc == '.') )
        {
            str.append(1,cc); continue;
        }

        // 提取数字。
        if (isdigit(cc)) str.append(1,cc);
    }

    dest=str;

    return dest;
}

string picknumber(const string &src,const bool bsigned,const bool bdot) //c++，无dest参数
{
    string dest;
    picknumber(src,dest,bsigned,bdot);
    return dest;
}

bool matchstr(const string &str,const string &rules)
{
    // 如果匹配规则表达式的内容是空的，返回false。
    if (rules.length() == 0) return false;

    // 如果如果匹配规则表达式的内容是"*"，直接返回true。
    if (rules == "*") return true;

    int  ii,jj;
    int  pos1,pos2;
    ccmdstr cmdstr,cmdsubstr;

    string filename=str;
    string matchstr=rules;

    // 把字符串都转换成大写后再来比较
    toupper(filename);
    toupper(matchstr);

    cmdstr.splittocmd(matchstr,",");

    for (ii=0;ii<cmdstr.size();ii++)
    {
        // 如果为空，就一定要跳过，否则就会被匹配上。
        if (cmdstr[ii].empty() == true) continue;

        pos1=pos2=0;
        cmdsubstr.splittocmd(cmdstr[ii],"*");

        for (jj=0;jj<cmdsubstr.size();jj++)
        {
            // 如果是文件名的首部
            if (jj == 0)
                if (filename.substr(0,cmdsubstr[jj].length())!=cmdsubstr[jj]) break;

            // 如果是文件名的尾部
            if (jj == cmdsubstr.size()-1)
                if (filename.find(cmdsubstr[jj],filename.length()-cmdsubstr[jj].length()) == string::npos) break;

            pos2=filename.find(cmdsubstr[jj],pos1);

            if (pos2 == string::npos) break;

            pos1=pos2+cmdsubstr[jj].length();
        }

        if (jj==cmdsubstr.size()) return true;
    }

    return false;
}

ccmdstr::ccmdstr(const string &buffer,const string &sepstr,const bool bdelspace)//类名::成员
{
    splittocmd(buffer,sepstr,bdelspace);
}

// 把字符串拆分到m_cmdstr容器中。
// buffer：待拆分的字符串。
// sepstr：buffer字符串中字段内容的分隔符，注意，分隔符是字符串，如","、" "、"|"、"~!~"。
// bdelspace：是否删除拆分后的字段内容前后的空格，true-删除；false-不删除，缺省不删除。
void ccmdstr::splittocmd(const string &buffer,const string &sepstr,const bool bdelspace)
{
    // 清除所有的旧数据
    m_cmdstr.clear();

    int pos=0;        // 每次从buffer中查找分隔符的起始位置。
    int pos1=0;      // 从pos的位置开始，查找下一个分隔符的位置。
    string substr;   // 存放每次拆分出来的子串。

    while ( (pos1=buffer.find(sepstr,pos)) != string::npos)   // 从pos的位置开始，查找下一个分隔符的位置。
    {                                                         // find(要查找的字符串，起始位置)，返回找到的第一个字符串位置
        substr=buffer.substr(pos,pos1-pos);            // 从buffer中截取子串。substr(起始位置，子串长度)

        if (bdelspace == true) deletelrchr(substr);   // 删除子串前后的空格。

        m_cmdstr.push_back(std::move(substr));     // 把子串放入m_cmdstr容器中，调用string类的移动构造函数。

        pos=pos1+sepstr.length();                           // 下次从buffer中查找分隔符的起始位置后移。
    }

    // 处理最后一个字段（最后一个分隔符之后的内容）。
    substr=buffer.substr(pos);

    if (bdelspace == true) deletelrchr(substr);

    m_cmdstr.push_back(std::move(substr));

    return;
}

bool ccmdstr::getvalue(const int ii,string &value,const int ilen) const
{
    if (ii>=m_cmdstr.size()) return false;  //检查是否超出m_cmdstr容器大小

    // 从xml中截取数据项的内容。
    // 视频中是以下代码：
    // value=m_cmdstr[ii];
    // 改为：
    int itmplen=m_cmdstr[ii].length();
    if ( (ilen>0) && (ilen<itmplen) ) itmplen=ilen;
    value=m_cmdstr[ii].substr(0,itmplen);
  
    return true;
}

bool ccmdstr::getvalue(const int ii,char *value,const int len) const
{
    if ( (ii>=m_cmdstr.size()) || (value==nullptr) ) return false;  //检查是否超出m_cmdstr容器大小，value是否为空指针
    // 调用者必须保证value的空间足够，否则这里会内存溢出。
    if (len>0) memset(value,0,len+1);//memset(目标内存区域的起始地址、要设置的值、以及要设置的字节数)。将value指向的内存区域的前len+1个字节设为零
                                     //这里+1是因为字符串的末尾自动插入零终止符\0
    if ( (m_cmdstr[ii].length()<=(unsigned int)len) || (len==0) )
    {
        m_cmdstr[ii].copy(value,m_cmdstr[ii].length()); //copy(要拷贝的原字符串地址，要拷贝的字符数)
        value[m_cmdstr[ii].length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。手动添加字符串的终止符
    }
    else
    {
        m_cmdstr[ii].copy(value,len);
        value[len]=0;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,int &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try                                               // try-catch用于处理异常情况
    {
        value = stoi(picknumber(m_cmdstr[ii],true));  // stoi有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }
    
    return true;
}

bool ccmdstr::getvalue(const int ii,unsigned int &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
       value = stoi(picknumber(m_cmdstr[ii]));  // stoi有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,long &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stol(picknumber(m_cmdstr[ii],true));  // stol有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,unsigned long &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stoul(picknumber(m_cmdstr[ii]));  // stoul有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,double &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stod(picknumber(m_cmdstr[ii],true,true));  // stod有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,float &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    try
    {
        value = stof(picknumber(m_cmdstr[ii],true,true));  // stof有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool ccmdstr::getvalue(const int ii,bool &value) const
{
    if (ii>=m_cmdstr.size()) return false;

    string str=m_cmdstr[ii];
    toupper(str);     // 转换为大写来判断。目的：不区分大小写

    if (str=="TRUE") value=true; 
    else value=false;

    return true;
}

ccmdstr::~ccmdstr() //对析构函数的定义
{
    m_cmdstr.clear();
}

ostream& operator<<(ostream& out, const ccmdstr& cmdstr)
{
    for (int ii=0;ii<cmdstr.size();ii++)
        out << "[" << ii << "]=" << cmdstr[ii] << endl; //[0]=messi
                                                        //[1]=10
    return out;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,string  &value,const int ilen)
{
    string start="<"+fieldname+">";            // 数据项开始的标签。
    string end="</"+fieldname+">";            // 数据项结束的标签。

    int startp=xmlbuffer.find(start);               // 在xml中查找数据项开始的标签的位置。
    if (startp==string::npos) return false;         //没找到

    int endp=xmlbuffer.find(end);                 // 在xml中查找数据项结束的标签的位置。
    if (endp==string::npos) return false;         //没找到

    // 从xml中截取数据项的内容。
    // 视频中是以下代码：
    // value=xmlbuffer.substr(startp+start.length(),endp-startp-start.length());
    // 改为：
    int itmplen=endp-startp-start.length();
    if ( (ilen>0) && (ilen<itmplen) ) itmplen=ilen;
    value=xmlbuffer.substr(startp+start.length(),itmplen);

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,char *value,const int len)
{
    if (value==nullptr) return false;

    if (len>0) memset(value,0,len+1);   // 调用者必须保证value的空间足够，否则这里会内存溢出。

    string str;
    getxmlbuffer(xmlbuffer,fieldname,str);

    if ( (str.length()<=(unsigned int)len) || (len==0) )
    {
        str.copy(value,str.length());
        value[str.length()]=0;    // string的copy函数不会给C风格字符串的结尾加0。
    }
    else
    {
        str.copy(value,len);
        value[len]=0;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,bool &value)
{
    string str;
    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    toupper(str);    // 转换为大写来判断（也可以转换为小写，效果相同）。

    if (str=="TRUE") value=true; 
    else value=false;

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,int &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
       value = stoi(picknumber(str,true));  // stoi有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,unsigned int &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
       value = stoi(picknumber(str));  // stoi有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,long &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
        value = stol(picknumber(str,true));  // stol有异常，需要处理异常。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,unsigned long &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
        value = stoul(picknumber(str));  // stoul有异常，需要处理异常。不提取符号 + -
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,double &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
        value = stod(picknumber(str,true,true));  // stod有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

bool getxmlbuffer(const string &xmlbuffer,const string &fieldname,float &value)
{
    string str;

    if (getxmlbuffer(xmlbuffer,fieldname,str)==false) return false;

    try
    {
        value = stof(picknumber(str,true,true));  // stof有异常，需要处理异常。提取符号和小数点。
    }
    catch(const std::exception& e)
    {
        return false;
    }

    return true;
}

// 把整数表示的时间转换为字符串表示的时间。
// ttime：整数表示的时间。
// strtime：字符串表示的时间。
// fmt：输出字符串时间strtime的格式，与ttime函数的fmt参数相同，如果fmt的格式不正确，strtime将为空。
string& timetostr(const time_t ttime,string &strtime,const string &fmt)
{
    //struct tm sttm = *localtime ( &ttime );       // localtime非线程安全,返回指向静态内存区域的指针。
    struct tm sttm; localtime_r (&ttime,&sttm);     // localtime_r线程安全,输出指向struct tm结构体的指针
    sttm.tm_year=sttm.tm_year+1900;                 // tm.tm_year成员要加上1900。
    sttm.tm_mon++;                                  // sttm.tm_mon成员是从0开始的，要加1。

    // 缺省的时间格式。
    if ( (fmt=="") || (fmt=="yyyy-mm-dd hh24:mi:ss") )
    {
        strtime=sformat("%04u-%02u-%02u %02u:%02u:%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,\
                   sttm.tm_hour,sttm.tm_min,sttm.tm_sec);
        return strtime;
    }

    if (fmt=="yyyy-mm-dd hh24:mi")
    {
        strtime=sformat("%04u-%02u-%02u %02u:%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,\
                   sttm.tm_hour,sttm.tm_min);
        return strtime;
    }

    if (fmt=="yyyy-mm-dd hh24")
    {
        strtime=sformat("%04u-%02u-%02u %02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
        return strtime;
    }

    if (fmt=="yyyy-mm-dd")
    {
        strtime=sformat("%04u-%02u-%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
        return strtime;
    }

    if (fmt=="yyyy-mm")
    {
        strtime=sformat("%04u-%02u",sttm.tm_year,sttm.tm_mon); 
        return strtime;
    }

    if (fmt=="yyyymmddhh24miss") 
    {
        strtime=sformat("%04u%02u%02u%02u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,\
                   sttm.tm_hour,sttm.tm_min,sttm.tm_sec);
        return strtime;
    }

    if (fmt=="yyyymmddhh24mi")
    {
        strtime=sformat("%04u%02u%02u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,\
                   sttm.tm_hour,sttm.tm_min);
        return strtime;
    }

    if (fmt=="yyyymmddhh24")
    {
        strtime=sformat("%04u%02u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday,sttm.tm_hour);
        return strtime;
    }

    if (fmt=="yyyymmdd")
    {
        strtime=sformat("%04u%02u%02u",sttm.tm_year,sttm.tm_mon,sttm.tm_mday); 
        return strtime;
    }

    if (fmt=="hh24miss")
    {
        strtime=sformat("%02u%02u%02u",sttm.tm_hour,sttm.tm_min,sttm.tm_sec); 
        return strtime;
    }

    if (fmt=="hh24mi") 
    {
        strtime=sformat("%02u%02u",sttm.tm_hour,sttm.tm_min); 
        return strtime;
    }

    if (fmt=="hh24")
    {
        strtime=sformat("%02u",sttm.tm_hour); 
        return strtime;
    }

    if (fmt=="mi")
    {
        strtime=sformat("%02u",sttm.tm_min); 
        return strtime;
    }

    return strtime;
}

char* timetostr(const time_t ttime,char *strtime,const string &fmt)
{
    if (strtime==nullptr) return nullptr;    // 判断空指针。

    string str;
    timetostr(ttime,str,fmt);           // 直接调用string& timetostr(const time_t ttime,string &strtime,const string &fmt="");
    str.copy(strtime,str.length());
    strtime[str.length()]=0;           // string的copy函数不会给C风格字符串的结尾加0。

    return strtime;
}

string timetostr1(const time_t ttime,const string &fmt)
{
    string str;
    timetostr(ttime,str,fmt);           // 直接调用string& timetostr(const time_t ttime,string &strtime,const string &fmt="");
    return str;
}

string& ltime(string &strtime,const string &fmt,const int timetvl)
{
    time_t  timer;
    time(&timer );                          // 获取系统当前时间。

    timer=timer+timetvl;              // 加上时间的偏移量。

    timetostr(timer,strtime,fmt);   // 把整数表示的时间转换为字符串表示的时间。

    return strtime;
}

char* ltime(char *strtime,const string &fmt,const int timetvl)
{
    if (strtime==nullptr) return nullptr;    // 判断空指针。

    time_t  timer;
    time(&timer );                          // 获取系统当前时间。

    timer=timer+timetvl;              // 加上时间的偏移量。

    timetostr(timer,strtime,fmt);   // 把整数表示的时间转换为字符串表示的时间。

    return strtime;
}

string ltime1(const string &fmt,const int timetvl)
{
    string strtime;

    ltime(strtime,fmt,timetvl);   // 直接调用string& ltime(string &strtime,const string &fmt="",const int timetvl=0);

    return strtime;
}

bool addtime(const string &in_stime,string &out_stime,const int timetvl,const string &fmt)
{
    time_t  timer;

    // 把字符串表示的时间转换为整数表示的时间，方便运算。
    if ( (timer=strtotime(in_stime))==-1) { out_stime=""; return false; }

    timer=timer+timetvl;  // 时间运算。

    // 把整数表示的时间转换为字符串表示的时间。
    timetostr(timer,out_stime,fmt);

    return true;
}

bool addtime(const string &in_stime,char *out_stime,const int timetvl,const string &fmt)
{
    if (out_stime==nullptr) return false;    // 判断空指针。

    time_t  timer;

    // 把字符串表示的时间转换为整数表示的时间，方便运算。
    if ( (timer=strtotime(in_stime))==-1) { strcpy(out_stime,""); return false; }

    timer=timer+timetvl;  // 时间运算。

    // 把整数表示的时间转换为字符串表示的时间。
    timetostr(timer,out_stime,fmt);

    return true;
}

ctimer::ctimer()
{
    start();   // 计时开始。
}

// 计时开始。
void ctimer::start()
{
    memset(&m_start,0,sizeof(struct timeval));
    memset(&m_end,0,sizeof(struct timeval));

    gettimeofday(&m_start, 0);    // 获取当前时间，精确到微秒。
}

// 计算已逝去的时间，单位：秒，小数点后面是微秒
// 每调用一次本方法之后，自动调用Start方法重新开始计时。
double ctimer::elapsed()
{
    gettimeofday(&m_end,0);     // 获取当前时间作为计时结束的时间，精确到微秒。

    string str;
    str=sformat("%ld.%06ld",m_start.tv_sec,m_start.tv_usec);
    double dstart=stod(str);      // 把计时开始的时间点转换为double。

    str=sformat("%ld.%06ld",m_end.tv_sec,m_end.tv_usec);
    double dend=stod(str);       // 把计时结束的时间点转换为double。

    start();                                  // 重新开始计时。

    return dend-dstart;
}