#pragma once
#include "../../NodeType/NodeType.hpp"
#include "../../../exceptions/BaseException.hpp"

namespace ieml {
	/// @brief Exception thrown when a node has been asked for a value that is not a node
	class NodeAnotherTypeException : public BaseException {
	private:
		NodeType requestedType;
		NodeType nodeType;
		
	public:
		NodeAnotherTypeException(NodeType requestedType, NodeType nodeType);
		
		/// @brief Gets the type of data that was queried.
		///
		/// @return The type of data that was queried.
		NodeType getRequestedType();
		
		/// @brief Gets the type of node whose data was requested.
		///
		/// @return The type of node whose data was requested.
		NodeType getNodeType();
	};
}
