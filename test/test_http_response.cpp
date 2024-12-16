#define BOOST_TEST_MODULE test_http_response
#include <boost/test/included/unit_test.hpp>
#include <boost/beast/http.hpp>
#include "../http_response.h"
#include "../http_response.cpp"

namespace beast = boost::beast;
namespace http = beast::http;

// Тест 1: Проверка статуса 200 OK
BOOST_AUTO_TEST_CASE(HttpResponse200BuildTests)
{
  HttpResponse response(http::status::ok, "Hello, World!", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::ok);
  BOOST_CHECK_EQUAL(res.body(), "Hello, World!");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 2: Проверка статуса 404 Not Found
BOOST_AUTO_TEST_CASE(HttpResponse404BuildTests)
{
  HttpResponse response(http::status::not_found, "Page not found", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::not_found);
  BOOST_CHECK_EQUAL(res.body(), "Page not found");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 3: Проверка статуса 500 Internal Server Error
BOOST_AUTO_TEST_CASE(HttpResponse500BuildTests)
{
  HttpResponse response(http::status::internal_server_error, "Internal error", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::internal_server_error);
  BOOST_CHECK_EQUAL(res.body(), "Internal error");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 4: Проверка статуса 204 No Content
BOOST_AUTO_TEST_CASE(HttpResponse204BuildTests)
{
  HttpResponse response(http::status::no_content);
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::no_content);
  BOOST_CHECK_EQUAL(res.body(), "");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "");
}

// Тест 5: Проверка статуса 201 Created
BOOST_AUTO_TEST_CASE(HttpResponse201BuildTests)
{
  HttpResponse response(http::status::created, "Resource created", "application/json");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::created);
  BOOST_CHECK_EQUAL(res.body(), "Resource created");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "application/json");
}

// Тест 6: Проверка статуса 400 Bad Request
BOOST_AUTO_TEST_CASE(HttpResponse400BuildTests)
{
  HttpResponse response(http::status::bad_request, "Bad request", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::bad_request);
  BOOST_CHECK_EQUAL(res.body(), "Bad request");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 7: Проверка статуса 403 Forbidden
BOOST_AUTO_TEST_CASE(HttpResponse403BuildTests)
{
  HttpResponse response(http::status::forbidden, "Access denied", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::forbidden);
  BOOST_CHECK_EQUAL(res.body(), "Access denied");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 8: Проверка статуса 301 Moved Permanently
BOOST_AUTO_TEST_CASE(HttpResponse301BuildTests)
{
  HttpResponse response(http::status::moved_permanently, "Redirecting", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::moved_permanently);
  BOOST_CHECK_EQUAL(res.body(), "Redirecting");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 9: Проверка статуса 500 с пустым телом и типом контента
BOOST_AUTO_TEST_CASE(HttpEmptyResponse500BuildTests)
{
  HttpResponse response(http::status::internal_server_error);
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::internal_server_error);
  BOOST_CHECK_EQUAL(res.body(), "");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "");
}

// Тест 10: Проверка статуса 429 Too Many Requests
BOOST_AUTO_TEST_CASE(HttpResponse429BuildTests)
{
  HttpResponse response(http::status::too_many_requests, "Rate limit exceeded", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::too_many_requests);
  BOOST_CHECK_EQUAL(res.body(), "Rate limit exceeded");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 11: Проверка статуса 406 Not Acceptable
BOOST_AUTO_TEST_CASE(HttpResponse406BuildTests)
{
  HttpResponse response(http::status::not_acceptable, "Not acceptable content", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::not_acceptable);
  BOOST_CHECK_EQUAL(res.body(), "Not acceptable content");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 12: Проверка статуса 408 Request Timeout
BOOST_AUTO_TEST_CASE(HttpResponse408BuildTests)
{
  HttpResponse response(http::status::request_timeout, "Request timeout", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::request_timeout);
  BOOST_CHECK_EQUAL(res.body(), "Request timeout");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 13: Проверка статуса 415 Unsupported Media Type
BOOST_AUTO_TEST_CASE(HttpResponse415BuildTests)
{
  HttpResponse response(http::status::unsupported_media_type, "Unsupported media type", "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::unsupported_media_type);
  BOOST_CHECK_EQUAL(res.body(), "Unsupported media type");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 14: Проверка статуса 301 с JSON телом
BOOST_AUTO_TEST_CASE(HttpJSONResponse301BuildTests)
{
  std::string redirect = "from";
  std::string new_location = "to";
  HttpResponse response(http::status::moved_permanently, "{" + redirect + ": " + new_location + "}", "application/json");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::moved_permanently);
  BOOST_CHECK_EQUAL(res.body(), "{" + redirect + ": " + new_location + "}");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "application/json");
}

// Тест 15: Проверка статуса 200 с пустым типом контента
BOOST_AUTO_TEST_CASE(HttpResponse200WithEmptyContentTypeBuildTests)
{
  HttpResponse response(http::status::ok, "Empty content type test", "");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::ok);
  BOOST_CHECK_EQUAL(res.body(), "Empty content type test");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "");
}

// Тест 16: Проверка статуса 204 с пустым телом и типом контента
BOOST_AUTO_TEST_CASE(HttpEmptyResponse204BuildTests)
{
  HttpResponse response(http::status::no_content);
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::no_content);
  BOOST_CHECK_EQUAL(res.body(), "");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "");
}

// Тест 17: Проверка статуса с длинным телом
BOOST_AUTO_TEST_CASE(HttpLongResponseBuildTests)
{
  std::string longBody(1000, 'A'); // Создаем тело из 1000 символов 'A'
  HttpResponse response(http::status::ok, longBody, "text/plain");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::ok);
  BOOST_CHECK_EQUAL(res.body(), longBody);
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/plain");
}

// Тест 18: Проверка статуса с HTML телом
BOOST_AUTO_TEST_CASE(HttpHTMLResponseBuildTests)
{
  HttpResponse response(http::status::ok, "<html><body>Hello</body></html>", "text/html");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::ok);
  BOOST_CHECK_EQUAL(res.body(), "<html><body>Hello</body></html>");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "text/html");
}

// Тест 19: Проверка статуса с XML телом
BOOST_AUTO_TEST_CASE(HttpXMLResponseBuildTests)
{
  HttpResponse response(http::status::ok, "<note><to>Tove</to><from>Jani</from></note>", "application/xml");
  auto res = response.build();
  BOOST_CHECK_EQUAL(res.result(), http::status::ok);
  BOOST_CHECK_EQUAL(res.body(), "<note><to>Tove</to><from>Jani</from></note>");
  BOOST_CHECK_EQUAL(res[http::field::content_type], "application/xml");
}
