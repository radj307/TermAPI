#include "pch.h"

#include "SequenceTest.hpp"
using namespace sys::term::unittests;

TEST_F(SequenceTest, EscapeSequenceValid)
{
	ASSERT_NO_THROW(ASSERT_EQ(Sequence(std::string(1ull, ESC) + CSI).operator const std::string(), std::string(1ull, ESC) + CSI) << "Sequence object is not moving strings around correctly!") << "Exception thrown during test!";
	ASSERT_NO_THROW(ASSERT_EQ(Sequence(std::move(std::string(1ull, ESC) + CSI)).operator const std::string(), std::string(1ull, ESC) + CSI) << "Sequence object is not moving strings around correctly!") << "Exception thrown during test!";
	ASSERT_NO_THROW(ASSERT_EQ(Sequence((std::string(1ull, ESC) + CSI).c_str()).operator const std::string(), std::string(1ull, ESC) + CSI) << "Sequence object is not moving strings around correctly!") << "Exception thrown during test!";
}
TEST(UtilityFunctions, make_sequence)
{
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, 1u, 'I'), std::string(1ull, ESC) + CSI + "1I"));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, ENABLE, DISABLE), std::string(1ull, ESC) + CSI + ENABLE + DISABLE));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, "\033", "\x1b"), std::string(3ull, ESC)));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, 1ull, 'I'), std::string(1ull, ESC) + CSI + "1I"));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, 1ll, 'I'), std::string(1ull, ESC) + CSI + "1I"));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, 1, 'I'), std::string(1ull, ESC) + CSI + "1I"));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, CSI, -1, 'I'), std::string(1ull, ESC) + CSI + "-1I"));
	ASSERT_NO_THROW(ASSERT_EQ(make_sequence(ESC, std::fixed, std::setprecision(32ll), 1.00000002322131312, 'I'), std::string(1ull, ESC) + "1.00000002322131309462349690875271I"));
}
TEST_F(SequenceTest, Function_setCharacterSet)
{
	ASSERT_EQ(setCharacterSet(CharacterSet::DEC_LINE_DRAWING).operator const std::string(), make_sequence(ESC, CHARACTER_SET, '0'));
	ASSERT_EQ(setCharacterSet(CharacterSet::ASCII).operator const std::string(), make_sequence(ESC, CHARACTER_SET, 'B'));
	ASSERT_ANY_THROW(setCharacterSet(static_cast<CharacterSet>('A')).operator const std::string());
}
TEST_F(SequenceTest, LineDrawing)
{
	using namespace streamutil;
	BufferManager bufman;
	bufman.begin_capture_stdout();

	draw_box();

	bufman.end_capture_stdout();
	const auto str{ bufman.get_string() };
}