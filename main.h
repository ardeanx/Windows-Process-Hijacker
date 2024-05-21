#pragma once
#pragma once


#define HJWND_PROGRAM L"notepad.exe"
#define MAX_CLASSNAME 255
#define MAX_WNDNAME 255
struct WindowsFinderParams {
    DWORD pidOwner = NULL;
    std::wstring wndClassName = L"";
    std::wstring wndName = L"";
    RECT pos = { 0, 0, 0, 0 };
    POINT res = { 0, 0 };
    float percentAllScreens = 0.0f;
    float percentMainScreen = 0.0f;
    DWORD style = NULL;
    DWORD styleEx = NULL;
    bool satisfyAllCriteria = false;
    std::vector<HWND> hwnds;
};
HWND HiJackNotepadWindow();
std::vector<DWORD> GetPIDs(std::wstring targetProcessName);
std::vector<HWND> WindowsFinder(WindowsFinderParams params);
BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam);
void TerminateNotepad();
HWND HiJackNotepadWindow()
{
    HWND hwndHiHjacked = NULL;
    std::vector<DWORD> existingNotepads = GetPIDs(HJWND_PROGRAM);
    if (!existingNotepads.empty()) {
        for (int i(0); i < existingNotepads.size(); ++i) {
            HANDLE hOldProcess = OpenProcess(PROCESS_TERMINATE, FALSE, existingNotepads[i]);
            TerminateProcess(hOldProcess, 0);
            CloseHandle(hOldProcess);
        }
    }
    system("start notepad");
    std::vector<DWORD> notepads = GetPIDs(HJWND_PROGRAM);
    if (notepads.empty() || notepads.size() > 1)
    {
        return hwndHiHjacked;
    }
    WindowsFinderParams params;
    params.pidOwner = notepads[0];
    params.style = WS_VISIBLE;
    params.satisfyAllCriteria = true;
    std::vector<HWND> hwnds;
    int attempt = 0;
    while (hwndHiHjacked == NULL || attempt > 50000) {
        Sleep(100);
        hwnds = WindowsFinder(params);
        if (hwnds.size() > 1)
        {
            return hwndHiHjacked;
        }
        hwndHiHjacked = hwnds[0];
        ++attempt;
    }
    if (!hwndHiHjacked)
    {
        return hwndHiHjacked;
    }
    SetMenu(hwndHiHjacked, NULL);
    return hwndHiHjacked;
}
void TerminateNotepad()
{
    std::vector<DWORD> existingNotepads = GetPIDs(HJWND_PROGRAM);
    if (!existingNotepads.empty()) {
        for (int i(0); i < existingNotepads.size(); ++i) {
            HANDLE hOldProcess = OpenProcess(PROCESS_TERMINATE, FALSE, existingNotepads[i]);
            TerminateProcess(hOldProcess, 0);
            CloseHandle(hOldProcess);
        }
    }
}

(BELUM SELESAI)
