*************************************************************************/
/*  Customized implementation of std::vector 										 */
/*	Author:Ananth S												 */
/*	License: GPL											 			 */
/*																		 */
/*************************************************************************/

template <class T>
class  Vector {
public:

    typedef T* Iterator;

    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const T & initial);
    Vector(const Vector<T>& v);
    ~Vector();

    unsigned int capacity() const;
    unsigned int size() const;
    bool empty() const;
    Iterator begin();
    Iterator end();
    T& front();
    T& back();
    void push_back(const T& value);
    void pop_back();

    void reserve(unsigned int capacity);
    void resize(unsigned int size);

    T & operator[](unsigned int index);
    Vector<T> & operator = (const Vector<T> &);
    void clear();
	
	
private:
    unsigned int _size;
    unsigned int _capacity;
    unsigned int _log;
    T* _buffer;
};
template<class T>
Vector<T>::Vector()
    : _size(0)
    , _capacity(0)
    , _log(0)
  
    ,_buffer(new char[sizeof(T) * capacity])
    // Note this assumes buffer is (char* as described above)
{}



template<class T>
    : _size(v._size)
    , _capacity(v._capacity)
    , Log(v.Log)
    , buffer(new char[sizeof(T) * _capacity])
{
    for (unsigned int i = 0; i < _size; i++)
    {
        new (buffer + sizeof(T) * i) T(v[i]);
    }
}

template<class T>
Vector<T>::Vector(unsigned int size) {
    _size = size;
    _log = ceil(_log((double) size) / _log(2.0));
    _capacity = 1 << _log;
    _buffer = new T[_capacity];
}

template <class T>
bool Vector<T>:: empty() const {
    return _size == 0;
}

template<class T>
Vector<T>::Vector(unsigned int size, const T& initial) {
    _size = size;
    _log = ceil(_log((double) size) / _log(2.0));
    _capacity = 1 << _log;
    _buffer = new T [_capacity];
    for (unsigned int i = 0; i < size; i++)
        _buffer[i] = initial;
}

template<class T>
Vector<T>& Vector<T>::operator = (const Vector<T> & v) {
    delete[] _buffer;
    _size = v._size;
    _log = v._log;
    _capacity = v._capacity;
    _buffer = new T [_capacity];
    for (unsigned int i = 0; i < _size; i++)
        _buffer[i] = v._buffer[i];
    return *this;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::begin() {
    return _buffer;
}

template<class T>
typename Vector<T>::Iterator Vector<T>::end() {
    return _buffer + size();
}

template<class T>
T& Vector<T>::front() {
    return _buffer[0];
}

template<class T>
T& Vector<T>::back() {
    return _buffer[_size - 1];
}

template<class T>
void Vector<T>::push_back(const T & v) {
    /*
        Incidentally, one common way of regrowing an array is to double the size as needed.
        This is so that if you are inserting n items at most only O(_log n) regrowths are performed
        and at most O(n) space is wasted.
    */
    if (_size >= _capacity) {
        reserve(1 << _log);
        _log++;
    }
    _buffer [_size++] = v;
}

template<class T>
void Vector<T>::pop_back() {
    _size--;
}

template<class T>
void Vector<T>::reserve(unsigned int capacity) {
    T * new_buffer = new T[capacity];

    for (unsigned int i = 0; i < _size; i++)
        new_buffer[i] = _buffer[i];

    _capacity = capacity;
    delete[] _buffer;
    _buffer = new_buffer;
}

template<class T>
unsigned int Vector<T>::size() const {
    return _size;
}

template<class T>
void Vector<T>::resize(unsigned int size) {
    _log = ceil(_log((double) size) / _log(2.0));
    reserve(1 << _log);
    _size = size;
}

template<class T>
T& Vector<T>::operator[](unsigned int index) {
    return _buffer[index];
}

template<class T>
unsigned int Vector<T>::capacity()const {
    return _capacity;
}

template<class T>
Vector<T>::~Vector() {
    delete[] _buffer;
}

template <class T>
void Vector<T>::clear() {
    _capacity = 0;
    _size = 0;
    _buffer = 0;
    _log = 0;
}
