#pragma once
#include <exception>
#include <string>

namespace ieml {
	/// @brief A base class, for convenient exception handling
	class BaseException : public std::exception {
	private:
		std::string description;
		
	public:
		BaseException(std::string description);
		
		/// @brief Gets an error description.
		///
		/// @return Error description.
		std::string getDescription();
		
		virtual const char* what() const noexcept;
	};
}
