#pragma once

#include "../Node/NodeException.hpp"

namespace ieml {
	template<typename Char_>
	class MapException : public NodeException {
	private:
		BasicString<Char_> requested_key_;
	
	public:
		MapException(Mark mark, BasicString<Char_> const& requested_key);
		
		String get_description() const override;
		
		/// @brief Gets the index that was requested.
		///
		/// @return The index.
		BasicStringView<Char_> get_requested_key() const;
		
		MapException* clone() const override;
	};
}

#include "MapException.inl"
