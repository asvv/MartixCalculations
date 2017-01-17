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
	void Replace(T&, unsigned int, unsigned int);
	void SetRowCount(unsigned int);
	void SetColumnCount(unsigned int);
	void SetSize(unsigned int, unsigned int);

	Matrix<T> Multiply(Matrix<T>&);
	Matrix<T> Multiply(T);

	Matrix<T> Transpose();


	Matrix<double> Inverse();
	T Determinant();

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
				_m(i,j) = x;
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
				out << _m.GetDataAt(i, j)<<" ";
			}
			std::cout << std::endl;
		}

		return out;
	}
#pragma endregion




private:
	unsigned int RowCount;
	unsigned int ColumnCount;
	std::vector<T> Data;
    T CalculateDeterminant(Matrix<T>&,unsigned int);
	Matrix<T> GetCoFactor(unsigned int, unsigned int);
	Matrix<T> GetAdjont();


};

template<typename T>
inline Matrix<double> Matrix<T>::Inverse()
{
	int N = ColumnCount;
	Matrix<double> ret(RowCount,ColumnCount);
	T det = Determinant();
	if (det == 0)
	{
		std::cerr<< "Singular matrix, can't find its inverse";
		return Matrix<double>();
	}

	//Matrix<T> adj(GetAdjont());
	auto adj = GetAdjont();
	
	for (int i = 0; i<N; i++)
		for (int j = 0; j<N; j++)
			ret(i,j) = adj(i,j) / double(det);




	return ret;
	// TODO: insert return statement here
}

template<typename T>
inline T Matrix<T>::Determinant()
{
	int ret = 0;
	
	if (this->ColumnCount != this->RowCount)
	{
		std::cerr << "Cannot calculate determinant of non-square matrix";
		return ret;
	}
	






	int dim = ColumnCount;
	ret = CalculateDeterminant(*this, dim);
	auto a = 0;
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
	

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds const ";
		T ret = NULL;
		return ret;
	}
	else
	{
		return = Data[_r*ColumnCount + _c];
	}


	//return ret;
}

template<typename T>
inline T&  Matrix<T>::operator()(unsigned int _r, unsigned int _c)
{
	

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds normal ";
		T ret = NULL;
		return ret;
	}
	else
	{
		return Data[_r*ColumnCount + _c];
	}

	
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
inline T Matrix<T>::CalculateDeterminant(Matrix<T>& _m,unsigned int dim)
{
	T ret= 0;
	//int dim = _m.ElementsCount();
	unsigned int x = 0;
	unsigned int y = 0;
	int flag = 1;

	if (dim == 1)
		ret = _m(0, 0);
		//return _m(0, 0);
	else if (dim == 2)
	{
		T a = _m(0, 0);
		T b = _m(1, 1);
		T c = _m(0, 1);
		T d = _m(1, 0);
		ret = a*b - c*d;
		 
	}
	else
	{
		Matrix<T> temp(_m);
		
		for (auto k = 0; k < dim; k++)
		{
			for (auto i = 0; i < dim; i++)
			{
				for (auto j = 0; j < dim; j++)
				{
					temp(i, j) = 0;
					if ((i != 0) && (j != k))
					{
						T item = _m(i, j);
						temp(x, y) = item;

						if (y < (dim - 2))
						{
							y++;
						}
						else
						{

							y = 0;
							x++;
						}


					}
				}
				
			}

			T tmp = _m(0, k);
			T tmp2 =  CalculateDeterminant(temp, dim - 1);
			ret += (flag*(tmp * tmp2));

			flag *= -1;
			x = 0;
			y = 0;

		}



	}
	auto a = ret;
	return ret;
}

