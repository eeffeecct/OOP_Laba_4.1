#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>


class Employee {
private:
	std::string name;
	int age;
	std::string position;
	std::string unit;
public:
	Employee(const std::string name, int age, const std::string position, const std::string str_unit) :
		name(name), age(age), position(position), unit(unit) { }

	const std::string& getName() const {
		return name;
	}

	int getAge() const {
		return age;
	}

	const std::string& getPosition() const {
		return position;
	}

	const std::string& getUnit() const {
		return unit;
	}

	void print() const {
		std::cout << name << ", " << age << ", " << position << ", " << unit << std::endl;
	}
};


class DB {
private: 
	std::vector<Employee*> data;
public:
	~DB() {
		for (Employee* emp : data) {
			delete emp;
		}
	}

	void addEmployee(Employee* emp) {
		data.push_back(emp);
	}
	
	// Print all Employees
	/*void printAll() {
		std::cout << "Employees: " << std::endl;
		for (Employee* emp : data) {
			emp->print();
		}
	}*/

	void printAll() {
		std::cout << "Employees: " << std::endl;
		std::for_each(data.begin(), data.end(), [](const Employee* emp) {emp->print();});
	}

	// Print all Engineers
	void printEngineers() {
		std::cout << "Engineers" << std::endl;
		std::for_each(data.begin(), data.end(), [](const Employee* emp) {
			if (emp->getPosition() == "инженер") 
				emp->print();
			});
	}

};


void readFile(DB& db, const std::string& filename) {
	std::ifstream file(filename);

	if (!file.is_open()) {
		std::cerr << "File opening error: " << filename;
		return;
	}

	std::string line;
	while (std::getline(file, line)) {	// line by line 
		size_t first_space = line.find(' '); // return index after lastname
 		size_t second_space = line.find(' ', first_space + 1); // after initials
		size_t first_comma = line.find(','); // after year
		size_t second_comma = line.find(',', first_comma + 1); // after position 
		
		std::string name = line.substr(0, second_space); // name
		int year = std::stoi(line.substr(second_space + 1, 4));
		std::string position = line.substr(
			first_comma + 2,
			second_comma - first_comma - 2
		);
		std::string group = line.substr(second_comma + 2);
		db.addEmployee(new Employee(name, year, position, group));
	}
}


int main() {
	DB db;
	std::string filename = "file.txt";

	readFile(db, filename);

	//db.printAll();
	db.printEngineers();

	return 0;
}