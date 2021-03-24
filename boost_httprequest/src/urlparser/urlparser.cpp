#include "urlparser.hpp"

// parse url into parts
URLParts URLParser::parseUrl(std::string urlSource)
{
  // capture 1(protocol) 2(secure) 3(username) 4(password) 5(auth) 6(domain) 7(port) 8(path) 9(query)
  boost::regex ex("(http(s)?)://(?:([^/ ]+):([^/ ]+)(@))?([^/ :]+)(?::([0-9]+))?(/[^ #?]*)?(?:\\x3f(.*))?");
  boost::smatch what;
  if(regex_match(urlSource, what, ex))
  {
    std::string protocol = std::string(what[1].first, what[1].second);
    bool secure = what[2].first != what[2].second;
    std::string username = std::string(what[3].first, what[3].second);
    std::string password = std::string(what[4].first, what[4].second);
    bool auth = what[5].first != what[5].second;
    std::string domain   = std::string(what[6].first, what[6].second);
    std::string port     = std::string(what[7].first, what[7].second);
    std::string path     = std::string(what[8].first, what[8].second);
    std::string query    = std::string(what[9].first, what[9].second);
    return URLParts(protocol, secure, username, password, auth, domain, (port.empty() ? (secure ? "443" : "80") : port), (path.empty() ? "/" : path), query);
  }
  throw std::runtime_error("Invalid URL, failed to parse.");
}
