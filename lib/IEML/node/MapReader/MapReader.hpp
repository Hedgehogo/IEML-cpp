#pragma once

#include <absl/container/flat_hash_set.h>
#include "../Mark/Mark.hpp"
#include "../NodeData/NodeData.hpp"
#include "../exception/Map/MapException.hpp"

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	template<typename Char_>
	class MapReader {
	public:
		using RequestedContainer = absl::flat_hash_set<BasicString<Char_> const*>;
		using KeyContainer = absl::flat_hash_set<BasicString<Char_> >;
		
		MapReader(BasicMapData<Char_> const& map, Mark mark);
		
		/// @brief Get all the extra keys.
		///
		/// @return All the extra keys.
		Option<KeyContainer> extra_keys();
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, MapException<Char_> > at(BasicString<Char_> const& key);
		
		/// @brief Gets a node in the passed path or an error at any step.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @return A node or NodeAnotherTypeException.
		template<typename... Steps>
		GetResult<Char_, BasicNode<Char_> const&> get(BasicString<Char_> const& key, Steps&&... steps);
		
		/// @brief Gets the T value converted from a node in the passed path or an error at any step or during conversion.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @tparam T Value type.
		///
		/// @return A T value or NodeAnotherTypeException or FailedDecodeDataException.
		template<typename T, typename... Steps>
		GetAsResult<Char_, T> get_as(BasicString<Char_> const& key, Steps&&... steps);
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, MapException<Char_> > operator[](BasicString<Char_> const& key);
	
	private:
		RequestedContainer requested_;
		BasicMapData<Char_> const& map_;
		Mark mark_;
	};
}
