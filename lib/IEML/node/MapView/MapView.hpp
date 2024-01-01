#pragma once

#include "../Mark/Mark.hpp"
#include "../NodeData/NodeData.hpp"
#include "../exception/Map/MapException.hpp"

namespace ieml {
	template<typename Char_>
	class BasicNode;
	
	template<typename Char_>
	class BasicMapView {
	public:
		BasicMapView(BasicMapData<Char_> const& map, Mark mark);
		
		/// @brief Gets the map size.
		///
		/// @return A map size.
		Size get_size() const;
		
		/// @brief Gets the node map.
		///
		/// @return A node map.
		BasicMapData<Char_> const& get_map() const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, MapException<Char_> > at(BasicString<Char_> const& key) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, MapException<Char_> > operator[](BasicString<Char_> const& key) const;
	
	private:
		BasicMapData<Char_> const& map_;
		Mark mark_;
	};
	
	using MapView = BasicMapView<Char>;
}