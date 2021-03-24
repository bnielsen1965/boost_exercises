
#include <boost/thread.hpp>
#include <iostream>
#include <string>
#include <boost/chrono.hpp>

#define THREAD_COUNT 5


void worker () {
  std::cout << "In worker..." << std::endl;
  std::cout << "Worker done" << std::endl;
}

void worker2 (int p) {
  std::cout << "In worker " << p << ", wait " << p << " seconds" << std::endl;
  boost::this_thread::sleep_for(boost::chrono::seconds(p));
  std::cout << "Worker " << p << " done" << std::endl;
}

int main()
{
  std::cout << "Create a boost thread and wait for completion..." << std::endl;
  boost::thread t1 = boost::thread(worker);
  std::cout << "Join t1 thread..." << std::endl;
  t1.join();

  std::cout << std::endl << "Create a boost thread and pass an int argument, and wait..." << std::endl;
  boost::thread t2 = boost::thread(worker2, 5);
  std::cout << "Join t2 thread..." << std::endl;
  t2.join();

  std::cout << std::endl << "Create array of boost threads and wait on all threads..." << std::endl;
  std::cout << "WARNING: Thread output may be jumbled due to multiple threads writing to cout simultaneously!" << std::endl;
  boost::thread * bt[THREAD_COUNT];
  size_t i;
  for (i = 0; i < THREAD_COUNT; i++)
  {
    bt[i] = new boost::thread(worker2, i);
  }
  for (i = 0; i < THREAD_COUNT; i++)
  {
    bt[i]->join();
  }

  std::cout << std::endl << "Create boost thread and join for x amount of time then continue..." << std::endl;
  boost::thread t3 = boost::thread(worker2, 5);
  if (! t3.try_join_for(boost::chrono::seconds(2)))
    std::cout << "Thread is not done after 2 seconds..." << std::endl;
  else
    std::cout << "Thread completed before 2 second timeout" << std::endl;
  t3.join();
  boost::thread t4 = boost::thread(worker2, 4);
  if (! t4.try_join_for(boost::chrono::seconds(10)))
    std::cout << "Thread is not done after 10 seconds..." << std::endl;
  else
    std::cout << "Thread completed before 10 second timeout" << std::endl;
  t4.join();

  std::cout << "Main end" << std::endl;
}
