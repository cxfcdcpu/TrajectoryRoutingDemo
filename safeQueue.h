#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
//!A thread safe queue that works as synchronized object
/**
  It is a template queue with thread safe mechanism
  TCP client will listen to the socket and produce message to the queue
  Another thread will pop out queue and handle the message
*/
template <typename T>
class Queue
{
 public:
  ///A template queue constructor
  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    return item;
  }
		/**
		  Pop the first data in the queue to the item reference

		  @param item The reference of where we want the pop value be popped
		*/  
  void pop(T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    queue_.pop();
  }
		/**
		  Push the value of the item to the queue

		  @param item The item value need to be pushed to the server
		*/ 
  void push(const T& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }
		/**
		  Push the address of item to the queue

		  @param item The address need to be pushed to the queue
		*/ 
  void push(T&& item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }
		/**
		  check if the queue is empty
		  @return If the queue is empty
		*/  
  bool isEmpty()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    bool res = queue_.empty();
    mlock.unlock();
    return res;
  }
 
 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};
