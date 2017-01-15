#include <vector>
#include <iostream>





template<typename T>
class Matrix
{
public:
#pragma region constructors
	Matrix();
	Matrix(const Matrix&);
	Matrix(unsigned int, unsigned int);
#pragma endregion

	Matrix<T>& operator=(const Matrix&);
    ~Matrix();

	const std::vector<T>& GetData() const;
	std::vector<T>& GetData();

	const T& GetDataAt(unsigned int, unsigned int) const;
	const std::vector<T>& GetDataAt(unsigned int) const;

	T& GetDataAt(unsigned int, unsigned int);
	std::vector<T>& GetDataAt(unsigned int);
	
	void Add(T&, unsigned int, unsigned int);
	void Add(T&);
	void SetRowCount(unsigned int);
	void SetColumnCount(unsigned int);
	void SetSize(unsigned int, unsigned int);

	Matrix<T>& Inverse() const;
	int Determinant();

	const int ElementsCount() const;

	const unsigned int GetColumnCount() const;
	const unsigned int GetRowCount() const;
	
#pragma region Acces Operators
	const T& operator()(unsigned int, unsigned int) const;
	T& operator()(unsigned int, unsigned int);


	const std::vector<T>& operator()(unsigned int) const;
	std::vector<T>& operator()(unsigned int);


#pragma endregion



#pragma region stream operators
	friend std::istream& operator >> (std::istream & _in, Matrix<T>& _m)
	{
		for (auto i = 0; i < _m.GetRowCount(); i++)
		{
			for (auto j = 0; j < _m.GetColumnCount(); j++)
			{
				T x;
				_in >> x;
				_m.Add(x);
			}
		}
		return _in;

	}
	friend std::ostream& operator << (std::ostream &out, Matrix<T> _m)
	{

		for (auto i = 0; i < _m.GetRowCount(); i++)
		{
			for (auto j = 0; j < _m.GetColumnCount(); j++)
			{
				out << _m.GetDataAt(i, j);
			}
		}

		return out;
	}
#pragma endregion




private:
	unsigned int RowCount;
	unsigned int ColumnCount;
	std::vector<T> Data;

	private int CalculateDeterminant(std::vector<T>);


};

template<typename T>
inline int Matrix<T>::Determinant()
{
	int ret = 0;






	return ret;
}

template<typename T>
inline const int Matrix<T>::ElementsCount() const
{
	return RowCount*ColumnCount;
}

template<typename T>
inline const unsigned int Matrix<T>::GetColumnCount() const
{
	return ColumnCount;
}

template<typename T>
inline const unsigned int Matrix<T>::GetRowCount() const
{
	return RowCount;
}

template<typename T>
inline const T & Matrix<T>::operator()(unsigned int _r, unsigned int _c) const
{
	T ret = NULL;

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
	}
	else
	{
		ret = Data[_r*ColumnCount + _c];
	}


	return ret;
}

template<typename T>
inline T & Matrix<T>::operator()(unsigned int _r, unsigned int _c)
{
	T ret = NULL;

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
	}
	else
	{
		ret = Data[_r*ColumnCount + _c];
	}


	return ret;
}

template<typename T>
inline const std::vector<T>& Matrix<T>::operator()(unsigned int _r) const
{
	std::vector<T> ret{ 0 };
	if (_r > RowCount)
	{
		std::cerr << "Out of bounds";
	}
	else
	{
		for (auto i = 0; i < ColumnCount; i++)
			ret.push_back(Data[_r*ColumnCount + i]);

	}

	return ret;
}

template<typename T>
inline std::vector<T>& Matrix<T>::operator()(unsigned int _r)
{
	std::vector<T> ret{ 0 };
	if (_r > RowCount)
	{
		std::cerr << "Out of bounds";
	}
	else
	{
		for (auto i = 0; i < ColumnCount; i++)
			ret.push_back(Data[_r*ColumnCount + i]);

	}

	return ret;
}

template<typename T>
inline Matrix<T>::Matrix():
	ColumnCount(0),
	RowCount(0)
{
	Data.resize(0);
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix & _m):
	RowCount(_m.RowCount),
	ColumnCount(_m.ColumnCount)
{
	Data = _m.Data;
}

template<typename T>
inline Matrix<T>::Matrix(unsigned int _c, unsigned int _r):
	RowCount(_r),
	ColumnCount(_c)
{
	Data.resize(_r*_c);
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix & _m)
{
	ColumnCount = _m.ColumnCount;
	RowCount = _m.RowCount;
	Data = _m.Data;

	return *this;
}

template<typename T>
inline Matrix<T>::~Matrix()
{
}

template<typename T>
inline const std::vector<T>& Matrix<T>::GetData() const
{
	return Data;
}

template<typename T>
inline std::vector<T>& Matrix<T>::GetData()
{
	return Data;
}

template<typename T>
inline const T & Matrix<T>::GetDataAt(unsigned int _r, unsigned int _c) const
{
	T ret = NULL;

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
	}
	else
	{
		ret = Data[_r*ColumnCount+_c];
	}


	return ret;
	

}

template<typename T>
inline const std::vector<T>& Matrix<T>::GetDataAt(unsigned int _r) const
{
	std::vector<T> ret{ 0 };
	if (_r > RowCount)
	{
		std::cerr << "Out of bounds";
	}	
	else
	{
		for (auto i = 0; i < ColumnCount; i++)
			ret.push_back(Data[_r*ColumnCount + i]);

	}

	return ret;
}

template<typename T>
inline T & Matrix<T>::GetDataAt(unsigned int _r, unsigned int _c)
{
	T ret = NULL;

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
	}
	else
	{
		ret = Data[_r*ColumnCount + _c];
	}


	return ret;
}

template<typename T>
inline std::vector<T>& Matrix<T>::GetDataAt(unsigned int)
{
	std::vector<T> ret{ 0 };
	if (_r > RowCount)
	{
		std::cerr << "Out of bounds";
	}
	else
	{
		for (auto i = 0; i < ColumnCount; i++)
			ret.push_back(Data[_r*ColumnCount + i]);

	}

	return ret;
}

template<typename T>
inline void Matrix<T>::Add(T &item, unsigned int _r, unsigned int _c)
{
	this->Data.insert(_r*ColumnCount + _c, item);

}

template<typename T>
inline void Matrix<T>::Add(T & item)
{
	this->Data.push_back(item);

}

template<typename T>
inline void Matrix<T>::SetRowCount(unsigned int _r)
{
	RowCount = _r;
	this->Data.resize(ColumnCount * RowCount);
}

template<typename T>
inline void Matrix<T>::SetColumnCount(unsigned int _c)
{
	ColumnCount = _c;
	this->Data.resize(ColumnCount * RowCount);

}

template<typename T>
inline void Matrix<T>::SetSize(unsigned int _r, unsigned int _c)
{
	this->SetRowCount(_r);
	this->SetColumnCount(_c);

}




 
