#pragma once
#include "../../NodeType/NodeType.hpp"
#include "../../../exceptions/BaseException.hpp"

namespace ieml {
	/// @brief Exception thrown when a node has been asked for a value that is not a node
	class NotRequestedTypeException : public BaseException {
	private:
		std::string type;
		NodeType nodeType;
		
	public:
		NotRequestedTypeException(std::string type, NodeType nodeType);
		
		/// @brief Gets the type of data that was queried as a string.
		///
		/// @return The type of data that was queried as a string.
		std::string getType();
		
		/// @brief Gets the type of node whose data was requested.
		///
		/// @return The type of node whose data was requested.
		NodeType getNodeType();
	};
}
