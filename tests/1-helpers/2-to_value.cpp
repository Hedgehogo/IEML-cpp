#include <gtest/gtest.h>

#include <IEML/helpers/to_value/to_value.hpp>

TEST(helpers_number, parse_digit) {
	ieml::String str{""};
	ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
	
	{
		std::uint8_t digit_0{parser.parse_digit('0', 10)};
		ASSERT_EQ(digit_0, 0);
		
		std::uint8_t digit_9{parser.parse_digit('9', 10)};
		ASSERT_EQ(digit_9, 9);
		
		std::uint8_t digit_A{parser.parse_digit('A', 10)};
		ASSERT_EQ(digit_A, 255);
	}
	{
		std::uint8_t digit_0{parser.parse_digit('0', 16)};
		ASSERT_EQ(digit_0, 0);
		
		std::uint8_t digit_9{parser.parse_digit('9', 16)};
		ASSERT_EQ(digit_9, 9);
		
		std::uint8_t digit_A{parser.parse_digit('A', 16)};
		ASSERT_EQ(digit_A, 10);
		
		std::uint8_t digit_F{parser.parse_digit('F', 16)};
		ASSERT_EQ(digit_F, 15);
		
		std::uint8_t digit_G{parser.parse_digit('G', 16)};
		ASSERT_EQ(digit_G, 255);
	}
}

TEST(helpers_number, parse_number_part) {
	{
		ieml::String str{"1_200"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parse_number_part(10)};
		ASSERT_TRUE(number.not_empty());
		ASSERT_EQ(number.factor, 10000);
		ASSERT_EQ(number.value, 1200);
	}
	{
		ieml::String str{"F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parse_number_part(16)};
		ASSERT_TRUE(number.not_empty());
		ASSERT_EQ(number.factor, 0x100);
		ASSERT_EQ(number.value, 0xF8);
	}
	{
		ieml::String str{"A5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::NumberPart number{parser.parse_number_part(10)};
		ASSERT_FALSE(number.not_empty());
	}
}

TEST(helpers_number, parse_number) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number(10)};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 120);
	}
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number(10)};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 120);
	}
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parse_number(10)};
		ASSERT_TRUE(number.is_some());
		ASSERT_FLOAT_EQ(number.some(), 120.5);
	}
	{
		ieml::String str{"F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number(16)};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 0xF8);
	}
	{
		ieml::String str{"A5"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number(10)};
		ASSERT_FALSE(number.is_some());
	}
}

TEST(helpers_number, parse_number_base) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<int> number{parser.parse_number_base()};
		ASSERT_TRUE(number.correct());
		ASSERT_EQ(number.value, 120);
	}
	{
		ieml::String str{"120.5"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<double> number{parser.parse_number_base()};
		ASSERT_TRUE(number.correct());
		ASSERT_FLOAT_EQ(number.value, 120.5);
	}
	{
		ieml::String str{"16'F8"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<int> number{parser.parse_number_base()};
		ASSERT_TRUE(number.correct());
		ASSERT_EQ(number.value, 248);
	}
	{
		ieml::String str{"-2'101.1"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::number::Number<double> number{parser.parse_number_base()};
		ASSERT_TRUE(number.correct());
		ASSERT_FLOAT_EQ(number.value, -5.5);
	}
}

TEST(helpers_number, parse_number_scientific) {
	{
		ieml::String str{"120"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number_scientific()};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 120);
	}
	{
		ieml::String str{"2'101.1"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parse_number_scientific()};
		ASSERT_TRUE(number.is_some());
		ASSERT_FLOAT_EQ(number.some(), 5.5);
	}
	{
		ieml::String str{"120e2'10"};
		ieml::number::Parser<char, int> parser{str.cbegin(), str.cend()};
		
		ieml::Option<int> number{parser.parse_number_scientific()};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 12000);
	}
	{
		ieml::String str{"2'101.1e-3"};
		ieml::number::Parser<char, double> parser{str.cbegin(), str.cend()};
		
		ieml::Option<double> number{parser.parse_number_scientific()};
		ASSERT_TRUE(number.is_some());
		ASSERT_FLOAT_EQ(number.some(), 0.6875);
	}
}

TEST(helpers, to_number) {
	{
		ieml::String str{"2'10e1"};
		ieml::Option<int> number{ieml::to_number<int, ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 4);
	}
	{
		ieml::String str{"2'10e1 # hello"};
		ieml::Option<int> number{ieml::to_number<int, ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_TRUE(number.is_some());
		ASSERT_EQ(number.some(), 4);
	}
	{
		ieml::String str{"2'10e1k"};
		ieml::Option<int> number{ieml::to_number<int, ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_FALSE(number.is_some());
	}
}

TEST(helpers, to_bool) {
	{
		ieml::String str{"yes"};
		ieml::Option<bool> bool_value{ieml::to_bool<ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_TRUE(bool_value.is_some());
		ASSERT_EQ(bool_value.some(), true);
	}
	{
		ieml::String str{"no # hello"};
		ieml::Option<bool> bool_value{ieml::to_bool<ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_TRUE(bool_value.is_some());
		ASSERT_EQ(bool_value.some(), false);
	}
	{
		ieml::String str{" no"};
		ieml::Option<bool> bool_value{ieml::to_bool<ieml::Char>(str.cbegin(), str.cend())};
		ASSERT_FALSE(bool_value.is_some());
	}
}