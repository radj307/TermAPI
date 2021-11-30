/**
 * @file ColorLib.hpp
 * @author radj307
 * @brief	Header-only library containing various methods & values used for modifying character attributes in the console screen buffer.
 *\n		This header is required by TermAPI.hpp
 */
#pragma once
 // Components of the color library:
#include <ANSIDefs.h>
#include <color-values.h>
#include <Layer.hpp>
#include <FormatFlag.hpp>
#include <format-functions.hpp>
#include <setcolor.hpp>
#include <setcolor-functions.hpp>

/**
 * @namespace color
 * @brief Contains various methods, functions, and functors for setting the color of text/backgrounds in terminal windows.
 */
namespace color {}