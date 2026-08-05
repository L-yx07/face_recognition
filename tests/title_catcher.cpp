// 捕获器：枚举所有可见窗口标题，打印 pid + Wide 标题（UTF-16 码元十六进制）。
// 用于核实 face_recognition.exe 实际创建的窗口标题是否乱码。
#include <windows.h>
#include <cstdio>

static BOOL CALLBACK enumProc(HWND hwnd, LPARAM) {
    if (!IsWindowVisible(hwnd)) return TRUE;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    wchar_t wbuf[256] = {0};
    GetWindowTextW(hwnd, wbuf, 256);
    if (wbuf[0]) {
        printf("pid=%lu title=", (unsigned long)pid);
        for (int i = 0; wbuf[i] && i < 50; i++) printf("%04x ", (unsigned)wbuf[i]);
        printf("\n");
    }
    return TRUE;
}

int main() {
    EnumWindows(enumProc, 0);
    return 0;
}
