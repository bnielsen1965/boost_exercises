#include "httprequest.hpp"

#include <iostream>

// parse url into parts
HTTPResponse HTTPRequest::send(URLParts up)
{
  #define HTTP_VERSION 11

boost::asio::ssl::context ctx(boost::asio::ssl::context::tlsv12_client);
// will use os ca list, but may need to impmlement a method load_root_certificates(ctx);
ctx.set_default_verify_paths();
/*
ssl::verify_none
ssl::verify_peer
ssl::verify_fail_if_no_peer_cert
ssl::verify_client_once
*/
ctx.set_verify_mode(boost::asio::ssl::verify_none); // TODO either no verification as an option or use try catch on handshake?


  boost::asio::io_context io;
  boost::asio::ip::tcp::resolver resolver(io);

boost::beast::ssl_stream<boost::beast::tcp_stream> sstream(io, ctx);
// Set SNI Hostname (many hosts need this to handshake successfully)
if(! SSL_set_tlsext_host_name(sstream.native_handle(), up.domain.c_str()))
{
    boost::beast::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
    throw boost::beast::system_error{ec};
}


//  boost::beast::tcp_stream stream(io);


  auto const endpoint_iterator = resolver.resolve(up.domain, up.port);
//  stream.connect(endpoint_iterator);

boost::beast::get_lowest_layer(sstream).connect(endpoint_iterator);
sstream.handshake(boost::asio::ssl::stream_base::client);

  boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, up.path, HTTP_VERSION}; // TODO why curly braces???
  req.set(boost::beast::http::field::host, up.domain);
  req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

//  boost::beast::http::write(stream, req);

boost::beast::http::write(sstream, req);

  boost::beast::flat_buffer buffer;
  boost::beast::http::response<boost::beast::http::dynamic_body> res;

//  boost::beast::http::read(stream, buffer, res);
std::cout << "READ START..." << std::endl;
boost::beast::http::read(sstream, buffer, res);
std::cout << "READ END..." << std::endl;

  boost::beast::error_code ec;
//  stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
std::cout << "START SHUTDOWN..." << std::endl;
sstream.shutdown(ec);
std::cout << "SHUTDOWN COMPLETE..." << std::endl;
  if (ec && ec != boost::beast::errc::not_connected)
  {
    std::cout << "EXCEPTION " << ec.message() << std::endl;
//    throw boost::beast::system_error{ec}; // TODO why curly braces???
  }

  HTTPResponse httpResponse = HTTPResponse(res.version(), res.result_int(), boost::beast::buffers_to_string(res.body().data()));

  for (auto& h : res.base())
    httpResponse.headers.push_back(HTTPHeader(std::string(h.name_string().begin(), h.name_string().end()), std::string(h.value().begin(), h.value().end())));

  return httpResponse;
}
