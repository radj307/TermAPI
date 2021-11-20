/**
 * @file Layer.hpp
 * @author radj307
 * @brief Contains the Layer struct, a pseudo-enum used to define a target layer (foreground/background) for the setcolor functor.
 */
#pragma once
#include <ostream>
#include <utility>
#include <ANSIDefs.h>
namespace color {
	/**
	 * @struct Layer
	 * @brief Determines which layer to apply colors to.
	 */
	struct Layer {
		const std::string _layer;

		/**
		 * @brief Constexpr Constructor
		 * @param layer	- 1u == Foreground, 0u == Background
		 */
		constexpr Layer(std::string layer) : _layer{ std::move(layer) } {}

		constexpr operator const std::string() const { return _layer; }

		static const Layer FOREGROUND, BACKGROUND;

		friend std::ostream& operator<<(std::ostream& os, const Layer& layer)
		{
			os << layer.operator const std::string();
			return os;
		}
	};

	/** @brief Foreground/text color layer */
	inline const Layer Layer::FOREGROUND{ SEQ_FORE };
	/** @brief Background color layer, appears "behind" text. */
	inline const Layer Layer::BACKGROUND{ SEQ_BACK };

}
#ifndef COLOR_NO_GLOBALS
/// @brief Allows specifying the color::Layer object with a shorter syntax. Define "COLOR_NO_GLOBALS" to disable.
using Layer = color::Layer;
#endif