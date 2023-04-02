#include <gtest/gtest.h>

#include <IEML/helpers/toValue/toValue.hpp>

TEST(helpers, toValue) {
	ieml::String strInt{"7_123_274"};
	ASSERT_EQ(ieml::toInt(strInt.cbegin(), strInt.cend()), 7123274);
	
	ieml::String strIntBasis{"0c112012"};
	ASSERT_EQ(ieml::toInt(strIntBasis.cbegin(), strIntBasis.cend()), 383);
	
	ieml::String strDouble{"7_123_274.123"};
	ASSERT_FLOAT_EQ(ieml::toDouble(strDouble.cbegin(), strDouble.cend()), 7123274.123);
	
	ieml::String strDoubleBasis{"0c112.212"};
	ASSERT_FLOAT_EQ(ieml::toDouble(strDoubleBasis.cbegin(), strDoubleBasis.cend()), 14. + 23. / 27.);
}