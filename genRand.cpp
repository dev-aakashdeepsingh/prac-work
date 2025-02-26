#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

int main(int argc, char* argv[]) {
	srand(time(NULL));

	vector<int> minHeap;

	ofstream file("random.h");
	if (!file.is_open()) {
		cerr << "File error" << endl;
		return 1;
	}


	int i = 0;
	while (i < atoi(argv[1])) {
		int temp = rand();
		minHeap.push_back(temp);
		i += 1;
	}

	make_heap(minHeap.begin(), minHeap.end(), greater<int>());

	// storing the generated numbers in the form of a header file
	file << "#ifndef HEAP_H\n";
	file << "#define HEAP_H\n\n";
	file << "#include <iostream>\n";
	file << "#include <vector>\n";
	file << "#include <algorithm>\n\n";

	file << "inline std::vector<std::pair<int, bool>> heap = {\n";

	// Write the min-heap to the file
	for (size_t i = 0; i < minHeap.size(); ++i) {
		int num = minHeap[i];
		file << "  {" << num << ", true}";

		if (i != minHeap.size() - 1)
			file << ",\n";
		else
			file << "\n";
	}

	file << "};\n";
	file << "#endif // HEAP_H\n";  //

	file.close();

	return 0;
}
