
# C++ and boost libraries

A work in progress...

Exercises to brush up on C++ and learn the boost libraries.

Linux was used as the host platform in this project, alternate operating systems
can be used with some tweaks to the README details and sub-projects.


# boost libraries

**Using boost 1.75.0...**

The boost libraries are mostly header based with some components that will require
binaries if used. The libraries can be installed as pre-built binaries or compiled
from source.

https://www.boost.org/


## build boost libraries

Download the current release from the boost download page and extract in a working
directory.

https://www.boost.org/users/download/


Next use the *Getting Started guide* to prepare and build the libraries.

**NOTE:** In these exercises the libraries were not installed system wide, the include
and library paths in the projects will point to the boost library build that is in
the projects path.

https://www.boost.org/doc/libs/1_75_0/more/getting_started/index.html

**NOTE:** A custom build may be an option to perform cross platform builds, i.e.
building ARM applications on an x86_64 platform.


# Projects

The Projects directory includes a range of exercises based on specific boost libraries.

Structure of each project are similar with a */src*, */obj*, */bin*, and in some cases
*/lib* directory. Each project will also have a *Makefile* to build the project and
any needed testing files or scripts.


## boost::regex

[boost_regex](boost_regex)

The boost_regex project is the example from the boost build documentation and demonstrates
how to use the boost regex library.

This is also a simple project that can be used to verify that the build step worked,
the boost include path and library paths both work when building a project.


## std::shared_ptr

[shared_ptr](shared_ptr)

Shared pointers in C++ provide an automated way of managing memory for objects that are
created, potentially used by various parts of an application, and later destroyed or
dereferenced. Something like garbage collection without a garbage collector.

The sample application demonstrates a shared pointer and how it is tracked by multiple
references until finally destroyed.

Shared pointers were first available in the C++11 standard.


## std::stringstream

[stringstream](stringstream)

Provides stream operations on a string similar to cin and cout streams.


## boost::thread

[boost_thread](boost_thread)

Demonstrate boost threads with main thread joining until complete and joining until
a timeout.

May consider std::thread since c++11 standard as most of boost::thread was incorporated
into the c++ standard.


## boost::bind

[boost_bind](boost_bind)

Most of boost::bind became part of the c++11 standard. In most cases std::bind can be
used in place of the boost library.


## boost::asio::io_context

[boost_iocontext](boost_iocontext)

The asio and io_context library provides an controlled method of executing tasks in
an asynchrnous manner with single thread, a pool of threads, in parallel, or serially.


## boost::beast::http::request

[boost_httprequest](boot_httprequest)

Example HTTP GET request using the beast http library.






## topics

- a simple starting application, boost_regex
- shared pointers
- stringstream
- boost::thread
- boost::bind
- boost::asio::io_context
- boost::beast::http::request

- boost::asio
- boost::asio::executor_work_guard<boost::asio::io_context::executor_type>
- boost::asio::make_work_guard
- boost::beast__error_code
- boost::asio::ip::tcp::endpoint
- boost::asio::socket_base::max_listen_connections
- boost::asio::make_strand
- boost::beast::bind_front_handler
- shared_from_this
- std::move
- boost::asio::ip::tcp::socket
- boost::asio::ip::make_address
- boost::asio::io_context
- boost::asio::ip::tcp::acceptor
- boost::thread_group
