
x = 1.2;

function packprint()
	print("_G:", _G.y);
	print("_ENV:", _ENV.y);
--[[	for i,v in pairs(_ENV) do
		print(i, type(v))
	end--]]
end

packprint();