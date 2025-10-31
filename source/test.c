#include <iostream>
#include <bits/stdc++.h>

void DebugPrint(const char * const format, ... )
{
	char buf[100] = {0,};
    char buf2[100] = {0,};
	int n;
    std::va_list arglist;
    std::va_list arglist2;
    va_start( arglist, (char *) format );
    //char buf[MAX_LOG_SIZE] = {0,};
    va_copy(arglist2, arglist);
	n = vsprintf(buf, format, arglist);
	std::cout<<n<<" var"<<va_arg(arglist2, std::string)<<std::endl;
    //std::cout<<n<<std::endl;
    va_end( arglist );
	std::cout<<buf<<std::endl;
}


int main()
{
    char* ptr;
    std::cout<<"Hello World"<<std::endl;
    DebugPrint("%s %s", "str1", "1234");
    return 0;
}