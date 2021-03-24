#ifndef HTTPREQUEST
#define HTTPREQUEST

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/beast/ssl.hpp>
#include <string>
#include <vector>
#include "urlparser.hpp"


struct HTTPHeader {
  HTTPHeader(std::string n, std::string v) :
  name(n), value(v) {}

  std::string name;
  std::string value;
};

struct HTTPResponse {
  // struct constructor
  HTTPResponse(unsigned ver, unsigned st, std::string b) :
  version(ver), status(st), body(b) {}

  unsigned version;
  unsigned status;
  std::string body;
  std::vector<HTTPHeader> headers;
};

class HTTPRequest {
  public:
    static HTTPResponse send(URLParts up);
};

#endif
