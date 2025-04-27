#include <utils/top.h>

#ifdef _WIN32
std::wstring Utf8ToWide(const std::string& utf8Str) {
	int wideStrLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
	std::wstring wideStr(wideStrLen, 0);
	MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, &wideStr[0], wideStrLen);
	return wideStr;
}

std::string UTF8ToANSI(const std::string& utf8Str) {
    // 先将 UTF-8 转换为宽字符（UTF-16）
    int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, nullptr, 0);
    wchar_t* wideStr = new wchar_t[wideLen];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wideStr, wideLen);

    // 将宽字符（UTF-16）转换为 ANSI
    int ansiLen = WideCharToMultiByte(CP_ACP, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    char* ansiStr = new char[ansiLen];
    WideCharToMultiByte(CP_ACP, 0, wideStr, -1, ansiStr, ansiLen, nullptr, nullptr);

    std::string result(ansiStr);
    delete[] wideStr;
    delete[] ansiStr;
    return result;
}

std::string GBKToUTF8(const std::string& gbkStr) {
    // 将 GBK 转换为宽字符（UTF-16）
    int wideLen = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, nullptr, 0);
    wchar_t* wideStr = new wchar_t[wideLen];
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, wideStr, wideLen);

    // 将宽字符（UTF-16）转换为 UTF-8
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, nullptr, 0, nullptr, nullptr);
    char* utf8Str = new char[utf8Len];
    WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, utf8Len, nullptr, nullptr);

    std::string result(utf8Str);
    delete[] wideStr;
    delete[] utf8Str;
    return result;
}
#endif

void Error(std::string str)
{
	ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), str.c_str());
}

void SubInfo(std::string str)
{
	ImGui::TextColored(ImVec4(.6f, .6f, .6f, 1.0f), str.c_str());
}

void Info(std::string str) {
	ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), str.c_str());
}

