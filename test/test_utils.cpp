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

BOOST_AUTO_TEST_CASE(ParseIntPositive)
{
  BOOST_CHECK_EQUAL(parseValue<int>("42"), 42);
}

BOOST_AUTO_TEST_CASE(ParseIntNegative)
{
  BOOST_CHECK_EQUAL(parseValue<int>("-10"), -10);
}

BOOST_AUTO_TEST_CASE(ParseIntZero)
{
  BOOST_CHECK_EQUAL(parseValue<int>("0"), 0);
}

BOOST_AUTO_TEST_CASE(ParseDoublePositive)
{
  BOOST_CHECK_EQUAL(parseValue<double>("3.14"), 3.14);
}

BOOST_AUTO_TEST_CASE(ParseDoubleNegative)
{
  BOOST_CHECK_EQUAL(parseValue<double>("-2.718"), -2.718);
}

BOOST_AUTO_TEST_CASE(ParseDoubleZero)
{
  BOOST_CHECK_EQUAL(parseValue<double>("0.0"), 0.0);
}

BOOST_AUTO_TEST_CASE(ParseBoolTrue)
{
  BOOST_CHECK(parseValue<bool>("true") == true);
}

BOOST_AUTO_TEST_CASE(ParseBoolFalse)
{
  BOOST_CHECK(parseValue<bool>("false") == false);
}

BOOST_AUTO_TEST_CASE(ParseBoolTrueUppercase)
{
  BOOST_CHECK(parseValue<bool>("TRUE") == true);
}

BOOST_AUTO_TEST_CASE(ParseBoolFalseUppercase)
{
  BOOST_CHECK(parseValue<bool>("FALSE") == false);
}

BOOST_AUTO_TEST_CASE(ParseBoolFalseMixedcase)
{
  BOOST_CHECK(parseValue<bool>("FaLsE") == false);
}

BOOST_AUTO_TEST_CASE(ParseBoolTrueMixedCase)
{
  BOOST_CHECK(parseValue<bool>("TruE") == true);
}

