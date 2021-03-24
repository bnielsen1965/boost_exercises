#include "httprequest.hpp"

// parse url into parts
HTTPResponse HTTPRequest::send(URLParts up)
{
  #define HTTP_VERSION 11

  boost::asio::io_context io;
  boost::asio::ip::tcp::resolver resolver(io);
  boost::beast::tcp_stream stream(io);
  auto const endpoint_iterator = resolver.resolve(up.domain, up.port);
  stream.connect(endpoint_iterator);

  boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, up.path, HTTP_VERSION}; // TODO why curly braces???
  req.set(boost::beast::http::field::host, up.domain);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

  boost::beast::http::write(stream, req);

  boost::beast::flat_buffer buffer;
  boost::beast::http::response<boost::beast::http::dynamic_body> res;
  boost::beast::http::read(stream, buffer, res);

  boost::beast::error_code ec;
  stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
  if (ec && ec != boost::beast::errc::not_connected)
    throw boost::beast::system_error{ec}; // TODO why curly braces???

  HTTPResponse httpResponse = HTTPResponse(res.version(), res.result_int(), boost::beast::buffers_to_string(res.body().data()));

  for (auto& h : res.base())
    httpResponse.headers.push_back(HTTPHeader(std::string(h.name_string().begin(), h.name_string().end()), std::string(h.value().begin(), h.value().end())));

  return httpResponse;
}
