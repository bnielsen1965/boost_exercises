
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>
#include <iostream>

#define THREAD_COUNT 5


void worker () {
  std::cout << "In worker..." << std::endl;
  std::cout << "Worker done" << std::endl;
}

void worker2 (int w) {
  std::cout << "Worker " << w << " start..." << std::endl;
  int c = 2 * (THREAD_COUNT + 1 - w);
  do {
    std::cout << "Worker " << w << " count " << c << std::endl;
    boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
  } while (c--);
  std::cout << "Worker " << w << " done" << std::endl;
}


int main()
{
  boost::asio::io_context io;

  // post some tasks to the io_context
  boost::asio::post(io, &worker);
  boost::asio::post(io, std::bind(&worker2, 1));
  boost::asio::post(io, []
  {
    std::cout << "In run" << std::endl;
  });

  // use the main thread to run the tasks
  std::cout << "Main thread calls io_context run()..." << std::endl;
  io.run();

  // run returns after all tasks are complete, we can restart the io_context and add tasks and run again
  io.restart();
  boost::asio::post(io, &worker);
  std::cout << std::endl << "Main thread calls io_context run() again..." << std::endl;
  io.run();

  // add some tasks and use multiple threads to execute
  io.restart();
  size_t i;
  for (i = 0; i < THREAD_COUNT; i++)
  {
    boost::asio::post(io, std::bind(&worker2, i));
  }
  std::cout << std::endl << "Create threads that call io_context run(), output may get jumbled..." << std::endl;
  boost::thread * bt[THREAD_COUNT];
  for (i = 0; i < THREAD_COUNT; i++)
  {
    std::cout << "----------> Create thread " << i << std::endl;
    bt[i] = new boost::thread([i, &io]
    {
      // simple wait to allow all threads to be created
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
      io.run();
    });
  }
  for (i = 0; i < THREAD_COUNT; i++)
  {
    bt[i]->join();
  }

  // use strand to execute synchronously even when using parallel threads
  io.restart();
  std::cout << std::endl << "Use strand to serialize multithreaded execution of io_context tasks..." << std::endl;
  // use the io_context executor for a strand
  auto strand = boost::asio::make_strand(io.get_executor());
  for (i = 0; i < 3; i++)
  {
    boost::asio::post(strand, std::bind(&worker2, i));
  }
  for (i = 0; i < 3; i++)
  {
    std::cout << "----------> Create thread " << i << std::endl;
    bt[i] = new boost::thread([i, &io]
    {
      // simple wait to allow all threads to be created
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
      io.run();
    });
  }
  for (i = 0; i < 3; i++)
  {
    bt[i]->join();
  }

  // use work_guard to prevent io_context run() from completing and exiting threads
  io.restart();
  std::cout << std::endl << "Use work_guard to prevent io_context from ending when all tasks are complete..." << std::endl;
  auto work_guard = boost::asio::make_work_guard(io.get_executor());
  for (i = 0; i < 3; i++)
  {
    boost::asio::post(io, std::bind(&worker2, i));
  }
  std::cout << std::endl << "Create threads that call io_context run(), output may get jumbled..." << std::endl;
  for (i = 0; i < 3; i++)
  {
    std::cout << "----------> Create thread " << i << std::endl;
    bt[i] = new boost::thread([i, &io]
    {
      // simple wait to allow all threads to be created
      boost::this_thread::sleep_for(boost::chrono::seconds(1));
      io.run();
    });
  }
  for (i = 0; i < 3; i++)
  {
    // timeout should always happen because the work_guard will prevent the empty io_context from completing
    if (! bt[i]->try_join_for(boost::chrono::seconds(12)))
      std::cout << "Timeout, thread " << i << " is not done after 12 seconds..." << std::endl;
    else
      std::cout << "Timeout, thread " << i << " has completed" << std::endl;
  }
  std::cout << "Add another task to the io_context that is likely empty at this time..." << std::endl;
  boost::asio::post(io, std::bind(&worker2, i));
  boost::this_thread::sleep_for(boost::chrono::seconds(12));
  std::cout << "Stopping io_context..." << std::endl;
//  io.stop();
  work_guard.reset();

}
