#include "threadpool.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {

	ThreadPool pool(thread::hardware_concurrency());

	srand(time(NULL));

	for (int i = 0; i < 20; i++) {
		pool.Enqueue([=]() {
			cout << "Start Processed: " << i << endl;
			vector<int> data;
			for (int j = 999999; j >= 0; j--) data.push_back(j);
			auto engine = default_random_engine{};
			shuffle(data.begin(), data.end(), engine);
			sort(data.begin(), data.end());

			if (rand() % 2) { throw runtime_error("booom!"); }

			cout << "Finish Processed: " << i << endl;
		});
	}

	return 0;
}
