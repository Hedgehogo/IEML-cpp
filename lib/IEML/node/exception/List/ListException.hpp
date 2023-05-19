#pragma once

#include "../Node/NodeException.hpp"

namespace ieml {
	class ListException : public NodeException {
	private:
		Size requested_index_;
		Size list_size_;
	
	public:
		ListException(Mark mark, Size requested_index, Size list_size);
		
		String get_description() const override;
		
		/// @brief Gets the index that was requested.
		///
		/// @return The index.
		Size get_requested_index() const;
		
		/// @brief Gets the size of the list.
		///
		/// @return The size.
		Size get_list_size() const;
		
		ListException* clone() const override;
	};
}
