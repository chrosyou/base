
#pragma once

/**
explicit 修饰的构造函数必须显示调用
*/

//智能指针
template<class T>
class smart_ptr
{
public:
	explicit smart_ptr(T* p = 0) : pointee(p) {}
	smart_ptr(smart_ptr<T>& rhs) : pointee(rhs.release()) {}
	~smart_ptr() { delete pointee; };
	smart_ptr<T>& operator=(smart_ptr<T>& rhs)
	{
		if (this != &rhs) reset(rhs.release());
		return *this;
	}
	T& operator*() const { return *pointee; }
	T* operator->() const { return pointee;};
	T* get() const { return pointee; };
	T* release()
	{
		T* oldPointee = pointee;
		pointee = 0;
		return oldPointee;
	}
	void reset(T* p = 0)
	{
		if (pointee != p)
		{
			delete pointee;
			pointee = p;
		}
	}
private:
	T* pointee;
};

/**
smart_ptr<int> a(new int(5));
smart_ptr<int> b(a);

int i = *a;
int j = *b;
*/