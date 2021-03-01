#include "vlocale.h"
#include "vmbswcs.h"

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

int main()
{
    const wchar_t* pwchello = L"Hello 世界！";
    std::string utf8str = wstrToStr(pwchello, CP_UTF8);
    std::string acpstr = wstrToStr(pwchello, (unsigned int)CP_ACP);
    myprint("wchar_t", pwchello);
    myprint("CP_ACP", acpstr.c_str());
    myprint("CP_UTF8", utf8str.c_str());

    std::string temp1 = wstrToStr(pwchello, "chinese-simplified");
    myprint("wcstombs", temp1.c_str());

    std::string temp2 = wstrToStr(pwchello, "zh_CN.utf8");
    myprint("wcstombs", temp2.c_str());

    std::wstring temp3 = strToWstr(acpstr.c_str(), "chinese-simplified");
    myprint("mbstowcs", temp3.c_str());

    std::wstring temp4 = strToWstr(utf8str.c_str(), "zh_CN.utf8");
    myprint("mbstowcs", temp4.c_str());

    getchar();
    return 0;
}
