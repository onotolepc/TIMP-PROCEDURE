#define _CRT_SECURE_NO_WARNINGS
#include "modules.h"

struct Gaming {
	char* _director;
};

void GamingInput(Gaming& _gaming, std::ifstream &_inputStream) {
	std::string _inputData = "";
	_inputStream >> _inputData;
	_gaming._director = new char[_inputData.size()+1];
	strcpy(_gaming._director, _inputData.c_str());
	return;
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

void CartoonInput(Cartoon& _cartoon, std::ifstream &_inputStream) {
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
	return;
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



enum _keyType {
	GAMING,
	CARTOON
};

struct Movie {
	std::string _name;
	_keyType _key;
	union {
		Gaming _gamingMovie;
		Cartoon _cartoonMovie;
	};
};

Movie* MovieInput(std::ifstream& _inputStream) {
	Movie* _movie;
	std::string _typeString = "";
	_inputStream >> _typeString;
	if (_typeString == "GAMING") {
		_movie = new Movie();
		_movie->_key = GAMING;
		std::string _nameString = "";
		_inputStream >> _nameString;
		_movie->_name = _nameString;
		GamingInput(_movie->_gamingMovie, _inputStream);
		return _movie;
	}
	else if (_typeString == "CARTOON") {
		_movie = new Movie();
		_movie->_key = CARTOON;
		std::string _nameString = "";
		_inputStream >> _nameString;
		_movie->_name = _nameString;
		CartoonInput(_movie->_cartoonMovie, _inputStream);
		return _movie;
	}
	return NULL;
};

void MovieOutput(Movie& _movie, std::ofstream& _outputStream) {
	switch (_movie._key)
	{
	case CARTOON: {
		_outputStream << "This is CARTOON movie with name " << _movie._name << ' ';
		CartoonOutput(_movie._cartoonMovie, _outputStream);
		break;
	};
	case GAMING: {
		_outputStream << "This is GAMING movie with name " << _movie._name<<' ';
		GamingOutput(_movie._gamingMovie, _outputStream);
		break;
	};
	};
	return;
};



struct ContainerNode {
	Movie* _movieData;
	ContainerNode* _next=NULL;
	ContainerNode* _prev=NULL;
};

ContainerNode* ContainerNodeInput (std::ifstream& _inputStream) {
	ContainerNode* _tempNode=new ContainerNode;
	_tempNode->_movieData = MovieInput(_inputStream);
	_tempNode->_next = NULL;
	_tempNode->_prev = NULL;
	return _tempNode;
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

void ContainerInput(Container* _container, std::ifstream& _inputStream) {
	_inputStream >> _container->_containerSize;
	_container->_dataContainer = new ContainerNode [_container->_containerSize];
	for (unsigned int i = 0; i < _container->_containerSize && !_inputStream.eof(); i++) {
		_container->_dataContainer[i]=*ContainerNodeInput(_inputStream);
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
		std::cout << "Skip ?\nEnter 0 if no skip, else enter\n1 if skip GAMING\n2 if skip CARTOON\n";
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
			unsigned int _countCartoonMovies = 0;
			ContainerNode* _current = _container->_head;
			do {
				if (_current->_movieData->_key == CARTOON)
					_countCartoonMovies++;
				_current = _current->_next;
			} while (_current != _container->_head);
			_outputStream << "Count of only CARTOON movies: " << _countCartoonMovies << '\n';
			do {
				if (_current->_movieData->_key == CARTOON) {
					ContainerNodeOutput(_current, _outputStream);
					_outputStream << '\n';
				};
				_current = _current->_next;
			} while (_current != _container->_head);
		}
		else if (_skip == 2) {
			unsigned int _countGamingMovies = 0;
			ContainerNode* _current = _container->_head;
			do {
				if (_current->_movieData->_key == GAMING)
					_countGamingMovies++;
				_current = _current->_next;
			} while (_current != _container->_head);
			_outputStream << "Count of only GAMING movies: " << _countGamingMovies << '\n';
			do {
				if (_current->_movieData->_key == GAMING) {
					ContainerNodeOutput(_current, _outputStream);
					_outputStream << '\n';
				};
				_current = _current->_next;
			} while (_current != _container->_head);

		};
	};
	return;
};

