#include "threadpool.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {

	ThreadPool pool(std::thread::hardware_concurrency());

	srand(time(NULL));

	for (int i = 0; i < 20; i++)
	{
		pool.Enqueue([=]() {
			cout << "Start Processed: " << i << endl;
			vector<int> data;
			for (int j = 999999; j >= 0; j--) data.push_back(j);
			auto engine = std::default_random_engine{};
			std::shuffle(data.begin(), data.end(), engine);
			std::sort(data.begin(), data.end());

			if (rand() % 2) { cout << "booom!" << endl; int a[5]; a[6] = 0; }

			cout << "Finish Processed: " << i << endl;
		});
	}

	cin.get();

	return 0;
}
