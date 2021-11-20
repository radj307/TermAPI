#include <TermAPI.hpp>
#include <SequenceDefinitions.hpp>

int main()
{
	try {
		using namespace sys::term;
		return 0;
	} catch (std::exception& ex) {
		std::cout << sys::term::error << ex.what() << std::endl;
		return -1;
	} catch (...) {
		std::cout << sys::term::error << "An unknown exception occurred!" << std::endl;
		return -2;
	}
}