#pragma once
#include "../NodeType/NodeType.hpp"
#include <string>

namespace ieml {
	using llint = long long;
	
	/// @brief  Interface for node data
	class INodeData {
	public:
		/// @brief Gets the node type.
		///
		/// @return Returns the node type.
		virtual NodeType getNodeType() = 0;
		
		/// @brief Gets the bool value.
		///
		/// @return A bool value or throws an exception NotRequestedTypeException.
		virtual bool getBool();
		
		/// @brief Gets the llint value.
		///
		/// @return A llint value or throws an exception NotRequestedTypeException.
		virtual llint getInt();
		
		/// @brief Gets the double value.
		///
		/// @return A double value or throws an exception NotRequestedTypeException.
		virtual double getDouble();
		
		/// @brief Gets the string value.
		///
		/// @return A string value or throws an exception NotRequestedTypeException.
		virtual std::string getString();
		
		~INodeData() = default;
	};
}
