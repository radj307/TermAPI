/**
 * @file TermAPI.hpp
 * @author radj307
 * @brief	This header-only library contains cross-platform ANSI escape sequence helper functions designed to be used with iostreams
 */
#pragma once
#include <TERMAPI.h>
#include <sysarch.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ColorLib.hpp>

#if CPP < 20
#error TermAPI.hpp Requires at least C++20
#endif

#ifdef OS_WIN // Include functions for enabling ANSI escape sequences
#include <TermAPIWin.hpp>
#endif

// update notice: all TermAPI functions have been moved to the sys::term namespace!
namespace sys::term {
#pragma region CursorPositioning

	inline void cursorPosUp(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uA", n);
	}
	inline void cursorPosDown(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uB", n);
	}
	inline void cursorPosRight(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uC", n);
	}
	inline void cursorPosLeft(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uD", n);
	}
	inline void cursorPosPrevious(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uF", n);
	}
	inline void cursorPosNext(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uE", n);
	}

	inline void cursorPosSave()
	{
		printf(SEQ_ESC "7");
	}
	inline void cursorPosLoad()
	{
		printf(SEQ_ESC "8");
	}
	/**
	 * @brief Sets the cursor's position to a given x/y coordinate, in relation to the origin point top left corner (0,0)
	 * @param x			- Target horizontal-axis position, measured in characters of the screen buffer
	 * @param y			- Target vertical-axis position, measured in characters of the screen buffer
	 */
	inline void cursorPosSet(unsigned x, unsigned y)
	{
		printf(SEQ_ESC SEQ_BRACKET "%u;%uH", y, x);
	}
	template<class T> requires std::is_integral_v<T>
	struct CursorPosSet {
		const T _x, _y;

		constexpr CursorPosSet(T x, T y) : _x{ std::move(x) }, _y{ std::move(y) } {}
		constexpr CursorPosSet(std::pair<T, T> xyPr) : _x{ std::move(xyPr.first) }, _y{ std::move(xyPr.second) } {}

		friend std::ostream& operator<<(std::ostream& os, const CursorPosSet& obj)
		{
			os << SEQ_ESC << SEQ_BRACKET << obj._y << ';' << obj._x << 'H';
			return os;
		}
	};
	/**
	 * @brief This causes the cursor's current position to be emitted to the STDIN stream.
	 */
	inline void cursorPosGet()
	{
		printf(SEQ_ESC SEQ_BRACKET "6n");
	}
	inline std::istream& cursorPosGet(std::istream& is)
	{
		cursorPosGet();
		return is;
	}
#pragma endregion CursorPositioning

#pragma region Viewport
	inline void scrollUp(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uS", n);
	}
	inline void scrollDown(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uT", n);
	}
#pragma endregion Viewport

#pragma region ScreenBuffer
	/**
	 * @brief This swaps to an alternative screen buffer. It is recommended to use this for applications that require user input, as it prevents overwriting the user's current session in the screen buffer and eliminates the need for clearing the screen.
	 */
	inline void screenBufferAlternate()
	{
		printf(SEQ_ESC SEQ_BRACKET "?1049h");
	}
	inline std::ostream& screenBufferAlternate(std::ostream& os)
	{
		screenBufferAlternate();
		return os;
	}
	/**
	 * @brief Sets the screen buffer back to main, it is (required) to call this before the program exits if screenBufferAlternate() was called.
	 */
	inline void screenBufferMain()
	{
		printf(SEQ_ESC SEQ_BRACKET "?1049l");
	}
	inline std::ostream& screenBufferMain(std::ostream& os)
	{
		screenBufferMain();
		return os;
	}
#pragma endregion ScreenBuffer

#pragma region TextModification
	inline void insertChar(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%u@", n);
	}
	// delete characters to the right (fore) of the cursor.
	inline void deleteNext(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uP", n);
	}
	// delete characters to the left (back) of the cursor.
	inline void deleteLast(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uX", n);
	}

	inline void insertLine(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uL", n);
	}
	inline void deleteLine(unsigned n = 1u)
	{
		printf(SEQ_ESC SEQ_BRACKET "%uM", n);
	}
#pragma endregion TextModification

#pragma region TextFormatting
	/**
	 * @brief Set the text formatting used on all future writes to the screen buffer. Similar/equivalent to calling functions in ColorLib.hpp
	 * @param mode	- Available modes can be found at https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences#text-formatting
	 */
	inline void setGraphicsRendition(unsigned mode)
	{
		printf(SEQ_ESC SEQ_BRACKET "%um", mode);
	}
#pragma endregion TextFormatting

