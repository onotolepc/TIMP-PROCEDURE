#define _CRT_SECURE_NO_WARNINGS
#include "modules.h"

struct Gaming {
	char* _director;
};

bool GamingInput(Gaming& _gaming, std::ifstream &_inputStream) {
	std::string _inputData = "";
	_inputStream >> _inputData;
	if (_inputData.size() <= 0)
		return false;
	_gaming._director = new char[_inputData.size()+1];
	strcpy(_gaming._director, _inputData.c_str());
	return true;
};

void GamingOutput(Gaming& _gaming, std::ofstream &_outputStream) {
	unsigned int _sizeStr = strlen(_gaming._director);
	_outputStream << "and his director is ";
	for (unsigned int i = 0; i < _sizeStr; i++) {
		_outputStream << _gaming._director[i];
	};
	return;
};

enum typeOfCartoon {
	anime,
	animation,
	puppets,
	plasticine,
	sandy
};

struct Cartoon {
	typeOfCartoon _creationMethod;
};

bool CartoonInput(Cartoon& _cartoon, std::ifstream &_inputStream) {
	std::string _inputData = "";
	_inputStream >> _inputData;
	if (_inputData == "anime")
		_cartoon._creationMethod = anime;
	else if (_inputData == "animation")
		_cartoon._creationMethod = animation;
	else if (_inputData == "puppets")
		_cartoon._creationMethod = puppets;
	else if (_inputData == "plasticine")
		_cartoon._creationMethod = plasticine;
	else if (_inputData == "sandy")
		_cartoon._creationMethod = sandy;
	else
		return false;
	return true;
};

void CartoonOutput(Cartoon& _cartoon, std::ofstream &_outputStream) {
	_outputStream << "and this creation method are ";
	switch (_cartoon._creationMethod) {
	case anime: {
		_outputStream << "anime";
		break;
	};
	case animation: {
		_outputStream << "animation";
		break;
	};
	case puppets: {
		_outputStream << "puppets";
		break;
	};
	case plasticine: {
		_outputStream << "plasticine";
		break;
	};
	case sandy: {
		_outputStream << "sandy";
		break;
	};
	};
	return;
};

struct Document {
	unsigned short int _year;
};

bool DocumentInput(Document& _document, std::ifstream& _inputStream) {
	int _checkInt = -1;
	_inputStream >> _checkInt;
	if (_checkInt >= 0) {
		_document._year = _checkInt;
		return true;
	}
	else
		return false;
};

void DocumentOutput(Document& _document, std::ofstream& _outputStream) {
	_outputStream << " and this creation year are " << _document._year;
};

enum _keyType {
	GAMING,
	CARTOON,
	DOCUMENT
};

struct Movie {
	std::string _name;
	std::string _country;
	_keyType _key;
	union {
		Gaming _gamingMovie;
		Cartoon _cartoonMovie;
		Document _documentMovie;
	};
};

Movie* MovieInput(std::ifstream& _inputStream) {
	Movie* _movie = new Movie();
	std::string _typeString = "";
	_inputStream >> _typeString;
	_inputStream >> _movie->_name;
	_inputStream >> _movie->_country;
	if (_typeString == "GAMING") {
		_movie->_key = GAMING;
		if (!GamingInput(_movie->_gamingMovie, _inputStream))
			return NULL;
		if (_movie->_name.size() <= 0)
			return NULL;
		if (_movie->_country.size() <= 0)
			return NULL;
		return _movie;
	}
	else if (_typeString == "CARTOON") {
		_movie->_key = CARTOON;
		if (!CartoonInput(_movie->_cartoonMovie, _inputStream))
			return NULL;
		if (_movie->_name.size() <= 0)
			return NULL;
		if (_movie->_country.size() <= 0)
			return NULL;
		return _movie;
	}
	else if (_typeString == "DOCUMENT") {
		_movie->_key = DOCUMENT;
		if (!DocumentInput(_movie->_documentMovie, _inputStream))
			return NULL;
		if (_movie->_name.size() <= 0)
			return NULL;
		if (_movie->_country.size() <= 0)
			return NULL;
		return _movie;
	}
	_inputStream >> _typeString;
	return NULL;
};

void MovieOutput(Movie& _movie, std::ofstream& _outputStream) {
	switch (_movie._key)
	{
	case CARTOON: {
		_outputStream << "This is CARTOON movie with name " << _movie._name << " (Count of Vowels: " << _countOfVowels(_movie) << ") and realeased in " << _movie._country << " ";
		CartoonOutput(_movie._cartoonMovie, _outputStream);
		break;
	};
	case GAMING: {
		_outputStream << "This is GAMING movie with name " << _movie._name << " (Count of Vowels: " << _countOfVowels(_movie) << ") and realeased in " << _movie._country <<" ";
		GamingOutput(_movie._gamingMovie, _outputStream);
		break;
	};
	case DOCUMENT: {
		_outputStream << "This is DOCUMENT movie with name " << _movie._name << " (Count of Vowels: " << _countOfVowels(_movie) << ") and realeased in " << _movie._country << " ";
		DocumentOutput(_movie._documentMovie, _outputStream);
		break;
	};
	};
	return;
};

unsigned long long int _countOfVowels(Movie _movie) {
	unsigned long long int _count = 0;
	for (unsigned long long int i = 0; i < _movie._name.size(); i++)
		if (_movie._name.at(i) == 'a' || _movie._name.at(i) == 'e' || _movie._name.at(i) == 'i' || _movie._name.at(i) == 'o' || _movie._name.at(i) == 'u' || _movie._name.at(i) == 'y')
			_count++;
		else if (_movie._name.at(i) == 'A' || _movie._name.at(i) == 'E' || _movie._name.at(i) == 'I' || _movie._name.at(i) == 'O' || _movie._name.at(i) == 'U' || _movie._name.at(i) == 'Y')
			_count++;
	return _count;
};

