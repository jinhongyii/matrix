#include <utility>

#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP
#include <bits/stdc++.h>
#include <cstddef>
#include <initializer_list>
#include <utility>
#include <iterator>

using std::size_t;

namespace sjtu
{

	template <class T>
	class Matrix
	{
	private:
		// your private member variables here.
        std::vector<std::vector<T> > matrix;
	public:

		Matrix() = default;

		Matrix(size_t n, size_t m, T _init = T())
		{
            if (n < 0 or m < 0) {
                throw std::invalid_argument("occur error!");
            }
			matrix.resize(n);

            for (int i = 0; i < n; i++) {
                matrix[i].resize(m,_init);
            }
		}

		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T()):Matrix(sz.first,sz.second,_init)
		{
		}

		Matrix(const Matrix &o)
		{
            matrix=o.matrix;
		}

		template <class U>
		Matrix(const Matrix<U> &o)
		{
            matrix.clear();
            matrix.resize(o.rowLength());
            for (int i = 0; i < o.rowLength(); i++) {
                for (int j = 0; j < o.columnLength(); j++) {
                    matrix[i].push_back(o(i,j));
                }
            }
		}

		/*Matrix &operator=(const Matrix &o)
		{
			matrix=o.matrix;
            return (*this);
		}*/

		//template <class U>
		/*Matrix &operator=(const Matrix<U> &o)
		{
            matrix.clear();
            matrix.resize(o.rowLength());
            for (int i = 0; i < o.rowLength(); i++) {
                for (int j = 0; j < o.columnLength(); j++) {
                    matrix[i].push_back(o(i,j));
                }
            }
            return (*this);
		}*/

		/*Matrix(Matrix &&o) noexcept
		{

		}

		Matrix &operator=(Matrix &&o) noexcept
		{

		}*/

		~Matrix() { }

		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
		    int temp;
		    bool flag=false;
            for (auto i:il) {
                if(flag and  i.size()!=temp) {
                    throw std::invalid_argument("occur error!");
                } else if (!flag) {
                    temp=i.size();
                }
                flag=true;
            }
		    matrix.clear();
		    matrix.resize(il.size());
            for (int i = 0; i < il.size(); i++) {
                for(auto j=(*(il.begin()+i)).begin();j!=(*(il.begin()+i)).end();j++) {
                    matrix[i].push_back(*j);
                }
            }
		}

	public:
		size_t rowLength() const {
            return matrix.size();
		}

		size_t columnLength() const {
            return (matrix.empty()?0:matrix[0].size());
		}

		void resize(size_t _n, size_t _m, T _init = T())
		{
		    if(_n<0 or _m<0) {
                throw std::invalid_argument("occur error!");
		    }
            matrix.resize(_n);
            for (int i = 0; i < _n; i++) {
                matrix[i].resize(_m,_init);
            }
		}

		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
		    resize(sz.first,sz.second,_init);
		}

		std::pair<size_t, size_t> size() const
		{
			std::pair<size_t ,size_t> a;
			a.first=rowLength();
			a.second=columnLength();
            return a;
		};

		void clear()
		{
			matrix.clear();
		}

	public:
		const T &operator()(size_t i, size_t j) const
		{
            if (i >= rowLength() or i<0 or j>=columnLength() or j<0) {
                throw std::invalid_argument("occur error!");
            }
            return matrix[i][j];
		}

		T &operator()(size_t i, size_t j)
		{
            if (i >= rowLength() or i<0 or j>=columnLength() or j<0) {
                throw std::invalid_argument("occur error!");
            }
            return matrix[i][j];
		}

		Matrix<T> row(size_t i) const
		{
            if (i >= rowLength() or i<0) {
                throw std::invalid_argument("occur error!");
            }
            Matrix<T> result(1,columnLength());
            for (int j = 0; j < columnLength(); j++) {
                result(0,j)=(*this)(i,j);
            }
            return result;
		}

		Matrix<T> column(size_t i) const
		{
            if (i >= columnLength() or i<0) {
                throw std::invalid_argument("occur error!");
            }
            Matrix<T> result(rowLength(),1);
            for (int j = 0; j < rowLength(); j++) {
                result(j,0)=(*this)(j,i);
            }
            return result;
		}


	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
            if (rowLength() != o.rowLength() or columnLength() != o.columnLength()) {
                return false;
            }
            for (int i = 0; i < rowLength(); i++) {
                for (int j = 0; j < columnLength(); j++) {
                    if((*this)(i,j)!=o(i,j)) {
                        return false;
                    }
                }
            }
            return true;
		}

		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
            return !((*this)==o);
		}

		Matrix operator-() const
		{
            Matrix result(rowLength(),columnLength());
            for (int i = 0; i < rowLength(); i++) {
                for (int j = 0; j < columnLength(); j++) {
                    result(i,j)=-((*this)(i,j));
                }
            }
            return result;
		}

		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
            if (rowLength() != o.rowLength() or columnLength() != o.columnLength()) {
                throw std::invalid_argument("occur error!");
            }
            for (int i = 0; i < rowLength(); i++) {
                for (int j = 0; j < columnLength(); j++) {
                    (*this)(i,j)+=o(i,j);
                }
            }
            return *this;
		}

		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
            return (*this)+=(-o);
		}

		template <class U>
		Matrix &operator*=(const U &x)
		{
            for (int i = 0; i < rowLength(); i++) {
                for (int j = 0; j < columnLength(); j++) {
                    (*this)(i,j)*=x;
                }
            }
            return *this;
		}

		Matrix tran() const
		{
			Matrix<T>  result(columnLength(),rowLength());
            for (int i = 0; i < rowLength(); i++) {
                for (int j = 0; j < columnLength(); j++) {
                    result(j,i)=(*this)(i,j);
                }
            }
            return result;
		}


	public: // iterator

		class iterator
		{
		public:
			using iterator_category = std::random_access_iterator_tag;
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;

			iterator() = default;

			iterator(Matrix<T> *m,std::pair<size_t,size_t>curplace):m(m),curplace(std::move(curplace)){

			}
			iterator(const iterator &)= default;

			iterator &operator=(const iterator &) = default;

		private:
            Matrix<T> *m;
			std::pair<size_t,size_t > curplace ;
		public:
			difference_type operator-(const iterator &o)
			{
                return (curplace.first-o.curplace.first)*m->columnLength()+curplace.second-o.curplace.second;
			}

			iterator &operator+=(difference_type offset)
			{
                auto r=curplace.first+(curplace.second+offset)/(m->columnLength());
                auto c=(curplace.second+offset)%(m->columnLength());
                curplace.first=r;
                curplace.second=c;
                return (*this);
			}

			iterator operator+(difference_type offset) const
			{
                auto temp=(*this);
                temp+=offset;
                return temp;
			}

			iterator &operator-=(difference_type offset)
			{
                auto r=curplace.first-(curplace.second-offset)/(m->columnLength());
                auto c=(curplace.second-offset)%(m->columnLength());
                if (c < 0) {
                    c+=(m->columnLength());
                    r--;
                }
                curplace.first=r;
                curplace.second=c;
                return (*this);
			}

			iterator operator-(difference_type offset) const
			{
                auto temp=(*this);
                temp-=offset;
                return temp;
			}

			iterator &operator++()
			{
                (*this)+=1;
                return (*this);
			}

            const iterator operator++(int)
			{
                auto temp=*this;
                ++(*this);
                return temp;
			}

			iterator &operator--()
			{
                (*this)-=1;
                return (*this);
			}

            const iterator operator--(int)
			{
                auto temp=*this;
                --(*this);
                return temp;
			}

			reference operator*() const
			{
                return (*m)(curplace.first,curplace.second);
			}

			pointer operator->() const
			{
                return &(*(*this));
			}

			bool operator==(const iterator &o) const
			{
                return curplace.first==o.curplace.first and curplace.second==o.curplace.second and m==o.m;
			}

			bool operator!=(const iterator &o) const
			{
                return (*this)==o;
			}
		};

		iterator begin()
		{
		    iterator result(this,{0,0});
            return result;
		}

		iterator end()
		{
            iterator result (this,{rowLength(),0});
            return result;
		}

		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r) {

            std::pair<iterator, iterator> result;
            result.first = begin() + l.first * columnLength() +l.second;
            result.second = begin() + r.first * columnLength() + r.second;
            return result;
        }
	};

}

