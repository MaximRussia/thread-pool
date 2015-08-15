#include "threadpool.h"

ThreadPool::ThreadPool(int threads)
{
	terminate = false;
	stopped = false;

    for(int i = 0; i < threads; i++)
    {
    	threadPool.emplace_back(thread(&ThreadPool::Runner, this));
    }
}

void ThreadPool::Enqueue(function<void()> f)
{
	{
		unique_lock<mutex> lock(tasksMutex);
		tasks.push(f);
	}

	// Wake up one (random) thread for task.
	condition.notify_one();
}

void ThreadPool::Runner() {

	function<void()> task;
	while(true)
	{
		{
			unique_lock<mutex> lock(tasksMutex);

			// Continue when: any task in tasks or terminate
			condition.wait(lock, [this]{ return !tasks.empty() || terminate; });

			// If terminate and tasks is empty go out form Runner
			if (terminate && tasks.empty())
			{
				return;
			}

			task = tasks.front();
			tasks.pop();
		}

		try
		{
			task();
		}
		catch (exception &ex)
		{
			cout << "at " << std::thread::id() << " " << ex.what() << endl;
		}
	}
}

void ThreadPool::ShutDown()
{
	terminate = true;
	condition.notify_all();

	for(thread &thread : threadPool)
	{
		thread.join();
	}

	threadPool.clear();
	stopped = true;
}

// Destructor
ThreadPool::~ThreadPool()
{
	if (!stopped)
	{
		ShutDown();
	}
}
