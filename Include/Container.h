#pragma once
// A data structure that holds shapes in the Raytracing render loop
// Dynamic array which can retrieve data at certain points of the array

template <class T>
class Vector
{
	public:
	// Create a container with an initial size of i
	Vector<T>(const unsigned int i_size) : m_capacity(i_size), m_size(0)
	{
		m_content_pointer = static_cast<T*>(malloc(m_capacity * sizeof(T)));

	}
	
	// Default constructor that creates a container with the capacity of 256
	Vector<T>() : m_capacity(256), m_size(0)
	{
		m_content_pointer = static_cast<T*>(malloc(m_capacity * sizeof(T)));
	}

	~Vector()
	{
		for (unsigned int i = 0; i < m_size; ++i) (m_content_pointer + i)->~T();
		free (m_content_pointer);
	}

	// Push back a shape at the end of the container
	void push_back(T content)
	{
		if (m_size >= m_capacity) increase_size();
		new(m_content_pointer + m_size) T(content);
		m_size++;

	}
	// Push a shape in the front of the container
	void push_front(T content)
	{ 
		unsigned int old_size = m_capacity;
		if (m_size >= m_capacity) increase_size();
		memmove(m_content_pointer + 1, m_content_pointer, sizeof(T) * (old_size - 1));
		new(m_content_pointer) T(content);
		m_size++;
	}

	T& operator[] (const unsigned int a_i) const
	{
		//assert(a_i <= m_size);
		assert(&m_content_pointer[a_i] != nullptr);
		return m_content_pointer[a_i];
	}

	T& at(const unsigned int a_i) const
	{
		return m_content_pointer[a_i];

	}
	T& begin() const
	{
		return m_content_pointer[0];
	}
	T& end() const
	{
		return m_content_pointer[m_size - 1];
	}

	const int find(const T& ref) const
	{
		if (ref == NULL) 
		{ 
			return -1; 
		}
		for (unsigned int i = 0; i < m_size; i++)
		{
			if (m_content_pointer[i] == ref)
			{
				return i;
			}
		}
		return -1;
	}

	bool pop(unsigned int at)
	{
		if (at >= m_size) return false;
		else if (at == (m_size - 1))
		{
			T* m_tempContainerPointer = m_content_pointer;
			m_content_pointer = static_cast<T*>(malloc((m_size - 1) * sizeof(T)));
			memcpy(m_content_pointer, m_tempContainerPointer, sizeof(T) * m_size - 1);
			delete[] m_tempContainerPointer;
		}
		else  memmove(m_content_pointer + at, m_content_pointer + at + 1, sizeof(T) * (m_size - 1));
		m_size--;
		return true;
	}

	const unsigned int size() const
	{
		return m_size;
	}


	// ==================================== PRIVATE ====================================

	private:

	unsigned int m_size_increase = 8;
	unsigned int m_capacity = 0;
	unsigned int m_size = 0;
	
	T* m_content_pointer = { nullptr };


	void increase_size()
	{
		T* m_tempContainerPointer = m_content_pointer;
		unsigned int new_size = m_capacity + m_size_increase;
		m_content_pointer = static_cast<T*>(malloc((new_size) * sizeof(T)));
		if (m_content_pointer != nullptr)	memcpy(m_content_pointer, m_tempContainerPointer, sizeof(T) * m_capacity);
		m_capacity += m_size_increase;
		delete[] m_tempContainerPointer;
	}
};