	/**
	 * @brief This causes the device's attributes to be emitted to STDIN.
	 */
	inline void getDeviceAttributes()
	{
		printf(SEQ_ESC SEQ_BRACKET "0c");
	}
	inline std::istream& getDeviceAttributes(std::istream& is)
	{
		getDeviceAttributes();
		return is;
	}

	/**
	 * @function cursorVisible(const bool)
	 * @brief Changes the cursor's visibility in the terminal
	 * @param state	- When true, the cursor is visible, else the cursor is not visible.
	 */
	inline void cursorVisible(const bool state) noexcept
	{
		if (state)
			printf(SEQ_ESC SEQ_BRACKET "?25" SEQ_ENABLE);
		else
			printf(SEQ_ESC SEQ_BRACKET "?25" SEQ_DISABLE);
	}
	struct CursorVisible {
		const bool _visible;

		/**
		 * @brief Stream inline cursorVisible() method.
		 * @param visible	- When true, the cursor will be set to be visible, else cursor will be set to hidden.
		 */
		constexpr CursorVisible(const bool visible) : _visible{ visible } {}

		friend std::ostream& operator<<(std::ostream& os, const CursorVisible& obj)
		{
			if (obj._visible)
				printf(SEQ_ESC SEQ_BRACKET "?25" SEQ_ENABLE);
			else
				printf(SEQ_ESC SEQ_BRACKET "?25" SEQ_DISABLE);
			return os;
		}
	};

	/**
	 * @brief Start or stop the cursor blinking effect.
	 * @param state	- When true, enables cursor blink, else disables cursor blink.
	 */
	inline void cursorBlink(const bool state) noexcept
	{
		if (state)
			printf(SEQ_ESC SEQ_BRACKET "?12" SEQ_ENABLE);
		else
			printf(SEQ_ESC SEQ_BRACKET "?12" SEQ_DISABLE);
	}
	struct CursorBlink {
		const bool _blinking;
		constexpr CursorBlink(const bool state) : _blinking{ state } {}

		friend std::ostream& operator<<(std::ostream& os, const CursorBlink& obj)
		{
			if (obj._blinking)
				printf(SEQ_ESC SEQ_BRACKET "?12" SEQ_ENABLE);
			else
				printf(SEQ_ESC SEQ_BRACKET "?12" SEQ_DISABLE);
			return os;
		}
	};

	/**
	 * @function colorSet(const short, const bool = true)
	 * @brief Change the color of characters printed to STDOUT using ColorLib.hpp.
	 * @param color			- The color value to set.
	 * @param foreground	- When true, changes the foreground color, else changes the background color.
	 */
	inline void colorSet(short color, color::Layer foreground = color::Layer::FOREGROUND)
	{
		std::cout << color::setcolor(std::move(color), std::move(foreground));
	}

	/**
	 * @function colorReset()
	 * @brief Reset the color and formatting of characters printed to STDOUT.
	 */
	inline void colorReset()
	{
		std::cout << color::reset;
	}

	struct Message {
	protected:
		std::string _message;
		short _color;
		std::streamsize _indent;

	public:
		Message(std::string message, short color, std::streamsize indent = 8) : _message{ std::move(message) }, _color{ std::move(color) }, _indent{ std::move(indent) } {}

		friend std::ostream& operator<<(std::ostream& os, const Message& obj)
		{
			os << color::f::setcolor(obj._color) << obj._message << color::reset << std::setw(std::abs(static_cast<std::streamsize>(obj._indent + 1 - obj._message.size()))) << ' ';
			return os;
		}
	};

	inline std::ostream& error(std::ostream& os)
	{
		os << Message("[ERROR]", color::intense_red);
		return os;
	}
	inline std::ostream& warn(std::ostream& os)
	{
		os << Message("[WARN]", color::orange);
		return os;
	}
	inline std::ostream& msg(std::ostream& os)
	{
		os << Message("[MSG]", color::intense_green);
		return os;
	}
	inline std::ostream& log(std::ostream& os)
	{
		os << Message("[LOG]", color::light_gray);
		return os;
	}
	inline std::ostream& debug(std::ostream& os)
	{
		os << Message("[DEBUG]", color::intense_magenta);
		return os;
	}
}