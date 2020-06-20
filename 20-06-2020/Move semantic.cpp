// ModernCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
using namespace std;

//class test {
//public:
//	test() {
//		x = 1;
//		std::cout << "default constructor" << x << std::endl;
//	}
//	int x;
//};

class test {
public:

	test() {
		cout << "Default: Test object created " << endl;
		NoIdea = -1;
		ptrNoIdea = nullptr;
	}
	test(int num) : NoIdea(num) {
		ptrNoIdea = new int;
		*ptrNoIdea = num + 1;
		cout << "Test object created \t" << NoIdea << "\t" << *ptrNoIdea << endl;
	}

	test(const test& obj) {
		NoIdea = obj.NoIdea * 2;
		ptrNoIdea = new int;
		*ptrNoIdea = *obj.ptrNoIdea;
		cout << "Test object created through copy-constructor\t" << NoIdea << "\t" << *ptrNoIdea << endl;
	}
	
	//test(test&& obj) = delete;

	test(test&& obj) noexcept {	//C.66: Make move operations noexcept

		//If i don't use move() here, NoIdea = obj.NoIdea will not be moved, it will be copied.
		// because inside this function obj is lvalue.
		NoIdea = std::move(obj.NoIdea);		

		ptrNoIdea = std::move(obj.ptrNoIdea);
		obj.ptrNoIdea = nullptr;	//If we miss to do this, it may break the application
		//we can use std::exchange(obj.ptrNoIdea, nullptr).
		//It replaces the value of obj with new_value and returns the old value of obj.
		//Ref: https://en.cppreference.com/w/cpp/utility/exchange
		
		obj.NoIdea = 0;	//this is opetional to set to default.

		//==>> go to main function.

		cout << "Test object created through move-constructor\t" << NoIdea << "\t" << *ptrNoIdea << endl;
		//cout<<ptrNoIdea<<"\t"<<obj.ptrNoIdea<<endl;
	}

	test& operator=(const test& obj) {
		this->NoIdea = obj.NoIdea;
		this->ptrNoIdea = new int;
		*(this->ptrNoIdea) = *obj.ptrNoIdea;
		cout << "Test object created through assingment operator.\t" << NoIdea << "\t" << *ptrNoIdea << endl;
		return *this;
	}

	test& operator=(test&& obj) noexcept {	//C.66: Make move operations noexcept

		delete this->ptrNoIdea;

		this->NoIdea = std::move(obj.NoIdea);
		this->ptrNoIdea = std::move(obj.ptrNoIdea);	//you can use std::exchange() also
		obj.ptrNoIdea = nullptr;
		obj.NoIdea = 0;	//optional
		//==>> go to main function.
		cout << "Test object created through Move assingment operator.\t" << this->NoIdea << "\t" << *this->ptrNoIdea << endl;
		return *this;
	}

	~test() {
		cout << "Test object destroyed\tNoIdea: " << NoIdea << endl;
		if (nullptr != ptrNoIdea) {
			cout << NoIdea << "\t" << *ptrNoIdea << endl;
			delete ptrNoIdea;
		}
	}

	int NoIdea;
	int* ptrNoIdea;
};

test&& createTestObj() {
	return test(20);
}

int add(int a, int b) { return a + b; }

int square1(int& num) {
	return num * num;
}

int square2(const int& num) {
	return num * num;
}

int multiplyByTwo(int& num) { 
	std::cout << "multiplyByTwo: lvalue reference." << std::endl; 
	return num * 2; 
}

int multiplyByTwo(int&& num) {
	std::cout << "multiplyByTwo: rvalue reference." << std::endl;
	return num * 2;
}

int main()
{
    std::cout << "Modern C++ !\n"; 

	//lvalue - rvalue

	int i;	// i is a lvalue.
	int* p = &i;

	i = 2;
	std::cout << i << std::endl;


	int x = 2;	//2 is rvalue.
	x = i + 2;	//(i + 2) is a rvalue. we can't get the address of (i+2).

	// i + 2 = 40;	

	int sum = add(2, 3);	//add(2, 3) will return a rvalue.

	//Uncomment below 2 lines.
	//test obj1;
	//obj1 = test(10);	//obj1 is lvalue and test() is rvalue.

	//Reference
	int& ref1 = i;	// lref is a reference to i.

	//If we try to create a reference of a rvalue, It will give an error.
	//int& ref = 5;	//error

	//It is possib;e to create a const reference to a rvalue.
	const int& ref2 = 5;

	//let's say we have a function square which takes an input num as a reference.
	/*
		int square1(int& num) {
			return num * num;
		}
	*/
	int sqr1 = square1(x);
	std::cout << sqr1 << std::endl;

	//int sqr2 = square1(2);	//Error

	//let's make a change in square function. Change the argument to const int&.
	/*
	int square2(const int& num) {
		return num * num;
	}
	*/
	int sqr2 = square2(2);

	//lvalue can be impliciatly transformed to rvalue but not vice-versa

	// If the expression has an identifiable memory address, it's lvalue otherwise, rvalue
	//*********************************************************************************************************************************

	//lvalue reference rvalue reference

	int num = 4;	//x islvalue
	int& lvref = num; //lvalue reference
	lvref = lvref + 1;
	std::cout << lvref << std::endl;
	int num2 = 10;
	//lvref = &num2;	//we can't do this.

	int&& rvref = 21;	//rvalue reference because 21 is a rvalue.
	rvref = rvref + 1;
	std::cout << rvref << std::endl;
	rvref = 31;			//we can re assign a new value to rvalue reference.
	std::cout << rvref << std::endl;

	int mulNum1 = multiplyByTwo(num);
	// Now let's pass a rvalue to this function.
	//int mulNum2 = multiplyByTwo(5);	//compile error
	//one way is make argument of multiplyByTwo as const int& other is rvalue reference.
	
	// Let's overload this function.
	int mulNum2 = multiplyByTwo(5);
	//*********************************************************************************************************************************
	cout << "*********************************************************************************************************************************" << endl;

	test obj1(10);

	test obj2;

	/*
	If you are testing below line with some older compiler gcc4.4 or older,
	this line will call copy constructor.
	As I am using VS2017 and it supports majority of Advance C++ features, this line will not call copy constuctor.
	Instead it will call default move constructor.
	To simulate this, let's delete dafault move constructor explicitly.
	add test(test&& obj) = delete; to class.
	*/
	test obj3 = createTestObj();	

	/*
	Note:
		-> Move semantics is implemented for all STL containers.
		-> If you are using C++11, your code will be faster without changing a line.
	*/

	obj2 = std::move(obj1);
	/*
	Once obj1 is moved to obj2, obj1 is not more having any valid data. 
	we must not use obj1 after moving it to obj2.
	Let it be as it is and it will die once it will go out of scope.
	*/

	// After Move Constructor explantion.
	//C.66: Make move operations noexcept
	//Ref: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#c66-make-move-operations-noexcept
	//
	//check https://www.youtube.com/watch?v=St0MNEU5b0o&t=2s at 26:48 min

	/*
	if we make int* ptrNoIdea; to unique_ptr. we need not to do phase 2(obj.ptrNoIdea = nullptr;)
	Then having default move constructor is fine. It will move memberwise. also noexcept.
	*/


	//Move Assingment operator.
	/*
	if we make int* ptrNoIdea; to unique_ptr. we need not to do phase 1 and 2 (obj.ptrNoIdea = nullptr;)
	Then having default move assingment constructor is fine. It will move memberwise. also noexcept.
	
	*/

	cout << "---------" << endl;


}

