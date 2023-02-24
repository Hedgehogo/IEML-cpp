#pragma once

#include <exception>
#include <string>

namespace ieml {
	/// @brief A base class, for convenient exception handling
	class BaseException : public std::exception {
	public:
		/// @brief Gets an error description.
		///
		/// @return Error description.
		virtual std::string getDescription() const = 0;
		
		virtual std::string getFullDescription() const;
		
		const char* what() const noexcept final;
	};
}
