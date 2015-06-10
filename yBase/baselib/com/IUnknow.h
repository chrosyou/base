
#pragma once
#include <iostream>

class IUnknow
{
public:
	virtual void Print() = 0;
};

class IX : public IUnknow
{
public:
	virtual void Print(){std::cout<<"X"<<std::endl;}
};

class IY : public IUnknow
{
public:
	virtual void Print(){std::cout<<"Y"<<std::endl;}
};


class CUser : public IX,
			  public IY
{
public:
	virtual void Print(){std::cout<<"user"<<std::endl;}
};
