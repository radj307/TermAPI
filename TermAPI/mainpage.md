@mainpage

__TermAPI__   
__A C++20 Library designed for using ANSI escape sequences inline with std iostreams, or independently.__   


__Visual Studio Usage:__  
Add the TermAPI.vcxitems project to your solution, then add a reference to the project you want to use it with by R+Clicking on "References" in the solution explorer & adding TermAPI under "Shared Projects".  
Including the TermAPI.hpp header will include everything needed by the library, including some of the terminal color library.  


__Windows-Only__  
By default, ANSI escape sequences are not enabled and must be explicitly enabled by programs in order to use them.  
TermAPI provides a convenient method for accomplishing this, available through the TermAPIWin.hpp header. 
_(Automatically included with <TermAPI.hpp> using preprocessor OS detection)_
```cpp
#include <TermAPI.hpp>
int main()
{
	std::cout << sys::term::EnableANSI;
	return 0;
}
```


_Version 2.0.0 Sequences_  
As of TermAPI 2.0.0, the old functions have been completely replaced with a new Sequence object.  
The Sequence object is returned from the functions found in SequenceDefinitions.hpp and is called by using one of its operators:  
- operator<<  
  Can be used inline with std::osteam like so:  
  ```cpp
  std::cout << sys::term::HideCursor << std::endl;
  ```
- operator>>
  Can be used inline with std::istream like so:  
  ```cpp
  std::cin >> sys::term::setCursorPosition(5, 5);
  ```
- operator()  
  Can be called anywhere.  
  ```cpp
  sys::term::HideCursor()();
  ```
Not all functions can be used inline, specifically functions that require multiple parameters for input or functions from TermAPIQuery.hpp that require reading responses from STDIN, such as getCursorPosition.  
  
_Version 1.0.0_
To use the functions from v1:
```cpp
#define TERMAPI_ENABLE_OLD_FUNCTIONS
#include <TermAPI.hpp>
```

These functions cannot be used inline for the most part, except for a few specific functions.

__A Note on Cursor Positioning__
By default, the screen buffer origin point is (1,1); _not (0,0) as one might expect._
TermAPI provides a function that allows you to change the origin point from (1,1) to (0,0) by automatically translating coordinates in all functions that accept or return cursor coordinates.
```cpp
// Set the cursor origin point to (0,0):
sys::term::SetCursorOrigin(0);
// Set the cursor origin point to (1,1):
sys::term::SetCursorOrigin(1);
```

__Color Library:__  
  TODO

__ColorPalette:__  
When using the color library, you may come across a situation where you want to be able to quickly set the same color for similar characters, and be able to disable all color sequences from being printed out in certain operation modes.  
To accomplish this, you can use the ColorPalette object from the ColorPalette.hpp header to quickly & easily set consistent colors, as well as disable/enable all sequences without changing your code.
All functions from the ColorPalette object will only insert characters into STDOUT when the color palette is set as active, otherwise they simply return right away.

```cpp
#include <TermAPI.hpp>
#include <ColorPalette.hpp>

// Create something to use as a key: (enum of type char uses only 1 byte, so is very useful)
enum class UIElement : char {
	MESSAGE,
	ERROR_CODE,
	BRACKETS,
	SOME_OTHER_ELEMENT,
}

// using UIElement as the key type:
using PaletteType = color::ColorPalette<UIElement>;

// define which colors to use for each UIElement:
PaletteType palette{
	std::make_pair(UIElement::MESSAGE, 				color::setcolor(color::green)),
	std::make_pair(UIElement::ERROR_CODE, 			color::setcolor(color::intense_red)),
	std::make_pair(UIElement::BRACKETS, 			color::setcolor(color::white, color::Layer::FOREGROUND, color::FormatFlag::BOLD | color::FormatFlag::INVERT)),
	std::make_pair(UIElement::SOME_OTHER_ELEMENT, 	color::setcolor(color::orange)),
};

void print_message()
{
	std::cout 
		<< palette.set(UIElement::MESSAGE)
		<< "This message is green!"
		<< palette.reset() 
		<< std::endl;
}

int main()
{
#ifdef OS_WIN
	std::cout << sys::term::EnableANSI;
#endif
	// Print a message with color:
	print_message();
	// Disable the palette & print a message without color:
	palette.setActive(false);
	print_message();
	return 0;
}
```


__DEC Line Drawings:__  
```cpp
// Enable Line Drawing Mode:
sys::term::setCharacterSet(sys::term::CharacterSet::DEC_LINE_DRAWING)();
// Disable Line Drawing Mode:
sys::term::setCharacterSet(sys::term::CharacterSet::ASCII)();
```
TermAPI provides a helper object for drawing lines in the LineCharacter.hpp header.  


__Windows Control Sequences:__  
TermAPI also provides functions for handling Ctrl+C, Ctrl+Break, & logoff/shutdown events in the ControlEventHandler.hpp header.  
Example:  
```cpp
#include <ControlEventHandler.hpp>

void handle_ctrlc()
{
	throw std::exception("User Pressed Ctrl+C!");
}

int main()
{
	// Initialize the event handler & register it with the WIN32 API:
	sys::registerEventHandler();
	// Set the handler function for Ctrl+C:
	sys::setEventHandlerFunc(sys::Event::CTRL_C, handle_ctrlc);
	return 0;
}
```