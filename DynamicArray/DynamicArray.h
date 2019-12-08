/* author : Rushikesh Keshavrao Deshmukh
*  email  : rushi.dm@gmail.com
*  date   : 08-Dec-2019
*
* Dynamic array data-structure with iterators using templates. 
* 
*/ 
#include <assert.h>
#include <array>
#include <iterator>

template<class T>
class DynamicArray
{
	size_t _size=0;
	size_t _capacity=0;
	T * _data = nullptr;

	public:

	class Iterator
	{
		T* _pdata;
	
		public:
		
		using value_type = T;
		using difference_type = std::ptrdiff_t;
		using pointer = T*;
		using reference = T&;
		using iterator_category = std::random_access_iterator_tag;

		Iterator(T* pdata):_pdata(pdata) {}

		const T& operator*() const 
		{
			return *_pdata;
		}

		T& operator*()
		{
			return *_pdata;
		}

		T* operator->()
		{
			return _pdata;
		}

		T& operator[](const size_t index)
		{
			return *(_pdata+index);
		}
	
		const T& operator[](const size_t index) const 
		{
			return *(_pdata+index);
		}

		Iterator& operator++()
		{
			_pdata++;
			return *this;
		}

		Iterator operator++(int)
		{
		    const Iterator old(_pdata);
			++(*this);
			return old;
		}

		Iterator& operator--()
		{
			_pdata--;
			return *this;
		}

		Iterator operator--(int)
		{
		    const Iterator old(_pdata);
			--(*this);
			return old;
		}

		Iterator operator+(const size_t sz)
		{
			return Iterator(_pdata+sz);
		}

		Iterator operator-(const size_t sz)
		{
			return Iterator(_pdata-sz);
		}

		difference_type operator-(Iterator const& itr)
		{
			return (_pdata - itr._pdata);
		}

		Iterator& operator+=(const size_t sz)
		{
			_pdata+=sz;
			return *this;
		}

		Iterator& operator-=(const size_t sz)
		{
			_pdata-=sz;
			return *this;
		}

		bool operator==(const Iterator& itr)
		{
			return _pdata == itr._pdata;
		}

		bool operator!=(const Iterator& itr)
		{
			return _pdata != itr._pdata;
		}

		bool operator<(const Iterator& itr)
		{
			return _pdata < itr._pdata;
		}

		bool operator>(const Iterator& itr)
		{
			return _pdata > itr._pdata;
		}

		bool operator<=(const Iterator& itr)
		{
			return _pdata <= itr._pdata;
		}

		bool operator>=(const Iterator& itr)
		{
			return _pdata >= itr._pdata;
		}
	};

	Iterator begin()
	{
		return Iterator(&_data[0]);
	}

	Iterator end()
	{
		return Iterator(&_data[_size]);
	}

	DynamicArray() {}

	~DynamicArray() 
	{
		delete[] _data;
		_size = 0;
		_capacity = 0;
	}


	DynamicArray(const size_t isize): _size(isize), _capacity(isize)
	{
		_data = new T[_size];
	}
	
	DynamicArray(const size_t isize, const T& t): DynamicArray(isize)
	{
		for(int I=0;I<isize;++I)
			_data[I] = t;
	}

	DynamicArray(DynamicArray& idynarr)
	{
		_size = idynarr._size;
		_capacity = _size;
		_data = new T[_size];
		for(int I=0;I<_size;++I)
			_data[I] = idynarr._data[I];
	}

	DynamicArray(DynamicArray&& idynarr)
	{
		_size = idynarr._size;
		_capacity = _size;
		_data = idynarr._data;
		idynarr._size = 0;
		idynarr._capacity = 0;
		idynarr._data = nullptr;
	}

	DynamicArray(std::initializer_list<T> lst): DynamicArray(lst.size())
	{
		size_t count = 0;
		for(auto & element: lst)
		{
			_data[count] = element;
			++count;
		}
	}
	
	DynamicArray(T * iarray, const size_t sz): DynamicArray(sz)
	{
		for(int I = 0; I < sz; ++I)
			_data[I] = iarray[I];
	}

	size_t size()
	{
		return _size;
	}

	const T& operator[](const size_t index) const 
	{
		assert(index < _size);
		return _data[index];
	}

	T& operator[](const size_t index) 
	{
		assert(index < _size);
		return _data[index];
	}

	void append(std::initializer_list<T> lst)
	{
		const size_t new_size = _size + lst.size();
		ensure_capacity(new_size);
		assert(_capacity >= new_size);
	
		size_t count = _size;
		for(auto& element : lst)
		{
			_data[count] = element;
			++count;
		}

		_size = new_size;
	}

	void append(DynamicArray<T> idynarr)
	{
		const size_t new_size = _size + idynarr.size();
		ensure_capacity(new_size);
		assert(_capacity >= new_size);
	
		size_t count = _size;
		for(int I=0;I<idynarr.size();++I)
		{
			_data[count] = idynarr[I];
			++count;
		}

		_size = new_size;
	}

	void append(const T* idata, const size_t sz)
	{
		const size_t new_size = _size + sz; 
		ensure_capacity(new_size);
		assert(_capacity >= new_size);
	
		size_t count = _size;
		for(int I=0;I<sz;++I)
		{
			_data[count] = idata[I];
			++count;
		}

		_size = new_size;
	}

	private:
	void ensure_capacity(const size_t new_capacity)
	{
		if(_capacity < new_capacity)
		{
			T* new_data = new T[new_capacity];

			for(int I = 0; I < _size; ++I)
				new_data[I] = _data[I];

			delete[] _data;
			_data = new_data;
			_capacity = new_capacity;
		}
	}
};
