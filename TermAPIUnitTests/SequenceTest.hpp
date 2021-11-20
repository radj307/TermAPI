#pragma once
#include "pch.h"
#include <LineCharacter.hpp>
namespace sys::term::unittests {
	class SequenceTest : public ::testing::Test {
	protected:
		inline static void draw_box(const std::pair<unsigned, unsigned>& origin = { 0u, 0u }, const std::pair<unsigned, unsigned>& size = { 10u, 6u })
		{
			using namespace sys::term;
			setCharacterSet(CharacterSet::DEC_LINE_DRAWING)(); // enable line drawing charset

			SetCursorOrigin(0); // set cursor coordinate origin to (0,0)

			const auto& [origin_x, origin_y] {origin};
			const auto& [size_x, size_y] {size};

			for (unsigned y{ origin_y }; y < origin_y + size_y; ++y) { // iterate through rows (vertical)
				for (unsigned x{ origin_x }; x < origin_x + size_x; ++x) { // iterate through columns (horizontal)
					std::cout << setCursorPosition(x, y);
					if (y == origin_y && x == origin_x) { // top-left corner
						std::cout << LineCharacter::CORNER_TOP_LEFT;
					}
					else if (y == origin_y + size_y - 1 && x == origin_x) { // bottom-left corner
						std::cout << LineCharacter::CORNER_BOTTOM_LEFT;
					}
					else if (y == origin_y && x == origin_x + size_x - 1) { // top-right corner
						std::cout << LineCharacter::CORNER_TOP_RIGHT;
					}
					else if (y == origin_y + size_y - 1 && x == origin_x + size_x - 1) { // bottom-right corner
						std::cout << LineCharacter::CORNER_BOTTOM_RIGHT;
					}
					else if (y == origin_y || y == origin_y + size_y - 1) { // first/last row
						std::cout << LineCharacter::LINE_HORIZONTAL;
					}
					else if (x == origin_x || x == origin_x + size_x - 1) { // first/last column
						std::cout << LineCharacter::LINE_VERTICAL;
					}
				}
			}

			setCharacterSet(CharacterSet::ASCII)(); // reset charset
		}


		void SetUp() override
		{
			std::cout << EnableANSI;
		}
	};
}