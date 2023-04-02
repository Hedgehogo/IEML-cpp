#include <gtest/gtest.h>

#include <IEML/helpers/isValue/isValue.hpp>

TEST(helpers, isValue) {
	ieml::String strInt{"7_123_274"};
	ASSERT_TRUE(ieml::isInt(strInt.cbegin(), strInt.cend()));
	
	ieml::String strIntOther{"7_a12"};
	ASSERT_FALSE(ieml::isInt(strIntOther.cbegin(), strIntOther.cend()));
	
	ieml::String strIntBasis{"0c112012"};
	ASSERT_TRUE(ieml::isInt(strIntBasis.cbegin(), strIntBasis.cend()));
	
	ieml::String strIntBasisOther{"0zZ01"};
	ASSERT_FALSE(ieml::isInt(strIntBasisOther.cbegin(), strIntBasisOther.cend()));
	
	ieml::String strDouble{"7_123_274.123"};
	ASSERT_TRUE(ieml::isDouble(strDouble.cbegin(), strDouble.cend()));
	
	ieml::String strDoubleOther{".123_237"};
	ASSERT_FALSE(ieml::isDouble(strDoubleOther.cbegin(), strDoubleOther.cend()));
	
	ieml::String strDoubleBasis{"0c112.212"};
	ASSERT_TRUE(ieml::isDouble(strDoubleBasis.cbegin(), strDoubleBasis.cend()));
	
	ieml::String strDoubleBasisOther{"0zZ01.903"};
	ASSERT_FALSE(ieml::isDouble(strDoubleBasisOther.cbegin(), strDoubleBasisOther.cend()));
}