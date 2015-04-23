print "Hello World"

--------------Lua变量
name = "Bilbo Baggins"
print ("name = "..name)
pi = 3.14159

name = pi

print ("name = "..name)

pi = false

--[[这是多行注释]]

A = 10
B = 10 ; A = 10;
B = 10 ; A = 10
B = 10 A = 10
-- 一个语句如果跨越多行语句，必须用一个分号来结束
print(
	"It is possible to span over multiple lines"
	);

-- 可以多个值给多个变量

a,b,c,d = 1,2,3,4
x,y,z = a,b,c

--如果左侧变量的数目多于右侧，那么nil值会被赋给多余的变量. nil是一个特殊的Lua类型，它表示没有意义
x,y,z = 1,2
print(x,y,z)

-- 在lua中有三种不同类型的变量， global (全局),local（局部） ， table fields（表）
-- 默认都为全局变量
local  name  = "sally" 
--一个值被赋值之前都是nil


------------------Lua 类型

-- nil 类型和其他所有类型都不同，表示没有意义，可以通过给变量赋值nil，将它删除。
-- Number （数值 ） 表示浮点数，这个值被处理为double, 当传递number给你的c/C++程序时，你必须记得把它们映射为正确的类型

--String  string类型表示浮点数  用 “..”操作符连接两个字符串。 如果“..”操作符的任何一边的操作数不是string ，那么这个操作数就先别转换然后再连接。 

age = 25
print( "I am "..age.." years of age ")

--Boolean 代表一个true 或者false 的值。 0和nil 为false， 其他的都是true
--Funtion 在Lua中也是一种类型，也可以赋给变量。 可以通过那个变量的名字，调用那个函数. 因为Lua 是弱类型语言，参数列表和返回值都不需要要指定类型.

add = function(a,b)
return a+b
end



--与C不同，Lua的函数可以一次返回多个变量
function IncrementTwoValues(a,b)
	return a+1,b+1
end
a =2 b = 10
print(a,b)
a,b = IncrementTwoValues(a,b);
print(a,b)

-- Table  表可以看成是一张关联数组或哈希表. 你可以用整数来索引一个表，也可以用任何类型的键值来索引一个表,而且Lua表时混合类型的，它们可以包含不同的数据类型

--创建一个表
test_table = {}
--指定一些值给它
test_table[1] = 4
test_table[2] = 5.6
test_table[3] = "Hello World"

--也可以通过下面的语法构建一个相同的表
test_table = {4,5.6,"Hello World"}

-- 加入关联索引
test_table["eigth"] = 8
test_table[3.141] = "Pi"



--建立n维表
lookup = {}
lookup["rock"]={}
lookup["rock"]["rock"] = "draw"
lookup["rock"]["paper"] = "lose"
lookup["rock"]["scissors"] = "win"
lookup["paper"]={}
lookup["paper"]["rock"]  = "win"
lookup["paper"]["parper"]  = "draw"
lookup["paper"]["scissors"]  = "lose"
lookup["scissors"]={}
lookup["scissors"]["rock"]  = "lose"
lookup["scissors"]["parper"]  = "win"
lookup["scissors"]["scissors"]  = "draw"


-- 建立n维表的另一种写法

lookup = {}
lookup["rock"] = {rock = "draw",paper = "lose",scissors = "win"}
lookup["parper"] =  {rock = "win",paper = "draw",scissors = "lose"}
lookup["scissors"] =  {rock = "lose",paper = "win",scissors = "draw"}

-- 可以使用（［］）方括号取值，也可以使用（.）操作符
test_table.eigth = 8;

--函数也可以赋值给表
function  add( a,b )
	return a+b
end
op = {}
op["add"] = add
print("a + b = "..op.add(4,7));

-- userdata允许Lua变量存储定制的c｜c++的数据
-- thread 产生一个新的线程

-- 逻辑运算符 and or 和not ，类似c++里的 && ,|| 和 ！.

--条件结构  

-- if 语句
if a == 4 then
	print ("yup")
else
	print ("nope")
end


-- while 语句

while a>1 do
	a = a-1
end

-- 注意要以end关键字结束

--repeat 和 until 的联用
a = 5
repeat
	a = a - 1
	print ("a = "..a)
until a == 0

-- for 结构

for i=1,10 , 2 do
	print(i)
end

data = {a = 1,b = 2,c = 3}
for k,v in pairs(data) do
	print(k,v)
end


--------------------------------------------------
--名字 ： rock_paper_scissors2.lua
--作者 ： 张世杰
--描述 ： 实现rock－paper－scissors游戏的Lua副本
--------------------------------------------------

--[[为随机数产生器找一个种子]]

-- math.randomseed(os.time())

-- [[这些变量保存玩家和计算机的分值]]
user_score = 0
comp_score = 0
-- [[这个表来决定谁赢了]]
lookup = {}
lookup["rock"] = {rock = "draw",paper = "lose",scissors = "win"}
lookup["parper"] =  {rock = "win",paper = "draw",scissors = "lose"}
lookup["scissors"] =  {rock = "lose",paper = "win",scissors = "draw"}

--[[这个函数返回计算机的最优猜测]]
function GetAIMove()
	-- 创建一个表，以使一个整数转换为一个代表的什么拳的索引
	local int_to_name = {"scissors","rock","paper"}
	--得到一个1-3的随机整数用来代表刚才创建的表的索引
	--这个函数通过这个索引返回一个随机的拳
	return int_to_name[1]
end

--[[这个函数使用查找表决定谁赢了并相应记分]]
function  EvaluateTheGuesses( user_guess,comp_guess )
	print("user guess..."..user_guess.."comp guess..."..comp_guess)
	if (lookup[user_guess][comp_guess] == "win") then
		print ("You Win The Round!")
		user_score = user_score + 1
	elseif (lookup[user_guess][comp_guess] == "lose") then
			print("Computer Wins the Round")
			comp_score = comp_score + 1
	else 
			print("Draw!")
			print (lookup[user_guess][comp_guess])
	end
end


--[[主游戏循环]]

print("Enter q to quit game")
print()
loop = true
while loop == true do
	--让用知道当前分值
	print("User: "..user_score.."Computer: "..comp_score)
	--获得用户的键盘输入
	-- io.open()
	user_guess = "s"
	--申请一个表 ，把用户输入变成字符串
	local  letter_to_string  = {s = "scissors",r = "rock" ,p = "paper"}

	if user_guess == "q" then
		loop = false
	elseif (user_guess == "r")or(user_guess == "p")or(user_guess == "s")then
		comp_guess = GetAIMove()
		EvaluateTheGuesses(letter_to_string[user_guess],comp_guess)
	else
		print("Invalid input,try again")
	end
end









