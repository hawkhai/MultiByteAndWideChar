#include "vlocale.h"
#include "vmbswcs.h"

void myprint(const char* tag, const wchar_t* pstr)
{
    printf("%8s\t{ ", tag);
    for (int i = 0; i < wcslen(pstr); i++) {
        wprintf(L"%#.x, ", unsigned int(pstr[i]));
    }
    wprintf(L"0 }\n");
}
void myprint(const char* tag, const char* pstr)
{
    printf("%8s\t { ", tag);
    for (int i = 0; i < strlen(pstr); i++) {
        printf("%#.x, ", unsigned char(pstr[i]));
    }
    printf("0 }\n");
}

int maintest()
{
    // const wchar_t* pwchello = L"Hello 世界！";
    wchar_t helloWc[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x4e16, 0x754c, 0xff01, 0, };
    unsigned char helloAcp[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0xca, 0xc0, 0xbd, 0xe7, 0xa3, 0xa1, 0, };
    unsigned char helloUtf8[] = { 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0xe4, 0xb8, 0x96, 0xe7, 0x95, 0x8c, 0xef, 0xbc, 0x81, 0, };

    std::string temp1 = wstrToStr(helloWc, LOCALE_CHINESE_CHINA_936);
    std::string temp2 = wstrToStr(helloWc, LOCALE_ZH_CN_UTF8);
    std::wstring temp3 = strToWstr((char*)helloAcp, LOCALE_CHINESE_CHINA_936);
    std::wstring temp4 = strToWstr((char*)helloUtf8, LOCALE_ZH_CN_UTF8);
    return 0;
}

int main()
{
    maintest();

    const wchar_t* pwchello = L"Hello 世界！";
    std::string utf8str = wstrToStr(pwchello, CP_UTF8);
    std::string acpstr = wstrToStr(pwchello, (unsigned int)CP_ACP);
    myprint("wchar_t", pwchello);
    myprint("CP_ACP", acpstr.c_str());
    myprint("CP_UTF8", utf8str.c_str());

    std::string temp1 = wstrToStr(pwchello, LOCALE_CHINESE_CHINA_936);
    myprint("wcstombs", temp1.c_str());

    std::string temp2 = wstrToStr(pwchello, LOCALE_ZH_CN_UTF8);
    myprint("wcstombs", temp2.c_str());

    std::wstring temp3 = strToWstr(acpstr.c_str(), LOCALE_CHINESE_CHINA_936);
    myprint("mbstowcs", temp3.c_str());

    std::wstring temp4 = strToWstr(utf8str.c_str(), LOCALE_ZH_CN_UTF8);
    myprint("mbstowcs", temp4.c_str());

    getchar();
    return 0;
}
