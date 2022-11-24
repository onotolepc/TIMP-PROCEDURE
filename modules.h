#define _CRT_SECURE_NO_WARNINGS
#ifndef __MODULES__
#define __MODULES__

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

struct Gaming;
void GamingDelete(Gaming& _gaming);
void GamingInput(Gaming& _gaming, std::ifstream &_inputStream);
void GamingOutput(Gaming& _gaming, std::ofstream &_outputStream);

struct Cartoon;
void CartoonInput(Cartoon& _cartoon, std::ifstream &_inputStream);
void CartoonOutput(Cartoon& _cartoon, std::ofstream &_outputStream);

struct Movie;
Movie* MovieInput(std::ifstream& _inputStream);
void MovieOutput(Movie& _movie, std::ofstream& _outputStream);
unsigned long long int _countOfVowels(Movie _movie);

struct ContainerNode;
ContainerNode* ContainerNodeInput(std::ifstream& _inputStream);
void ContainerNodeOutput(ContainerNode* _tempNode, std::ofstream& _outputStream);

struct Container;
Container* InitializationContainer();
void ContainerClear(Container* _container);
bool checkSort(ContainerNode* _first, ContainerNode* _second);
void ContainerSort(Container* _container);
void ContainerInput(Container* _container, std::ifstream& _inputStream);
void ContainerOutput(Container* _container, std::ofstream& _outputStream);


#endif // !__MODULES__

