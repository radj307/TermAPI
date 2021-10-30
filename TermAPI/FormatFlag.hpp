/**
 * @file FormatFlag.hpp
 * @author radj307
 * @brief Contains the FormatFlag struct, a pseudo-enum used to pass formatting information to the setcolor functor. 
 */
#pragma once
#include <utility>
namespace color {
#pragma region DECLARATION
	/**
	 * @struct FormatFlag
	 * @brief Used by the setcolor functor to store formatting options.
	 *\n	  This struct emulates a flag-enum, and can contain (FormatFlag::NONE) or any or all of the following types: (FormatFlag::BOLD, FormatFlag::INVERT, FormatFlag::UNDERLINE)
	 *\n	  To assign multiple flags, use the bitwise OR operator. For example, to assign the bold and invert flags, use this operation:
	 *\n	  FormatFlag::BOLD | FormatFlag::INVERT
	 */
	struct FormatFlag {
		unsigned _format;

		constexpr FormatFlag(unsigned format) : _format { std::move(format) } {}

		constexpr operator unsigned() const { return _format; }

		/** @brief Bitwise AND */
		FormatFlag operator&(const FormatFlag& o) const { return _format & o._format; }
		/** @brief Bitwise OR */
		FormatFlag operator|(const FormatFlag& o) const { return _format | o._format; }
		/** @brief Bitwise XOR */
		FormatFlag operator^(const FormatFlag& o) const { return _format ^ o._format; }
		/** @brief Bitwise AND Setter */
		FormatFlag& operator&=(const FormatFlag& o) { return *this = *this & o; }
		/** @brief Bitwise OR Setter */
		FormatFlag& operator|=(const FormatFlag& o) { return *this = *this | o; }
		/** @brief Bitwise XOR Setter */
		FormatFlag& operator^=(const FormatFlag& o) { return *this = *this ^ o; }

		/**
		 * @brief Check if this instance contains the given flag.
		 * @param flag	- Flag to compare.
		 * @returns bool
		 */
		bool has_flag(const FormatFlag& flag) const
		{
			return this->operator&(flag)._format != 0;
		}
		/**
		 * @brief Check if this instance contains all of the given flags.
		 * @tparam T...	- Variadic Templated Type. Must be FormatFlag!
		 * @param flags	- Flags to compare.
		 * @returns bool
		 */
		template<class... T> std::enable_if_t<( sizeof...( T ) > 0 && std::conjunction_v<std::is_same<FormatFlag, T>...> ), bool> has_flag_all(const T&... flags) const
		{
			return (has_flag(flags) && ...);
		}
		/**
		 * @brief Check if this instance contains any of the given flags.
		 * @tparam T...	- Variadic Templated Type. Must be FormatFlag!
		 * @param flags	- Flags to compare.
		 * @returns bool
		 */
		template<class... T> std::enable_if_t<( sizeof...( T ) > 0 && std::conjunction_v<std::is_same<T, FormatFlag>...> ), bool> has_flag_any(const T&... flags) const
		{
			return (has_flag(flags) || ...);
		}

		// Declare enum vars
		static const FormatFlag NONE, BOLD, RESET_BOLD, INVERT, RESET_INVERT, UNDERLINE, RESET_UNDERLINE;
	};
#pragma endregion DECLARATION
#pragma region DEFINITIONS
	/** @brief No special formatting */
	constexpr FormatFlag FormatFlag::NONE { 0u };
	/** @brief Bold printed text. */
	constexpr FormatFlag FormatFlag::BOLD { 1u };
	/** @brief Unset the bold flag specifically. */
	constexpr FormatFlag FormatFlag::RESET_BOLD { 2u };
	/** @brief Invert foreground & background colors of printed text. */
	constexpr FormatFlag FormatFlag::INVERT { 4u };
	/** @brief Unset the invert flag specifically. */
	constexpr FormatFlag FormatFlag::RESET_INVERT { 8u };
	/** @brief Underline printed text. */
	constexpr FormatFlag FormatFlag::UNDERLINE { 16u };
	/** @brief Unset the underline flag specifically. */
	constexpr FormatFlag FormatFlag::RESET_UNDERLINE { 32u };
#pragma endregion DEFINITIONS
}