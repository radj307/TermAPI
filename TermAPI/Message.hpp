#pragma once
#include <Sequence.hpp>
#include <ColorPalette.hpp>

namespace sys::term {
	/**
	 * @enum	MessageType
	 * @brief	Defines the types of messages available, as well as acting as the key type for the message color palette.
	 */
	enum class MessageType : unsigned char {
		INFO,		///< Program Informational Message
		LOG,		///< Program Log
		DEBUG,		///< Program Debug Message
		MSG,		///< Program Message
		WARN,		///< Program Minor Error / Warning
		ERR,		///< Program Error
		CRIT,		///< Critical Program Error
	};

	/**
	 * @brief	The color palette used to print each type of message.
	 */
	inline static color::ColorPalette<MessageType> message_palette{
		std::make_pair(MessageType::INFO, color::setcolor{color::light_gray }),
		std::make_pair(MessageType::LOG, color::setcolor{color::white }),
		std::make_pair(MessageType::DEBUG, color::setcolor{color::magenta }),
		std::make_pair(MessageType::MSG, color::setcolor{color::green }),
		std::make_pair(MessageType::WARN, color::setcolor{color::orange}),
		std::make_pair(MessageType::ERR, color::setcolor{color::red }),
		std::make_pair(MessageType::CRIT, color::setcolor{color::intense_red, color::FormatFlag::BOLD }),
	};

	/**
	 * @brief			Allows enabling/disabling the use of ANSI color sequences in message functions.
	 * @param enable	When true, sets the message_palette to active. Else, disables message colors.
	 * @returns			bool
	 */
	inline constexpr bool setUseMessageColor(const bool& enable)
	{
		return message_palette.setActive(enable);
	}

	/**
	 * @brief				Creates & returns a message Sequence.
	 * @param type			The type of message to print.
	 * @param content		The content of the message to print.
	 * @param max_indent	How many characters the indentation should take up in total. Should be longer than content.size().
	 * @returns				Sequence
	 */
	struct make_message {
	private:
		const MessageType& _type;
		const std::string& _content;
		const std::streamsize& _max_indent = 8ull;
	public:
		make_message(const MessageType& type, const std::string& content, const std::streamsize& max_indent = 8ull) : _type{ type }, _content{ content }, _max_indent{ max_indent } {}
		friend std::ostream& operator<<(std::ostream& os, const make_message& msg)
		{
			return os << message_palette.set(msg._type) << msg._content << str::VIndent(msg._max_indent, msg._content.size());
		}
	};

	/// @brief Prints "[INFO]" in light_gray.
	inline std::ostream& info(std::ostream& os) noexcept { return os << make_message(MessageType::INFO, "[INFO]"); }
	/// @brief Prints "[LOG]" in white.
	inline std::ostream& log(std::ostream& os) noexcept { return os << make_message(MessageType::LOG, "[LOG]"); }
	/// @brief Prints "[DEBUG]" in magenta.
	inline std::ostream& debug(std::ostream& os) noexcept { return os << make_message(MessageType::DEBUG, "[DEBUG]"); }
	/// @brief Prints "[MSG]" in green.
	inline std::ostream& msg(std::ostream& os) noexcept { return os << make_message(MessageType::MSG, "[MSG]"); }
	/// @brief Prints "[WARN]" in orange.
	inline std::ostream& warn(std::ostream& os) noexcept { return os << make_message(MessageType::WARN, "[WARN]"); }
	/// @brief Prints "[ERROR]" in intense_red.
	inline std::ostream& error(std::ostream& os) noexcept { return os << make_message(MessageType::ERR, "[ERROR]"); }
	/// @brief Prints "[ERROR]" in bold intense_red.
	inline std::ostream& crit(std::ostream& os) noexcept { return os << make_message(MessageType::CRIT, "[ERROR]"); }
}