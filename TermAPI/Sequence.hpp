#pragma once
#include <ANSIDefs.h>
#include <cstdio>
#include <ostream>
namespace ANSI {
	/**
	 * @struct Sequence
	 * @brief	Virtual functor that exposes multiple methods of executing an ANSI escape sequence.
	 *\n		- operator<<	_Output Streams_
	 *\n 		- operator>>	_Input Streams_
	 *\n 		- operator()	_Inline_
	 */
	struct Sequence {
	private:
		const std::string _seq;
	protected:
		constexpr Sequence(char* seq) noexcept : _seq{ seq } {}
	public:
		constexpr explicit Sequence(const std::string& seq) : _seq{ seq.c_str() } {}
		constexpr ~Sequence() noexcept = default;
		/// @brief Retrieve the escape sequence string.
		constexpr operator const std::string() const { return _seq; }
		/// @brief Prints this sequence to STDOUT
		void operator()() const noexcept
		{
			fflush(stdout);
			printf(_seq.c_str());
		}
		/// @brief Prints this sequence to STDOUT
		friend std::ostream& operator<<(std::ostream& os, const Sequence& seq) noexcept
		{
			seq.operator()();
			return os;
		}
		/// @brief Prints this sequence to STDOUT
		friend std::istream& operator>>(std::istream& is, const Sequence& seq) noexcept
		{
			seq.operator()();
			return is;
		}
	};
}