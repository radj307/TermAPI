#pragma once
#include <ANSIDefs.h>
#include <ostream>
namespace color {
	/**
	 * @function bold(std::ostream&)
	 * @brief Sets all future characters printed to an output stream as bold using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& bold(std::ostream& os)
	{
		os << SEQ_ESC << "[1" << SEQ_END;
		return os;
	}
	/**
	 * @function reset_invert(std::ostream&)
	 * @brief Removes only bold formatting for all future characters printed to an output stream using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& reset_bold(std::ostream& os)
	{
		os << SEQ_ESC << "[22" << SEQ_END;
		return os;
	}

	/**
	 * @function underline(std::ostream&)
	 * @brief Sets all future characters printed to an output stream as underlined using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& underline(std::ostream& os)
	{
		os << SEQ_ESC << "[4" << SEQ_END;
		return os;
	}
	/**
	 * @function reset_invert(std::ostream&)
	 * @brief Removes only underline formatting for all future characters printed to an output stream using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& reset_underline(std::ostream& os)
	{
		os << SEQ_ESC << "[24" << SEQ_END;
		return os;
	}

	/**
	 * @function invert(std::ostream&)
	 * @brief Sets all future characters printed to an output stream as inverted using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& invert(std::ostream& os)
	{
		os << SEQ_ESC << "[7" << SEQ_END;
		return os;
	}
	/**
	 * @function reset_invert(std::ostream&)
	 * @brief Removes only invert formatting for all future characters printed to an output stream using ANSI escape sequences.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& reset_invert(std::ostream& os)
	{
		os << SEQ_ESC << "[27" << SEQ_END;
		return os;
	}

	/**
	 * @brief Simple output stream placeholder, does not insert anything into an output stream. For use with ternary expressions.
	 * @param os	- Target output stream
	 * @returns std::ostream&
	 */
	inline std::ostream& placeholder(std::ostream& os) { return os; }

	/**
	 * @function reset(std::ostream&)
	 * @brief Reset all formatting & colors in the terminal.
	 * @param os	- (implicit) Target output stream.
	 * @returns std::ostream&
	 */
	inline std::ostream& reset(std::ostream& os)
	{
		os << SEQ_ESC << SEQ_BRACKET << "0" << SEQ_END;
		return os;
	}

}