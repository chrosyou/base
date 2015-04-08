
class Operator
{
private:
	double dOpeA;
	double dOpeB;

public:
	void SetOpeA(double dTmp) { dOpeA = dTmp; }
	double GetOpeA() { return dOpeA; }

	void SetOpeB(double dTmp) { dOpeB = dTmp; }
	double GetOpeB() { return dOpeB; }

	virtual double GetResult() { return 0; }
};

class OperatorAdd : Operator
{
	virtual double GetResult() { return GetOpeA() + GetOpeB(); }
};

class FactoryOperator
{
public:
	Operator CreateOperator(std::wstring& strOperatorName)
	{
		Operator* oper = NULL;
		if (_T("+") == strOperatorName)
		{
			oper = new OperatorAdd();
		}
	}

};