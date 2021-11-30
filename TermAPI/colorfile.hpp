/**
 * @file	colorfile.hpp
 * @author	radj307
 * @brief	Extends the color namespace with file i/o capabilities.
 */
#pragma once
#include <ColorPalette.hpp>
#include <str.hpp>
#include <INI.hpp>

namespace color::file {
	using namespace ::file;
	/**
	 * colorfile format:
	 * INI-based
	 *
	 * <KEYNAME> = <HEXCOLOR>
	 */

	namespace token {
		enum class TokenType {
			NULL_TYPE,		// [Unexpected]
			ESC,			// escape
			CSI,			// '['
			LAYER,			// [38(fg)|48(bg)]
			SEPARATOR,		// ';'
			INTEGER,		// [color-value]
			END,			// 'm'
		};

		struct Token : ::token::TokenBase<TokenType> {
			Token(std::string str, const TokenType& type) : TokenBase(std::move(str), type) {}
			Token(const TokenType& type) : TokenBase(type) {}
			Token(std::pair<std::string, TokenType> pr) : TokenBase(std::move(pr)) {}
		};

		struct SequenceTokenizer : ::token::TokenizerBaseFunctions<Token> {
		private:
			std::stringstream ss;
			std::streamoff lastPos{ 0ll };

		public:
			SequenceTokenizer(std::stringstream ss) : ss{ std::move(ss) } {}

			Token getNext() override
			{
				const auto ch{ getch() };
				using enum ::token::LEXEME;
				switch (::token::get_lexeme(ch)) {
				case SEMICOLON:
					return TokenType::SEPARATOR;
				case DIGIT: {
					std::string str{ 1ull, ch };
					str += getch();
					if (const auto front{ str.front() }, back{ str.back() }; (front == '3' || front == '4') && back == '8')
						return Token{ str, TokenType::LAYER };
					return Token{ str + getsimilar(DIGIT), TokenType::INTEGER };
				}
				default:
					switch (ch) {
					case INSEQ_ESC:
						return TokenType::ESC;
					case INSEQ_BRACKET:
						return TokenType::CSI;
					}
				}
			}
		};
	}

	/// ANSI COLOR SEQUENCE: \033 \133 [38|48] ; [COLOR] m


	template<typename KeyType>
	struct ColorFile {
		ColorPalette<KeyType>& _palette;

		ColorFile(ColorPalette<KeyType>& palette) : _palette{ palette } {}

		friend std::ostream& operator<<(std::ostream& os, const ColorFile<KeyType>& colfile)
		{
			return os;
		}
	};
}
namespace color {
	// todo: add functions for calling file read/write methods
}