-- some test class
SomeClass = {}
SomeClass.mt = { __index = SomeClass }

-- Create a SomeClass instance.
function SomeClass.new(setValue)
	-- Create and return instance
	return setmetatable({value = setValue or 0}, SomeClass.mt)
end -- SomeClass.new

--	Returns the square length of the vector.
function SomeClass:SquaredValue()
	return self.value * self.value
end

-- Unit Tests
require "LuaUnit"
TestSomeClass = {} -- class
function TestSomeClass:SquaredValue()
	local someInstance = SomeClass.new(5)
	-- This should return 25
	Assert.Equal(25, someInstance:SquaredValue())
	-- Also print it to see something in the console window
	-- Note: We usually do not do this in unit tests ..
	print("Amazingly 5*5 is " .. someInstance:SquaredValue())
end
LuaUnit:run("TestSomeClass")
