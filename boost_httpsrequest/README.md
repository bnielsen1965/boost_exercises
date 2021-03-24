# boost_iocontext

Control of task execution is accomplished by boost::asio::io_context with the run function.

Tasks can be submitted to an io_context and then executed by a thread or pool of threads
that call the run() function.

io_context [tasks] <--- thread { call io_context.run() to run next task }
                     \_ thread { call io_context.run() to run next task }
                     \_ thread { call io_context.run() to run next task }
