#include "getTypeName.hpp"

#if defined(__GNUG__)

#include <cstdlib>
#include <memory>
#include <cxxabi.h>

namespace ieml {
	namespace detail {
		String demangle(const char* name) {
			int status = -4; // some arbitrary value to eliminate the compiler warning
			
			// enable c++11 by passing the flag -std=c++11 to g++
			std::unique_ptr<char, void (*)(void*)> res{
				abi::__cxa_demangle(name, nullptr, nullptr, &status),
				std::free
			};
			
			return (status == 0) ? res.get() : name;
		}
	}
}

#else

// does nothing if not g++
namespace ieml {
	namespace detail {
		String demangle(const char* name) {
			return name;
		}
	}
}

#endif