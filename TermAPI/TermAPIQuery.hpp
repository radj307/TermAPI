/**
 * @file TermAPIQuery.hpp
 * @author radj307
 * @brief TermAPI extension that includes query escape sequences, such as retrieving the cursor position.
 *\n	  This header requires non-standard <conio.h>
 */
#pragma once
#include <ANSIDefs.h>
#include <str.hpp>
#include <utility>
#include <iostream>
#include <thread>
#include <conio.h>

namespace sys::term {
	using namespace std::chrono_literals;
	/**
	 * @namespace _internal
	 * @brief Contains functions used internally by the sys::term namespace.
	 */
	namespace _internal {
		/**
		 * @brief Receive a query response from STDIN, and return it as a string.
		 *\n	  It is ___highly discouraged___ to call this function from outside of TermAPIQuery.hpp!
		 * @param timeout	- Maximum amount of wait cycles before breaking and returning nothing.
		 * @returns std::string
		 */
		inline std::string get_query_response(const int& timeout = 256, const bool flush_output_stream = false) noexcept
		{
			if (flush_output_stream)
				fflush(stdout);
			std::string seq; // already has enough space reserved
			for (int i{ 0 }; !_kbhit() && i < timeout; ++i) // wait until a "key press" or until timeout is reached.
				std::this_thread::sleep_for(1ms);
			while (_kbhit()) // while a key is "pressed"
				seq += static_cast<char>(_getch()); // get key code, cast to char
			return seq;
		}
	}

	/**
	 * @brief Prints the escape sequence for DECXCPR (Report Cursor Position). Not thread-safe when multiple threads are printing/reading from STDOUT/STDIN.
	 *\n	  Emits to STDIN: "ESC[<ROW>;<COLUMN>R"
	 */
	inline void reportCursorPosition() noexcept
	{
		fflush(stdin); // Flush STDIN
		printf(SEQ_ESC SEQ_BRACKET "6n"); // Send DECXCPR - Report Cursor Position
		fflush(stdout); // Flush STDOUT
	}

	/**
	 * @brief Retrieve the current position of the cursor, measured in characters of the screen buffer.
	 * @tparam RT	- Templated Return Type (Integral)
	 * @returns std::pair<RT, RT>
	 */
	template<typename RT = unsigned short>
	inline std::enable_if<std::is_integral<RT>::value, std::pair<RT, RT>>::type getCursorPosition() noexcept(false)
	{
		reportCursorPosition();
		std::string row, col;
		bool select_col{ false }; ///< @brief when true, appends digits to column; else, appends to row.
		for (auto& c : _internal::get_query_response()) {
			switch (c) {
			case '0': [[fallthrough]];
			case '1': [[fallthrough]];
			case '2': [[fallthrough]];
			case '3': [[fallthrough]];
			case '4': [[fallthrough]];
			case '5': [[fallthrough]];
			case '6': [[fallthrough]];
			case '7': [[fallthrough]];
			case '8': [[fallthrough]];
			case '9':
				if (!select_col)
					row += c;
				else
					col += c;
				break;
			case ';': // delim
				select_col = true;
				break;
			case INSEQ_ESC: [[fallthrough]];// ESC
			case INSEQ_BRACKET:
				break;
			case 'R': // sequence end
				if (!row.empty() && !col.empty()) // divider delim has been reached
					return{ static_cast<RT>(!!_internal::CURSOR_POS_MIN_ZERO + str::stoull(row)), static_cast<RT>(!!_internal::CURSOR_POS_MIN_ZERO + str::stoull(col)) };
				// else:
				[[fallthrough]];
			default:
				throw std::exception(str::stringify("getCursorPosition()\tReceived unexpected character: \'", c, "\'!").c_str());
			}
		}
		throw std::exception("getCursorPosition()\tDidn't receive expected escape sequence! No ending character found!");
	}

	/**
	 * @brief This causes the device's attributes to be emitted to STDIN.
	 *\n	  Emits to STDIN (windows): "\x1b[?1;0c" (Indicates "VT101 with No Options")
	 */
	inline void deviceAttributes() noexcept
	{
		printf(SEQ_ESC SEQ_BRACKET "0c");
	}

	inline std::string getDeviceAttributes() noexcept
	{
		deviceAttributes();
		return _internal::get_query_response();
	}
}