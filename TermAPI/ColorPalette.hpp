/**
 * @file ColorPalette.hpp
 * @author radj307
 * @brief Contains the ColorPalette struct, which provides a convenient API for applying consistent colors throughout a program.
 *
 *	# Example Implementation: #
 *
 *	enum class MyKeyType {
 *		TYPE1,
 *		TYPE2,
 *		TYPE3,
 *	}
 *
 *	using Palette = color::ColorPalette<MyKeyType>;
 *
 *	Palette myPalette{
 *	{
 *		{ MyKeyType::TYPE1, color::red },
 *		{ MyKeyType::TYPE2, { color::green, color::Layer::FOREGROUND, color::FormatFlags::BOLD | color::FormatFlags::UNDERLINE } },
 *		{ MyKeyType::TYPE3, color::blue },
 *	}
 *	};
 *
 *	void example()
 *	{
 *		std::cout << myPalette(MyKeyType::TYPE1) << "red text" << color::reset;
 *	}
 */
#pragma once
#include <TERMAPI.h>
#include <unordered_map>
#include <Colorlib.hpp>

namespace color {
	/**
	 * @struct ColorPalette
	 * @brief Contains a key-color map and functions to set terminal colors inline.
	 * @tparam KeyType	- The type of key to use as an identifier for each color.
	 */
	template<class KeyType> struct ColorPalette {
		using PaletteType = std::unordered_map<KeyType, setcolor>;
		PaletteType _palette;
		bool _active{ true }; ///< @brief When false, a blank setcolor placeholder will always be returned from the set() function. This can be used to programmatically enable/disable output colors depending on need.

		ColorPalette() = default;
		ColorPalette(PaletteType palette) : _palette{ std::move(palette) } {}

		virtual bool key_exists(const KeyType& key) const
		{
			return _palette.contains(key);
		}

		/**
			* @brief Retrieve the mapped color setter functor for the given key.
			* @param key	- Key associated with the target color.
			* @returns setcolor
			* @throws std::exception("set(KeyType): Key not found!");
			*/
		virtual setcolor set(const KeyType& key) const
		{
			if ( key_exists(key) )
				return _active ? _palette.at(key) : setcolor_placeholder;
			throw std::exception("set(KeyType): Key not found!");
		}

		/**
			* @brief Retrieve the mapped color setter functor for the given key. You can use this with output stream operator<< as an inline console color changer.
			* @returns setcolor
			*/
		virtual setcolor operator()(const KeyType& key) const
		{
			return set(key);
		}

		explicit operator PaletteType() const { return _palette; }
	};
	};