/**
 * @file
 * @author Neyko Naydenov ( neyko641@gmail.com )
 * @brief 
 * @version 1.0
 * @date 
 * 
 * @section DESCRIPTION
 * 
 * Win32 implementation of the Window class.
 */


#include <Platform/WindowInstance.hpp>
#include <types.hpp>
#include <optional>
#include "Renderer/Window.hpp"

namespace Engine
{
 
    class Win32Window: public Window
    {
    public:
        Win32Window() noexcept;
        ResultValueType <WindowStatus>Init() noexcept;
        Win32Window(const Win32Window&) = delete;
        Win32Window& operator=(const Win32Window&) = delete;
        ~Win32Window();

        static LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMessageThunk(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMessage(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static std::optional<i32> ProcessMessages();

    public:
        //  Keyboard kbd;

    private:
        HWND m_hWnd;
        HINSTANCE m_hInstance;
        RendererSpec m_RenderSpec;
    };
}// namespace engine