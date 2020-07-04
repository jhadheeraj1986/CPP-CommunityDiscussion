/*
Ref:
	https://www.cprogramming.com/tutorial/initialization-lists-c++.html
	https://www.youtube.com/watch?v=1nfuYMXjZsA
	https://www.youtube.com/watch?v=vmMKXLuDgYQ

*/

#include <iostream>
#include <vector>
using namespace std;


//==================================================================================================================


//==================================================================================================================

//	==>> Initialization Lists to Initialize Fields

//the initialization list also lets you specify which constructor gets called for the objects that are fields of the class

class Foo3
{
public:
	Foo3() : str{ "This is a initializer string!" } { }
	// This is nearly equivalent to 
	// Foo3() { str = ""This is a initializer string!"; }
	// but without the extra call to construct an empty string

private:
	std::string str;
};

//==================================================================================================================

// ==>What happens if we don't do this?

class Foo4 {
public:
	int class1Member;

	Foo4() {
		cout << "This is a Foo4 default constructor" << endl;
	}

	Foo4(int num3) : class1Member(num3) {
		cout << "This is a Foo4 parameterized constructor" << endl;
	}
};

class Bar4 {
public:
	int x;
	int y;
	Foo4 obj;

	Bar4(int num1, int num2) /*:x{ num1 }, y{ num2 }, obj{ Foo4(5) }*/ {	


		//This is assingment not initialization. This will first create a memory for int x.
		//Than it will copy num1 to it.
		x = num1;
		y = num2;

		//If we have a class object as a member data we try to initialize it as below, inside a constructor.
		//there will be 2 calls to class1 constructor.
		// 1 - it will create a memory for obj.
		// 2 - It will create a memory for a temp object.
		// 3 - It will assigne temp object to obj
		//obj = Foo4(5);
		//If we initialize this object in initializer list, it will be initialize as soon as memory is allocated.

	}
};

/*
int main()
{
	Bar4 obj(2, 3);
	cout << obj.x << "\t" << obj.y << endl;
}
*/

//the names of the objects being initialized should appear in the order they are declared in the class 
//(and after any parent class constructor call)

//==================================================================================================================

//	==> Initialization Lists and Scope Issues
//If you have a field of your class that is the same name as the argument to your constructor,
//then the initialization list "does the right thing."

class Foo5 {
public:
	Foo5(std::string str) {
		str = str;
		cout << str << endl;
	}
	void print() { cout << str << endl; }

private:
	std::string str;
};

//class Foo5 {
//public:
//	Foo5(std::string str) : str{ str } { }
//private:
//	std::string str;
//};

//equivalent to 
/*
class Foo5
{
public:
	Foo5(std::string str)
	{
		this->str = str;
	}
private:
	std::string str;
};

int main(){
	cout<<"Namaste world!!!"<<endl;
	Foo5 obj("test");
	obj.print();
}
*/


//==================================================================================================================

//	==> Initialization Lists and Primitive Types
// initialization lists work to initialize both user-defined types (objects of classes) and primitive types (e.g., int).
// When the field is a primitive type, giving it an argument is equivalent to assignment.

// This, allows you to specify templates where the templated type can be either a class or a primitive type
//	Otherwise, you will have to handle each type seperataly.
template <class T>
class Foo6
{
public:
	// works as long as T has a copy constructor
	Foo6(T temp) : tempObj(temp) { }

private:
	T tempObj;
};

//==================================================================================================================

//	==> Initialization Lists and Const Fields

//class Foo7 {
//public:
//	const int x;
//	Foo7() /*: x{ 0 }*/ {}
//	Foo7(int a) /*: x{ a }*/ {
//
//		//note: �const int class3::x� should be initialized const int x;
//		//error: assignment of read-only member �class3::x� x = a;
//		//x = a;
//
//		cout << x << endl;
//	}
//};
//
//int main() {
//
//	//If you have to initialize a non static constant data member in a class, You will have to use Initializer list.
//	Foo7 obj3;
//	Foo7 obj4(10);
//}

//==================================================================================================================

class Foo
{
public:
	Foo() { std::cout << "Foo's constructor" << std::endl; }
};
class Bar : public Foo
{
public:
	Bar() { std::cout << "Bar's constructor" << std::endl; }
};

