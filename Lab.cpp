#include "modules.h"

int main(int argc, char* argv[]) {
	std::ifstream _inputStream("asdasd.txt");
	std::ofstream _outputStream("output.txt");
	if (!_inputStream.is_open() or !_outputStream.is_open()) {
		std::cout << "Error! Incorrect file arguments. Files cannot be open.\n";
		return 882;
	};
	std::cout << "|/| START PROGRAMM |\\|\n";
	Container* _dataContainer= InitializationContainer();
	ContainerInput(_dataContainer, _inputStream);
	ContainerOutput(_dataContainer, _outputStream);
	std::cout << "Filled container:\n";
	ContainerSort(_dataContainer);
	ContainerOutput(_dataContainer, _outputStream);
	std::cout << "Sort container:\n";
	ContainerOutput(_dataContainer, _outputStream);
	ContainerClear(_dataContainer);
	ContainerOutput(_dataContainer, _outputStream);
	std::cout << "Empty container.\n";
	_outputStream.close();
	std::cout << "|/|  END PROGRAMM  |\\|\n";
	return 0;
};
