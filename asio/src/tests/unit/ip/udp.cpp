//
// udp.cpp
// ~~~~~~~
//
// Copyright (c) 2003-2025 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Disable autolinking for unit tests.
#if !defined(BOOST_ALL_NO_LIB)
#define BOOST_ALL_NO_LIB 1
#endif // !defined(BOOST_ALL_NO_LIB)

// Test that header file is self-contained.
#include "asio/ip/udp.hpp"

#include <cstring>
#include <functional>
#include "asio/io_context.hpp"
#include "../unit_test.hpp"
#include "../archetypes/async_result.hpp"
#include "../archetypes/gettable_socket_option.hpp"
#include "../archetypes/io_control_command.hpp"
#include "../archetypes/settable_socket_option.hpp"

//------------------------------------------------------------------------------

// ip_udp_socket_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// ip::udp::socket compile and link correctly. Runtime failures are ignored.

namespace ip_udp_socket_compile {

struct connect_handler
{
  connect_handler() {}
  void operator()(const asio::error_code&) {}
  connect_handler(connect_handler&&) {}
private:
  connect_handler(const connect_handler&);
};

struct wait_handler
{
  wait_handler() {}
  void operator()(const asio::error_code&) {}
  wait_handler(wait_handler&&) {}
private:
  wait_handler(const wait_handler&);
};

struct send_handler
{
  send_handler() {}
  void operator()(const asio::error_code&, std::size_t) {}
  send_handler(send_handler&&) {}
private:
  send_handler(const send_handler&);
};

struct receive_handler
{
  receive_handler() {}
  void operator()(const asio::error_code&, std::size_t) {}
  receive_handler(receive_handler&&) {}
private:
  receive_handler(const receive_handler&);
};

void test()
{
  using namespace asio;
  namespace ip = asio::ip;

  try
  {
    io_context ioc;
    const io_context::executor_type ioc_ex = ioc.get_executor();
    char mutable_char_buffer[128] = "";
    const char const_char_buffer[128] = "";
    socket_base::message_flags in_flags = 0;
    archetypes::settable_socket_option<void> settable_socket_option1;
    archetypes::settable_socket_option<int> settable_socket_option2;
    archetypes::settable_socket_option<double> settable_socket_option3;
    archetypes::gettable_socket_option<void> gettable_socket_option1;
    archetypes::gettable_socket_option<int> gettable_socket_option2;
    archetypes::gettable_socket_option<double> gettable_socket_option3;
    archetypes::io_control_command io_control_command;
    archetypes::immediate_handler immediate;
    archetypes::lazy_handler lazy;
    asio::error_code ec;

    // basic_datagram_socket constructors.

    ip::udp::socket socket1(ioc);
    ip::udp::socket socket2(ioc, ip::udp::v4());
    ip::udp::socket socket3(ioc, ip::udp::v6());
    ip::udp::socket socket4(ioc, ip::udp::endpoint(ip::udp::v4(), 0));
    ip::udp::socket socket5(ioc, ip::udp::endpoint(ip::udp::v6(), 0));
#if !defined(ASIO_WINDOWS_RUNTIME)
    ip::udp::socket::native_handle_type native_socket1
      = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    ip::udp::socket socket6(ioc, ip::udp::v4(), native_socket1);
#endif // !defined(ASIO_WINDOWS_RUNTIME)

    ip::udp::socket socket7(ioc_ex);
    ip::udp::socket socket8(ioc_ex, ip::udp::v4());
    ip::udp::socket socket9(ioc_ex, ip::udp::v6());
    ip::udp::socket socket10(ioc_ex, ip::udp::endpoint(ip::udp::v4(), 0));
    ip::udp::socket socket11(ioc_ex, ip::udp::endpoint(ip::udp::v6(), 0));
#if !defined(ASIO_WINDOWS_RUNTIME)
    ip::udp::socket::native_handle_type native_socket2
      = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    ip::udp::socket socket12(ioc_ex, ip::udp::v4(), native_socket2);
#endif // !defined(ASIO_WINDOWS_RUNTIME)

    ip::udp::socket socket13(std::move(socket6));

    // basic_datagram_socket operators.

    socket1 = ip::udp::socket(ioc);
    socket1 = std::move(socket2);

    // I/O object functions.

    ip::udp::socket::executor_type ex = socket1.get_executor();
    (void)ex;

    // basic_socket functions.

    ip::udp::socket::lowest_layer_type& lowest_layer = socket1.lowest_layer();
    (void)lowest_layer;

    const ip::udp::socket& socket14 = socket1;
    const ip::udp::socket::lowest_layer_type& lowest_layer2
      = socket14.lowest_layer();
    (void)lowest_layer2;

    socket1.open(ip::udp::v4());
    socket1.open(ip::udp::v6());
    socket1.open(ip::udp::v4(), ec);
    socket1.open(ip::udp::v6(), ec);

#if !defined(ASIO_WINDOWS_RUNTIME)
    ip::udp::socket::native_handle_type native_socket3
      = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    socket1.assign(ip::udp::v4(), native_socket3);
    ip::udp::socket::native_handle_type native_socket4
      = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    socket1.assign(ip::udp::v4(), native_socket4, ec);
#endif // !defined(ASIO_WINDOWS_RUNTIME)

    bool is_open = socket1.is_open();
    (void)is_open;

    socket1.close();
    socket1.close(ec);

    socket1.release();
    socket1.release(ec);

    ip::udp::socket::native_handle_type native_socket5
      = socket1.native_handle();
    (void)native_socket5;

    socket1.cancel();
    socket1.cancel(ec);

    bool at_mark1 = socket1.at_mark();
    (void)at_mark1;
    bool at_mark2 = socket1.at_mark(ec);
    (void)at_mark2;

    std::size_t available1 = socket1.available();
    (void)available1;
    std::size_t available2 = socket1.available(ec);
    (void)available2;

    socket1.bind(ip::udp::endpoint(ip::udp::v4(), 0));
    socket1.bind(ip::udp::endpoint(ip::udp::v6(), 0));
    socket1.bind(ip::udp::endpoint(ip::udp::v4(), 0), ec);
    socket1.bind(ip::udp::endpoint(ip::udp::v6(), 0), ec);

    socket1.connect(ip::udp::endpoint(ip::udp::v4(), 0));
    socket1.connect(ip::udp::endpoint(ip::udp::v6(), 0));
    socket1.connect(ip::udp::endpoint(ip::udp::v4(), 0), ec);
    socket1.connect(ip::udp::endpoint(ip::udp::v6(), 0), ec);

    socket1.async_connect(ip::udp::endpoint(ip::udp::v4(), 0),
        connect_handler());
    socket1.async_connect(ip::udp::endpoint(ip::udp::v6(), 0),
        connect_handler());
    socket1.async_connect(ip::udp::endpoint(ip::udp::v4(), 0), immediate);
    socket1.async_connect(ip::udp::endpoint(ip::udp::v6(), 0), immediate);
    int i1 = socket1.async_connect(ip::udp::endpoint(ip::udp::v4(), 0), lazy);
    (void)i1;
    int i2 = socket1.async_connect(ip::udp::endpoint(ip::udp::v6(), 0), lazy);
    (void)i2;

    socket1.set_option(settable_socket_option1);
    socket1.set_option(settable_socket_option1, ec);
    socket1.set_option(settable_socket_option2);
    socket1.set_option(settable_socket_option2, ec);
    socket1.set_option(settable_socket_option3);
    socket1.set_option(settable_socket_option3, ec);

    socket1.get_option(gettable_socket_option1);
    socket1.get_option(gettable_socket_option1, ec);
    socket1.get_option(gettable_socket_option2);
    socket1.get_option(gettable_socket_option2, ec);
    socket1.get_option(gettable_socket_option3);
    socket1.get_option(gettable_socket_option3, ec);

    socket1.io_control(io_control_command);
    socket1.io_control(io_control_command, ec);

    bool non_blocking1 = socket1.non_blocking();
    (void)non_blocking1;
    socket1.non_blocking(true);
    socket1.non_blocking(false, ec);

    bool non_blocking2 = socket1.native_non_blocking();
    (void)non_blocking2;
    socket1.native_non_blocking(true);
    socket1.native_non_blocking(false, ec);

    ip::udp::endpoint endpoint1 = socket1.local_endpoint();
    (void)endpoint1;
    ip::udp::endpoint endpoint2 = socket1.local_endpoint(ec);
    (void)endpoint2;

    ip::udp::endpoint endpoint3 = socket1.remote_endpoint();
    (void)endpoint3;
    ip::udp::endpoint endpoint4 = socket1.remote_endpoint(ec);
    (void)endpoint4;

    socket1.shutdown(socket_base::shutdown_both);
    socket1.shutdown(socket_base::shutdown_both, ec);

    socket1.wait(socket_base::wait_read);
    socket1.wait(socket_base::wait_write, ec);

    socket1.async_wait(socket_base::wait_read, wait_handler());
    socket1.async_wait(socket_base::wait_read, immediate);
    int i3 = socket1.async_wait(socket_base::wait_write, lazy);
    (void)i3;

    // basic_datagram_socket functions.

    socket1.send(buffer(mutable_char_buffer));
    socket1.send(buffer(const_char_buffer));
    socket1.send(null_buffers());
    socket1.send(buffer(mutable_char_buffer), in_flags);
    socket1.send(buffer(const_char_buffer), in_flags);
    socket1.send(null_buffers(), in_flags);
    socket1.send(buffer(mutable_char_buffer), in_flags, ec);
    socket1.send(buffer(const_char_buffer), in_flags, ec);
    socket1.send(null_buffers(), in_flags, ec);

    socket1.async_send(buffer(mutable_char_buffer), send_handler());
    socket1.async_send(buffer(const_char_buffer), send_handler());
    socket1.async_send(null_buffers(), send_handler());
    socket1.async_send(buffer(mutable_char_buffer), in_flags, send_handler());
    socket1.async_send(buffer(const_char_buffer), in_flags, send_handler());
    socket1.async_send(null_buffers(), in_flags, send_handler());
    socket1.async_send(buffer(mutable_char_buffer), immediate);
    socket1.async_send(buffer(const_char_buffer), immediate);
    socket1.async_send(null_buffers(), immediate);
    socket1.async_send(buffer(mutable_char_buffer), in_flags, immediate);
    socket1.async_send(buffer(const_char_buffer), in_flags, immediate);
    socket1.async_send(null_buffers(), in_flags, immediate);
    int i4 = socket1.async_send(buffer(mutable_char_buffer), lazy);
    (void)i4;
    int i5 = socket1.async_send(buffer(const_char_buffer), lazy);
    (void)i5;
    int i6 = socket1.async_send(null_buffers(), lazy);
    (void)i6;
    int i7 = socket1.async_send(buffer(mutable_char_buffer), in_flags, lazy);
    (void)i7;
    int i8 = socket1.async_send(buffer(const_char_buffer), in_flags, lazy);
    (void)i8;
    int i9 = socket1.async_send(null_buffers(), in_flags, lazy);
    (void)i9;

    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0));
    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0));
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0));
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0));
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0));
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0));
    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags);
    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags);
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags);
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags);
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags);
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags);
    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, ec);
    socket1.send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, ec);
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, ec);
    socket1.send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, ec);
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, ec);
    socket1.send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, ec);

    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), send_handler());
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), send_handler());
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), send_handler());
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), send_handler());
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), send_handler());
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), send_handler());
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, send_handler());
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, send_handler());
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, send_handler());
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, send_handler());
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, send_handler());
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, send_handler());
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), immediate);
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), immediate);
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), immediate);
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), immediate);
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), immediate);
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), immediate);
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, immediate);
    socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, immediate);
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, immediate);
    socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, immediate);
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, immediate);
    socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, immediate);
    int i10 = socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), lazy);
    (void)i10;
    int i11 = socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), lazy);
    (void)i11;
    int i12 = socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), lazy);
    (void)i12;
    int i13 = socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), lazy);
    (void)i13;
    int i14 = socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), lazy);
    (void)i14;
    int i15 = socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), lazy);
    (void)i15;
    int i16 = socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, lazy);
    (void)i16;
    int i17 = socket1.async_send_to(buffer(mutable_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, lazy);
    (void)i17;
    int i18 = socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, lazy);
    (void)i18;
    int i19 = socket1.async_send_to(buffer(const_char_buffer),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, lazy);
    (void)i19;
    int i20 = socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v4(), 0), in_flags, lazy);
    (void)i20;
    int i21 = socket1.async_send_to(null_buffers(),
        ip::udp::endpoint(ip::udp::v6(), 0), in_flags, lazy);
    (void)i21;

    socket1.receive(buffer(mutable_char_buffer));
    socket1.receive(null_buffers());
    socket1.receive(buffer(mutable_char_buffer), in_flags);
    socket1.receive(null_buffers(), in_flags);
    socket1.receive(buffer(mutable_char_buffer), in_flags, ec);
    socket1.receive(null_buffers(), in_flags, ec);

    socket1.async_receive(buffer(mutable_char_buffer), receive_handler());
    socket1.async_receive(null_buffers(), receive_handler());
    socket1.async_receive(buffer(mutable_char_buffer), in_flags,
        receive_handler());
    socket1.async_receive(null_buffers(), in_flags, receive_handler());
    socket1.async_receive(buffer(mutable_char_buffer), immediate);
    socket1.async_receive(null_buffers(), immediate);
    socket1.async_receive(buffer(mutable_char_buffer), in_flags, immediate);
    socket1.async_receive(null_buffers(), in_flags, immediate);
    int i22 = socket1.async_receive(buffer(mutable_char_buffer), lazy);
    (void)i22;
    int i23 = socket1.async_receive(null_buffers(), lazy);
    (void)i23;
    int i24 = socket1.async_receive(buffer(mutable_char_buffer),
        in_flags, lazy);
    (void)i24;
    int i25 = socket1.async_receive(null_buffers(), in_flags, lazy);
    (void)i25;

    ip::udp::endpoint endpoint;
    socket1.receive_from(buffer(mutable_char_buffer), endpoint);
    socket1.receive_from(null_buffers(), endpoint);
    socket1.receive_from(buffer(mutable_char_buffer), endpoint, in_flags);
    socket1.receive_from(null_buffers(), endpoint, in_flags);
    socket1.receive_from(buffer(mutable_char_buffer), endpoint, in_flags, ec);
    socket1.receive_from(null_buffers(), endpoint, in_flags, ec);

    socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, receive_handler());
    socket1.async_receive_from(null_buffers(),
        endpoint, receive_handler());
    socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, in_flags, receive_handler());
    socket1.async_receive_from(null_buffers(),
        endpoint, in_flags, receive_handler());
    socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, immediate);
    socket1.async_receive_from(null_buffers(),
        endpoint, immediate);
    socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, in_flags, immediate);
    socket1.async_receive_from(null_buffers(),
        endpoint, in_flags, immediate);
    int i26 = socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, lazy);
    (void)i26;
    int i27 = socket1.async_receive_from(null_buffers(),
        endpoint, lazy);
    (void)i27;
    int i28 = socket1.async_receive_from(buffer(mutable_char_buffer),
        endpoint, in_flags, lazy);
    (void)i28;
    int i29 = socket1.async_receive_from(null_buffers(),
        endpoint, in_flags, lazy);
    (void)i29;
  }
  catch (std::exception&)
  {
  }
}

} // namespace ip_udp_socket_compile