BOOST_AUTO_TEST_CASE(ParseInvalidInt)
{
  BOOST_CHECK_THROW(parseValue<int>("abc"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseInvalidDouble)
{
  BOOST_CHECK_THROW(parseValue<double>("xyz"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseInvalidBool)
{
  BOOST_CHECK_THROW(parseValue<bool>("maybe"), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseWhitespaceInt)
{
  BOOST_CHECK_THROW(parseValue<int>("  "), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseWhitespaceBool)
{
  BOOST_CHECK_THROW(parseValue<bool>("   "), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseEmptyStringInt)
{
  BOOST_CHECK_THROW(parseValue<int>(""), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(ParseEmptyStringBool)
{
  BOOST_CHECK_THROW(parseValue<bool>(""), std::runtime_error);
}
// Проверка формата UUID

BOOST_AUTO_TEST_CASE(ValidUUIDTest1)
{
  BOOST_CHECK(isValidUUID("123e4567-e89b-12d3-a456-426614174000"));
}

BOOST_AUTO_TEST_CASE(ValidUUIDTest2)
{
  BOOST_CHECK(isValidUUID("550e8400-e29b-41d4-a716-446655440000"));
}

BOOST_AUTO_TEST_CASE(ValidUUIDTest3)
{
  BOOST_CHECK(isValidUUID("c9eb1852-8f6b-4e5e-bc0a-5f8b1a8c8a2f"));
}

BOOST_AUTO_TEST_CASE(TooShortUUIDTest)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-42661417400")); // слишком короткий
}

BOOST_AUTO_TEST_CASE(TooLongUUIDTest)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-4266141740000")); // слишком длинный
}

BOOST_AUTO_TEST_CASE(UUIDWithInvalidSymbolTest1)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-4266141740g")); // содержит недопустимый символ
}

BOOST_AUTO_TEST_CASE(UUIDWithInvalidSymbolTest2)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-42661417400x")); // содержит недопустимый символ
}

BOOST_AUTO_TEST_CASE(FewGroupsUIDTest)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-42661417")); // недостаточно групп
}

BOOST_AUTO_TEST_CASE(ManyGroupsUIDTest)
{
  BOOST_CHECK(!isValidUUID("123e4567-e89b-12d3-a456-42661417400000")); // слишком много групп
}

BOOST_AUTO_TEST_CASE(EmptyUUIDTest)
{
  BOOST_CHECK(!isValidUUID("")); // пустая строка
}

// Тест на генерацию UUID
BOOST_AUTO_TEST_CASE(GenerateUUIDTest)
{
  std::string uuid = generateUUID();

  BOOST_CHECK(!uuid.empty());
  BOOST_CHECK(isValidUUID(uuid));
}

// Тест на уникальность с несколькими вызовами
BOOST_AUTO_TEST_CASE(GenerateUniqueUUIDsTest)
{
  std::set<std::string> uuids;

  for (int i = 0; i < 100; ++i)
  {
    std::string uuid = generateUUID();
    BOOST_CHECK(isValidUUID(uuid));
    uuids.insert(uuid);
  }

  BOOST_CHECK(uuids.size() == 100);
}

BOOST_AUTO_TEST_CASE(TextWithCharsetContentTypeTests)
{
  BOOST_CHECK_EQUAL(getContentType("txt"), "text/plain; charset=utf-8");
}

BOOST_AUTO_TEST_CASE(TextDocumentContentTypeTests)
{
  BOOST_CHECK_EQUAL(getContentType("html"), "text/html");
  BOOST_CHECK_EQUAL(getContentType("htm"), "text/html");
  BOOST_CHECK_EQUAL(getContentType("css"), "text/css");
  BOOST_CHECK_EQUAL(getContentType("js"), "application/javascript");
  BOOST_CHECK_EQUAL(getContentType("csv"), "text/csv");
}

BOOST_AUTO_TEST_CASE(ImageContentTypeTests)
{
  BOOST_CHECK_EQUAL(getContentType("jpg"), "image/jpeg");
  BOOST_CHECK_EQUAL(getContentType("jpeg"), "image/jpeg");
  BOOST_CHECK_EQUAL(getContentType("png"), "image/png");
  BOOST_CHECK_EQUAL(getContentType("gif"), "image/gif");
  BOOST_CHECK_EQUAL(getContentType("svg"), "image/svg+xml");
  BOOST_CHECK_EQUAL(getContentType("webp"), "image/webp");
  BOOST_CHECK_EQUAL(getContentType("bmp"), "image/bmp");
  BOOST_CHECK_EQUAL(getContentType("ico"), "image/x-icon");
}

BOOST_AUTO_TEST_CASE(DocumentContentTypeTests)
{
  BOOST_CHECK_EQUAL(getContentType("pdf"), "application/pdf");
  BOOST_CHECK_EQUAL(getContentType("docx"), "application/vnd.openxmlformats-officedocument.wordprocessingml.document");
  BOOST_CHECK_EQUAL(getContentType("xlsx"), "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
  BOOST_CHECK_EQUAL(getContentType("pptx"), "application/vnd.openxmlformats-officedocument.presentationml.presentation");
  BOOST_CHECK_EQUAL(getContentType("doc"), "application/msword");
  BOOST_CHECK_EQUAL(getContentType("xls"), "application/vnd.ms-excel");
  BOOST_CHECK_EQUAL(getContentType("ppt"), "application/vnd.ms-powerpoint");
  BOOST_CHECK_EQUAL(getContentType("odt"), "application/vnd.oasis.opendocument.text");
  BOOST_CHECK_EQUAL(getContentType("ods"), "application/vnd.oasis.opendocument.spreadsheet");
  BOOST_CHECK_EQUAL(getContentType("odp"), "application/vnd.oasis.opendocument.presentation");
}

BOOST_AUTO_TEST_CASE(ArchiveContentTypeTests)
{
  BOOST_CHECK_EQUAL(getContentType("zip"), "application/zip");
  BOOST_CHECK_EQUAL(getContentType("rar"), "application/x-rar-compressed");
  BOOST_CHECK_EQUAL(getContentType("7z"), "application/x-7z-compressed");
  BOOST_CHECK_EQUAL(getContentType("tar"), "application/x-tar");
  BOOST_CHECK_EQUAL(getContentType("gz"), "application/gzip");
}

BOOST_AUTO_TEST_CASE(CommonOtherTypesTests)
{
  BOOST_CHECK_EQUAL(getContentType("json"), "application/json");
  BOOST_CHECK_EQUAL(getContentType("xml"), "application/xml");
  BOOST_CHECK_EQUAL(getContentType("mp3"), "audio/mpeg");
  BOOST_CHECK_EQUAL(getContentType("mp4"), "video/mp4");
  BOOST_CHECK_EQUAL(getContentType("avi"), "video/x-msvideo");
  BOOST_CHECK_EQUAL(getContentType("mov"), "video/quicktime");
}

BOOST_AUTO_TEST_CASE(UnknownExtensionTest)
{
  BOOST_CHECK_EQUAL(getContentType("unknown_extension"), "application/octet-stream");
}

BOOST_AUTO_TEST_CASE(EmptyStringTest)
{
  BOOST_CHECK_EQUAL(getContentType(""), "application/octet-stream");
}