#define _CRTDBG_MAP_ALLOC
#include<iostream>
#include <crtdbg.h>
#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include<list>
using namespace std;

template <class T>
class Alocations
{
private:

    static T** _pointers;
    static int id;

public:

    ~Alocations()
    {

    }

    static void clear()
    {
        for (int i = 0; i < id; i++)
        {
            delete _pointers[i];
            _pointers[i] = 0;
        }
        delete[] _pointers;
    }
    static T* allocate()
    {
        _pointers[id] = new T;
        id++;
        return _pointers[id];
    }
};


template <class T>
T **  Alocations<T>::_pointers = new T*[1000];
template <class T>
int Alocations<T>::id = 0;


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    
    char* a =  Alocations<char>::allocate();

    Alocations<char>::clear();

    return 0;
}