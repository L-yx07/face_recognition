// 验证：把 UTF-8 中文标题运行时转成 ANSI(GBK) 后传给 OpenCV，
// 窗口标题是否显示正确（WideTitle 应等于 4eba 8138 68c0 6d4b 6f14 793a）。
#include <opencv2/opencv.hpp>
#include <windows.h>
#include <string>
#include <cstdio>

static std::string utf8ToAnsi(const std::string& utf8) {
    if (utf8.empty()) return utf8;
    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    std::wstring wide(wlen, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &wide[0], wlen);
    int alen = WideCharToMultiByte(CP_ACP, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string ansi(alen, '\0');
    WideCharToMultiByte(CP_ACP, 0, wide.c_str(), -1, &ansi[0], alen, nullptr, nullptr);
    ansi.resize(alen - 1);
    return ansi;
}

static BOOL CALLBACK enumProc(HWND hwnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    wchar_t wbuf[256] = {0};
    GetWindowTextW(hwnd, wbuf, 256);
    printf("HWND=%p  WideTitle(hex):", (void*)hwnd);
    for (int i = 0; wbuf[i] && i < 40; i++) printf(" %04x", (unsigned)wbuf[i]);
    printf("\n");
    return TRUE;
}

int main() {
    std::string ansi = utf8ToAnsi("OpenCV DNN 人脸检测演示");
    printf("converted ANSI bytes:");
    for (unsigned char c : ansi) printf(" %02x", c);
    printf("\n");

    cv::namedWindow(ansi, cv::WINDOW_AUTOSIZE);
    cv::imshow(ansi, cv::Mat::zeros(120, 160, CV_8UC3));
    cv::waitKey(1);
    cv::waitKey(1);
    EnumWindows(enumProc, 0);

    printf("\n期望正确 WideTitle: 4f70 656e 4356 2044 4e4e 0020 4eba 8138 68c0 6d4b 6f14 793a\n");
    printf("(OpenCV DNN + 空格 + 人脸检测演示)\n");

    cv::waitKey(0);
    return 0;
}