//------------------------------------------------------------------------------

// ip_udp_socket_runtime test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks the runtime operation of the ip::udp::socket class.

namespace ip_udp_socket_runtime {

void handle_send(size_t expected_bytes_sent,
    const asio::error_code& err, size_t bytes_sent)
{
  ASIO_CHECK(!err);
  ASIO_CHECK(expected_bytes_sent == bytes_sent);
}

void handle_recv(size_t expected_bytes_recvd,
    const asio::error_code& err, size_t bytes_recvd)
{
  ASIO_CHECK(!err);
  ASIO_CHECK(expected_bytes_recvd == bytes_recvd);
}

void test()
{
  using namespace std; // For memcmp and memset.
  using namespace asio;
  namespace ip = asio::ip;

  namespace bindns = std;
  using bindns::placeholders::_1;
  using bindns::placeholders::_2;

  io_context ioc;

  ip::udp::socket s1(ioc, ip::udp::endpoint(ip::udp::v4(), 0));
  ip::udp::endpoint target_endpoint = s1.local_endpoint();
  target_endpoint.address(ip::address_v4::loopback());

  ip::udp::socket s2(ioc);
  s2.open(ip::udp::v4());
  s2.bind(ip::udp::endpoint(ip::udp::v4(), 0));
  char send_msg[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  s2.send_to(buffer(send_msg, sizeof(send_msg)), target_endpoint);

  char recv_msg[sizeof(send_msg)];
  ip::udp::endpoint sender_endpoint;
  size_t bytes_recvd = s1.receive_from(buffer(recv_msg, sizeof(recv_msg)),
      sender_endpoint);

  ASIO_CHECK(bytes_recvd == sizeof(send_msg));
  ASIO_CHECK(memcmp(send_msg, recv_msg, sizeof(send_msg)) == 0);

  memset(recv_msg, 0, sizeof(recv_msg));

  target_endpoint = sender_endpoint;
  s1.async_send_to(buffer(send_msg, sizeof(send_msg)), target_endpoint,
      bindns::bind(handle_send, sizeof(send_msg), _1, _2));
  s2.async_receive_from(buffer(recv_msg, sizeof(recv_msg)), sender_endpoint,
      bindns::bind(handle_recv, sizeof(recv_msg), _1, _2));

  ioc.run();

  ASIO_CHECK(memcmp(send_msg, recv_msg, sizeof(send_msg)) == 0);
}

} // namespace ip_udp_socket_runtime

//------------------------------------------------------------------------------

// ip_udp_resolver_compile test
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The following test checks that all public member functions on the class
// ip::udp::resolver compile and link correctly. Runtime failures are ignored.

namespace ip_udp_resolver_compile {

struct resolve_handler
{
  resolve_handler() {}
  void operator()(const asio::error_code&,
      asio::ip::udp::resolver::results_type) {}
  resolve_handler(resolve_handler&&) {}
private:
  resolve_handler(const resolve_handler&);
};

void test()
{
  using namespace asio;
  namespace ip = asio::ip;

  try
  {
    io_context ioc;
    const io_context::executor_type ioc_ex = ioc.get_executor();
    archetypes::lazy_handler lazy;
    asio::error_code ec;
    ip::udp::endpoint e(ip::address_v4::loopback(), 0);

    // basic_resolver constructors.

    ip::udp::resolver resolver(ioc);
    ip::udp::resolver resolver2(ioc_ex);

    ip::udp::resolver resolver3(std::move(resolver));

    // basic_resolver operators.

    resolver = ip::udp::resolver(ioc);
    resolver = std::move(resolver3);

    // I/O object functions.

    ip::udp::resolver::executor_type ex = resolver.get_executor();
    (void)ex;

    // basic_resolver functions.

    resolver.cancel();

    ip::udp::resolver::results_type results1 = resolver.resolve("", "");
    (void)results1;

    ip::udp::resolver::results_type results2 = resolver.resolve("", "", ec);
    (void)results2;

    ip::udp::resolver::results_type results3 =
      resolver.resolve("", "", ip::udp::resolver::flags());
    (void)results3;

    ip::udp::resolver::results_type results4 =
      resolver.resolve("", "", ip::udp::resolver::flags(), ec);
    (void)results4;

    ip::udp::resolver::results_type results5 =
      resolver.resolve(ip::udp::v4(), "", "");
    (void)results5;

    ip::udp::resolver::results_type results6 =
      resolver.resolve(ip::udp::v4(), "", "", ec);
    (void)results6;

    ip::udp::resolver::results_type results7 =
      resolver.resolve(ip::udp::v4(), "", "", ip::udp::resolver::flags());
    (void)results7;

    ip::udp::resolver::results_type results8 =
      resolver.resolve(ip::udp::v4(), "", "", ip::udp::resolver::flags(), ec);
    (void)results8;

    ip::udp::resolver::results_type results9 = resolver.resolve(e);
    (void)results9;

    ip::udp::resolver::results_type results10 = resolver.resolve(e, ec);
    (void)results10;

    resolver.async_resolve("", "", resolve_handler());
    int i1 = resolver.async_resolve("", "", lazy);
    (void)i1;

    resolver.async_resolve("", "",
        ip::udp::resolver::flags(), resolve_handler());
    int i2 = resolver.async_resolve("", "",
        ip::udp::resolver::flags(), lazy);
    (void)i2;

    resolver.async_resolve(ip::udp::v4(), "", "", resolve_handler());
    int i3 = resolver.async_resolve(ip::udp::v4(), "", "", lazy);
    (void)i3;

    resolver.async_resolve(ip::udp::v4(),
        "", "", ip::udp::resolver::flags(), resolve_handler());
    int i4 = resolver.async_resolve(ip::udp::v4(),
        "", "", ip::udp::resolver::flags(), lazy);
    (void)i4;

    resolver.async_resolve(e, resolve_handler());
    int i5 = resolver.async_resolve(e, lazy);
    (void)i5;
  }
  catch (std::exception&)
  {
  }
}

} // namespace ip_udp_resolver_compile

//------------------------------------------------------------------------------

ASIO_TEST_SUITE
(
  "ip/udp",
  ASIO_COMPILE_TEST_CASE(ip_udp_socket_compile::test)
  ASIO_TEST_CASE(ip_udp_socket_runtime::test)
  ASIO_COMPILE_TEST_CASE(ip_udp_resolver_compile::test)
)