template<typename T>
inline Matrix<T> Matrix<T>::GetCoFactor(unsigned int _r, unsigned int _c)
{
	Matrix<T> ret(RowCount, ColumnCount);
	unsigned int p = 0;
	unsigned int q = 0;

	for (int i = 0; i < RowCount; i++)
	{
		for (int j = 0; j < ColumnCount; j++)
		{
			//  Copying into temporary matrix only those element
			//  which are not in given row and column
			if (i != _r && j != _c)
			{
				
				ret(p,q++) = GetDataAt(i,j);
				//auto u = ret(p, q);
				// Row is filled, so increase row index and
				// reset col index
				if (q == ColumnCount - 1)
				{
					q = 0;
					p++;
				}
			}
		}
	}



	auto v = ret;
	int yq = 0;
	return v;
}

template<typename T>
inline Matrix<T> Matrix<T>::GetAdjont()
{
	int N = ColumnCount;

	Matrix<T> adj(RowCount, ColumnCount);
	if (ColumnCount == 1)
	{
		adj(0, 0) = 1;
	}


	int sign = 1;
	for (int i = 0; i<N; i++)
	{
		for (int j = 0; j<N; j++)
		{
			
            Matrix<T> temp=GetCoFactor(i, j);
			sign = ((i + j) % 2 == 0) ? 1 : -1;
			auto det = CalculateDeterminant(temp, N - 1);
			
			adj(j,i) = (sign)*(det);
		}
	}








	auto w = adj;
	auto n = 0;
	return adj;
	// TODO: insert return statement here
}



template<typename T>
inline Matrix<T>::Matrix():
	ColumnCount(0),
	RowCount(0)
{
	//Data.resize(0);
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
	Data.resize(_m.ElementsCount());
	for (int i = 0; i < _m.ElementsCount(); i++)
	{
		Data[i] = _m.Data[i];
	}


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
	

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
        T ret = NULL;
		return ret;
	}
	else
	{
		return Data[_r*ColumnCount+_c];
	}


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
	

	if (_c > ColumnCount || _r > RowCount)
	{
		std::cerr << "out of bounds";
        T ret = NULL;
        return ret;
	}
	else
	{
		return Data[_r*ColumnCount + _c];
	}


	
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
inline void Matrix<T>::Replace(T & item, unsigned int _r, unsigned int _c)
{
	GetDataAt(_r, _c) = item;
}

template<typename T>
inline void Matrix<T>::SetRowCount(unsigned int _r)
{
	RowCount = _r;
	//this->Data.resize(ColumnCount * RowCount);
}

template<typename T>
inline void Matrix<T>::SetColumnCount(unsigned int _c)
{
	ColumnCount = _c;
	//this->Data.resize(ColumnCount * RowCount);

}

template<typename T>
inline void Matrix<T>::SetSize(unsigned int _r, unsigned int _c)
{
	this->SetRowCount(_r);
	this->SetColumnCount(_c);

}

template<typename T>
inline Matrix<T> Matrix<T>::Multiply(Matrix<T>& _m)
{
	Matrix<T> ret(RowCount,_m.ColumnCount);
	if (ColumnCount != _m.RowCount())
	{
		std::cerr << "Error! column of first matrix not equal to row of second. ";
	
    }
	else
	{
		for (i = 0; i < RowCount; ++i)
			for (j = 0; j < _m.ColumnCount; ++j)
				for (k = 0; k < ColumnCount; ++k)
				{
					ret(i, j) += GetDataAt(i, k) * _m(k, j);
				}
	}


		return ret;
}

template<typename T>
inline Matrix<T> Matrix<T>::Multiply(T _val)
{
	Matrix<T> ret(RowCount,ColumnCount);

	for (auto i = 0; i < RowCount; i++)
		for (auto j = 0; j < ColumnCount; j++)
		{
			ret(i, j) = GetDataAt(i, j) * _val;
		}
	
		 
	return ret;
}

template<typename T>
inline Matrix<T> Matrix<T>::Transpose()
{
	Matrix<T> ret(ColumnCount,RowCount);
	for(auto i = 0 ; i < RowCount ; i++)
		for (auto j = 0; j < ColumnCount; j++)
		{
			ret(j, i) = GetDataAt(i, j);
		}

	return ret;
}




 
