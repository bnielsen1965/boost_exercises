
#include <boost/regex.hpp>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <iostream>
#include <ostream>
#include <istream>
#include <string>
#include "urlparser.hpp"
#include "httprequest.hpp"


void usage()
{
  std::cout << "HTTP request parameters required." << std:: endl;
  std::cout << "  main HOST" << std::endl;
}


// raw socket read for http get request
void rawRead(URLParts up)
{
  boost::asio::io_context io;
  boost::asio::ip::tcp::resolver resolver(io);
  boost::asio::ip::tcp::resolver::query query(up.domain, up.port);
  std::cout << "Resolve " << up.domain << ":" << up.port << std::endl << std::endl;
  boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

  boost::asio::ip::tcp::socket socket(io);
  boost::asio::connect(socket, endpoint_iterator);

  boost::asio::streambuf request;
  std::ostream request_stream(&request);
  request_stream << "GET " << up.path << " HTTP/1.1\r\n";  // note that you can change it if you wish to HTTP/1.0
  request_stream << "Host: " << up.domain << "\r\n";
  request_stream << "Accept: */*\r\n";
  request_stream << "Connection: close\r\n\r\n";

  // Send the request.
  boost::asio::write(socket, request);

  // Read the response status line. The response streambuf will automatically
  // grow to accommodate the entire line. The growth may be limited by passing
  // a maximum size to the streambuf constructor.
  boost::asio::streambuf response;
  boost::asio::read_until(socket, response, "\r\n");

  // Check that response is OK.
  std::istream response_stream(&response);

  std::string http_version;
  response_stream >> http_version;
  unsigned int status_code;
  response_stream >> status_code;
  std::string status_message;
  std::getline(response_stream, status_message);
  std::cout << "Status message: " << status_message.c_str() << std::endl << std::endl;
  std::ostringstream error_stream;
  if (!response_stream || http_version.substr(0, 5) != "HTTP/")
  {
    error_stream << "Invalid HTTP response.";
    throw std::runtime_error(error_stream.str());
  }

  if (status_code != 200)
  {
    error_stream << "HTTP response returned status code " << status_code << ", rawRead() cannot process.";
    throw std::runtime_error(error_stream.str());
  }

  // Read the response headers, which are terminated by a blank line.
  boost::asio::read_until(socket, response, "\r\n\r\n");

  // Process the response headers.
  std::string header;
  while (std::getline(response_stream, header) && header != "\r")
  {
      std::cout << header << std::endl;
  }

  std::cout << std::endl;

  // Write whatever content we already have to output.
  if (response.size() > 0)
  {
      std::cout << &response;
  }

  // Read until EOF, writing data to output as we go.
  boost::system::error_code error;
  while (boost::asio::read(socket, response,boost::asio::transfer_at_least(1), error))
  {
        std::cout << &response;
  }

  if (error != boost::asio::error::eof)
  {
        throw boost::system::system_error(error);
  }

  std::cout << "rawRead() complete" << std::endl << std::endl;
}

int main(int argc, char * argv[])
{
  if (argc < 2) {
    usage();
    return 1;
  }

  URLParts up = URLParser::parseUrl(argv[1]);
  std::cout << "protocol: " << up.protocol << " secure: " << (up.secure ? "YES" : "NO") << std::endl <<
  "username: " << up.username << " password: " << up.password << " auth: " << (up.auth ? "YES" : "NO") << std::endl <<
  "domain: " << up.domain << " port: " << up.port << " path: " << up.path << " query: " << up.query << std::endl << std::endl;



  std::cout << "RAW READ---------------" << std::endl;
  try
  {
    rawRead(up);
  }
  catch (std::exception &e)
  {
    std::cout << "Exception in rawRead(): " << e.what() << std::endl;
  }
  std::cout << "---------------RAW READ" << std::endl << std::endl;



  try
  {
    HTTPResponse res = HTTPRequest::send(up);
    std::cout << "HEADERS..." << std::endl;
    for (HTTPHeader h : res.headers)
    {
      std::cout << "\"" << h.name << "\": \"" << h.value << "\"" << std::endl;
    }
    std::cout << std::endl;
    std::cout << res.version << std::endl << res.status << std::endl << res.body << std::endl;
//    std::cout << HTTPRequest::send(up) << std::endl;
  }
  catch (std::exception &e)
  {
    std::cout << "Exception in beastRead(): " << e.what() << std::endl;
  }


  return 0;
}
