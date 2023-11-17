#include <chrono>

#include <filesystem>
#include <iostream>
#include <fstream>

#include <vector>
#include <string>

std::chrono::duration<double, std::milli> sortAndCount(std::vector<int>& array, int size, int i, int j, bool & swapped, std::chrono::milliseconds mstart, std::chrono::milliseconds mend)
{
	mstart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	for (i = 0; i < size - 1; i++) {
		swapped = false;
		for (j = 0; j < size - i - 1; j++) {
			if (array[j] > array[j + 1]) {
				std::swap(array[j], array[j + 1]);
				swapped = true;
			}
		}

		// If no elements were swapped, break
		if (swapped == false)
			break;
	}
	mend = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch());
	return mend - mstart;
}

std::vector<int> loadDataFromFile(int size, int & buffer, std::vector<int>& data, std::string fileName)
{
	data.clear();
	fileName = std::filesystem::current_path().string() + "\\" + std::to_string(size) + ".txt";

	// Open file
	std::ifstream inputFile(fileName);

	if (inputFile.is_open()) {

		// Read values from the file
		while (inputFile >> buffer) {
			//std::cout << buffer << std::endl;
			data.push_back(buffer);
		}

		inputFile.close();
	}
	else {
		std::cout << "Unable to open file: " << fileName << std::endl;
	}

	std::cout << size << " (values) -> ";
	return data;
}

int main(int argc, char* argv[])
{
	// Memory leak detection
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::chrono::milliseconds mstart{}, mend{};
	std::chrono::duration<double, std::milli> bufferMillisec;

	int i{}, j{}, bufferInt{};
	bool swapped{};
	std::vector<int> bufferVector;
	std::string fileName;

	int arraySizes[] = { 20000, 40000, 60000, 80000, 100000, 200000, 300000, 400000, 500000 };

	// Load data from files, run it through sortAndCount(), print runtime
	for (int size : arraySizes) {
		bufferVector = loadDataFromFile(size, bufferInt, bufferVector, fileName);
		 bufferMillisec = sortAndCount(bufferVector, size, i, j, swapped, mstart, mend);
		 std::cout << bufferMillisec.count() << " (milliseconds)" << std::endl;
	}
}