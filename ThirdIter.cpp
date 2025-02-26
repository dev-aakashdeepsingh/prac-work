
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

std::vector<int> heap;
std::vector<bool> heapB;
std::vector<int> cache;

void heapifyalongpath(int index) {
    while (heap[cache[index]] < heap[cache[(index-1)/2]]) {
        std::swap(cache[(index-1)/2], cache[index]);
        index = (index -1)/2 ;
    }
}


void heapify(int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && heap[cache[left]] < heap[cache[smallest]]) {
        smallest = left;
    }
    if (right < n && heap[cache[right]] < heap[cache[smallest]]) {
        smallest = right;
    }
    if (smallest != i) {
        std::swap(cache[i], cache[smallest]);
        heapify(n, smallest);
    }
}
// removes the minimum element !

int heapExtract() {

    if (cache.empty() && heap.empty()) {
        std::cout << "Nothing here" << std::endl;
        return -1;
    }

    //cache empty initially !
    if (cache.empty()) {
        //we extract the minimum value from the heap (root), adding indices of children to the cache.
        int to_extract = heap[0];
        //making the flag for the extracted value false.
        heapB[0] = false;

        if(heap.size()>1)
            cache.push_back(1);
        if(heap.size()>2)
            cache.push_back(2);
        return to_extract;
    }

    else {
        //initially we need the indice of the element to be extracted.
        int to_extract_index = cache[0];
        cache.erase(cache.begin());
        int to_extract = heap[to_extract_index];
        heapB[to_extract_index] = false;
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

// void insert(int value) {
//     heap.push_back({value, true});
//     heapifyalongpath(heap.size() - 1);
//     heapify(cache.size(), 0);
// }

int main( int argc, char* argv[]) {

    // initializing the heap with random values
    srand(time(NULL));
    int i= 0;
    while(i < atoi(argv[1])){
        int temp = rand();
        heap.push_back(temp);
        // all counter part boolean values would be true since no extractions have happened.
        heapB.push_back(true);
        i +=1;
    }
    make_heap(heap.begin(), heap.end(), greater<int>());

    //std::cout << "Initial heap: ";
    //for (auto val : heap) std::cout << val.first << " ";
    //std::cout << std::endl;

    for(int i=0; i<atoi(argv[2]); i++){
        std::cout << "Extracted element: " << heapExtract() << std::endl;
        std::cout << "Cache after extraction: ";
        for (int val : cache) std::cout << val << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Vals in cache after extractions: ";
    for (int val : cache) std::cout << heap[val] << " ";

    return 0;
}


