#ifndef URLPARSER
#define URLPARSER

#include <boost/regex.hpp>

// struct to hold parsed url parts
struct URLParts
{
  // struct constructor
  URLParts(std::string pr, bool s, std::string un, std::string pw, bool a, std::string d, std::string po, std::string pa, std::string q) :
  protocol(pr), secure(s), username(un), password(pw), auth(a), domain(d), port(po), path(pa), query(q) {}

  std::string protocol;
  bool secure;
  std::string username;
  std::string password;
  bool auth;
  std::string domain;
  std::string port;
  std::string path;
  std::string query;
};


class URLParser {
  public:
    static URLParts parseUrl(std::string urlSource);
};

#endif
