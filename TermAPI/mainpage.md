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

__ColorPalette__
When using the color library, you may come across a situation where you want to be able to quickly set the same color for similar characters, and be able to disable all color sequences from being printed out in certain operation modes.  
To accomplish this, you can use the ColorPalette object from the ColorPalette.hpp header to quickly & easily 


__DEC Line Drawings:__  
TermAPI provides a helper object for drawing lines in the LineCharacter.hpp header.  
To enable line drawing mode, use 


__Windows Control Sequences:__  
TermAPI also provides a method for catching Ctrl+C, Ctrl+Break, logoff, shutdown