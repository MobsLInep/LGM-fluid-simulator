#include "gpu/renderer.h"
#include <iostream>
#include <vector>
#include <windows.h>

namespace lbm::gpu {

bool Renderer::initialize(int w, int h) { W = w; H = h; return true; }

bool Renderer::setWindow(void* hwnd) { window = hwnd; return window != nullptr; }

void Renderer::renderFrame(const lbm::LBMGrid& g) {
    if (!window) return;
    std::vector<unsigned char> rgba(static_cast<std::size_t>(W * H * 4), 0);
    for (int y = 0; y < H; ++y) {
        for (int x = 0; x < W; ++x) {
            auto u = g.velocity(x,y);
            double s = u.magnitude();
            double v = s * 4.0;
            if (v < 0.0) v = 0.0; if (v > 1.0) v = 1.0;
            unsigned char c = static_cast<unsigned char>(v * 255.0);
            std::size_t idx = static_cast<std::size_t>((y * W + x) * 4);
            rgba[idx + 0] = c;
            rgba[idx + 1] = c;
            rgba[idx + 2] = c;
            rgba[idx + 3] = 255;
        }
    }
    BITMAPINFO bmi{};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = W;
    bmi.bmiHeader.biHeight = -H;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    HDC hdc = GetDC((HWND)window);
    StretchDIBits(hdc, 0, 0, W, H, 0, 0, W, H, rgba.data(), &bmi, DIB_RGB_COLORS, SRCCOPY);
    ReleaseDC((HWND)window, hdc);
}

}
