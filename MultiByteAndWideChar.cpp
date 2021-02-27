// MultiByteAndWideChar.cpp: 定义应用程序的入口点。
//
#include "MultiByteAndWideChar.h"
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wchar.h>

//
//  Code Page Default Values.
//  Please Use Unicode, either UTF-16 (as in WCHAR) or UTF-8 (code page CP_ACP)
//
#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations
#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation
std::wstring to_wpath(const std::string& text, unsigned codepage = CP_UTF8)
{
    const int length = ::MultiByteToWideChar(codepage, 0, text.c_str(), (int)text.size(), NULL, 0);
    if (length > 0) {
        std::wstring wt;
        wt.resize(length);
        if (0 != ::MultiByteToWideChar(codepage, 0, text.c_str(), (int)text.size(), &wt[0], (int)wt.size()))
            return wt;
    }
    return L"";
}
std::string from_wpath(const std::wstring& text, unsigned codepage = CP_UTF8)
{
    const int length = ::WideCharToMultiByte(codepage, 0, text.c_str(), (int)text.size(), NULL, 0, NULL, NULL);
    if (length > 0) {
        std::string str;
        str.resize(length);
        if (0 != ::WideCharToMultiByte(codepage, 0, text.c_str(), (int)text.size(), &str[0], (int)str.size(), NULL, NULL))
            return str;
    }
    return "";
}

void myprint(const char* tag, const wchar_t* pstr)
{
    printf("%8s\t", tag);
    for (int i = 0; i < wcslen(pstr); i++) {
        wprintf(L"%x ", unsigned int(pstr[i]));
    }
    wprintf(L"\r\n");
}
void myprint(const char* tag, const char* pstr)
{
    printf("%8s\t", tag);
    for (int i = 0; i < strlen(pstr); i++) {
        printf("%x ", unsigned int(pstr[i]));
    }
    printf("\r\n");
}

int trytrans(char const* locale, const wchar_t* pwchello) {
    char* localeInfo = setlocale(LC_ALL, locale);
    printf("Locale information set to %s\n", localeInfo);

    int requiredSize = wcstombs(NULL, pwchello, 0);
    unsigned char* pmbhello = (unsigned char*)malloc(requiredSize + 1);
    size_t size = wcstombs((char*)pmbhello, pwchello, requiredSize + 1);
    if (size == (size_t)(-1)) {
        return 1;
    }
    myprint("wcstombs", (const char*)pmbhello);
    free(pmbhello);
    return 0;
}

int trytrans(char const* locale, const char* pmbhello) {
    char* localeInfo = setlocale(LC_ALL, locale);
    printf("Locale information set to %s\n", localeInfo);

    int requiredSize = mbstowcs(NULL, pmbhello, 0);
    wchar_t* pwc = (wchar_t*)malloc((requiredSize + 1) * sizeof(wchar_t));
    size_t size = mbstowcs(pwc, (char const*)pmbhello, requiredSize + 1); // C4996
    if (size == (size_t)(-1)) {
        return 1;
    }
    myprint("mbstowcs", pwc);
    free(pwc);
    return 0;
}

inline std::string wstr2str(const std::wstring& xsistr)
{
    if (xsistr.empty()) {
        return "";
    }

    size_t c = ::wcstombs(0, xsistr.c_str(), 0);
    char* tmp = new char[c + 1];
    ::wcstombs(tmp, xsistr.c_str(), c);
    tmp[c] = '\0';

    std::string ret(tmp);
    delete[] tmp;
    return ret;
}

inline std::wstring str2wstr(const std::string& str)
{
    if (str.empty()) {
        return L"";
    }

    size_t c = ::mbstowcs(0, str.c_str(), 0);
    wchar_t* tmp = new wchar_t[c + 1];
    ::mbstowcs(tmp, str.c_str(), c);
    tmp[c] = '\0';

    std::wstring ret(tmp);
    delete[] tmp;
    return ret;
}

int mainz()
{
    const wchar_t* pwchello = L"Hello 世界！";
    std::wstring text = pwchello;
    std::string utf8str = from_wpath(text, CP_UTF8);
    std::string acpstr = from_wpath(text, CP_ACP);
    myprint("Lwchar_t", text.c_str());
    myprint("CP_UTF8", utf8str.c_str());
    myprint("CP_ACP", acpstr.c_str());

    // Locale information set to Chinese_China.936
    trytrans("chinese-simplified", pwchello);

    // Locale information set to zh_CN.utf8
    trytrans("zh_CN.utf8", pwchello);

    //setlocale(LC_CTYPE, "chinese-traditional"); // 认为输入的 MBS是 Big5 编码
    //setlocale(LC_CTYPE, "chinese-simplified");  // 设置输出的 MBS 为 GBK 编码
    trytrans("chinese-simplified", acpstr.c_str());
    trytrans("zh_CN.utf8", utf8str.c_str());
    return 0;
}

int main()
{
    mainz();
    // 将文件保存为 utf8 编码
    char const* source = "Hello 世界！";

#define BUFFER_SIZE (128)
    wchar_t wc_out[BUFFER_SIZE];
    char    mb_out[BUFFER_SIZE];
    printf("\n%s", source);     // 输出不正常

    // 认为输入的 MBS 是 ?? 编码
    //setlocale(LC_CTYPE, "chinese-traditional");
    setlocale(LC_CTYPE, "chinese-simplified");
    mbstowcs(wc_out, source, BUFFER_SIZE);
    wprintf(L"\n%s", wc_out);     // 正常输出

    // 设置输出的 MBS 为 GBK 编码
    setlocale(LC_CTYPE, "chinese-simplified");
    wcstombs(mb_out, wc_out, BUFFER_SIZE);
    printf("\n%s", mb_out);     // 正常输出
}
