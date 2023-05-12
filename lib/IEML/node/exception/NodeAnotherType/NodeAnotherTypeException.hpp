#pragma once

#include "../../NodeType/NodeType.hpp"
#include "../WithMark/WithMarkException.hpp"

namespace ieml {
	/// @brief Exception thrown when a node has been asked for a value that is not a node
	class NodeAnotherTypeException : public WithMarkException {
	private:
		NodeType requested_type_;
		NodeType node_type_;
	
	public:
		NodeAnotherTypeException(Mark mark, NodeType requested_type, NodeType node_type);
		
		String get_description() const override;
		
		/// @brief Gets the type of data that was queried.
		///
		/// @return The type of data that was queried.
		NodeType get_requested_type();
		
		/// @brief Gets the type of node whose data was requested.
		///
		/// @return The type of node whose data was requested.
		NodeType get_node_type();
	};
}
