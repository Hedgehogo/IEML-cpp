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

TEST(helpers_number, parseDigit) {
	ieml::String str{""};
	ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
	
	{
		std::uint8_t digit_0{parser.parseDigit('0', 10)};
		ASSERT_EQ(digit_0, 0);
		
		std::uint8_t digit_9{parser.parseDigit('9', 10)};
		ASSERT_EQ(digit_9, 9);
		
		std::uint8_t digit_A{parser.parseDigit('A', 10)};
		ASSERT_EQ(digit_A, 255);
	}
	
	{
		std::uint8_t digit_0{parser.parseDigit('0', 16)};
		ASSERT_EQ(digit_0, 0);
		
		std::uint8_t digit_9{parser.parseDigit('9', 16)};
		ASSERT_EQ(digit_9, 9);
		
		std::uint8_t digit_A{parser.parseDigit('A', 16)};
		ASSERT_EQ(digit_A, 10);
		
		std::uint8_t digit_F{parser.parseDigit('F', 16)};
		ASSERT_EQ(digit_F, 15);
		
		std::uint8_t digit_G{parser.parseDigit('G', 16)};
		ASSERT_EQ(digit_G, 255);
	}
}

TEST(helpers_number, parseNumberPart) {
	{
		ieml::String str{"1_200"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parseNumberPart(10)};
		ASSERT_TRUE(number.notEmpty());
		ASSERT_EQ(number.factor, 10000);
		ASSERT_EQ(number.value, 1200);
	}
	
	{
		ieml::String str{"F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parseNumberPart(16)};
		ASSERT_TRUE(number.notEmpty());
		ASSERT_EQ(number.factor, 0x100);
		ASSERT_EQ(number.value, 0xF8);
	}
	
	{
		ieml::String str{"A5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parseNumberPart(10)};
		ASSERT_FALSE(number.notEmpty());
	}
}

TEST(helpers_number, parseNumber) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumber(10)};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(number.value(), 120);
	}
	
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumber(10)};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(number.value(), 120);
	}
	
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parseNumber(10)};
		ASSERT_TRUE(number.has_value());
		ASSERT_FLOAT_EQ(number.value(), 120.5);
	}
	
	{
		ieml::String str{"F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumber(16)};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(number.value(), 0xF8);
	}
	
	{
		ieml::String str{"A5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumber(10)};
		ASSERT_FALSE(number.has_value());
	}
}

TEST(helpers_number, parseNumberBase) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<int> number{parser.parseNumberBase()};
		ASSERT_TRUE(number.correct());
		ASSERT_EQ(number.value, 120);
	}
	
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<double> number{parser.parseNumberBase()};
		ASSERT_TRUE(number.correct());
		ASSERT_FLOAT_EQ(number.value, 120.5);
	}
	
	{
		ieml::String str{"16'F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<int> number{parser.parseNumberBase()};
		ASSERT_TRUE(number.correct());
		ASSERT_EQ(number.value, 248);
	}
	
	{
		ieml::String str{"-2'101.1"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<double> number{parser.parseNumberBase()};
		ASSERT_TRUE(number.correct());
		ASSERT_FLOAT_EQ(number.value, -5.5);
	}
}

TEST(helpers_number, parseNumberScientific) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumberScientific()};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(*number, 120);
	}
	
	{
		ieml::String str{"2'101.1"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parseNumberScientific()};
		ASSERT_TRUE(number.has_value());
		ASSERT_FLOAT_EQ(*number, 5.5);
	}
	
	{
		ieml::String str{"120e2'10"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parseNumberScientific()};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(*number, 12000);
	}
	
	{
		ieml::String str{"2'101.1e-3"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parseNumberScientific()};
		ASSERT_TRUE(number.has_value());
		ASSERT_FLOAT_EQ(*number, 0.6875);
	}
}

TEST(helpers, toNumber) {
	{
		ieml::String str{"2'10e1"};
		ieml::Option<int> number{ieml::toNumber<int, ieml::String::value_type>(str.cbegin(), str.cend())};
		ASSERT_TRUE(number.has_value());
		ASSERT_EQ(*number, 4);
	}
	
	{
		ieml::String str{"2'10e1k"};
		ieml::Option<int> number{ieml::toNumber<int, ieml::String::value_type>(str.cbegin(), str.cend())};
		ASSERT_FALSE(number.has_value());
	}
}