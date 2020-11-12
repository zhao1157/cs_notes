//===== 51 =====
//Have a thorough study of class inheritence
#include <iostream>

class Family{
    private:
        int num_people;
        std::string name = "Family";
    public:
        Family(){}
        Family(int num): num_people(num){
        }
        void Get_NumPeople(){
            std::cout << "Family " << this -> num_people << std::endl;
            std::cout << "name: " << this -> name << std::endl;
        }
};

class My_Family: public Family{ //without public, it is private by default
    private:
        //since num_people and name are private in Family, so My_Family can not access them
        //thus we have to define our own copy of them, otherwise this->name/num_people will
        //try to access the ones in Family, causing access errors 
        int num_people;
        std::string name = "My_Family";
        int age;
    public:
        My_Family(int num): Family(num){
        }
        void Get_NumPeople(){
            //these variables are the ones in My_Family, not the ones in Family
            std::cout << "My_Family " << this -> num_people << std::endl;
            std::cout << "My name: " << this -> name << std::endl;
        }
        void Only_Children(){
            std::cout << "Only in the child class" << std::endl;
        }

};

void Family_NumPeople(Family *family){
    family -> Get_NumPeople();
}

int main(){
    Family family(0), *ptr_family;
    My_Family my_family(5), *ptr_my_family;

    ptr_family = & my_family;
    ptr_family -> Get_NumPeople(); // we do not get polymorphysim, i.e. always the function of the base class
    //ptr_family -> Only_Children(); //the base class does not have this member function, so can not call it
    std::cout << "_________" << std::endl;
    Family_NumPeople(& my_family);
    std::cout << "________" << std::endl;
    ptr_my_family = (My_Family *) & family; //since My_Family can not access the member attributes of Family, thus random values
    //if these attributes are protected and not redefined in My_Family, then My_Family can access the values in Family
    ptr_my_family -> Get_NumPeople();
}

