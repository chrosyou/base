
package.path = package.path..";D:\\work\\base\\yBase\\baselib\\lua\\package\\?.lua"
require "calc\\calc"

--print((package.path));
local a = 1;
print(Test(1, 3));
print((Calc:Add(2, 5)));
print((Calc:Status()));

