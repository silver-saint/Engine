#include "Win32Window.hpp"
#include <iostream>

namespace Engine
{
    Win32Window::Win32Window() noexcept : m_hInstance{GetModuleHandle(nullptr)}
    {
        WNDCLASSEX winClass;
        winClass = {};
        winClass.cbSize = sizeof(winClass);
        winClass.lpszClassName = "stuff";
        winClass.lpfnWndProc = HandleMessageSetup;
        winClass.cbClsExtra = 0;
        winClass.cbWndExtra = 0;
        winClass.hIcon = nullptr;
        winClass.hCursor = nullptr;
        winClass.hbrBackground = nullptr;
        winClass.lpszMenuName = nullptr;
        winClass.hIconSm = nullptr;
        winClass.style = CS_VREDRAW | CS_HREDRAW;
        winClass.hInstance = m_hInstance;
        RegisterClassEx(&winClass);
    }

    ResultValueType<WindowStatus>Win32Window::Init()
    {

        RECT windowRect = {};
        windowRect.left = 100;
        windowRect.bottom = 100;
        windowRect.right = windowRect.left + m_RenderSpec.width;
        windowRect.top = windowRect.bottom + m_RenderSpec.height;
        AdjustWindowRect(&windowRect, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
        m_hWnd = CreateWindow("stuff", m_RenderSpec.AppName.data(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                            windowRect.right - windowRect.left, windowRect.top - windowRect.bottom, nullptr, nullptr,
                            m_hInstance, this);
        if (!m_hWnd)
        {
            MessageBox(m_hWnd, "Couldn't init hwnd", "Error!", MB_OK);
            return WindowStatus::Fail;
        }
        ShowWindow(m_hWnd, SW_SHOWDEFAULT);
        return WindowStatus::Created;
    }

    Win32Window::~Win32Window() 
    { 
        
        DestroyWindow(m_hWnd);
    }

    LRESULT CALLBACK Win32Window::HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        if (msg == WM_NCCREATE)
        {
            //extract the ptr and link the pointer to the window procedure.
            const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
            Win32Window* const pWnd = static_cast<Win32Window*>(pCreate->lpCreateParams);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
            SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Win32Window::HandleMessageThunk));

            return pWnd->HandleMessage(hwnd, msg, wParam, lParam);
        }
        //if we get a message before NCCREATE we handle it here
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    LRESULT CALLBACK Win32Window::HandleMessageThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        Win32Window* const pWnd = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        return pWnd->HandleMessage(hwnd, msg, wParam, lParam);
    }

    LRESULT Win32Window::HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
    {
        switch (msg)
        {
            case WM_CLOSE:
                if (MessageBox(hwnd, "Do you really want to close?", "Engine", MB_OKCANCEL) == IDOK)
                {
                    PostQuitMessage(0);
                }
                break;
            case WM_KILLFOCUS:
                // kbd.ClearState();
                break;
            case WM_KEYDOWN:
                //  kbd.onKeyPressed(static_cast<u8>(wParam));
                break;
            case WM_KEYUP:
                //  kbd.onKeyReleased(static_cast<u8>(wParam));
                break;
            case WM_CHAR:
                //  kbd.onChar(static_cast<u8>(wParam));
                break;
            case WM_PAINT:
                break;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    std::optional<i32> Win32Window::ProcessMessages()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) { return msg.wParam; }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return {};
    }
}// namespace Engine