/*
//====== 50 ======
//This is to study the overriding of functions for classes
#include <iostream>

class Shape {
	protected:
		std::string name;
	public:
		Shape(std::string name){
			this -> name = name;
		}
		Shape(){
			std::cout << "Empty initialization" << std::endl;
		}

		void Shape_Name(){
			std::cout << "Shape: " << this -> name << std::endl;
		}
};
class Square: public Shape {
	public:
		Square(std::string name_arg): Shape() { // the base class should be called here
			//if name is passed, then name in this scope only refers to this one
			//Shape(name); // error in this way, got to be before {
			name = name_arg;
			std::cout << "before adding _end: " << name << std::endl; //here name is the one being passed into the constructor
			std::cout << this -> name << std::endl; // "this" pointer differentiates the class member and the argument being passed
			name += "_end";
			std::cout << "after adding _end: " << name << std::endl; // the same is here
			std::cout << this -> name << std::endl;
		}
		void Shape_Name(){
			std::cout << "Square: " << name << std::endl; // here now name refers to the class member
		}
};

int main(){
	Shape s_base("shape");
	s_base.Shape_Name();

	Square s_derive("square");
	s_derive . Shape_Name(); //. operator: can be separated with spaces
	
	std::cout << "++++++++++++" << std::endl;

	Shape *ptr_base = &s_base;
	Square *ptr_derive = &s_derive;

	ptr_base -> Shape_Name();
	ptr_derive -> Shape_Name();

	std::cout << "++++++++++++" << std::endl;

	ptr_base = & s_derive;
	ptr_base -> Shape_Name();

	ptr_derive = (Square *) & s_base;
	ptr_derive -> Shape_Name();

}
//========== 49 ==========
#include <iostream>
#include <map>
#include <vector>

int main(){
	std::map <int, std::string> me;
	me[0] = "zls";
	me[2] = "male";

	me.insert({3, "30"});
	me.insert({2, "femal"});//this does not change the value of an existing key
	me[2] = "female"; //this works

	for (auto entry = me.begin(); entry != me.end(); entry++){
		std::cout << entry -> first << "=" << entry -> second << "; ";
	}
	std::cout << std::endl;

	std::map <int, std::string>::iterator itr;
	itr = me.find(0);
	if (itr == me.end()){
		std::cout << "NOT FOUND" << std::endl;
	}else{
		std::cout << itr -> first << "=" << itr -> second << std::endl;
	}

	std::vector <int> keys;
	for (auto itr = me.begin(); itr != me.end(); itr ++){
		keys.push_back(itr->first);
	}
	for (auto i = 0; i < keys.size(); i++){
		std::cout << keys[i] << " ";
	}
	std::cout << std::endl;
	std::cout << me.size() << " " << me.max_size() << std::endl;
	me.erase(2);
	std::cout << me.size() << std::endl;
	std::cout << keys.size() << " ";
	keys.erase(keys.begin()+2);
	std::cout << keys.size() << std::endl;
	std::cout << keys.capacity() << std::endl;
	keys[40] = 30;
	std::cout << keys.capacity() << std::endl;
	keys.shrink_to_fit();
	std::cout << keys[40] << " " << keys.size() << std::endl;
}

//========== 48 =========
#include <iostream>
#include <vector>
#include <map>

int main(){//MAIN has to be int-return type
	std::vector <std::string> shared_entries;
	std::string entry;

	std::cout << "Please enter the entries you'd like to share (enter 'end' to stop):";
	while (true){
		std::cin >> entry;
		if (entry == "end")
			break;
		shared_entries.push_back(entry);
	}

	std::cout << "You would like to share the following information with us:";
	for (auto i = shared_entries.begin(); i < shared_entries.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	std::cout << "total " << shared_entries.size() << " entries" << std::endl;
	shared_entries.shrink_to_fit(); // DOES this save memory?

	std::map <std::string,std::string> my_info;
	std::cout << "Please enter your following information:" << std::endl;
	for (auto entry = shared_entries.begin(); entry < shared_entries.end(); entry ++){
		std::cout << *entry << ":";
		std::cin >> my_info[*entry];
	}

	for (auto entry = my_info.begin(); entry != my_info.end(); entry ++){
		std::cout << entry -> first << "=" << entry -> second << "; ";
	}
	std::cout << std::endl;
	for (auto entry = my_info.rbegin(); entry != my_info.rend(); entry ++){
		std::cout << entry -> first << " ";	
	}
	std::cout << std::endl;
	for (auto entry = shared_entries.begin(); entry < shared_entries.end(); entry ++){
		std::cout << *entry << "=" << my_info.at(*entry) << "; ";
	}
	std::cout << std::endl;
	//just to practice []
	std::cout << my_info["name"] << " " << my_info["age"] << std::endl;
}


//========= 47 ==========
//this is to pratice map
#include <iostream>
#include <vector>
#include <map>

int main(){
	std::map <int, std::string> me;
	std::map <int, std::string>::iterator itr; //iterator in the normal order
	me[1] = "ZLS";
	me[2] = "30";
	me[300] = "male";
	me[-23] = "str_23";

	std::cout << me[1] << " " << me[2] << " " << me[3] << std::endl;

	itr = me.find(232); //the key value to be tested has to be of the correct type supported in this map object
	if (itr != me.end()){
		std::cout << itr -> first << " " << itr -> second << std::endl;
	}else{
		std::cout << "Not found" << std::endl;
	}

	//map is always sorted, so usually not in the order the elementa are inserted/created
	for (auto i = me.begin(); i != me.end(); i++){
		std::cout << i -> first << " -> " << i -> second << " "; 
	}
	std::cout << std::endl;

	//reverse iterator
	std::map <int, std::string> ::reverse_iterator itr2; //iterator in the reverse order
	for (itr2 = me.rbegin(); itr2 != me.rend(); itr2 ++){ //or we can just use auto to simplify this 
		std::cout << itr2 -> first << " -> " << itr2 -> second << " ";
	}
	std::cout << std::endl;

	//map pointer comparison
	std::map<int, std::string> *you_ptr, you;
	you_ptr = &me; //BY VALUE
	you = me;

	(*you_ptr)[1] = "dsy_ptr";
	you[1] = "dys";
	std::cout << me[1] << " " << (*you_ptr)[1] << " " << you[1] << std::endl;

	std::vector <std::string> key;
	std::cout << "Please enter the information that you would like to share with us (enter 'end' to stop):";
	std::string entry;
	while(true){
		std::cin >> entry;
		if (entry == "end")
			break;
		std::cout << entry << std::endl;
		key.push_back(entry);
	}

	std::map <std::string, std::string> my_info;
	std::cout << "Please enter your" << std::endl;
	for (auto entry = key.begin(); entry < key.end(); entry ++){
		std::cout << "\t" << *entry << ":";
		std::cin >> my_info[*entry];
	}
	for (auto itr = my_info.begin(); itr != my_info.end(); itr ++){
		std::cout << itr->first << " -> " << itr -> second << "; ";
	}
	std::cout << std::endl;
}


//=============== 46 =============
// this is to test empty and iterator
#include<iostream>
#include<vector>

int main(){
	std::vector <int> a{2, 3, 4, 5};
	std::vector <float> b;
	//empty() is find out if a vector is empty or not
	std::cout << a.empty() << " " << b.empty() << std::endl;
	
	//iterator has to be of the same type as it points to
	std::vector<int>::iterator itr;
	for (itr = a.begin(); itr < a.end(); itr++){
		std::cout << *itr << " ";
	}
	std::cout << std::endl;
	//somehow this does not work
	//for (itr = a.rbegin(); itr != a.rend(); itr++){
	//	std::cout << *itr << " ";
	//}
	std::cout << std::endl;
}


//=========== 45 =========
//This is to test the vector, which stores data in contiguous manner
//the size is flexible, i.e. shrinking or expanding freely,
//the storage is handled by the container automatically
#include <iostream>
#include <vector>

int main(){
	std::vector<int> v1;

	int num_ele = 9;

	for (int i = 0; i < num_ele; i++){
		v1.push_back(i+1); // use push_back to assign values to the vector
	}

	std::cout << "Show the vector" << std::endl;
	//just like arrays, access its elements by indexing
	for (auto i = 0; i < num_ele; i++){
		std::cout << "\t" << v1[i] << std::endl;
	}
	
	//for an array we can access it by referencing
	int arr[5]={3, 4, 5, 6, 7};
	for (int i = 0; i < 5; i++){
		//std::cout << *(&arr[0]+i) << std::endl;
		std::cout << *(arr+i) << std::endl;
	}
	//through address iterator, we can access each element by dereferencing
	for (auto i = v1.begin(); i < v1.end(); i++){ //an iterator
		std::cout << "\t" << *i << std::endl;
	}
	for (auto i = v1.end() - 1; i >= v1.begin(); i--){
		std::cout << *i << std::endl;
	}
	//use the reverse order address iterator, note still use ++, not --
	for (auto i = v1.rbegin(); i != v1.rend(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;

	v1[4] = 222;
	std::cout << v1.back() << " " << v1[4] << " " << v1.at(4) << std::endl;
	std::cout << v1[0] << " " << v1[2] << std::endl;
	std::cout << v1.at(0) << " " << v1.at(2) << std::endl;

	std::cout << "size of int " << sizeof(int) << std::endl;
	int *v1_ptr = v1.data();
	int *add1, *add2;
	for (auto i = 0; i < 5; i++){
		std::cout << (v1_ptr+i) << " " << *(v1_ptr+i) << std::endl;
		if (i == 0)
			continue;
		add1 = v1_ptr+i-1;
		add2 = v1_ptr+i;
		std::cout << "\t" << add2-add1 << std::endl;
	}
	std::cout << std::endl;

	std::cout << 0x55ef3a6a4eb0 - 0x55ef3a6a4eb4 << std::endl;

	std::vector<double> v2;
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.max_size() << " " << v2.max_size() << " " << v1.max_size()*1.0/v2.max_size() << std::endl;
	//shrink the vector
	v1.shrink_to_fit();
	std::cout << v1.capacity() << std::endl;
	//one size is changed, the capacity is modified
	v1.push_back(2323);
	std::cout << v1.size() << " " << v1.capacity()  << std::endl;
	v1.shrink_to_fit();
	std::cout << v1.capacity() << std::endl;
	std::cout << v1.front() << " " << v1.back() << std::endl;

	v1.insert(v1.begin(), 23);
	std::cout << v1.front() << std::endl;
	v1.insert(v1.end()-1, 0);
	std::cout << v1.at(v1.size()-2) << std::endl;
	v1.insert(v1.end(), 11);
	std::cout << v1.back() << std::endl;

	//v1.insert(*(v1.data()+v1.size()), 2222222);
	std::cout << "****" << v1[2] << std::endl;
	*(v1.data()+2) = 222222; //modify this address and is reflected in the vector
	std::cout << v1.back() << std::endl;
	std::cout << v1.size() << " " << v1.capacity() << std::endl;
	std::cout << *(v1.data()+2) << " " << v1[2] << std::endl;

	v1.clear();
	v1.shrink_to_fit();
	std::cout << v1.size() << std::endl;
	v1.push_back(22);
	v1.push_back(3);
	std::cout << v1.size() << " " << v1.capacity() << std::endl;

	v1.pop_back();
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.emplace_back(23234); //JUST LIKE POP_BACK()
	v1.emplace_back(200000);
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.erase(v1.end()-1); //remove the last element, just like pop_back()
	std::cout << v1.size() << " " << v1.capacity() << " " << v1.back() << std::endl;

	v1.clear();
	v1.assign(4, 2);
	for (auto i = v1.begin(); i < v1.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	int a[] = {9, 8, 7, 6, 5, 4};
	v1.assign(a, a+sizeof(a)/sizeof(int)); // assign array to a vector, and the values in its old version are cleared
	for (auto i = v1.begin(); i < v1.end(); i++){
		std::cout << *i << " ";
	}
	std::cout << std::endl;
	std::vector<int> v3;
	v3.assign(v1.begin()+1, v1.end()-1);
	for(auto i = v3.begin(); i < v3.end(); i++){
		std::cout << *i  << " ";
	}
	std::cout << std::endl;

	std::vector <double> v4;
	for (int i = 0; i <9; i++){
		v4.push_back(i);
	}

	for (auto i = v4.begin(); i < v4.end(); i++){
		//the odd-index values
		if ((i - v4.begin())%2 == 0){
			std::cout << *i << " ";
		}
	}
	std::cout << std::endl;

	//initializing
	std::vector <float> v5 {2.2, 3, 5.9};
	std::cout << v5[0] << " " << v5[1] << " " << v5[2] << std::endl;
}

//============ 44 ============
// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread

void foo()
{
  std::cout << std::this_thread::get_id() << std::endl;
}

void bar(int x)
{
  std::cout << std::this_thread::get_id() << std::endl;
}

int main()
{
  std::thread first (foo);     // spawn new thread that calls foo()
  first.join();
  std::thread second (bar,0);  // spawn new thread that calls bar(0)
    second.join();
    std::cout << std::this_thread::get_id() << std::endl;

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}

//============= 43 =========
#include <iostream>
#include <memory>
#include <unistd.h>
struct Person{
	public:
		int age;
		Person():age(-1){}
		Person(int age):age(age){}
		~Person(){
			std::cout << age << " is destroyed" << std::endl;
		}
};

int main(){
	std::shared_ptr<Person> p1; 
	//p1 = new int(2); // this is wrong as p1 and the assignment have different types
	p1 = std::make_shared<Person> ();
	std::cout << p1 << " " << p1.get() << " " << p1.use_count() << " " << p1->age << std::endl;

	std::cout << "before p1 switches" << std::endl;
	p1 = std::make_shared<Person> (3);
	std::cout << "after p1 switches" << std::endl;
	std::cout << p1 << " " << p1.get() << " " << p1.use_count() << " " << p1->age << std::endl;
	sleep(2);
	std::cout <<"__________ END __________" << std::endl;
}
//============= 42 ========
#include<iostream>
#include<memory>
#include<string>

struct Person{
	public:
		std::string name;
		Person():name("zls"){}
		Person(std::string name): name(name){}
		~Person(){
			std::cout << name << " is destroyed" << std::endl;
		}
};

int main(){
	std::shared_ptr<Person> p1(new Person("xx"));
	std::cout << p1 -> name << std::endl;
	//since p1 is pointing to another space, 'xx' will be destroyed
	p1 = std::make_shared<Person> ("yy"); //the arguments are the ones needed by the constructor
	//the same goes here, 'yy' will be destroyed
	p1 = std::make_shared<Person>();
	std::cout << p1 -> name << std::endl;
	std::cout << "__________ END __________" << std::endl;
}
//========== 41 ===========
#include <iostream>
#include <memory>
#include <map>

int main(){
	std::map<int, double> i_d;
	i_d.insert({2, 3.14});

	std::shared_ptr<std::map<int, double>> ptr_i_d (new std::map<int, double>);
	ptr_i_d->insert({2, 3.14});
	ptr_i_d->insert({3, 4.14});

	for (auto it = ptr_i_d->begin(); it != ptr_i_d->end(); it++){
		std::cout << it -> first << ": " << it -> second << std::endl;
	}

	std::cout << ptr_i_d << " " << ptr_i_d.use_count() << std::endl;

	ptr_i_d = std::make_shared<std::map<int, double>>();
	ptr_i_d->insert({9, 9.9});
	ptr_i_d->erase(9);
	std::cout << ptr_i_d << " " << ptr_i_d.use_count() << std::endl;
}

//========== 40 =========
//this is to practice make_shared which creates a shared_ptr that points to type T object with args
#include <iostream>
#include <memory>

int main(){
	int a = 3;
	std::shared_ptr<int> p_1 = std::make_shared<int> (a);

	std::cout << p_1.use_count() << " " << *p_1 << std::endl;
	std::cout << &a << std::endl << p_1 << std::endl << p_1.get() << std::endl;


	int *b ;//= new int(9);
	b = new int (9);
	std::shared_ptr<int> p_2(b);
	std::cout << b << std::endl << p_2 << std::endl;


	std::shared_ptr<int> p_3(&a);
}

//=========== 39 =========
//This is to practice shared_ptr with customized class
#include <iostream>
#include <string>
#include <memory>

class Person{
	private:
		std::string name;
		int age;
	public:
		Person(): name("xx"), age(30){};
		Person(std::string name, int age):name(name), age(age){}
		~Person(){
			std::cout << name << " is destroyed" << std::endl;
		}
		int get_age(){
			return age;
		}
};

int main(){
	std::shared_ptr<Person> me_ptr(new Person);
	std::cout << me_ptr->get_age() << std::endl;


	Person * me = new Person("zls", 29);
	std::shared_ptr<Person> me_ptr_2(me);
	std::cout << me_ptr_2->get_age() << me_ptr_2.use_count()<< std::endl;
	//delete me; //causing segmentation fault
	//std::shared_ptr<Person> me_ptr_3(me); //causing segmentation fault as me is trying to be deleted twice
	std::shared_ptr<Person> me_ptr_3(me_ptr_2);
	std::cout << "_________ END _________" << std::endl;
}

//========= 38 =========
//This is to practice shared_ptr
#include <iostream>
#include <memory>

int main(){
	int * p0;
	p0 = new int(30);
	std::cout << "p0 points to " << p0 << std::endl;
	std::shared_ptr<int> p1(p0);

	std::cout << "p1 use_count(): " << p1.use_count() << std::endl;
	std::cout << *p1 << std::endl;
	std::cout << p1 << std::endl;
	std::cout << &p1 << std::endl;

	std::shared_ptr<int> p2(p1);
	std::cout << "p1 use_count(): " << p1.use_count() << ", p2.use_count(): " << p2.use_count() << std::endl;
	std::shared_ptr<int> p3(p0); // in this case p1 and p2 doesnot know p3 is also pointing to p0, this might cause crashing
	std::cout << "p1 use_count(): " << p1.use_count() << ", p2.use_count(): " << p2.use_count() << ", p3.use_count(): " << p3.use_count() << std::endl;

	std::cout << *p1 << *p2 << *p3 << std::endl;
	delete p0; //what it really deletes is the content in the memory space pointed to by p0, not p0 itself
	std::cout << "after deleting p0, p0 points to " << p0 << std::endl;
	std::shared_ptr <int> p4(p1);
	std::cout << *p1  << " " << *p2 << " " << *p3 << " " << *p4<< std::endl;
}

//====== 37 ======
//this is to practice new and delete objects
#include <iostream>

struct me_struct{
	public:
	int me_i;
	me_struct(int _i){
		me_i = _i;
	}
	me_struct(){}
	~me_struct(){
		std::cout << "me_struct is destroyed " << me_i << std::endl;
	}
};

int main(){
	//dynamically allocate a memory space with size of sizeof(int)
	int *p = new int(2);
	//releasing the memory block pointed to by p, otherwise memory leak
	std::cout << *p << std::endl;
	delete p;

	double *p_double;
	p_double = new double;
	*p_double = 3.1415;
	std::cout << *p_double << std::endl;
	delete p_double;

	float *p_float = new float[3];
	for (int i = 0; i < 3; i++){
		p_float[i] = i*i;
	}
	std::cout << p_float[2] << std::endl;
	delete [] p_float;

	me_struct* me_ptr = new me_struct(2);

	std::cout << "Before deleting struct" << std::endl;
	delete me_ptr;
	std::cout << "After deleting struct" << std::endl;
	
	std::cout << "\n\n";
	me_struct * me_arr_p;
	me_arr_p = new me_struct[3];
	
	for (int i = 0; i < 3; i++){
		me_arr_p[i].me_i = i+3;
	}
	std::cout << "\n______ before ______\n";
	delete [] me_arr_p; // without this line, the struct objects will not be destroyed
	std::cout << "______ after ______\n";
	std::cout << "______ END _____\n";
}
//====== 36 ========
//this is to practice basic type initialization
#include <stdio.h>
int main(){
	int i(2); //initialize i, i.e. i = 2. it's just like initializing a custom class
	printf("i = %d\n", i);
}

//=========== 35 =========
//this is to test memcpy, which is defined in string.h
#include <iostream>
#include <string.h>
#include <string>

int main(){
	int a = 2;
	int b;
	std::cout << b ; // a very small number which is default
	memcpy(&b, &a, sizeof(a)); // source and destination have to be of the same type
	std::cout << "sizeof(a) " << sizeof(a) << ", b: " << b << std::endl;
	std::cout << "sizeof(size_t): " << sizeof(size_t) << std::endl;

	std::string str_1 = "love me";
	std::cout << "length of str_1 " << str_1.size() << std::endl;
	char str_2[str_1.size()];
	std::cout << "strlen " << strlen(str_1.c_str()) << std::endl;
	memcpy(str_2, str_1.c_str(), strlen(str_1.c_str())); 
	std::cout << sizeof(str_1) << std::endl;
	std::cout << "str_2 " << str_2 << std::endl;

	for(auto c : str_1){
		std::cout << c << " ";
	}
	std::cout << std::endl;
	//the size of string, string.size()
	std::cout << str_1[0] << str_1[str_1.size()-2] << std::endl;

	char str_3[] = "";
	std::cout << sizeof(str_3) << std::endl;
	puts("sdf"); // in c
}


//=========== 34 =========
//this is to test that thread shares information with the the main process
#include <iostream>
#include <thread>
#include <unistd.h>

int value = 0;
int send = 0;

void test_value(){
	int count = 0;
	sleep(1);
	send = 99;
	while(value == 0){
		sleep(1);
		std::cout << ++count << std::endl;
}
	std::cout << "test_thread exit " << value << std::endl;
}

int main(){
	std::thread test_thread (test_value);
	sleep(5);
	std::cout << "main process " << send << std::endl;
	sleep(3);
	value = 2;

	test_thread.join();
}

//========= 33 ========
//this is to practice string
#include <iostream>
#include <stdio.h> //printf

int main(){
	std::string a = "love", b = " ", c = "me", sentence;
	sentence = a+b+c;
	std::cout << "sentence: " << sentence << std::endl;
	printf ("sentence %s\n", sentence.c_str());
}
//============ 32 =======
//This is to practice getenv which grabs the environment variables
#include <iostream>

int main(){
	std::cout << std::getenv("mexx") << std::endl; 
	std::cout << std::getenv("PATH") << std::endl;
}


//======= 31 ======
//This is to practice thread and sleep function 
#include <thread>
#include <iostream>
#include <unistd.h> //sleep function in linux
void slm(){
	std::cout << std::this_thread::get_id() << " is sleeping for 3 s" << std::endl;
	sleep(3);
	std::cout << std::this_thread::get_id() << " woke up" << std::endl;
}

int main(){
	std::thread me(slm);
	sleep(0.5);
	std::cout << "main " << std::this_thread::get_id() << " is sleeping for 2 s" << std::endl;
	sleep(2);
	std::cout << "main " << std::this_thread::get_id() << " woke up" << std::endl;

	me.join(); //use join otherwise core dump error at the end
}


//========== 30 =========
#include "my_funcs/my_funcs.h"

#if defined_in_cmake == 0
#define cmake "zero"
#elif defined_in_cmake == 1
#define cmake "one"
#endif

int main(int argc, char*args[]){
	int a = ret_square(2);
	std::cout << a << std::endl;
	std::cout << "CMAKE --VERSION: " << cmake << std::endl;
}

//========== 29 ============
//This is to practice taking input from command line
#include <iostream>
#include <sstream>

int main(int argc, char *arg[]){
	std::cout << arg[0] << std::endl;
	for (int i = 1; i < argc; i++){
		std::cout << arg[i] << " ";
	}
	std::cout << std::endl;

	std::string i = "2323";
	std::stringstream convert;
	int a, b=-1;

	convert << arg[1] << " " << arg[2];
	convert >> a; //here the content in convert is not getting pushed out completely, so it will stay there
	std::cout << a << " " << b << std::endl;
	
	//concate numbers
	convert << " " << arg[1] << arg[2]; //here it combines the new and old ones in the stream
	convert >> a >> b;
	std::cout << a << " " << b << " " << arg[1] << " " << arg[2] << std::endl;
}

//========== 28 =======
#include <iostream>

#define NO_CLASS 0

#if (NO_CLASS == 1)
int add(int a, int b){
	return a+b;
}

int main(){
	std::cout << "Add_func: " << add(2, 3) << std::endl;
}
#else
class Add{
	protected:
		int a, b;
	public:
		Add(int a, int b){
			this -> a = a;
			this -> b = b;
		}
		int RetAdd(){
			return a+b;
		}
};

int main(){
	Add my_add(2, 3);
	std::cout << "My_add: " << my_add.RetAdd() << std::endl;
}

#endif


//=========== 27 =========
//this is to find the type of a variable
#include <iostream>
#include <typeinfo>

int main(){
	int i = 0;
	double j = 2.3;
	float a = 2;
	char c = 's';
	std::string b = "ss";
	std::cout << "int: " << typeid(i).name() << std::endl;
	std::cout << "double: " << typeid(j).name() << std::endl;
	std::cout << "float: " << typeid(a).name() << std::endl;
	std::cout << "char: " << typeid(c).name() << std::endl;
	std::cout << "string: " << typeid(b).name() << std::endl;

	std::string s = (std::string)typeid(b).name() + (std::string) typeid(j).name();
	std::cout << s << std::endl;
}


//========== 26 =======
#include <iostream>

int main(){
	const char * str1 = "ss"; //COMPILER warning, we should add const in front as string is a char constant
	const char *str2 = "xx";
	std::cout << str1 << " " << str2 << std::endl;

	const char * str3 = (char *) malloc(sizeof(char) * 3);
	std::cout << sizeof(str3) << std::endl; //POINTER size is still 8
	str3 = "xyz";
	std::cout << str3  << " " << ((std::string) str3).size() << std::endl;

	std::cout << str3[2] << std::endl;
	//str3[2] = 'x'; // YOU CAN NOT change const of chars
	// BUT we can do it in string
	std::string str4 = "xyz";
	std::cout << str4 << " -> ";
	str4[2] = 'x';
	std:: cout << str4 << std::endl;

	char str5[11] = "i love you";
	std::cout << sizeof(str5) << std::endl;
	std::cout << str5;
	for (int i = 0; i < sizeof(str5); i++){
		if (str5[i] == ' ')
			str5[i] = '_';
	}
	std::cout << " -> " << str5 << std::endl;

	std::cout << std::endl;

	char a = 'A', b = 'B';
	char *ptr = & a;
	//print out the address
	std::cout << static_cast<void*> (ptr) << " " << static_cast<void*> (&a) << std::endl;
	ptr = &b;
	std::cout << static_cast<void*> (ptr) << " " << static_cast<void*> (&b) << std::endl;
	
	//constant pointer which can not point to a second address, but you can change the content in the first address
	char *const const_ptr = &a;
	std::cout << static_cast<void*>(const_ptr) << " " << *const_ptr<< std::endl;
	//const_ptr = &b; 
	*const_ptr = 'a'; //'A' becomes 'a'
	std::cout << static_cast<void*>(const_ptr) << " " << *const_ptr << std::endl;

	//can not point to a second location, nor change the value in the first address through the pointer 
	const char *const cc_ptr = &a;
	std::cout << static_cast<const void *>(cc_ptr) << " | " << *cc_ptr << std::endl;
	//cc_ptr = &b;
	// *cc_ptr = b;
	//but we can change the value in the first address by other variables relating to it
	a = 'A';
	std::cout << static_cast<const void *>(cc_ptr) << " | " << *cc_ptr << std::endl;

}


//========== 25 =========
#include <iostream>

int main(){
	char a = 's';
	//char *a_ptr = &'s'; //invalid as & has to be followed by a variable, which is how we refer to objects. define a variable first
	//char *a_ptr = 's'; // type wrong
	char * a_ptr = &a;

	const char * b_ptr = "ss"; //however this migically works
	std::string str = b_ptr;
	std::cout << str <<  " " << sizeof(str) << " " << str.size()<< std::endl;
	str = "";
	std::cout << sizeof("") << " " << sizeof(str) << std::endl;

	//const char * c_ptr = str;
	const char * c_ptr = str.c_str();
	std::cout << c_ptr << sizeof(c_ptr) << std::endl;
}



//
//========= 24 ==========
#include <iostream>

int main(){
	//here str is just a pointer typed of char
	//mutable
	char c = 'd';
	char *c_ptr = &c; // need to pass an address to char pointer
	std::cout << c  << *c_ptr<< std::endl;
	c = 'e';
	//immutable
	const char d = 'e';
	std::cout << d << std::endl;
	//d = 'f'; //read-only variable
	
	//a sequence of char, AGAIN A POINTER, but a one with const char
	const char * seq = "this is the first";
	std::cout << sizeof(const char *) << " " << sizeof(seq) << std::endl; // the size of this type
	std::cout << sizeof(const int *) << " " << sizeof(double*); // looks like all pointers have size of 8
	for (int i = 0; i < 17; i++)
		std::cout << seq[i];
	std::cout << "--xx";
	std::cout << sizeof("") << " " << sizeof("more than one") << std::endl;

	//array of char
	char arr_char[] = {'2', '3', 'x', 'y'};
	std::cout << sizeof(arr_char) << " " << sizeof(arr_char[0]) << " " << sizeof(arr_char)/sizeof(arr_char[0]) << std::endl;
	for (auto c : arr_char)
		std::cout << c;
	std::cout << std::endl;
	//array of sequences
	const char *arr_str[] = {"sd", "sdfs", "", "s"};
	//here sizeof() means the size of the pointers
	std::cout << sizeof(arr_str) << " " << sizeof(arr_str[2]) << std::endl;
	for (auto strptr : arr_str)
		std::cout << strptr << "|";
	std::cout << std::endl;
	for (int i = 0; i < sizeof(arr_str)/sizeof(arr_str[0]); i++)
		std::cout << arr_str[i] << "|";
	
	//string
	std::cout << "\n\n";
	std::string stdstr = "sd";
	for (auto c : stdstr)
		std::cout << c << " ";
	std::string empty = "";
	std::cout << "empty string size: " << empty.size(); // this is different from sizeof("") as shown before
	std::cout << std::endl;
}


//============ 23 ===========
//This is to test string and char
#include <iostream>
#include <string>

std::string ret_str(){
	return "ret_str";
}

const char * ret_char(){
	static std::string s = "ret_str";
	//std::string s = "ret_str"; //this leads to garbage output
	return s.c_str(); // converting string to const char, 
	//return (char *) s; // can not do type casting, why?
}

int main(){
	std::string str = ret_str();
	std::cout << str << std::endl;

	const char * str_char = ret_char();
	std::cout << str_char << std::endl;
}


//====== 22 =====
//FAILED
//this is practice friend class template with a condition
#include <iostream>
template <typename T, typename V>
class AllNames{
        protected:
                T CurrAllNames;
        public:
                void AddOneName(V p){
                        this -> CurrAllNames += p.name;
                }
		void ShowAllNames(){
			std::cout << this -> CurrAllNames << std::endl;
		}
};

template <typename T, typename U>
class Person{
	protected:
		T age;
		U name;
		template <typename t, typename u> friend class AllNames;
	public:
		Person(T age, U name){
			this -> age = age;
			this -> name = name;
		}
};

int main(){
	Person <int, std::string> me(30, "zls");
	AllNames<std::string, Person<int, std::string>> allnames;
	allnames.AddOneName(me);
	allnames.AddOneName(me);
	allnames.ShowAllNames();
}

//======= 21 ======
#include <iostream>

int main(){
	std::string a = "zls";
	std::string b = "dsy";
	std::cout << a << " " << a.size() << " " << a.length() << std::endl;
	std::cout << a+b << (a+b).size() << " " << (a+b).length() << std::endl;
}

//===== 20 =====
//can we make friend class a template
#include <iostream>
template <typename T, typename U>
class Person{
	protected:
		template <typename V> friend class GetPerson; //here V should be a different name from those above
		T name;
		U age;
	public:
		Person(T name, U age){
			this -> name = name;
			this -> age = age;
		}
		void ShowPerson(){
			std::cout << this -> name << " " << this -> age << std::endl;
		}
};

template <typename T> 
class GetPerson{
	public:
		void ShowPerson(T p){
			std::cout << p.name << " " << p.age << std::endl;
		}
};

int main(){
	Person<std::string, int> me("zls", 30);
	me.ShowPerson();

	GetPerson<Person<std::string, int>> getme;
	getme.ShowPerson(me);
}

//======= 19 ======
#include <iostream>
#define INCLUDE_CLASS
#ifdef INCLUDE_CLASS
class Me{
	public:
		Me(){
			std::cout << "This is me" << std::endl;
		}
};
#endif

int main(){
	Me me;
}


//========= 18 ==========
//This is to test function overloading
#include <iostream>

int add(int a, int b){
	std::cout << " add_int: ";
	return a+b;
}

double add(double a, double b){
	std::cout << " add_double: ";
	return a+b;
}

float add(float a, float b){
	std::cout << " add_float: ";
	return a+b;
}

int add(int a){
	std::cout << " add_int_single ";
	return a;
}

double add(double a){
	std::cout << " add_double_single ";
	return a;
}

float add(float a){
	std::cout << " add_float_single ";
	return a;
}


int main(){
	int a = 2, b = 3;
	double c = 4, d = 5;
	float e = 6, f = 7;

	std::cout << add(a, b) << add(c, d) << add(e, f) << std::endl;
	std::cout << add(a) << add(c) << add(e) << std::endl;

}
//======= 17 ====
#include <iostream>

void not_swap(int a, int b){
	int tmp = a;
	a = b;
	b = tmp;
}

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

void swap_ptr (int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int main(){
	int a = 2, b = 3;
	not_swap(a, b);
	std::cout << a << b << std::endl;

	swap(a, b);
	std::cout << a << b << std::endl;

	a = 2; b = 3;
	swap_ptr(&a, &b);
	std::cout << a << b << std::endl;
}
//========= 16 =======
#include <iostream>

#define MaxNumPeople 5

struct Person{
	//it should use class as it contains private members
	public:
		std::string name;
		int age;
		std::string gender;
	
		Person(std::string name, int age, std::string gender) {
			this -> name = name;
			this -> age = age;
			this -> gender = gender;
		}
		Person(){}; // it seems this is a must-have function
		void InfoP(){
			std::cout << "\t " << this -> name << " " << this -> age << " " << this -> gender << std::endl;
		}
};

template <typename T, typename U, typename V> //here T is just Person
class Family{
	protected:
		friend class GetThisFamily;
		T AllMembers[MaxNumPeople];
		U current_numofpeople = 0;
		static V totalpeople; //count the total people of all families
	public:
		//no initialization functions
		void AddMember(T p){
			this -> totalpeople ++;
			this -> current_numofpeople ++;
			U ind = this -> current_numofpeople - 1;
			this -> AllMembers[ind] = p;
		}
		void GetFamily(){
			std::cout << "This family has " << this -> current_numofpeople << " people:" << std::endl;
			for (int i = 0; i < this -> current_numofpeople; i++){
				AllMembers[i].InfoP();
			}
		}
		V GetTotalPeople();
};

template <typename T, typename U, typename V> V Family<T, U, V>::totalpeople;

template <typename T, typename U, typename V> V Family<T, U, V>::GetTotalPeople(){
	return Family<T,U,V>::totalpeople;
}

//template <typename X> //T is just family in our case
class GetThisFamily{
	public:
		void ShowThisFamily(Family <Person, int, int> family){ 
			for (auto i = 0; i < family.current_numofpeople; i++)
				family.AllMembers[i].InfoP();
		}
};


int main(){
	Person p1("zls", 30, "male");
	Person p2("dsy", 32, "female");
	//========= one family =========
	Family<Person, int, int> my_family;
	my_family.AddMember(p1);
	my_family.AddMember(p2);

	my_family.GetFamily();
	//========= second family =========
	Family<Person, int ,int> you_family;
	you_family.AddMember(p2);
	you_family.AddMember(p1);
	you_family.AddMember(p2);

	you_family.GetFamily();

	std::cout << my_family.GetTotalPeople() << std::endl;

	//======== friend class ========
	std::cout << "==================" << std::endl;
	GetThisFamily getyou;
	std::cout << "my_family:" << std::endl;
	getyou.ShowThisFamily(my_family);
}

// non-template type class implementation
class Family{
	protected:
		Person AllMembers[MaxNumPeople];
		int current_numofpeople = 0;

	public:
		//only provide add_member method to add family members
		Family(){}
		void AddMembers(Person p){
			this -> current_numofpeople ++;
			int ind = this -> current_numofpeople - 1;
			this -> AllMembers[ind] = p;
		};

		int GetTotalPeople(){
			return this -> current_numofpeople;
		}

		void ExamineFamily(){
			//Person allmembers = this -> AllMembers; //can not do this as c++ does not support passing arrays, only pointers
			Person *allmembers = this -> AllMembers;
			for (int i = 0; i < this -> current_numofpeople; i++){
				std::cout << allmembers[i].name << " " << allmembers[i].age << " " << allmembers[i].gender << std::endl;
			}
		}
};

int main(){
	Person p1 ("ZLS", 30, "male");
	Person p2 ("DSY", 32, "female");

	Family my_family;
	my_family.AddMembers(p1);
	my_family.AddMembers(p2);
	
	std::cout << my_family.GetTotalPeople() << std::endl;
	
	my_family.ExamineFamily();
}

//======= 15 ========
#include <iostream>
//bubble sort for different numeric types: int, float, double, etc.
template <typename T>
void bubble_sort(T *arr, int n){
	for (int i = 0; i <= n-2 ; i++){
		for (int j = i+1; j <= n-1; j++){
			if (arr[i] > arr[j]) {
				T tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}

int main(){
	int a[5] = {2, 0, 3, -5, 9};
	bubble_sort(a, 5);

	for (auto ele : a)
		std::cout << ele << " ";
	std::cout << std::endl;
}

//======= 14 ======
#include <iostream>

template <typename T, typename U, typename V>
void output(T t, U u, V v){
	std::cout << "value: size -> ";
	std::cout << t << ": " << sizeof(T) << "; " << u << ": " << sizeof(U) << "; " << v << ": " << sizeof(V) << " ";
	std::cout <<sizeof(t)/sizeof(T) << " " << sizeof(u)/sizeof(U) << " " << sizeof(v)/sizeof(V) << std::endl;
}

int main(){
	//pass some constants to a template function
	output<int, float, double>(2.2, 3.2, 4.2);

	int a = 3;
	std::string b = "xxx";
	double c[2]={32, 3};
	output(a, b, c);
	std::cout << *c << sizeof(c) << std::endl;
}

//========== 13 =========
//This is to practice template function
#include <iostream>

int double_int(int a){ return a*2;}
double double_double(double a){ return a*2;}
float double_float(float a){ return a*2;}
//create a template that does the same functionality
template <typename T>
T double_type(T a){
	std::cout << "sizeof this type: " << sizeof(T) << std::endl;
	return a*2;
}

int main(){
	int a = 2;
	double b = 3;
	float c = 4;
	std::cout << double_int(a) << " " << double_double(b) << " " << double_float(c) << std::endl;

	auto aa = double_type(a);
	auto bb = double_type(b);
	auto cc = double_type(c);
	std::cout << sizeof(aa) << sizeof(bb) << sizeof(cc) << std::endl;
	std::cout << aa << bb << cc << std::endl;

}


//============= 12 ================
#include "preprocessing.h"
#include <iostream>

#ifdef OUTSIDE_ANIMAL
Animal::Animal(int a, int b){
	this -> a = a;
	this -> b = b;
}
void Animal::Get(){
	std::cout << this -> a << " " << this -> b << std::endl;
}
#endif 

int main(){
	Animal a(2, 3);
	a.Get();
	std::cout << OUTSIDE_ANIMAL << std::endl;
}

//========= 11 ===========
#include <iostream>
#define max(a, b) (a>b? a:b) //MACRO functions can be very problematic
#define NUM_ELEMENTS 

#ifdef NUM_ELEMENTS //defined but without any value in it
//can not include more than MACROs
//std::cout << "xxxx" << std::endl;
#define XX 9
#endif
//void m(int a, int b){
//	a > b? a:b;
//}

int main(){
	std::cout << XX << std::endl;
	//here NUM_ELEMENTS is none, so there will be a compiling error
	//std::cout << NUM_ELEMENTS << std::endl;
	int a = 2;
	int b = 3;
	max(a, ++b);
	std::cout << b << std::endl;

	a = 2;
	b = 3;
	//define a function inside main()
	//lambda
	auto m = [](int a, int b){
		a > b? a:b;
	};
	m(a, ++b);
	std::cout << b << std::endl;
}



//========= 10 ==========
//This is to practice preprocessing macros
//
#include <iostream>
#include "preprocessing.h"

#ifndef NUM_ELEMENTS
#define NUM_ELEMENTS 100
#endif

#if NUM_ELEMENTS > 10
#undef NUM_ELEMENTS //BETTER undefine it first before redefining it
#define NUM_ELEMENTS 10
#elif NUM_ELEMENTS > 5
#undef NUM_ELEMENTS
#define NUM_ELEMENTS 5
#endif

int main(){
	double a[NUM_ELEMENTS];
	for (int i = 0; i < NUM_ELEMENTS; i++)
		a[i] = i;
	for (auto ele : a){
		std::cout << ele << " ";
	}
	std::cout << std::endl;
}


//=========== 9 ===========
//This is to practice struct (EXCEPT the default visibility, struct and class are basically the same)
//choose between struct and class: as long as there is a private/protected variable, use class
#include <iostream>

struct Info{
	//by default everything is public
	std::string name;
	int age;
};

Info RetInfo(){
	Info me;
	me.name = "ZLS";
	me.age = 30;
	return me;
}

int main(){
	Info me = RetInfo();
	std::cout << me.name << " " << me.age << std::endl;
}



//=========== 8 ==========
//this is to practice friend class
#include <iostream>

class Customer{
	private:
		//name and age can be accessible in GetCustomer environment
		friend class GetCustomer; 
		std::string name;
		int age;
	public:
		Customer(std::string name, int age){
			this -> name = name;
			this -> age = age;
		}
};

class GetCustomer{
	public: //without this keywork, it will be private by default
	void OutputCustomer (Customer customer){
		std::cout << "name: " << customer.name << "; age: " << customer.age << std::endl;
	}
};

int main(){
	Customer customer("zls", 30);
	GetCustomer getcustomer;
	getcustomer.OutputCustomer(customer);
}

//========= 7 ========
//practice polymorphism
#include <iostream>

class Base{
	public:
		Base(int i) {std::cout << "Base ArgInit" << std::endl;}
		Base(){std::cout << "Base Init" << std::endl;}
		virtual void WhereAbout(){std::cout << "Base" << std::endl;}
		void Random(){std::cout << "Random_Base" << std::endl;}
};

class Control{
        public:
                Control(){}
                void WhereAbout(){std::cout << "Control" << std::endl;}
		void CC(){std::cout << "CC_Control" << std::endl;}
};


class Child_1: public Base, public Control { //multiple inheritence
	public:
		//it seems the base constructor without argument is called implicitly unless it's called explicitly
		Child_1(){std::cout << "Child_1 Init" << std::endl;}
		Child_1(int i): Base(i) {std::cout << "Child_1 ArgInit" << std::endl;}
		//method with the same name as in base class, it will be overridden
		void WhereAbout(); // we can call the function in the base class, if not we have to declare and implement it
		void Random(){std::cout << "Random_Child_1" << std::endl;}
		virtual void CC(){std::cout << "CC_Child_1" << std::endl;}
};

void Child_1::WhereAbout(){
	std::cout << "Child_1" << std::endl;
}

void base_whereabout(Base *b){
	b -> WhereAbout(); //use the function in the pointed class
	b -> Random(); // use the function in the Base class
}

void control_whereabout(Control *c){
	//since both functions in the parsent class are non-virtual functions, so they will be called
	c -> WhereAbout();
	c -> CC();
}

void child_1_whereabout(Child_1 *c){
	c -> WhereAbout();
	c -> Random();
	c -> CC();
}

void child_1_whereabout_dot(Child_1 c){ //why & is used by someone else?
        c . WhereAbout();
        c . Random();
        c . CC();
}


int main(){
	Base c1; //DONT c1() if no arguments need to be passed
	c1.WhereAbout();

	std::cout << "======== Child_1 ======" << std::endl;
	Child_1 c2(2);
	c2.WhereAbout();
	
	std::cout << "======== Pure ========" << std::endl;
	//new creates a pointer pointing to Child_1, so the virtual functions in the type-cased class will be replaced
	Child_1 *c_ptr = new Child_1;
	c_ptr -> WhereAbout();
	std::cout << "***********" << std::endl;
	child_1_whereabout(c_ptr);
	
	//base_whereabout(new Base(2));
	std::cout << "========= Base Child_1 ========" << std::endl;
	base_whereabout(new Child_1(2));

	std::cout << "======== CC =========" << std::endl;
	control_whereabout(new Child_1);

	std::cout << "================" << std::endl;
	Child_1 C(2);
	child_1_whereabout_dot(C);
}


//============ 6 ===========
#include <iostream>
#include <cmath>

class Rectangle{
	protected:
		double height, width;

	public:
		Rectangle(double, double);
		Rectangle(){}
		~Rectangle(){std::cout << "Destroying Rectangle Instance " << this->height << std::endl;}

		void SetAll(double, double);
		double Area();
		double GetHeight(){return this -> height;}
		double GetWidth(){return this -> width;}
};
Rectangle::Rectangle(double h, double w){
	this -> height = h;
	this -> width =w;
}
void Rectangle::SetAll(double h, double w){
	this -> height = h;
	this -> width = w;
}
double Rectangle::Area(){
	return this->height * this->width;
}

double make_h(int i){
	return i;
}
double make_w(int i){
	return pow(i, 3);
}

int main(){
	//Rectangle is just like a datatype, e.g. int, dboule, etc., so we can create an array of this type
	Rectangle rec[2]; //this array is only destroyed just before exting main()

	std::cout << rec << " " << sizeof(double) << " " << sizeof(rec) << std::endl;
	
	for (int i = 1; i <=2; i++){
		int rec_ind = i - 1;
		rec[rec_ind].SetAll(make_h(i), make_w(i));
		std::cout << rec[rec_ind].GetHeight() << " " << rec[rec_ind].GetWidth() << " " << rec[rec_ind].Area() << std::endl;
	}
	//new and delete provide the possibility of controling allocating and deallocating objects at will
	Rectangle *rec_3 = new Rectangle(4, 44);
	std::cout << rec_3->Area() << std::endl;
	delete rec_3; // WITHOUT this line, seems the destructor is not called

	Rectangle *rec_arr = new Rectangle[3];
	for (int i = 4; i < 7; i++){
		rec_arr[i-4].SetAll(make_h(i+1), make_w(i+1));
		std::cout << rec_arr[i-4].GetHeight() << " " << rec_arr[i-4].GetWidth() << " " << rec_arr[i-4].Area() << std::endl;
	}
	delete [] rec_arr; //not sure why [] is needed here while it is not in the following array example

	//================
	int *t_1 = new int;
	delete t_1;
	double *t_2 = new double[3] {2, 3, 4};
	std::cout << t_2[0] << t_2[1] << t_2[2] << std::endl;	
	delete t_2;

	std::cout << "End of main, but the variables in this scope will be destroyed after this line." << std::endl;
}


//=========== 5 ========
//This is to practice virtual class with override
#include <iostream>
#include <cmath>

class Shape{
	protected:
		int s = 2323;
	public:
		//return some common properties
		//virtual functions with no implimentation, so add "= 0" after it
		virtual std::string Instance_Shape() = 0;
		virtual double Instance_Area() = 0;
		//int get_s(){
		//	return this -> s;
		//}
};

class Rectangle: public Shape{
	protected:
		double height;
		double width;
	public:
		Rectangle(double height, double width){
			this -> height = height;
			this -> width = width;
		}
		std::string Instance_Shape() override {
			return "Rectangle";
		}
		double Instance_Area() override final { //final: the child classes can not override this function
			return this -> height * this -> width;
		}
};

class Square: public Rectangle{
	public:
		Square(double side): Rectangle(side, side){}
		std::string Instance_Shape() override {
			return "Square";
		}
		int get_s(){
			return this-> s;
		}
};

void output_rectangle(Rectangle rec){ //when to use Rectangle&??
	std::cout << "Shape: " << rec.Instance_Shape() << "; Area: " << rec.Instance_Area() << std::endl;
}

class Circle: public Shape{
	protected:
		double radius;
	public:
		Circle(double radius){
			this -> radius = radius;
		}
		std::string Instance_Shape() override {
			return "Circle";
		}
		double Instance_Area() override {
			return M_PI * std::pow(this -> radius, 2);
		}
};

void output_circle(Circle cir){
	std::cout << "Shape: " << cir.Instance_Shape() << "; Area: " << cir.Instance_Area() << std::endl;
}

void output_shape(Shape &shape){ //can not use "Shape shape" as abstract class Shape can not have instances, but can have pointer like variable
	std::cout << "Shape: " << shape.Instance_Shape() << "; Area: " << shape.Instance_Area() << std::endl;
} 

int main(){
	//Shape shape; // the abstract class can not be instantiated
	Rectangle rec_1(2, 3), rec_2(4, 5);
		
	//std::cout << "Shape: " << rec_1.Instance_Shape() << "; Area: " << rec_1.Instance_Area() << std::endl;
	//std::cout << "Shape: " << rec_2.Instance_Shape() << "; Area: " << rec_2.Instance_Area() << std::endl;
	output_rectangle(rec_1);
	output_rectangle(rec_2);

	std::cout << std::endl << std::endl;
	
	Circle cir_1(1), cir_2(2);
	output_circle(cir_1);
	output_circle(cir_2);
	
	std::cout << std::endl << std::endl;
	output_shape(rec_1);
	output_shape(rec_2);
	output_shape(cir_1);
	output_shape(cir_2);

	std::cout << std::endl << std::endl;
	Square sqr(2);
	output_shape(sqr);
	std::cout << sqr.get_s() << std::endl;
}


//========== 4 ==========
//This is to comprehensively practice static syntax
//static variable in a function
#include <iostream>

void static_1(){
	//static is something like the mutables passed into a python closure
	static int a = 2;
	static double b[3] = {2.1, 3};
	int num_elements = sizeof(b)/sizeof(b[0]);
	a ++;
	for (int i = 0; i < num_elements; i++){
		b[i] ++;
	}
	
	std::cout << "a: " << a << " b: ";
	for (auto ele : b){
		std::cout << ele << " ";
	}	
	std::cout << std::endl;
}

//To test that static variables last till the end of the life of the program, we take class as an example
class Test_Static_LifeTime{
	private:
		int order;
	public:
		Test_Static_LifeTime(int);
		~Test_Static_LifeTime();
};

Test_Static_LifeTime::Test_Static_LifeTime(int order){
	this -> order = order;
	std::cout << "Test_Static_LifeTime_" << order << std::endl;
}

Test_Static_LifeTime::~Test_Static_LifeTime(){
	std::cout << "Destroying " << this -> order << std::endl;
}

//To test static variables/functions in class
class Static{
	private:
		int MaxNumIns = 3;
		int order;
		static int current_num_ins; //even though is private, it can still be initialized outside of class
	public:
		Static(int order){
			this -> order = order;
			current_num_ins ++;
			if (Static::GetCurrentnumins() > MaxNumIns){
				std::cout << "ERROR: exceeded the maxium number of objects allowed to create!!" << std::endl;
				this -> ~Static();
				std::cout << "\tDone fake deleting " << this -> order << " i.e. only executing the destructor." << std::endl;
			}
		}
		~Static(){
			std::cout << "Destroying " << this -> order << std::endl;
		}

		static int GetCurrentnumins(){
			return Static::current_num_ins;
		}

};
int Static::current_num_ins = 0; //it can only be initialized like this? I.E. outside of the original class and main function


int main(){
	static_1();
	static_1();
	if (true){ //LOWER-CASE
		Test_Static_LifeTime o_1(1);
		for (int i = 1; i < 1000000; i++)
			i*i;
		std::cout << "end of if " << std::endl;
		//looks like o_1 is alive till the end of if statement
	}
	//the class objects are destroyed in reverse order
	if (false){
		Test_Static_LifeTime o_2(2);
		Test_Static_LifeTime o_3(3);
	}
	std::cout << "\n\n==========\n";	
	Static me_1(1);
	Static me_2(2);
	Static me_3(3);
	Static me_4(4);
	Static me_5(5);

	//class::attribute or method, inside the class this->, object: obj.public_attribute or function
	std::cout << "the value of the static variable is shared among the objects " << Static::GetCurrentnumins() << me_1.GetCurrentnumins() << me_2.GetCurrentnumins() << std::endl;
	std::cout << "end of main" << std::endl;
}


//============= 3 ==========
//practice class
#include <iostream>

//test static variable which accumulates over the whole period of the program
void test_static_variable(){
	static int a = 9;
	a ++;
	std::cout << a << std::endl;
}
//test_static_variable::a = 9; // can not assign a static variable outside of a function
class Animal {
protected:
	//these can not be accessed by class instances directly
	std::string name;
	double height;
	double weight;
	static int numofanimals; //can not initialize non-const static variable
public:
	int fake_static = this -> numofanimals;
	//std::cout << "******* fake_static: " << fake_static << std::endl; // you can not print here, it only allows types
	std::string height_unit = "cm";
	std::string weight_unit = "kg";
	Animal(std::string name, double height, double weight); // no return type
	Animal();
	~Animal();

	void SetName(std::string);
	void SetHeight(double);
	void SetWeight(double);
	
	//static function can be accessed by both clas itself and class instances
	static void SetNumofanimals(int num){
		//inside a static function, we can not access instance a
		numofanimals = num;
	}

	std::string GetName();
	double GetHeight();
	double GetWeight();

	static int GetNumofanimals(){
		//return this -> numofanimals;
		//return Animal::numofanimals;
		return numofanimals; //don't use this ->, otherwise Animal:: will not be able to access it
	}

	void ToString(){
		std::cout << this -> name << " " << this -> height << " " << this -> weight << std::endl;
	}		

}; //; is needed

int Animal::numofanimals = 0; //it has to be assigned outside of the class

Animal::Animal(std::string name, double height, double weight){
	//use this -> pointer to access attributes/methods in class definition
	this -> name = name; //looks like this pointer is necessary
	this -> height = height;
	this -> weight = weight;
	Animal::numofanimals ++;
}

Animal::Animal(){
	this -> name = "zls";
	this -> height = 0;
	this -> weight = 0;
	Animal::numofanimals ++;
}

Animal::~Animal(){
	std::cout << GetName() << " is destroyed!" << std::endl;
}

void Animal::SetName(std::string name){
	this -> name = name;
}

void Animal::SetHeight(double height){
	this -> height = height;
}

void Animal::SetWeight(double weight){
	this -> weight = weight;
}

std::string Animal::GetName(){
	return name;
}

double Animal::GetHeight(){
	return this -> height;
}

double Animal::GetWeight(){
	return this -> weight;
}

class Dog: public Animal {
	protected:
		std::string sound;
	public: 
		Dog(std::string, double, double, std::string);
		Dog(): Animal(){
			std::cout << "empty dog" << std::endl;
		}
		std::string MakeSound();


};

Dog::Dog(std::string name, double height, double weight, std::string sound):Animal (name, height, weight){
	this -> sound = sound;
}

std::string Dog::MakeSound(){
	return this -> sound;
}

// xx returns 1 while xx() returns 9;
int xx(){
	return 9;
}

int main(){
	test_static_variable();
	test_static_variable();

	//Animal::numofanimals = 3; // can not be accessed as it is protected
	//Animal::SetNumofanimals(4);
	Animal me;
	//me.SetNumofanimals(1);
	//use dot operator to access attribute/method by an object
	me.SetName("Seth Zhao");
	me.SetHeight(178);
	me.SetWeight(69);

	std::cout << "name: " << me.GetName() << " height: " << me.GetHeight() << me.height_unit << " weight: " << me.GetWeight() << me.weight_unit << std::endl;
	std::cout << Animal::GetNumofanimals() << std::endl;
	std::cout << "fake_static: " << me.fake_static << std::endl;
	me.ToString();

	Animal you("zls", 178, 69);
	std::cout << "name: " << you.GetName() << " height: " << you.GetHeight() << you.height_unit << " weight: " << you.GetWeight() << you.weight_unit << std::endl;
        std::cout << you.GetNumofanimals() << std::endl;
	std::cout << "fake_static: " << you.fake_static << std::endl;
	you.ToString();

	std::cout << "\n\n=============" << std::endl;
	//Dog::SetNumofanimals (2);
	Dog dog;
	std::cout << dog.GetName() << std::endl;
	dog.ToString();
	std::cout << "number of dogs: " << Animal::GetNumofanimals() << std::endl;

	Dog dog_zls ("dog_zls", 178, 69, "bark");
	dog_zls.ToString();
	std::cout << "number of dogs: " << Animal::GetNumofanimals() << std::endl;

	std::cout << "\n\nxx returns " << xx << " (" << xx() << ")" << std::endl; //why it returns 1????

	std::cout << "\n\n========== Destroying ======" << std::endl;
}

//========= 2 =========
#include "my_funcs/my_func_1.h" 

int main(){
	int a = 2;
	std::cout << a << " " << ret_square(a) << std::endl;
}

//=============== 1 ==============
#include <iostream> //std::count is in iostream

int ret_double(int a) {
	return a*2;
}

void change_arr(double *arr, int num_elements){
	//std::cout << "arr: " << arr << std::endl;
	//int num_elements = sizeof(arr)/sizeof(arr[0]);
	std::cout << "num_elements: " << num_elements << std::endl;
	for (int i = 0; i < num_elements; i++){
		arr[i] += 1;
	}
}

 int * create_arr(){
	static int a[3] = {1, 2, 3}; // this variable is only allocated once and the previous values carry through to the future
				     // its initialization is executed only once
	for (int i = 0; i < 3; i++)
		a[i] += 2;
	return a; // it returns an address
}


int main(){
	std::string sep_line = "\n\n==================\n";
	
	//just get started warming up my c++ memory
	std::cout << sep_line;
	int a;
	a = 3;
	std::cout << "first" << std::endl << "second\n"; //\n looks like the same as std::endl
	std::cout << "input: " << a << ", ret_double returned:" << ret_double(a) << "\n";

	//try some arrays	
	std::cout <<sep_line;
	int list[3] = {4, 5, 6};
	std::cout << list[0] << ": " << list[1] << ": " << list[2] << "\n";
	//iterate over an array
	std::cout << "char has size of " << sizeof(char) << std::endl;
	std::cout << "int has size of " << sizeof(int) << std::endl;
	std::cout << "float has size of " << sizeof(float) << std::endl;
	std::cout << "double has size of " << sizeof(double) << std::endl;
	std::cout << "the size of list is " << sizeof(list) << std::endl;
	for (auto ele : list){ 
		std::cout << "\t" << ele << " whose size is " << sizeof(ele) << std::endl;
	}
	//ele is declared inside the for loop, so it is not accessible after it, which is quite different form python
	//std::cout << ele << "\n";
	
	//try some pointers
	std::cout << sep_line;
	//float a = 3; // a was declared before
	//int a = 4;
	float c = 4;
	float *c_pr = &c; //c_pr contains the address of c, *c_pr refers to what is in c
	std::cout << c << "'s address is " << &c << std::endl; 
	std::cout << *c_pr << "'s address is " << c_pr << std::endl;
	int num_elements = 7;
	double arr [num_elements] = {2.1, 3.0};
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	// change array elements
	change_arr(arr, num_elements); //cpp does not take the entire array, but it takes the position of an array, and number of elements
	std::cout << "after being modified" << std::endl;
	for (auto ele : arr){
		std::cout << ele << std::endl;
	}
	int skip_first_elements = 3;
	skip_first_elements = skip_first_elements < num_elements ? skip_first_elements : num_elements;
	change_arr(&arr[skip_first_elements], num_elements - skip_first_elements);
	std::cout << "not modify the first element" << std::endl;
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	std::cout << "all add 200" << std::endl;
	int i = -1;
	for (auto ele : arr){ //ele is a new variable, which has the same value as the element, but in different location
		i ++;
		std::cout << &arr[i] << " =? " << &ele << std::endl;
		* (&ele) = ele +200;
		std::cout << ele << std::endl;
	}
	for (auto ele : arr){
		std::cout << "\t" << ele << std::endl;
	}
	
	//try a function which returns arrays
	int *new_arr;
	int num_ele = 3;
	new_arr = create_arr();
	for (int i = 0; i < num_ele; i++){
		//std::cout << new_arr[0];
		std::cout << *(new_arr+i) << std::endl;
	}
	new_arr = create_arr();
	for (int i = 0; i < num_ele; i++){
		std::cout << "\t" << *(new_arr + i) << std::endl;
	}
}
*/