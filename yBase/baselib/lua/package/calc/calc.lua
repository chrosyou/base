
local tmpCalc = 
{
	status = 2;
}

function tmpCalc.Add(a, b)
	return a + b;
end

function tmpCalc:Status()
	return self.status;
end

function Test(a, b)
	return a + b;
end

a = 1;

Calc = tmpCalc;
