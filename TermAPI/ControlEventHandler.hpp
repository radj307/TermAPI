/**
 * @file ControlEventHandler.hpp
 * @author radj307
 * @brief Contains functions & methods for handling WIN32 Control Events, such as SIGINT (CTRL + C) & SIGBREAK (CTRL + BREAK), and signals emitted when the user closes a console, logs off, or shuts down the system.
 */
#pragma once
#include <sysarch.h>
#include <functional>
#include <array>
#ifdef OS_WIN
#include <Windows.h>

namespace sys {
	/**
	 * @enum Event
	 * @brief WIN32 API Control Event types that can be emitted at runtime.
	 */
	enum class Event : unsigned char {
		CTRL_C = 0u,			///< @brief Emitted when the user presses CTRL+C.
		CTRL_BREAK = 1u,		///< @brief Emitted when the user presses CTRL+BREAK
		CLOSE = 2u,		///< @brief Emitted when the user closes the console window while the program is running.
		LOGOFF = 3u,		///< @brief Emitted when the user logs off while the program is running.
		SHUTDOWN = 4u,		///< @brief Emitted when the user shuts down the system while the program is running.
	};
	using ControlEventFunctionT = std::function<void()>;
	/**
	 * @brief Control Event Handler
	 * @tparam RT		- Handler function return type.
	 * @tparam ...ArgT	- Handler function argument types.
	 */
	static struct {
	private:
		bool _isRegistered{ false };

		/**
		 * @brief Array containing Event-Function bindings
		 */
		std::array<std::pair<Event, std::unique_ptr<ControlEventFunctionT>>, 5ull> functions{
			std::make_pair(Event::CTRL_C, nullptr),
			std::make_pair(Event::CTRL_BREAK, nullptr),
			std::make_pair(Event::CLOSE, nullptr),
			std::make_pair(Event::LOGOFF, nullptr),
			std::make_pair(Event::SHUTDOWN, nullptr),
		};

	public:
		/**
		 * @brief Bind a function to a specified event type.
		 * @param evbind	- A pair containing the target event type & a unique_ptr to the associated function.
		 */
		void bind(std::pair<Event, std::unique_ptr<ControlEventFunctionT>> evbind) noexcept
		{
			functions[static_cast<size_t>(evbind.first)] = std::move(evbind);
		}

		/**
		 * @brief Bind a function to a specified event type.
		 * @param ev		- The target event.
		 * @param function	- The function to associate with the given event.
		 */
		void bind(const Event& ev, ControlEventFunctionT function) noexcept
		{
			bind(std::make_pair(ev, std::make_unique<ControlEventFunctionT>(std::move(function))));
		}

		/**
		 * @brief Unbind a function from a specified event type.
		 * @param ev	- Target event
		 */
		void unbind(const Event& ev) noexcept
		{
			functions[static_cast<size_t>(ev)].second = nullptr;
		}

		/**
		 * @brief Execute a bound function. This function should not be called manually.
		 * @param ev	- Execute the function bound to this event.
		 * @returns BOOL
		 */
		BOOL WINAPI exec(const Event& ev) const noexcept
		{
			try {
				if (const auto index{ static_cast<size_t>(ev) }; functions[index].second) {
					(*functions[index].second.get())(); //< execute associated function
					return TRUE;
				}
			} catch (...) {}
			return FALSE;
		}

		/**
		 * @brief This function is passed to the WIN32 SetConsoleCtrlHandler function, and executes the function associated with the received event. This function should not be called manually.
		 * @param ev	- An event trigger received from the WIN32 API.
		 * @returns BOOL
		 */
		static BOOL WINAPI handler(DWORD ev) noexcept
		{
			try {
				switch (ev) {
				case CTRL_C_EVENT:
					return ControlEventHandler.exec(Event::CTRL_C);
				case CTRL_CLOSE_EVENT:
					return ControlEventHandler.exec(Event::CLOSE);
				case CTRL_BREAK_EVENT:
					return ControlEventHandler.exec(Event::CTRL_BREAK);
				case CTRL_LOGOFF_EVENT:
					return ControlEventHandler.exec(Event::LOGOFF);
				case CTRL_SHUTDOWN_EVENT:
					return ControlEventHandler.exec(Event::SHUTDOWN);
				default:
					break;
				}
			} catch (...) {}
			return FALSE;
		}
		/**
		 * @brief Register the event handler. This function must be called before any control events are caught.
		 * @param add	- Passed to the SetConsoleCtrlHandler function.
		 * @returns BOOL
		 */
		BOOL WINAPI init(const BOOL& add = TRUE) noexcept
		{
			_isRegistered = SetConsoleCtrlHandler(ControlEventHandler.handler, add);
			return _isRegistered;
		}
	} ControlEventHandler;
	/**
	 * @brief Register the ControlEventHandler with the WIN32 API.
	 * @returns bool
	 */
	inline bool registerEventHandler()
	{
		return static_cast<bool>(ControlEventHandler.init());
	}
	/**
	 * @brief Associate a function with a given event type.
	 * @param ev	- Target event type
	 * @param func	- Target function
	 */
	inline void setEventHandlerFunc(const Event& ev, const ControlEventFunctionT& func)
	{
		ControlEventHandler.bind(ev, func);
	}
	/**
	 * @brief Remove an event's associated function.
	 * @param ev	- Target event type
	 */
	inline void unsetEventHandlerFunc(const Event& ev)
	{
		ControlEventHandler.unbind(ev);
	}
}
#endif