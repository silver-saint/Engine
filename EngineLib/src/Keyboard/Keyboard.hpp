/**
 * @file
 * @author Neyko Naydenov ( neyko641@gmail.com )
 * @brief 
 * @version 1.0
 * @date 
 * 
 * @section DESCRIPTION
 * 
 * implementation of the Keyboard class.
 */

#pragma once
#include <queue>
#include <bitset>
#include <types.hpp>

namespace Engine
{
    class Event
    {
    public:
        enum class Type
        {
            Invalid,
            Pressed,
            Released
        };
        Event() noexcept;
        Event(Type type, u8 code) noexcept;
        bool isPressed() const noexcept;
        bool isReleased() const noexcept;
        bool isValid() const noexcept;
        u8 GetCode() const noexcept;

    private:
        Type type;
        u8 code;
    };

    class Keyboard
    {
        friend class Win32Window;
        friend class Event;

    public:
        Keyboard() = default;
        Keyboard(const Keyboard&) = delete;
        Keyboard& operator=(const Keyboard&) = delete;

    public:
        bool KeyIsPressed(u8 code) const noexcept { return keyStates[code]; }

        Event ReadKey() noexcept;
        bool KeyIsEmpty() const noexcept;
        void ClearKey() noexcept;
        char ReadChar() noexcept;
        bool CharIsEmpty() noexcept;
        void ClearChar() noexcept;
        void Clear() noexcept;
        void EnableAutorepeat() noexcept;
        void DisableAutorepeat() noexcept;
        bool AutorepeatIsEnabled() const noexcept;

    private:
        void onKeyPressed(u8 keycode) noexcept;
        void onKeyReleased(u8 keycode) noexcept;
        void onChar(char ch) noexcept;
        void ClearState() noexcept;
        template <typename T>
        static void TrimBuffer(std::queue<T>& buffer) noexcept;

    private:
        static constexpr u32 sKeys = 256u;
        static constexpr u32 sBufferSize = 16u;
        std::bitset<sKeys> keyStates;
        std::queue<Event> keyBuffer;
        std::queue<char> charBuffer;
        bool autoRepeatEnabled = {false};
    };

    template <typename T>
    inline void Keyboard::TrimBuffer(std::queue<T>& buffer) noexcept
    {
        while (buffer.size() > sBufferSize) { buffer.pop(); }
    }
}// namespace Engine