/**
 * @file ANSIDefs.h
 * @author radj307
 * @brief Contains all of the macros for ANSI escape sequences
 */
#pragma once
#include <TERMAPI.h>
#include <type_traits>
#include <str.hpp>

namespace ANSI {
	inline constexpr const auto ESC{ '\033' }; ///< @brief Escape Character. Required at the beginning of all escape sequences.
	inline constexpr const auto CSI{ '\133' }; ///< @brief Control Sequence Introducer. Only valid when preceeded by ESC.
	inline constexpr const auto OSC{ '\133' }; ///< @brief Operating System Command. Only valid when preceeded by ESC.

	inline constexpr const auto FORE{ "38;5" }; ///< @brief Foreground color.
	inline constexpr const auto BACK{ "48;5" }; ///< @brief Background color.

	inline constexpr const auto ENABLE{ 'h' };
	inline constexpr const auto DISABLE{ 'l' };

	inline constexpr const auto CURSOR_VISIBLE{ "?25" };
	inline constexpr const auto CURSOR_BLINK{ "?12" };

	inline constexpr const auto CHARACTER_SET{ '(' };
	inline constexpr const auto STRING_TERMINATOR{ '\0' };

	template<typename... VT>
	inline constexpr auto make_sequence(const VT&... ch)
	{
		return std::move(str::stringify(ch...));
	}
}


#define SEQ_ESC "\033"		///< @brief Escape character.
#define SEQ_BRACKET "\133"
#define SEQ_FORE "38;5"	///< @brief Foreground set color sequence.
#define SEQ_BACK "48;5"	///< @brief Background set color sequence.
#define SEQ_END "m"			///< @brief End escape sequence.
#define SEQ_ENABLE "h"		///< @brief Enable escape sequence.
#define SEQ_DISABLE "l"		///< @brief Disable escape sequence.

#define INSEQ_ESC '\033'
#define INSEQ_BRACKET '\133'