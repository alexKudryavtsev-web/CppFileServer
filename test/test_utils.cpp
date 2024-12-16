#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "../utils.h"
#include "../utils.cpp"

BOOST_AUTO_TEST_CASE(EmptyString)
{
  BOOST_CHECK_EQUAL(trim(""), "");
}

BOOST_AUTO_TEST_CASE(StringWithSpaces)
{
  BOOST_CHECK_EQUAL(trim("   "), "");
}

BOOST_AUTO_TEST_CASE(StringWithTabs)
{
  BOOST_CHECK_EQUAL(trim("\t\t\t"), "");
}

BOOST_AUTO_TEST_CASE(StringWithLeadingSpaces)
{
  BOOST_CHECK_EQUAL(trim("   Hello World"), "Hello World");
}

BOOST_AUTO_TEST_CASE(StringWithTrailingSpaces)
{
  BOOST_CHECK_EQUAL(trim("Hello World   "), "Hello World");
}

BOOST_AUTO_TEST_CASE(StringWithLeadingAndTrailingSpaces)
{
  BOOST_CHECK_EQUAL(trim("   Hello World   "), "Hello World");
}

BOOST_AUTO_TEST_CASE(StringWithMixedSpacesAndTabs)
{
  BOOST_CHECK_EQUAL(trim("\t   Hello\tWorld   \t"), "Hello\tWorld");
}

BOOST_AUTO_TEST_CASE(StringWithoutSpaces)
{
  BOOST_CHECK_EQUAL(trim("HelloWorld"), "HelloWorld");
}

BOOST_AUTO_TEST_CASE(SingleCharacterString)
{
  BOOST_CHECK_EQUAL(trim("a"), "a");
  BOOST_CHECK_EQUAL(trim(" "), "");
  BOOST_CHECK_EQUAL(trim("\t"), "");
}

BOOST_AUTO_TEST_CASE(StringWithMultipleSpacesBetweenWords)
{
  BOOST_CHECK_EQUAL(trim("   Hello     World   "), "Hello     World");
}

BOOST_AUTO_TEST_CASE(StringWithNewlineCharacters)
{
  BOOST_CHECK_EQUAL(trim("\nHello World\n"), "Hello World");
}

BOOST_AUTO_TEST_CASE(StringWithOnlyWhitespaceCharacters)
{
  BOOST_CHECK_EQUAL(trim("\n\t \n\t"), "");
}

BOOST_AUTO_TEST_CASE(StringWithLeadingAndTrailingNewlines)
{
  BOOST_CHECK_EQUAL(trim("\n\nHello World\n\n"), "Hello World");
}

BOOST_AUTO_TEST_CASE(LongStringWithSpaces)
{
  std::string longString = "   This is a long string with spaces at the ends.   ";
  BOOST_CHECK_EQUAL(trim(longString), "This is a long string with spaces at the ends.");
}

BOOST_AUTO_TEST_CASE(NoChangeNeeded)
{
  std::string normalString = "No leading or trailing spaces.";
  BOOST_CHECK_EQUAL(trim(normalString), normalString);
}