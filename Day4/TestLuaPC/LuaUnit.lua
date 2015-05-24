--[[ LuaUnit.lua - A unit testing framework
based on LuaUnit by Philippe Fremy: http://phil.freehackers.org/luaunit/
Initial author: Ryu, Gwang (http://www.gpgstudy.com/gpgiki/LuaUnit) ]]--

-- Assert helper class
Assert = {}

-- Helper to perform low level assert (just makes sure assertion is not false)
function Assert.Check(assertion, baseMsg, userMsg)
	if not assertion then
		if userMsg then
			error(baseMsg..": "..userMsg, 3)
		else
			error(baseMsg.."!", 3)
		end
	end
end

function Assert.Error(f, ...)
	-- assert that calling f with the arguments will raise an error
	-- example: assertError(f, 1, 2) => f(1,2) should generate an error
	local hasError, errorMsg = not pcall(f, ...)
	if hasError then
		return
	end
	error("No error generated, but an error was expected!", 2)
end

-- Equal function, for non-tables actually very simple, but due a lot
-- of type checking and table compare support, this is a little bit longer
function Assert.Equal(expected, actual, msg)
	local function better_tostring(someTable)
		if type(someTable) ~= "table" then
			return tostring(someTable)
		end

		local result, done = {}, {}
		for key, value in ipairs(someTable) do
			table.insert(result, tostring(value))
			done[key] = true
		end
		for key, value in pairs(someTable) do
			if not done[key] then
				table.insert(result, tostring(key) .. "=" .. tostring(value))
			end
		end
		return tostring(someTable) .. " {" .. table.concat(result, ",") .. "}"
	end

	if type(expected) ~= type(actual) then
		Assert.Check(expected == actual,
			"Type of expected '"..better_tostring(expected)..
			"' and actual '"..better_tostring(actual).."' do not match " ..
			type(expected) .. " ~= " .. type(actual), msg)
	end

	if type(expected) == "table" then
		local tablesDoMatch = true
		for num in ipairs(expected) do
			if expected[num] ~= actual[num] then
				tablesDoMatch = false
				break
			end
		end
		if tablesDoMatch then
			return
		end
	end

	--print("checking equal: " .. tostring(expected) .. " and " ..
	--	tostring(actual))
	Assert.Check(expected == actual,
		"expected: '"..better_tostring(expected)..
		"', actual: '"..better_tostring(actual).."'", msg)
	return actual
end

function Assert.Contains(text, containsValue)
	if type(text) ~= "string" then
		error(tostring(text) .. " is not a string, unable to do a contains check!")
	end
	if string.find(text, containsValue) == nil then
		error("Unable to find " .. containsValue .. " in string " .. text)
	end
	return text
end

function Assert.NotEqual(unexpected, actual, msg)
	--print("checking not equal: " .. tostring(unexpected) .. " and " .. tostring(actual))
	Assert.Check(unexpected ~= actual, "not expected: '"..tostring(expected)..
		"', actual: '"..tostring(actual).."'", msg)
	return actual
end

function Assert.NearlyEqual(expected, actual, delta)
	if type(expected) ~= type(actual) then
		Assert.Check(expected == actual,
			"Type of expected '"..tostring(expected)..
			"' and actual '"..tostring(actual).."' do not match " ..
			type(expected) .. " ~= " .. type(actual), msg)
	end

	-- Make sure we have a delta!
	delta = delta or 0.00001

	Assert.Check(expected >= actual - delta and expected <= actual + delta,
		"expected with delta " .. delta .. ": '"..tostring(expected)..
		"', actual: '"..tostring(actual).."'", msg)
	return actual
end

function Assert.True(actual, msg)
	Assert.Check(type(actual) == "boolean",
		"true expected but was a "..type(actual), msg)
	Assert.Check(actual == true, "true expected but was false", msg)
	return actual
end

function Assert.False(actual, msg)
	Assert.Check(type(actual) == "boolean",
		"false expected but was a "..type(actual), msg)
	Assert.Check(actual == false, "false expected but was true", msg)
	return actual
end

function Assert.Match(pattern, actual, msg)
	Assert.Check(type(pattern) == "string",
		"assert_match expects the pattern as a string")
	Assert.Check(type(actual) == "string",
		"expected a string to match pattern '"..
		pattern.."' but was a '"..type(actual).."'", msg)
	Assert.Check(string.find(actual, pattern) ~= nil, "expected '"..actual..
		"' to match pattern '"..pattern.."' but it doesn't!", msg)
	return actual
end

function Assert.NotMatch(pattern, actual, msg)
	Assert.Check(type(actual) == "string",
		"expected a string to not match pattern '"..
		pattern.."' but was a '"..type(actual).."'", msg)
	Assert.Check(string.find(actual, pattern) == nil, "expected '"..actual..
		"' to not match pattern '"..pattern.."' but it does!", msg)
	return actual
end

function Assert.Nil(actual, msg)
	Assert.Check(type(actual) == "nil",
		"nil expected but was a "..type(actual), msg)
	return actual
end

function Assert.NotNil(actual, msg)
	Assert.Check(type(actual) ~= "nil", "nil not expected but it is nil!", msg)
	return actual
end

function Assert.IsBoolean(actual, msg)
	Assert.Check(type(actual) == "boolean",
		"boolean expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsNumber(actual, msg)
	Assert.Check(type(actual) == "number",
		"number expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsString(actual, msg)
	Assert.Check(type(actual) == "string",
		"string expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsTable(actual, msg)
	Assert.Check(type(actual) == "table",
		"table expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsFunction(actual, msg)
	Assert.Check(type(actual) == "function",
		"function expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsThread(actual, msg)
	Assert.Check(type(actual) == "thread",
		"thread expected but was a "..type(actual), msg)
	return actual
end

function Assert.IsUserdata(actual, msg)
	Assert.Check(type(actual) == "userdata",
		"userdata expected but was a "..type(actual), msg)
	return actual
end

-- Test all Assert methods here to make sure they are working correctly!
Assert.Check(true, "true always passes")
Assert.Error(function()
	error("This function will fail, but that is expected!")
end)
Assert.Equal(2, 2, "2 is 2")
Assert.Equal("yes", "yes", "yes is yes")
Assert.Equal({1,2,3}, {1,2,3}, "{1,2,3} is {1,2,3}")
Assert.NotEqual(2, 3, "2 is not 3")
Assert.NotEqual("yes", "yo", "yes is not yo")
Assert.True(true, "true is true")
Assert.True(300 > 18, "300 is bigger than 18")
Assert.False(false, "false will never be true")
Assert.False(10 > 700, "10 is not greater than 700")
Assert.Match("%d", "325", "325 looks like a few digits")
Assert.Match("%a", "abcd", "abdc are certainly letters")
Assert.NotMatch("%d", "abc", "abc does not contain any digits")
Assert.NotMatch("%a", "$^@^%", "no letters here")
Assert.Nil(nil, "nil is very nil-y")
Assert.NotNil(Assert, "everything else is not!")
Assert.IsBoolean(true, "true seems to be a boolean")
Assert.IsNumber(489, "looks like a number")
Assert.IsNumber(489.46, "this looks like a number too")
Assert.IsString("eouta", "string like ..")
Assert.IsString("eouta" .. "nag", "also a string")
Assert.IsTable({1, 2, 3}, "thats a table")
Assert.IsFunction(function() end, "this is a function")
--dunno how: Assert.IsThread(thread(), "a simple thread created just for this")
--got no userdata here: Assert.IsUserdata(blablabla, "blablabla is userdata")

function Assert.WrapFunctions(...)
	-- Use me to wrap a set of functions into a Runnable test class:
	-- TestToto = wrapFunctions( f1, f2, f3, f3, f5 )
	-- Now, TestToto will be picked up by LuaUnit:run()
	local testClass, testFunction
	testClass = {}
	local function storeAsMethod(idx, testName)
		testFunction = _G[testName]
		testClass[testName] = testFunction
	end
	table.foreachi( {...}, storeAsMethod )
	return testClass
end

function Assert.__genOrderedIndex(t)
	local orderedIndex = {}
	for key,_ in pairs(t) do
		table.insert(orderedIndex, key)
	end
	table.sort(orderedIndex)
	return orderedIndex
end

function Assert.OrderedNext(t, state)
	-- Equivalent of the next() function of table iteration, but returns the
	-- keys in the alphabetic order. We use a temporary ordered key table that
	-- is stored in the table being iterated.

	--print("orderedNext: state = "..tostring(state) )
	if state == nil then
		-- the first time, generate the index
		t.__orderedIndex = Assert.__genOrderedIndex( t )
		key = t.__orderedIndex[1]
		return key, t[key]
	end
	-- fetch the next value
	key = nil
	for i = 1,table.getn(t.__orderedIndex) do
		if t.__orderedIndex[i] == state then
			key = t.__orderedIndex[i+1]
		end
	end
	if key then
		return key, t[key]
	end

	-- no more value to return, cleanup
	t.__orderedIndex = nil
	return
end

function Assert.OrderedPairs(t)
	-- Equivalent of the pairs() function on tables. Allows to iterate in order
	return Assert.OrderedNext, t, nil
end

-- UnitResult class
UnitResult =
{
	failureCount = 0,
	testCount = 0,
	errorList = {},
	currentClassName = "",
	currentTestName = "",
	testHasFailure = false,
	verbosity = 0 -- set this to 1 for more info
}
function UnitResult:displayClassName()
	if self.verbosity > 0 then
		print('>>>>>>>>> '.. self.currentClassName)
	end
end

function UnitResult:displayTestName()
	if self.verbosity > 0 then
		print(">>> ".. self.currentTestName)
	end
end

function UnitResult:displayFailure(errorMsg)
	if self.verbosity == 0 then
		io.stdout:write("F")
	else
		print(errorMsg)
		print('Failed')
	end
end

function UnitResult:displaySuccess()
	if self.verbosity > 0 then
		--print ("Ok" )
	else
		io.stdout:write(".")
	end
end

function UnitResult:displayOneFailedTest(failure)
	local testName, errorMsg = unpack(failure)
	print(">>> "..testName.." failed")--tst: at " .. os.date())
	print(errorMsg)
end

function UnitResult:displayFailedTests()
	if table.getn(self.errorList) == 0 then
		return
	end
	--not that exciting text: print("Failed tests:")
	--print("-------------")
	table.foreachi(self.errorList, self.displayOneFailedTest)
	print()
end

function UnitResult:displayFinalResult()
	--print("=========================================================")
	self:displayFailedTests()
	local failurePercent
	if self.testCount == 0 then
		failurePercent = 0
	else
		failurePercent = 100 * self.failureCount / self.testCount
	end
	-- Only log if anything went wrong!
	if self.failureCount > 0 then
		local successCount = self.testCount - self.failureCount
		print(self.currentClassName .. ": " ..
			string.format("%d Unit Tests (%d succeeded / %d failed = %d%%).",
			self.testCount, successCount, self.testCount-successCount,
			100-math.ceil(failurePercent)))
	end
	-- Kill error list to start over next time!
	self.errorList = {}
	return self.failureCount
end

function UnitResult:startClass(className)
	-- Always reset counters in case we want to retest
	self.failureCount = 0
	self.testCount = 0
	self.testHasFailure = false
	self.currentClassName = className
	self:displayClassName()
end

function UnitResult:startTest(testName)
	self.currentTestName = testName
	self:displayTestName()
		self.testCount = self.testCount + 1
	self.testHasFailure = false
end

function UnitResult:addFailure(errorMsg)
	self.failureCount = self.failureCount + 1
	self.testHasFailure = true
	table.insert( self.errorList, { self.currentTestName, errorMsg } )
	self:displayFailure(errorMsg)
end

function UnitResult:endTest()
	if not self.testHasFailure then
		self:displaySuccess()
	end
end
-- class UnitResult end

LuaUnit = { result = UnitResult }
-- Split text into a list consisting of the strings in text,
-- separated by strings matching delimiter (which may be a pattern).
-- example: strsplit(",%s*", "Anna, Bob, Charlie,Dolores")
function LuaUnit.strsplit(delimiter, text)
	local list = {}
	local pos = 1
	-- this would result in endless loops, prevent that
	if string.find("", delimiter, 1) then
		error("delimiter matches empty string!")
	end
	if type(text) ~= "string" then
		error("text " .. tostring(text) .. " is not a string, unable to continue!")
	end
	while true do
		local first, last = string.find(text, delimiter, pos)
		-- found?
		if first then
			table.insert(list, string.sub(text, pos, first-1))
			pos = last+1
		else
			table.insert(list, string.sub(text, pos))
			break
		end
	end
	return list
end

function LuaUnit.strip_luaunit_stack(stack_trace)
	-- Transform string into array
	local originalStack = LuaUnit.strsplit("\n", stack_trace)
	local retStack = {}
	-- Go through all lines and only add those that are not boring
	for line = 1, table.getn(originalStack) do
		if not string.find(originalStack[line], "stack traceback:") and
			not string.find(originalStack[line], "in function 'xpcall'") and
			not string.find(originalStack[line], "in function 'error'") and
			not string.find(originalStack[line], "in function 'foreachi'") and
			not string.find(originalStack[line], ".\LuaUnit.lua:") then
			table.insert(retStack, originalStack[line])
		end
	end
	-- In case we do have no more useable info (maybe something went wrong
	-- inside LuaUnit.cs), use the original stack instead!
	if table.getn(retStack) < 2 then
		return stack_trace
	end
	-- Build string from table again
	return table.concat(retStack, "\n")
	--[[ orginial
	local stack_list = LuaUnit.strsplit("\n", stack_trace)
	local strip_end = nil
	for i = table.getn(stack_list),1,-1 do
		-- a bit rude but it works !
		if string.find(stack_list[i], "[C]: in function 'xpcall'", 0, true)
			then
			strip_end = i - 2
		end
	end
	if strip_end then
		table.setn(stack_list, strip_end)
	end
	stack_trace = table.concat(stack_list, "\n")
	return stack_trace
	]]
end

function LuaUnit:runTestMethod(aName, aClassInstance, aMethod)
	-- Stop if not in debug mode!
	if not debug then
		return
	end

	local ok, errorMsg
	-- example: runTestMethod('Tests:test1', Tests, Tests.testToto(self))
	LuaUnit.result:startTest(aName)

	-- run setUp first(if any)
	if type(aClassInstance.setUp) == "function" then
		aClassInstance:setUp()
	end

	local function err_handler(e)
		return tostring(e)..' \n'..debug.traceback()
	end

	-- run testMethod()
	ok, errorMsg = xpcall(aMethod, err_handler)
	if not ok then
		errorMsg  = self.strip_luaunit_stack(errorMsg)
		LuaUnit.result:addFailure( errorMsg )
	end

	-- lastly, run tearDown(if any)
	if type(aClassInstance.tearDown) == "function" then
		aClassInstance:tearDown()
	end

	self.result:endTest()
end

function LuaUnit:runTestMethodName( methodName, classInstance )
	--tst: print("LuaUnit:runTestMethodName(" .. methodName .. ",
	-- " .. tostring(classInstance) .. ")")
	-- example: runTestMethodName( 'TestToto:testToto', TestToto )
	local methodInstance = loadstring(methodName .. '()')
	LuaUnit:runTestMethod(methodName, classInstance, methodInstance)
end

function LuaUnit:runTestClassByName(aClassName)
	--tst: print("LuaUnit:runTestClassByName(" .. aClassName .. ")")

	-- Stop if not in debug mode!
	if not debug then
		return
	end

	-- example: runTestMethodName( 'TestToto' )
	local hasMethod, methodName, classInstance
	if type(aClassName) == "table" then
		print("Unable to run unit tests for ", table,
			", please use the class name, not the class itself!")
		return
	else
		-- Search for class by name (its also allowed to call class methods)
		hasMethod = string.find(aClassName, ':' )
		if hasMethod then
			methodName = string.sub(aClassName, hasMethod+1)
			aClassName = string.sub(aClassName,1,hasMethod-1)
		end
		classInstance = _G[aClassName]
		if not classInstance then
			error("No such class: " .. aClassName)
		end
	end

	LuaUnit.result:startClass(aClassName)

	if hasMethod then
		if not classInstance[methodName] then
			error("No such method: " .. methodName)
		end
		LuaUnit:runTestMethodName(aClassName .. ':' .. methodName,
			classInstance)
	else
		-- run all test methods of the class
		for methodName, method in --Assert.OrderedPairs(classInstance) do
			pairs(classInstance) do
			--for methodName, method in classInstance do
			if type(method) == "function" then
				--obs: and string.sub(methodName, 1, 4) == "Test" then
				LuaUnit:runTestMethodName(aClassName .. ':' .. methodName,
					classInstance)
			end
		end
	end
	--not required: print()
end

-- Run some specific test classes, e.g. LuaUnit.run("TestMyClass")
-- Note: Will not run in release mode (would slow down startup speed)!
function LuaUnit:run(...)
	-- Stop if not in debug mode!
	if not debug then
		return
	end

	-- If no arguments are passed, run the class names specified on the
	-- command line. If no class name is specified on the command line
	-- run all classes whose name starts with 'Test'. If arguments are
	-- passed, they must be strings of the class names that you want to run
	args = {...}
	--tst: print("LuaUnit:run(" .. table.tostring(args) .. ")")
	if #args > 0 then
		table.foreachi(args, LuaUnit.runTestClassByName)
	else
		-- create the list before. If you do not do it now, you
		-- get undefined result because you modify _G while iterating
		-- over it.
		testClassList = {}
		for key, val in pairs(_G) do
			if string.sub(key,1,4) == 'Test' then
				table.insert(testClassList, key)
			end
		end
		for i, val in --obs: Assert.OrderedPairs(testClassList) do
			pairs(testClassList) do
			LuaUnit:runTestClassByName(val)
		end
	end
	return LuaUnit.result:displayFinalResult()
end
-- class LuaUnit
