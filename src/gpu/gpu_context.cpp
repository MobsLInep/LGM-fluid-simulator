#include "gpu/gpu_context.h"
#include <windows.h>

namespace lbm::gpu {

bool GPUContext::initialize(int w, int h, const std::string& title) {
    width = w;
    height = h;
    running = true;
    device = nullptr;
    queue = nullptr;
    WNDCLASSA wc{};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = GetModuleHandleA(nullptr);
    wc.lpszClassName = "LBMWnd";
    RegisterClassA(&wc);
    HWND hwnd = CreateWindowExA(0, wc.lpszClassName, title.c_str(), WS_OVERLAPPEDWINDOW,
                                CW_USEDEFAULT, CW_USEDEFAULT, width, height,
                                nullptr, nullptr, wc.hInstance, nullptr);
    ShowWindow(hwnd, SW_SHOW);
    window = hwnd;
    return true;
}

bool GPUContext::isRunning() const { return running; }
void* GPUContext::getDevice() const { return device; }
void* GPUContext::getQueue() const { return queue; }
void* GPUContext::getWindow() const { return window; }

bool GPUContext::pump() {
    MSG msg;
    while (PeekMessageA(&msg, (HWND)window, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_CLOSE || msg.message == WM_QUIT) { running = false; }
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return running;
}

}
