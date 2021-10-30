// INLINE DOCUMENTATION
/*\
 * Operating System Macros:
 *		OS_WIN		- Windows OS
 *		OS_LINUX	- (g++/gcc) or cygwin
 *
 * Architecture Macros:
 *		ARCH	=
 *			64		- 64-bit
 *			32		- 32-bit
 *			16		- 16-bit
 *			8		- 8-bit
 *
 * Language Macros:
 *		CPP		=
 *			98		- C++ 1998 / C++ 2003
 *			11		- C++ 2011
 *			14		- C++ 2014
 *			17		- C++ 2017
 *			20		- C++ 2020
 *			23		- C++ 2023
 *		C		=
 *			95		- C 1995
 *			99		- C 1999
 *			11		- C 2011
 *			17		- C 2018
 *			20		- C 202X
 *
 * Compiler Macros:
 *		COMPILER_MSVC		- Microsoft Visual C/C++ Compiler
 *		COMPILER_GCC		- GCC/G++ Compiler
 *		COMPILER_CLANG		- Clang Compiler
 *		COMPILER_WEB		- Web Assembly Compiler
 *		COMPILER_MINGW		- MinGW/MinGW-w64 Compiler
 */
// DOXYGEN DOCUMENTATION:
/**
 * @file sysarch.h
 * @author radj307
 * @brief Defines various pre-processor macros that can be used to check OS, architecture, language, and version. \n
 * These macros are used throughout the shared library project.
 *
 * ## Available Pre-Processor Definitions: #
 *#### Operating System Definitions #
 *		- _OS_WIN_
 *			- Current operating system was detected as Windows.
 *		- _OS_LINUX_
 *			- Current operating system was detected as Linux.
 *## Available Pre-Processor Macros: #
 *#### System Architecture #
 *		- _ARCH_
 *			- Possible Values:
 *			1. 8	- 8-bit architecture
 *			2. 16	- 16-bit architecture
 *			3. 32	- 32-bit architecture
 *			4. 64	- 64-bit architecture
 *#### C/C++ Language Standard #
 *		- _CPP_
 *			- Possible Values:
 *			1. 98	- C++97 / C++03
 *			2. 11	- C++11
 *			3. 14	- C++14
 *			4. 17	- C++17
 *			5. 20	- C++20
 *			6. 23	- C++23
 *		- _C_
 *			- Possible Values:
 *			1. 95	- C95
 *			2. 99	- C99
 *			3. 11	- C11
 *			4. 17	- C18
 *			5. 2	- C2X
 *#### Compiler #
 *		- _COMPILER_MSVC_
 *			Microsoft Visual C/C++ Compiler
 *		- _COMPILER_GCC_
 *			GCC/G++ Compiler
 *		- _COMPILER_CLANG_
 *			Clang Compiler
 *		- _COMPILER_WEB_
 *			Web Assembly Compiler
 *		- _COMPILER_MINGW_
 *			MinGW/MinGW-w64 Compiler
 */
#pragma once
#ifndef SYSARCH_H
	#define SYSARCH_H ///< @brief Macro used to determine if the sysarch.h file was included.

	// Determine Operating System
	#if defined(_WIN32) || defined(WIN32) || defined(__WIN32__) || defined(_WIN64) || defined(WIN64) || defined(__WIN64__) || defined(__NT__)
		#define OS_WIN		///< Windows Operating System
	#elif __GNUG__ || __GNUC__ || __CYGWIN__
		#define OS_LINUX	///< Linux/GNU/WSL Operating System
	#else
		#warning Unrecognized Architecture!
	#endif

	// Determine Processor/OS Architecture
	#pragma region ARCH
	#if INTPTR_MAX == INT64_MAX
		#define ARCH 64		///< 64-Bit System Architecture
	#elif INTPTR_MAX == INT32_MAX
		#define ARCH 32		///< 32-Bit System Architecture
	#elif INTPTR_MAX == INT16_MAX
		#define ARCH 16		///< 16-Bit System Architecture
	#elif INTPTR_MAX == INT8_MAX
		#define ARCH 8		///< 8-Bit System Architecture
	#else
		#warning Unable to determine architecture. (Check that INTPTR_MAX is defined)
	#endif
	#pragma endregion ARCH

	// Determine C++ Version:
	#if __cplusplus == 199711L && defined(_MSC_VER) // This is the default state of the MSVC compiler.
		// R+Click Project -> Alt+Enter, or click Properties, then go to ( Configuration Properties -> C/C++ -> Commandline ) and add "/Zc:__cplusplus"
		#error Unable to detect C++ version because "/Zc:__cplusplus" was not added to the MSVC command line! ( Project Configuration Properties -> C/C++ -> Commandline -> Additional Options)
	#elif __cplusplus == 199711L // This means the compiler is set to C++98.
		#define CPP 98		///< C++ Version 1998/2003
	#elif __cplusplus == 201102L // This means the compiler is set to C++11.
		#define CPP 11		///< C++ Version 2011
	#elif __cplusplus == 201402L // This means the compiler is set to C++14.
		#define CPP 14		///< C++ Version 2014
	#elif __cplusplus == 201703L // This means the compiler is set to C++17.
		#define CPP 17		///< C++ Version 2017
	#elif __cplusplus == 202002L || (defined(_MSC_VER) && __cplusplus == 201705L) // This means the compiler is set to C++20
		#define CPP 20		///< C++ Version 2020
	#elif __cplusplus > 202002L
		#define CPP 23		///< C++ Version 2023
	#elif defined(__cplusplus) // This means the compiler is set to C++, but the macro value is unknown.
		#warning Unable to detect C++ version!
	#else // This means the compiler is not set to C++, or the compiler does not define the __cplusplus macro at all.
		#ifdef __STDC_VERSION__ // Determine C Version if compiler is not using C++
			#if __STDC_VERSION__ == 199409L
				#define C 95	///< C Version 1995
			#elif __STDC_VERSION__ == 199901L
				#define C 99	///< C Version 1999
			#elif __STDC_VERSION__ == 201112L
				#define C 11	///< C Version 2011
			#elif __STDC_VERSION__ == 201710L
				#define C 17	///< C Version 2017
			#elif __STDC_VERSION__ > 201710L
				#define C 2		///< C Version 202X
			#else
				#warning Unable to detect C version!
			#endif
		#else // This means the compiler is not set to C++, and the compiler is not set to C, or the compiler does not define either of these macros. (Get a better compiler, damn)
			#warning Unable to detect C version! (The macro "__STDC_VERSION__" was undefined, or has an unrecognized value.)
		#endif
	#endif

	#if defined(_MSC_VER)
		#define COMPILER_MSVC 		///< @brief Detected Microsoft Visual C/C++ Compiler
	#elif defined(__GNUC__)
		#define COMPILER_GCC 		///< @brief Detected GCC Compiler
	#elif defined(__clang__)
		#define COMPILER_CLANG 		///< @brief Detected Clang Compiler
	#elif defined(__EMSCRIPTEN__)
		#define COMPILER_WEB		///< @brief Detected Web Compiler
	#elif defined(__MINGW32__) || defined(__MINGW64__)
		#define COMPILER_MINGW		///< @brief Detected MinGW/MinGW-w64
	#endif
#endif