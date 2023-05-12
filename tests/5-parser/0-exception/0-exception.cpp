#include <gtest/gtest.h>

#include <IEML/parser/exception/FailedParseException/FailedParseException.hpp>

TEST(parser, exception) {
	ieml::FailedParseException exception0{ieml::FilePath{"file.ieml"}, ieml::FailedParseException::Reason::FailedDetermineType, ieml::Mark{2, 5}};
	ASSERT_EQ(exception0.get_file_path(), ieml::FilePath{"file.ieml"});
	ASSERT_EQ(exception0.get_reason(), ieml::FailedParseException::Reason::FailedDetermineType);
	ASSERT_EQ(exception0.get_mark().line, 2);
	ASSERT_EQ(exception0.get_mark().symbol, 5);
	ASSERT_EQ(exception0.get_full_description(), ieml::String("2:5: Failed to determine the type of data in the file 'file.ieml'. Failed to determine data type."));
	
	ieml::FailedParseException exception2{ieml::FilePath{}, ieml::FailedParseException::Reason::ExpectedMapKey, ieml::Mark{0, 0}};
	ASSERT_EQ(exception2.get_reason(), ieml::FailedParseException::Reason::ExpectedMapKey);
	ASSERT_EQ(exception2.get_full_description(), ieml::String("0:0: Failed to determine the type of data. Expected Map Key."));
	
	ieml::FailedParseException exception3{ieml::FilePath{}, ieml::FailedParseException::Reason::ExpectedListItem, ieml::Mark{0, 0}};
	ASSERT_EQ(exception3.get_reason(), ieml::FailedParseException::Reason::ExpectedListItem);
	ASSERT_EQ(exception3.get_full_description(), ieml::String("0:0: Failed to determine the type of data. Expected List Item."));
	
	ieml::FailedParseException exception4{ieml::FilePath{}, ieml::FailedParseException::Reason::ImpermissibleSpace, ieml::Mark{0, 0}};
	ASSERT_EQ(exception4.get_reason(), ieml::FailedParseException::Reason::ImpermissibleSpace);
	ASSERT_EQ(exception4.get_full_description(), ieml::String("0:0: Failed to determine the type of data. A space was detected. Perhaps you meant to write a tab as an indentation."));
	
	ieml::FailedParseException exception5{ieml::FilePath{}, ieml::FailedParseException::Reason::AnchorAlreadyExists, ieml::Mark{0, 0}};
	ASSERT_EQ(exception5.get_reason(), ieml::FailedParseException::Reason::AnchorAlreadyExists);
	ASSERT_EQ(exception5.get_full_description(), ieml::String("0:0: Failed to determine the type of data. An attempt was made to take an anchor with the name of an anchor that already exists."));
	
	ieml::FailedParseException exception6{ieml::FilePath{}, ieml::FailedParseException::Reason::IncompleteString, ieml::Mark{0, 0}};
	ASSERT_EQ(exception6.get_reason(), ieml::FailedParseException::Reason::IncompleteString);
	ASSERT_EQ(exception6.get_full_description(), ieml::String("0:0: Failed to determine the type of data. The end of the file has been reached, but the String is not completed."));
}