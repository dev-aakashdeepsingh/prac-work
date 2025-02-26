
#include "random.h"

using namespace std;

std::vector<int> heap = {17,18,19,19,28,28,22};
std::vector<int> cache;
std::vector<bool> cache2;

void heapifyalongpath(int index) {
    while (heap[cache[index]].first < heap[cache[(index-1)/2]].first) {
        std::swap(cache[(index-1)/2], cache[index]);
        index = (index -1)/2 ;
    }
}

void heapify(int n, int i) {

    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[cache[left]].first < heap[cache[smallest]].first) {
        smallest = left;
    }
    if (right < n && heap[cache[right]].first < heap[cache[smallest]].first) {
        smallest = right;
    }
    if (smallest != i) {
        std::swap(cache[i], cache[smallest]);
        heapify(n, smallest);
    }
}

// removes the minimum element !

int heapExtract() {

    if (cache.empty() && cache2.empty() && heap.empty()) {
        std::cout << "Nothing here" << std::endl;
        return -1;
    }

    //cache empty initially !
    if (cache.empty() == true && cache2.empty() == true) {
	//we extract the minimum value from the heap (root), adding indices of children to the cache.
        int to_extract = heap[0];
	//making the flag (for binary search) for the extracted value false.
        cache2[0] = 0;

	if(heap.size()>1)
        	cache2.push_back(1);
	if(heap.size()>2)
        	cache1.push_back(2);

        return to_extract;
    }

    else {
	//initially we need the indice of the element to be extracted.
        int to_extract_index = cache[0];
        cache.erase(cache.begin());


        int to_extract = heap[to_extract_index].first;
        heap[to_extract_index].second = false;
	heapify(cache.size(), 0);
        int left = to_extract_index * 2 + 1;
        int right = to_extract_index * 2 + 2;

        if(left<heap.size()) {
            cache.push_back(left);
	    heapifyalongpath(cache.size() -1);
    	}
        if(right<heap.size()) {
            cache.push_back(right);
	    heapifyalongpath(cache.size() -1);
        }
        return to_extract;
    }

}


void insert(int value) {
    heap.push_back({value, true});
    heapifyalongpath(heap.size() - 1);
    heapify(cache.size(), 0);
}

int main( int argc, char* argv[]) {

    //std::cout << "Initial heap: ";
    //for (auto val : heap) std::cout << val.first << " ";
    //std::cout << std::endl;

    for(int i=0; i<atoi(argv[1]); i++){
    	std::cout << "Extracted element: " << heapExtract() << std::endl;
    	std::cout << "Cache after extraction: ";
        for (int val : cache) std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Vals in cache after extractions: ";
    for (int val : cache) std::cout << heap[val].first << " ";

    return 0;
}


