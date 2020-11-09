//========== 4 ==========
#include <iostream>

template<class T>
T add(T a, T b){
	return a+b;
}

extern "C"{
int add_int (int a, int b){
	return add<int> (a, b);
}
float add_double(float a, float b){
	return a+b; //add<double> (a, b);
}

int main(){
	//std::cout << add<int>(2, 3) << " " << add<double>(2.2, 3.3) << std::endl;
	std::cout << add_int (2, 3) << " " << add_double(2.2, 3.3) << std::endl;
}
}

/*
//=========== 3 ===========
#include <iostream>

extern "C"{
const char * accumulate(const char * new_str){
	static std::string str = "First";
	str += "|" + (std::string) new_str; // in order to use concatenation, we have to convert const char * to string by type-casting
	//from string to const char*, we have to convert it to c string
	return str.c_str();
}
}

int main(){
	std::string a = "Second";
	std::cout << accumulate(a.c_str()) << std::endl;

	a = "Third";
	std::cout << accumulate(a.c_str()) << std::endl;
}

/*
//============== 2 =============
//This is to test string type returned by a function to be called by python
#include <iostream>

extern "C"{
const char * ret_str(){
	static std::string str = "ret_str"; //GOT TO USE STATIC
	return str.c_str();
}
}
int main(){
	const char * str = ret_str();
	std::cout << str << std::endl;
	std::cout << ret_str() << std::endl;	
}


/*
//============ 1 =============
#include <iostream>

class Person {
	protected:
		int age;
		float height;
	public:
		Person(int age, float height){
			this -> age = age;
			this -> height = height;
		}
		Person(){
			this -> age = 30;
			this -> height = 178.9;
		}
		void ShowPerson();
};

void Person::ShowPerson(){
	std::cout << "age: " << this -> age << ", height: " << this -> height << std::endl;
}

extern "C"{
Person *MakePersonPtr(){
	return new Person;
}
}

Person *MakePersonPtr(int age, float height){
	return new Person(age, height);
}

extern "C" {
void ShowPerson(Person *p){
	p -> ShowPerson();
}
}

extern "C"{
//looks like this does not work well, so use the pointer one
Person MakePerson(){
	Person xx;
	return xx;
}
}

int main(){
	Person * me = MakePersonPtr();
	me -> ShowPerson();

	me = MakePersonPtr(30, 178.9);
	me -> ShowPerson();
	//ShowPerson(me);

	Person xx = MakePerson();
	xx.ShowPerson();
}
*/