/*
int main()
{

	Bar bar;
	//Object of Bar is getting constructed in 2 ssteps:
	//	First Foo constructor will get called and than Bar constructor will be invoked.
	//	=> see the output.
	//	Why this?
	//	-> Each class has to initialize the stuff belongs to it, not which belongs to other class.
	//	-> So child class will call base class constructor to initialize its stuffs after that child class will initialize its own.
	//
}
*/
//==================================================================================================================

//	==>>What if parant class has a constructor which takes a parameter.

//class Foo1
//{
//public:
//	Foo1(int x) { std::cout << "Foo1's constructor - " << x << std::endl; }
//};
//class Bar1 : public Foo1
//{
//public:
//	Bar1() { std::cout << "Bar1's constructor" << std::endl; }
//};

//int main()
//{
//	Bar1 bar1;
//	//error: no matching function for call to �Foo1::Foo1()�
//	//Bar1() { std::cout << "Bar1's constructor" << std::endl; }
//
//	//In this case you will get above compile time error.
//	//So how you will solve this issue?
//}

//==================================================================================================================

//	==>> This is the place initializer list play it's role.

/*
class Foo2
{
public:
	Foo2(int x) { std::cout << "Foo2's constructor - " << x << std::endl; }
};
class Bar2 : public Foo2
{
public:
	Bar2(int a) : Foo2{a} { std::cout << "Bar2's constructor" << std::endl; }
	//To call a particular class constructor, you just need to call it constructor as a normal function call.
};
int main()
{
	Bar2 bar2(2);

	//Output:
		//Foo2's constructor - 2
		//Bar2's constructor
}
*/

//==================================================================================================================

//	==> No Default Constructor
//If you have a field that has no default constructor(or a parent class with no default constructor), 
//you must specify which constructor you wish to use.

//	==> References
//If you have a field that is a reference, you also must initialize it in the initialization list; 
//since references are immutable they can be initialized only once.


//==================================================================================================================
//	==>	 Implicit narrowing


class Foo8 {
public:
	//char x;
	int x;

	/*
	This will narrowdown the int variable to char. which is wrong but compiler will not give any warning or error.
	*/
	Foo8(int a) :x(a) {
		cout << (int)x << endl;
	}

	/*
	InitializerLists.cpp: In constructor �Foo8::Foo8(int)�:
	InitializerLists.cpp:41:22: warning: narrowing conversion of �a� from �int� to �char� inside { } [-Wnarrowing]
		Foo8(int a) :x{ a } {
	*/
	//Foo8(int a) :x{ a } {
	//	cout << (int)x << endl;
	//}

};

//int main() {
//	//Implicit narrowing
//
//	int i = 7.8;
//	int j(7.8);
//
//	//int k{ 7.8 };	//Error:	This line will not compile.
//	//cout << i << " " << j << " " << k << endl;
//
//	double d;
//	vector<int> v(1.2, 2.2);
//	//vector<int> v1{ 1.2,2.2 };	//Error:	This line will not compile.
//
//	//Foo8 obj2(300);
//
//
//	//Sometimes narrowing is useful
//	char c{ 'a' };
//	//char c1{ c + 1 };		//This will give warning or error
//
//	//or you can use these way.
//	//char ch2{ static_cast<char>(c + 1) };
//	//char ch3 = c + 1;
//	//char ch4(c + 1);
//
//}

//==================================================================================================================

#include <iterator>
//	Istream iterators are input iterators that read successive elements from an input stream (such as cin).


//int main() {
//	vector<int> v( istream_iterator<int>(cin), istream_iterator<int>() );
//	//vector<int> v{ istream_iterator<int>(cin), istream_iterator<int>() };	//C++11
//
//
//	cout << v.size();
//}

//==================================================================================================================

//	Overload resolutions for constructors with initializer lists
//		==> () initialization for ordinary constructors only
//		==> {} initialization for all constructors
//			==> std::initializer_list<> constructors have higher priority
//			==> But the default constructor has HIgest priority.

class test {
public: 
	test(int = 0) { cout << "Default Constructor" << endl; }
	test(std::initializer_list<int>) { cout << "Initializer list constructor" << endl; }
};

int main() {
	test a;
	test b(55);
	test c = 66;

	test d{};			//Default constructor called
	test e{ 78 };		//Initializer list constructor called
	test f{ 44,66,88,66,45 };	//Initializer list constructor called

	test g = {};		//Default Constructor
	test h = { 12 };	//Initializer list constructor called
	test i = { 23,36 };	//Initializer list constructor called
}