//
namespace sjtu
{
	template <class T, class U>
	 auto operator*(const Matrix<T> &mat, const U &x)
	{
	    Matrix<decltype(U()*T())> result(mat.rowLength(),mat.columnLength());
        for (int i = 0; i < mat.rowLength(); i++) {
            for (int j = 0; j < mat.columnLength(); j++) {
                result(i,j)=mat(i,j)*x;
            }
        }
        return result;
	}

	template <class T, class U>
	 auto operator*(const U &x, const Matrix<T> &mat)
	{
        Matrix<decltype(U()*T())> result(mat.rowLength(),mat.columnLength());
        for (int i = 0; i < mat.rowLength(); i++) {
            for (int j = 0; j < mat.columnLength(); j++) {
                result(i,j)=mat(i,j)*x;
            }
        }
        return result;
	}

	template <class U, class V>
	 auto operator*(const Matrix<U> &a, const Matrix<V> &b)
	{
        if (a.columnLength() != b.rowLength()) {
            throw std::invalid_argument("occur error!");
        }
		Matrix<decltype(U()*V())> result(a.rowLength(),b.columnLength());
        for (int i = 0; i < result.rowLength(); i++) {
            for (int j = 0; j < result.columnLength(); j++) {
                for (int k = 0; k < a.columnLength(); k++) {
                    result(i,j)+=a(i,k)*b(k,j);
                }
            }
        }
        return result;
	}

	template <class U, class V>
	 auto operator+(const Matrix<U> &a, const Matrix<V> &b)
	{
        if (a.rowLength() != b.rowLength() or a.columnLength() != b.columnLength()) {
            throw std::invalid_argument("occur error!");
        }
        Matrix<decltype(U()+V())> result(a.rowLength(),b.columnLength());
        result+=a;
        result+=b;
        return result;
	}

	template <class U, class V>
	 auto operator-(const Matrix<U> &a, const Matrix<V> &b)
	{
        return a+(-b);
	}

}

#endif //SJTU_MATRIX_HPP

