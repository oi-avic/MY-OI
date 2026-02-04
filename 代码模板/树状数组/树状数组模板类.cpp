#include<cstddef>
#include<stdexcept>
#include<initializer_list>
#include<vector>
template <typename T>
class fenwick{
	private:
		std::vector<T>tr;
		size_t Size;
	public:
		fenwick():Size(0),tr(1,T()){}
		void clear()
		{
			tr.clear();
			tr.push_back(T());
			Size=0;
		}
		void update(size_t p,T val)
		{
			if(p>Size||p<1)
			{
				throw std::out_of_range("Index out of range");
			}
			for(size_t i=p;i<=Size;i+=(i&-i))
			{
				tr[i]=tr[i]+val;
			}
		}
		fenwick(std::initializer_list<T> a):tr(a.size()+1,T()),Size(a.size())
		{
			size_t i=1;
			for(const auto& v:a)
			{
				update(i,v);
			}
		}
		explicit fenwick(size_t n):tr(n+1,T()),Size(n){}
		fenwick(size_t n,T a):tr(n+1,T()),Size(n)
		{
			for(size_t i=1;i<=Size;++i)
			{
				update(i,a);
			}
		}
		template<size_t N>
		fenwick(const T (&a)[N]):tr(N+1,T()),Size(N)
		{
			for(size_t i=0;i<Size;++i)
			{
				update(i+1,a[i]);
			}
		}
		fenwick(const std::vector<T> &a):tr(a.size()+1,T()),Size(a.size())
		{
			for(size_t i=0;i<Size;++i)
			{
				update(i+1,a[i]);
			}
		}
		T query_prefix(size_t x) const
		{
			if(x>Size)
			{
				throw std::out_of_range("Index out of range");
			}
			if(x==0)
			{
				return T();
			}
			T ans=T();
			for(size_t i=x;i>0;i-=(i&-i))
			{
				ans=ans+tr[i];
			}
			return ans;
		}
		T query_range(size_t l,size_t r) const
		{
			if(l>Size||r>Size||l<1||r<1)
			{
				throw std::out_of_range("Index out of range");
			}
			if(l>r)
			{
				size_t t;
				t=l;
				l=r;
				r=t;
			}
			return query_prefix(r)-query_prefix(l-1);
		}
		T query_point(size_t x) const
		{
			if(x>Size)
			{
				throw std::out_of_range("Index out of range");
			}
			if(x==0)
			{
				return T();
			}
			return query_range(x,x);
		}
		void set(size_t p,T val)
		{
			if(p>Size||p<1)
			{
				throw std::out_of_range("Index out of range");
			}
			T now=query_point(p);
			if(now==val)
			{
				return;
			}
			update(p,val-now);
		}
		std::vector<T> to_vector() const
		{
			std::vector<T>arr;
			for(size_t i=1;i<=Size;++i)
			{
				arr.push_back(query_point(i));
			}
			return arr;
		}
		void resize(size_t newsize)
		{
			if(newsize==Size)
			{
				return;
			}
			if(newsize==0)
			{
				*this=fenwick();
				return;
			}
			std::vector<T>old=to_vector();
			Size=newsize;
			tr.assign(Size+1,T());
			for(size_t i=0;i<old.size()&&i<Size;++i)
			{
				update(i+1,old[i]);
			}
		}
		void resize(size_t newsize,T val)
		{
			if(newsize==Size)
			{
				for(size_t i=1;i<=Size;++i)
				{
					set(i,val);
				}
				return;
			}
			if(newsize==0)
			{
				*this=fenwick();
				return;
			}
			std::vector<T>old=to_vector();
			Size=newsize;
			tr.assign(Size+1,T());
			for(size_t i=0;i<Size;++i)
			{
				if(i<old.size())
				{
					update(i+1,old[i]);
				}
				else
				{
					update(i+1,val);
				}
			}
		}
		size_t lower_bound(T tar) const
		{
			if(Size==0)
			{
				return 0;
			}
			if(tar<=T())
			{
				return 1;
			}
			size_t pos=0,bit=1;
			T sum=T();
			while(bit<Size)
			{
				bit<<=1;
			}
   			for(;bit>0;bit>>=1)
			{
				size_t next=pos+bit;
				if(next<=Size&&sum+tr[next]<tar)
				{
					sum+=tr[next];
					pos=next;
				}
			}
			return pos+1;
		}
		bool empty() const
		{
			return Size==0;
		}
		size_t size() const
		{
			return Size;
		}
		bool operator == (const fenwick& other) const
		{
			if(Size!=other.size())
			{
				return false;
			}
			for(size_t i=1;i<=Size;++i)
			{
				if(tr[i]!=other.tr[i])
				{
					return false;
				}
			}
			return true;
		}
		bool operator != (const fenwick& other) const
		{
			return !(*this==other);
		}
		fenwick& operator = (const fenwick& other)
		{
			if(this!=other)
			{
				tr=other.tr;
				Size=other.Size;
			}
   			return *this;
		}
};
