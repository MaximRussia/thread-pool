#include "threadpool.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

int main() {

	ThreadPool pool(std::thread::hardware_concurrency());

	for (int i = 0; i < 20; i++)
	{
		pool.Enqueue([=]() {
			cout << "Start Processed: " << i << endl;
			vector<int> data;
			for (int j = 9999999; j >= 0; j--) data.push_back(j);
			auto engine = std::default_random_engine{};
			std::shuffle(data.begin(), data.end(), engine);
			std::sort(data.begin(), data.end());
			cout << "Finish Processed: " << i << endl;
		});
	}

	cin.get();

	return 0;
}
