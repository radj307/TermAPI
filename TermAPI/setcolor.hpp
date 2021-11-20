/**
 * @file setcolor.hpp
 * @author radj307
 * @brief Contains the setcolor struct, which can be used inline with ostream's operator<< to set text/background color, as well as apply formatting like bold, invert, and underline.
 */
#pragma once
#include <Layer.hpp>
#include <FormatFlag.hpp>
#include <format-functions.hpp>
#include <sstream>
namespace color {
	/**
	 * @brief Builds the escape sequence needed to change console colors.
	 * @param color			- The color value to set.
	 * @param foreground	- When true, changes the color of the foreground (text) instead of the background.
	 * @returns std::string
	 */
	inline std::string makeColorSequence(const short& color, const Layer& layer)
	{
		std::stringstream ss;
		ss << SEQ_ESC << SEQ_BRACKET << layer << ';' << color << SEQ_END;
		return ss.str();
	}

	/**
	 * @struct set
	 * @brief Designed as an inline ANSI-escape-sequence-based color changer. Example: std::cout << color::set(color::red);
	 *\n	NOTE: If you're using Windows, you need to enable virtual terminal sequences by using the following line: (requires windows TermAPI lib or custom implementation)
	 *\n	std::cout << sys::term::EnableANSI;
	 */
	struct setcolor {
	private:
		std::string _seq; ///< @brief The escape sequence to set colors.
		ColorFormat _format; ///< @brief Stores information about bold/underline/invert

	public:
		/**
		 * @brief Escape Sequence Constructor that automatically generates an escape sequence based on the given parameters.
		 * @param color		 - A number within the terminal's color range.
		 * @param foreground - When true, the foreground (text) color will be set, else changes the background color.
		 */
		setcolor(const short color, const Layer foreground = Layer::FOREGROUND, const FormatFlag& format = FormatFlag::NONE) : _seq{ std::move(makeColorSequence(color, foreground)) }, _format{ format } {}
		/**
		 * @brief Constructor that accepts an escape sequence string.
		 * @param color_sequence	- The full ANSI escape sequence, stored in a string variable. This is simply inserted into whichever output stream you target.
		 */
		setcolor(std::string color_sequence, const FormatFlag& format = FormatFlag::NONE) : _seq{ std::move(color_sequence) }, _format{ format } {}

		// Allow conversion to string
		operator std::string() const { return _seq; }

		/**
		 * @brief Retrieve the current format flags.
		 * @returns FormatFlag
		 */
		virtual ColorFormat getFormat() const { return _format; }
		/**
		 * @brief Set the format flag to a new value.
		 * @param newFormat		- Replaces the current formatting flags.
		 * @returns FormatFlag	- Previous format flags
		 */
		virtual ColorFormat setFormat(const FormatFlag& newFormat) { const auto copy{ _format }; _format = newFormat; return copy; }
		virtual ColorFormat addFormat(const FormatFlag& modFormat)
		{
			const auto copy{ _format };
			_format |= modFormat;
			return copy;
		}
		virtual ColorFormat removeFormat(const FormatFlag& modFormat)
		{
			const auto copy{ _format };
			_format &= modFormat;
			return copy;
		}

		// Comparison Operators
		virtual bool operator==(const setcolor& o) const
		{
			return _seq == o._seq;
		}
		virtual bool operator!=(const setcolor& o) const
		{
			return !this->operator==(o);
		}

		// Output Stream insertion operator
		friend std::ostream& operator<<(std::ostream& os, const setcolor& obj)
		{
			os << obj._seq;
			if (obj._format != FormatFlag::NONE) {
				if (obj._format == FormatFlag::BOLD)
					os << bold;
				if (obj._format == FormatFlag::RESET_BOLD)
					os << reset_bold;
				if (obj._format == FormatFlag::UNDERLINE)
					os << underline;
				if (obj._format == FormatFlag::RESET_UNDERLINE)
					os << reset_underline;
				if (obj._format == FormatFlag::INVERT)
					os << invert;
				if (obj._format == FormatFlag::RESET_INVERT)
					os << reset_invert;
			}
			return os;
		}
	};
	/// @brief This setcolor instance can be used as a placeholder, when operator<< is called, nothing will be inserted. (Note that operator<< will still cause certain stream flags/facets to be reset!)
	static const setcolor setcolor_placeholder{ std::string(""), FormatFlag::NONE };
	struct textcolor : setcolor { textcolor(const short color, FormatFlag format = FormatFlag::NONE) : setcolor(color, Layer::FOREGROUND, std::move(format)) {} };

}