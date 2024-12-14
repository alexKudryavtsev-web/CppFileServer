
# Using HttpResponse

```cpp
#include <iostream>
#include <boost/beast/http.hpp>
#include "http_response.h"
#include "http_response.cpp"

namespace beast = boost::beast;
namespace http = beast::http;

int main()
{

  try {
    HttpResponse response(http::status::ok, "Hello, world!");

    http::response<http::string_body> http_response = response.build();

    std::cout << http_response << std::endl;

  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }
}
```
