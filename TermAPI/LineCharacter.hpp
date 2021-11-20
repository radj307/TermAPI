/**
 * @file	LineCharacter.hpp
 * @author	radj307
 * @brief	TermAPI Extension that adds the LineCharacter object, which wraps most of the DEC Line Drawing characters with friendlier names.
 */
#pragma once
#include <ostream>	// For std::ostream
namespace sys::term {
	/**
	 * @struct	LineCharacter
	 * @brief	Contains pre-made definitions for all DEC line drawing characters.
	 */
	struct LineCharacter {
	private:
		const unsigned char _ch;
		constexpr LineCharacter(const unsigned char& character) : _ch{ character } {}
	public:
		constexpr operator const unsigned char() const { return _ch; }
		static const LineCharacter
			CORNER_BOTTOM_RIGHT,
			CORNER_TOP_RIGHT,
			CORNER_TOP_LEFT,
			CORNER_BOTTOM_LEFT,
			JUNCTION_4_WAY,
			JUNCTION_3_WAY_RIGHT,
			JUNCTION_3_WAY_LEFT,
			JUNCTION_3_WAY_TOP,
			JUNCTION_3_WAY_BOTTOM,
			LINE_VERTICAL,
			LINE_HORIZONTAL;

		friend std::ostream& operator<<(std::ostream& os, const LineCharacter& line)
		{
			return os << line._ch;
		}
	};
	inline constexpr const LineCharacter
		LineCharacter::CORNER_BOTTOM_RIGHT{ '\x6a' },
		LineCharacter::CORNER_TOP_RIGHT{ '\x6b' },
		LineCharacter::CORNER_TOP_LEFT{ '\x6c' },
		LineCharacter::CORNER_BOTTOM_LEFT{ '\x6d' },
		LineCharacter::JUNCTION_4_WAY{ '\x6e' },
		LineCharacter::LINE_HORIZONTAL{ '\x71' },
		LineCharacter::JUNCTION_3_WAY_LEFT{ '\x74' },
		LineCharacter::JUNCTION_3_WAY_RIGHT{ '\x75' },
		LineCharacter::JUNCTION_3_WAY_BOTTOM{ '\x76' },
		LineCharacter::JUNCTION_3_WAY_TOP{ '\x77' },
		LineCharacter::LINE_VERTICAL{ '\x78' };
}