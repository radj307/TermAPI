/**
 * @file TermAPIWin.hpp
 * @author radj307
 * @brief	Provides windows-only functionality to the TermAPI.hpp header-only-library, such as enabling ANSI escape sequences.
 */
#pragma once
#include <TERMAPI.h>
#include <sysarch.h>
#include <memory>
#include <optional>
#if defined(OS_WIN) && defined(TERMAPI) // if OS is windows and termapi has been defined
#define TERMAPIWIN_HPP
#include <Windows.h> // for windows-specific functions

namespace sys::term {
	struct TargetHandle {
		unsigned _target;
		constexpr TargetHandle(unsigned target) : _target { std::move(target) } {}
		constexpr operator unsigned() const { return _target; }

		unsigned operator&(const unsigned& o) const { return _target & o; }
		unsigned operator|(const unsigned& o) const { return _target | o; }

		bool has_flag(const unsigned& flag_value) const
		{
			return this->operator&(flag_value) != 0u;
		}

		static const TargetHandle NONE, STDIN, STDOUT;
	};
	inline const TargetHandle TargetHandle::NONE { 0u }, TargetHandle::STDIN { 1u }, TargetHandle::STDOUT { 2u };
	static struct {
	private:
		std::unique_ptr<HANDLE> _STDIN{
			std::make_unique<HANDLE>(GetStdHandle(STD_INPUT_HANDLE))
		}, _STDOUT{
			std::make_unique<HANDLE>(GetStdHandle(STD_OUTPUT_HANDLE))
		};

		using Mode = std::optional<DWORD>;

		/**
		 * @brief Get the current STDIN console mode.
		 * @returns Mode
		 */
		Mode getInputMode() const noexcept
		{
			try {
				if ( DWORD mode; GetConsoleMode(*_STDIN.get(), &mode) )
					return mode;
			} catch ( ... ) {}
			return std::nullopt;
		}
		/**
		 * @brief Set the console mode for the STDIN handle.
		 * @param dwMode	- Mode parameter to set.
		 * @returns bool
		 */
		bool setInputMode(const DWORD& dwMode) const
		{
			return SetConsoleMode(_STDIN.get(), dwMode);
		}
		/**
		 * @brief Modify the console mode for the STDOUT handle by adding the given mode.
		 * @param dwMode	- Mode parameter to add.
		 * @returns bool
		*/
		bool modInputMode(const DWORD& dwMode) const
		{
			return setInputMode(getInputMode().value_or(0ul) | dwMode);
		}

		/**
		 * @brief Get the current STDOUT console mode.
		 * @returns Mode
		 */
		Mode getOutputMode() const noexcept
		{
			try {
				if ( DWORD mode; GetConsoleMode(*_STDOUT.get(), &mode) )
					return mode;
			} catch ( ... ) {}
			return std::nullopt;
		}
		/**
		 * @brief Set the console mode for the STDOUT handle.
		 * @param dwMode	- Mode parameter to set. 
		 * @returns bool
		 */
		bool setOutputMode(const DWORD& dwMode) const
		{
			return SetConsoleMode(_STDOUT.get(), dwMode);
		}
		/**
		 * @brief Modify the console mode for the STDOUT handle by adding the given mode.
		 * @param dwMode	- Mode parameter to add.
		 * @returns bool
		*/
		bool modOutputMode(const DWORD& dwMode) const
		{
			return setOutputMode(getOutputMode().value_or(0ul) | dwMode);
		}

	public:

		bool VirtualSequences(TargetHandle target, const bool enable)
		{
			if ( target.has_flag(TargetHandle::STDIN) )
				return modInputMode(ENABLE_VIRTUAL_TERMINAL_INPUT);
			else if ( target.has_flag(TargetHandle::STDOUT) )
				return modOutputMode(ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
			return false;
		}
	} ConsoleModeSetter;
	inline std::istream& EnableANSI(std::istream& is)
	{
		ConsoleModeSetter.VirtualSequences(TargetHandle::STDIN, true);
		return is;
	}
	inline std::istream& DisableANSI(std::istream& is)
	{
		ConsoleModeSetter.VirtualSequences(TargetHandle::STDIN, false);
		return is;
	}
	inline std::ostream& EnableANSI(std::ostream& os)
	{
		ConsoleModeSetter.VirtualSequences(
			TargetHandle::STDOUT,
			true
		);
		return os;
	}
	inline std::ostream& DisableANSI(std::ostream& os)
	{
		ConsoleModeSetter.VirtualSequences(
			TargetHandle::STDOUT, 
			false
		);
		return os;
	}
	inline bool EnableANSI(const TargetHandle& target = TargetHandle::STDIN | TargetHandle::STDOUT)
	{
		return ConsoleModeSetter.VirtualSequences(
			TargetHandle::STDIN | TargetHandle::STDOUT, 
			true
		);
	}
	inline bool DisableANSI(const TargetHandle& target = TargetHandle::STDIN | TargetHandle::STDOUT)
	{
		return ConsoleModeSetter.VirtualSequences(
			TargetHandle::STDIN | TargetHandle::STDOUT,
			false
		);
	}
}
#endif
#ifndef TERMAPI_HPP
#include <TermAPI.hpp>
#endif