struct ContainerNode {
	Movie* _movieData;
	ContainerNode* _next=NULL;
	ContainerNode* _prev=NULL;
};

ContainerNode* ContainerNodeInput (std::ifstream& _inputStream) {
	ContainerNode* _tempNode=new ContainerNode;
	Movie* _tempMovie = MovieInput(_inputStream);
	if (_tempMovie != NULL) {
		_tempNode->_movieData = _tempMovie;
		_tempNode->_next = NULL;
		_tempNode->_prev = NULL;
		return _tempNode;
	}
	else
		return NULL;
};

void ContainerNodeOutput(ContainerNode* _tempNode, std::ofstream& _outputStream) {
	MovieOutput(*_tempNode->_movieData, _outputStream);
};

struct Container {
	ContainerNode* _head;
	unsigned int _containerSize;
	ContainerNode *_dataContainer;
};

Container* InitializationContainer() {
	Container* _container=new Container();
	_container->_head = NULL;
	_container->_containerSize = 0;
	_container->_dataContainer = NULL;
	return _container;
};

void ContainerClear(Container *_container) {
	_container->_containerSize = 0;
	_container->_head = NULL;
	_container->_dataContainer=NULL;
	return;
};

bool compare(ContainerNode* _first, ContainerNode* _second) {
	if (_countOfVowels(*(_first->_movieData)) < _countOfVowels(*(_second->_movieData)))
		return true;
	else
		return false;
};

void ContainerSort(Container* _container) {
	for (ContainerNode* _current = _container->_head; (_current != _container->_head->_prev && _current != NULL); _current = _current->_next) {
		for (ContainerNode* _currentSecond = _current; (_currentSecond != _container->_head->_prev && _currentSecond != NULL); ) {
			_currentSecond = _currentSecond->_next;
			if (compare(_current, _currentSecond)) {
				Movie* _temp = _current->_movieData;
				_current->_movieData = _currentSecond->_movieData;
				_currentSecond->_movieData = _temp;
			};
		};
	};

};

void ContainerInput(Container* _container, std::ifstream& _inputStream) {
	_inputStream >> _container->_containerSize;
	_container->_dataContainer = new ContainerNode [_container->_containerSize];
	for (unsigned int i = 0; i < _container->_containerSize && !_inputStream.eof(); i++) {
		ContainerNode* _tempNode = ContainerNodeInput(_inputStream);
		if (_tempNode == NULL) {
			_container->_containerSize--;
			i--;
			continue;
		};
		_container->_dataContainer[i] = *_tempNode;
	};
	for (unsigned int i = 0; i < _container->_containerSize; i++) {
		if (i == 0) _container->_head = &_container->_dataContainer[i];
		_container->_dataContainer[i]._next = &(_container->_dataContainer[(i + 1) % _container->_containerSize]);
		_container->_dataContainer[i]._prev = &(_container->_dataContainer[(i + _container->_containerSize - 1) % _container->_containerSize]);
	};
	return;
};

void ContainerOutput(Container* _container, std::ofstream& _outputStream) {
	if (_container->_containerSize > 0 && _container->_head != NULL) {
		std::cout << "Skip ?\nEnter 0 if no skip, else enter\n1 if skip GAMING\n2 if skip CARTOON\n3 if skip DOCUMENT\n";
		int _skip = 0;
		std::cin >> _skip;
		if (_skip == 0) {
			_outputStream << "Count of movies: " << _container->_containerSize << '\n';
			ContainerNode* _current = _container->_head;
			do {
				ContainerNodeOutput(_current, _outputStream);
				_outputStream << '\n';
				_current = _current->_next;
			} while (_current != _container->_head);
		}
		else if (_skip == 1) {
			unsigned int _countMovies = 0;
			ContainerNode* _current = _container->_head;
			do {
				if (_current->_movieData->_key != GAMING)
					_countMovies++;
				_current = _current->_next;
			} while (_current != _container->_head);
			_outputStream << "Count of non GAMING movies: " << _countMovies << '\n';
			do {
				if (_current->_movieData->_key != GAMING) {
					ContainerNodeOutput(_current, _outputStream);
					_outputStream << '\n';
				};
				_current = _current->_next;
			} while (_current != _container->_head);
		}
		else if (_skip == 2) {
			unsigned int _countMovies = 0;
			ContainerNode* _current = _container->_head;
			do {
				if (_current->_movieData->_key != CARTOON)
					_countMovies++;
				_current = _current->_next;
			} while (_current != _container->_head);
			_outputStream << "Count of non CARTOON movies: " << _countMovies << '\n';
			do {
				if (_current->_movieData->_key != CARTOON) {
					ContainerNodeOutput(_current, _outputStream);
					_outputStream << '\n';
				};
				_current = _current->_next;
			} while (_current != _container->_head);
		}
		else if (_skip == 3) {
			unsigned int _countMovies = 0;
			ContainerNode* _current = _container->_head;
			do {
				if (_current->_movieData->_key != DOCUMENT)
					_countMovies++;
				_current = _current->_next;
			} while (_current != _container->_head);
			_outputStream << "Count of non DOCUMENT movies: " << _countMovies << '\n';
			do {
				if (_current->_movieData->_key != DOCUMENT) {
					ContainerNodeOutput(_current, _outputStream);
					_outputStream << '\n';
				};
				_current = _current->_next;
			} while (_current != _container->_head);
		};
		_outputStream << '\n';
	};
	return;
};