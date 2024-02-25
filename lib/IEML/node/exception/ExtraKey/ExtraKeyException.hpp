#pragma once

#include <absl/container/flat_hash_set.h>
#include "../Node/NodeException.hpp"

namespace ieml {
	template<typename Char_>
	class ExtraKeyException : public NodeException {
	public:
		using KeyContainer = absl::flat_hash_set<BasicString<Char_> >;
		
		ExtraKeyException(Mark mark, KeyContainer extra_keys);
		
		String get_description() const override;
		
		/// @brief Gets the index that was requested.
		///
		/// @return The index.
		KeyContainer get_extra_keys() const;
		
		ExtraKeyException* clone() const override;
	
	private:
		absl::flat_hash_set<BasicString<Char_> > extra_keys_;
	};
}

#include "ExtraKeyException.inl"
