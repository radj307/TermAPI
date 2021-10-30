/**
 * @file ANSIDefs.h
 * @author radj307
 * @brief Contains all of the macros for ANSI escape sequences
 */
#pragma once
#include <TERMAPI.h>

#define SEQ_ESC "\033"		///< @brief Escape character.
#define SEQ_BRACKET "\133"
#define SEQ_FORE "38;5"	///< @brief Foreground set color sequence.
#define SEQ_BACK "48;5"	///< @brief Background set color sequence.
#define SEQ_END "m"			///< @brief End escape sequence.
#define SEQ_ENABLE "h"		///< @brief Enable escape sequence.
#define SEQ_DISABLE "l"		///< @brief Disable escape sequence.

#define INSEQ_ESC '\033'
#define INSEQ_BRACKET '\133'