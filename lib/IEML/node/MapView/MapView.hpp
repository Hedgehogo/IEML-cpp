#pragma once

#include "../MapReader/MapReader.hpp"

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
		
		/// @brief Allows to read a map with an error if an extra key is present.
		///
		/// @param f A function where queries are made to the map.
		///
		/// @return Result of calling `f` or NodeAnotherTypeException or MapException.
		template<typename F>
		Result<std::invoke_result_t<F, MapReader<Char_>&>, ExtraKeyException<Char_> > read(F f) const;
		
		/// @brief Gets a node from the map by key.
		///
		/// @param key Key of the requested node.
		///
		/// @return A node.
		Result<BasicNode<Char_> const&, MapException<Char_> > at(BasicString<Char_> const& key) const;
		
		/// @brief Gets a node in the passed path or an error at any step.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @return A node or NodeAnotherTypeException.
		template<typename... Steps>
		GetResult<Char_, BasicNode<Char_> const&> get(BasicString<Char_> const& key, Steps&&... steps) const;
		
		/// @brief Gets the T value converted from a node in the passed path or an error at any step or during conversion.
		///
		/// @param args Path steps, can be: strings for map keys (including literals), numbers for indexes, ieml::clear to call get_clear().
		///
		/// @tparam T Value type.
		///
		/// @return A T value or NodeAnotherTypeException or FailedDecodeDataException.
		template<typename T, typename... Steps>
		GetAsResult<Char_, T> get_as(BasicString<Char_> const& key, Steps&&... steps) const;
		
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