#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <iostream>
#include <exception>
#include <iostream>
using namespace std;

class ThreadPool {
public:
	ThreadPool(int threads);
	~ThreadPool();

	void Enqueue(function<void()> f);
	void ShutDown();

private:
	vector<thread> threadPool;
	queue<function<void()>> tasks;
	mutex tasksMutex;
	condition_variable condition;
	atomic_bool terminate;
	atomic_bool stopped;
	void Runner();
};

#endif // THREADPOOL_H
