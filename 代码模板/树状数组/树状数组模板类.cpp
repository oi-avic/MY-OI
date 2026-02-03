#include<cstdlib>
#include<stdexcept>
#include<initializer_list>
#include<vector>
template <typename T,size_t Size>
class fenwick{
	private:
		T tr[Size+1];
	public:
		fenwick()
		{
			for(size_t i=0;i<=Size;++i)
			{
				tr[i]=T();
			}
		}
		void clear()
		{
			for(size_t i=0;i<=Size;++i)
			{
				tr[i]=T();
			}
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
		fenwick(std::initializer_list<T> a)
		{
			clear();
			size_t i=1;
			for(const auto& v:a)
			{
				if(i>Size)
				{
					break;
				}
				update(i,v);
				++i;
			}
		}
		fenwick(T a)
		{
			clear();
			for(size_t i=1;i<=Size;++i)
			{
				update(i,a);
			}
		}
		fenwick(const T a[])
		{
			clear();
			for(size_t i=0;i<Size;++i)
			{
				update(i+1,a[i]);
			}
		}
		fenwick(const std::vector<T> &a)
		{
			clear();
			size_t n=std::min(a.size(),Size);
			for(size_t i=0;i<n;++i)
			{
				update(i+1,a[i]);
			}
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
			T ans=tr[x];
			for(size_t i=x-1;i>x-(x&-x);i-=(i&-i))
			{
				ans-=tr[i];
			}
			return ans;
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
			for(size_t i=p;i<=Size;i+=(i&-i))
			{
				tr[i]=tr[i]-now+val;
			}
		}
		size_t lower_bound(T tar)
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
		constexpr size_t size() const
		{
			return Size;
		}
		bool operator == (const fenwick& other) const
		{
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
};
