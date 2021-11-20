#pragma once
#define TERMAPI

/**
 * @namespace color
 * @brief Contains functions, functors, and definitions for stream-inline terminal colors.
 */
namespace color {}
/**
 * @namespace sys::term
 * @brief Contains objects, methods, & functions related to using cross-platform ANSI escape sequences.
 */
namespace sys::term {
	/**
	 * @namespace _internal
	 * @brief Contains variables/functions not meant to be accessed from outside of the TermAPI library.
	 */
	namespace _internal {
		// @brief Controls whether cursor position origin is indexed from 1 (false/default behavior) or 0 (true). This is applied by calling (!!_internal::CURSOR_POS_MIN_ZERO + <n>)
		static bool CURSOR_POS_MIN_ZERO{ false };
	}
	/**
	 * @brief Allows changing the default origin index for all I/O cursor positioning functions from (1,1) to (0,0) & vice-versa.
	 * @param zero	When false / 0, origin/top-left point is set to __(0,0)__.
	 *\n			_default:_ When true, origin/top-left point is set to __(1,1)__.
	 */
	inline void SetCursorOrigin(const bool& index = true)
	{
		_internal::CURSOR_POS_MIN_ZERO = !index;
	}
}