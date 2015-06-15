
package.path = "D:\\work\\base\\yBase\\baselib\\lua\\metamethord\\pack.lua";
--require "pack"

function test()
	dofile("D:\\work\\base\\yBase\\baselib\\lua\\metamethord\\pack.lua")
end

print(_G.x)
print(_ENV.x)

--[[for i,v in pairs(_ENV) do
	print(i, type(v))
end--]]
test();

y = 1;
print("#####");
print(_G.y)
print(_ENV.y)

test();
print("#####");
print(_G.x)
print(_ENV.x)