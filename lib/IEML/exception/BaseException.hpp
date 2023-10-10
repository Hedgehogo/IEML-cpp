#pragma once

#include <exception>
#include "../usings/usings.hpp"

namespace ieml {
	/// @brief A base class, for convenient exception handling
	class BaseException : public std::exception {
	public:
		/// @brief Gets an error description.
		///
		/// @return Error description.
		virtual String get_description() const = 0;
		
		virtual String get_full_description() const;
		
		const char* what() const noexcept final;
	};
	
	std::ostream& operator<<(std::ostream& stream, const BaseException& exception);
}
