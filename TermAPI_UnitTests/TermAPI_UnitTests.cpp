#include "pch.h"

#include <TermAPI.hpp>
using namespace color;
using namespace sys::term;

namespace TermAPIUnitTests
{
	TEST_CLASS(TermAPIUnitTests)
	{
	public:
		
		TEST_METHOD(ColorLib_Validate_FormatFlag)
		{
			const std::vector<FormatFlag> subjects {
				FormatFlag::NONE,
				FormatFlag::BOLD,
				FormatFlag::RESET_BOLD,
				FormatFlag::INVERT,
				FormatFlag::RESET_INVERT,
				FormatFlag::UNDERLINE,
				FormatFlag::RESET_UNDERLINE,
			};

			unsigned flag_combine{ 0u };

			unsigned i { 0u };
			for ( auto& flag : subjects ) {
				Assert::AreEqual(i, unsigned(flag));

				i = i == 0 ? 1 : i * 2;

				if ( i > 1u )
					flag_combine |= flag;
			}

			FormatFlag combined { std::move(flag_combine) };

			Assert::IsFalse(combined.has_flag(FormatFlag::NONE));
			Assert::IsTrue(combined.has_flag(FormatFlag::BOLD));
			Assert::IsTrue(combined.has_flag(FormatFlag::RESET_BOLD));
			Assert::IsTrue(combined.has_flag(FormatFlag::INVERT));
			Assert::IsTrue(combined.has_flag(FormatFlag::RESET_INVERT));
			Assert::IsTrue(combined.has_flag(FormatFlag::UNDERLINE));
			Assert::IsTrue(combined.has_flag(FormatFlag::RESET_UNDERLINE));

			Assert::IsTrue(combined.has_flag_all(FormatFlag::BOLD, FormatFlag::INVERT, FormatFlag::UNDERLINE));
			Assert::IsFalse(combined.has_flag_all(FormatFlag::NONE, FormatFlag::BOLD, FormatFlag::INVERT, FormatFlag::UNDERLINE));
			
			Assert::IsTrue(combined.has_flag_any(FormatFlag::BOLD, FormatFlag::INVERT));
			Assert::IsFalse(combined.has_flag_any(FormatFlag::NONE));
		}

		TEST_METHOD(ColorLib_Validate_Layer)
		{
			Assert::AreEqual(std::string(SEQ_FORE), Layer::FOREGROUND._layer);
			Assert::AreEqual(std::string(SEQ_BACK), Layer::BACKGROUND._layer);
		}

		TEST_METHOD(ANSI_Definitions)
		{
			Assert::AreEqual("\033", SEQ_ESC);
			Assert::AreEqual('\033', INSEQ_ESC);

			Assert::AreEqual("\133", SEQ_BRACKET);
			Assert::AreEqual("[", SEQ_BRACKET);
			Assert::AreEqual('\133', INSEQ_BRACKET);
			Assert::AreEqual('[', INSEQ_BRACKET);

			Assert::AreEqual("38;5", SEQ_FORE);
			Assert::AreEqual("48;5", SEQ_BACK);

			Assert::AreEqual("m", SEQ_END);
			Assert::AreEqual("h", SEQ_ENABLE);
			Assert::AreEqual("l", SEQ_DISABLE);
		}

		TEST_METHOD(ColorLib_setcolor_makeColorSequence)
		{
			for ( short i { 0 }; i < 255; ++i ) {
				std::stringstream ss;
				ss << SEQ_ESC << SEQ_BRACKET << Layer::FOREGROUND << ';' << i << SEQ_END;
				Assert::AreEqual(ss.str(), makeColorSequence(i, Layer::FOREGROUND));
				ss = {};
				ss << SEQ_ESC << SEQ_BRACKET << Layer::BACKGROUND << ';' << i << SEQ_END;
				Assert::AreEqual(ss.str(), makeColorSequence(i, Layer::BACKGROUND));
			}
		}

		TEST_METHOD(ColorLib_setcolor_placeholder)
		{
			std::stringstream buffer;
			buffer << setcolor_placeholder;
			const auto placeholder{ buffer.str() };
			Assert::AreEqual(placeholder.c_str(), "");
		}

		TEST_METHOD(TermAPI_Windows_EnableANSI)
		{
			std::stringstream buffer;
			const auto cout_buffer{ std::cout.rdbuf(buffer.rdbuf()) };
			std::cout << EnableANSI;
			std::cout.rdbuf(cout_buffer);
		}

		/**
		 * TODO: Add test methods for:
		 * setcolor constructors
		 * setcolor correctly uses layer
		 * setcolor correctly uses format flags
		 * setcolor correctly outputs a color escape sequence
		 * setcolor can be correctly copied & moved
		 * color palette constructors
		 * color palette correctly applies setcolor instances
		 * term api functions work correctly
		 * term api correctly enables escape sequences on windows
		 */
	};
}
