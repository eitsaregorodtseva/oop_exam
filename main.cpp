#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <memory>

using namespace std;

int CodeSum(string string_) {
  int sum = 0;
  for (unsigned char ch_ : string_) {
        sum += static_cast<int>(ch_); 
  } 
  return sum;
}

class Student {
public:
    Student() = default;

    Student(string group, string fio) {
        this->group_ = group;
        this->fio_ = fio;
       }

    Student(const Student& other) = default;
    Student(Student&& other) = default;
    Student& operator=(const Student& other) = default;
    Student& operator=(Student&& other) = default;
    string getFIO() {
      return this->fio_;
    }

    string getGroup() {
      return this->group_;
    }

    ~Student() = default;

private:
    string group_;
    string fio_;
};

bool operator>(Student& lhs, Student& rhs) {
      return (CodeSum(lhs.getFIO()) > CodeSum(rhs.getFIO()));
}

class Group {
public:
    Group() = default;
    Group(const Group& other) = default;
    Group(Group&& other) = default;
    Group& operator=(const Group& other) = default;
    Group& operator=(Group&& other) = default;
    
    int getSize() {
      return this->size_;
    }

    string findStudentGroup(const string name) {
      for (int i = 0; i < this->size_; i++)
      if (name == this->group_[i].getFIO()) {
        return this->group_[i].getGroup();
      }
      return "";
    }

    void addStudent(Student& student) {
      if (this->size_ >= this->allocated_) {
        this->allocated_ += 1;
        auto newMemory = new Student[this->allocated_];
        for (size_t i = 0; i < this->size_; ++i) {
            newMemory[i] = this->group_[i];
        }
        delete[] this->group_;
        this->group_ = new Student[this->allocated_];
        for (int i = 0; i < this->size_; ++i) {
            this->group_[i] = newMemory[i];
        }
        delete[] newMemory;
    }
    this->group_[this->size_] = student;
    ++this->size_;
    }

    void sortGroup() {
      for (int i = 0; i < this->size_ - 1; i++) {
        for (int j = 0; j < this->size_ - i - 1; j++) {
            if (this->group_[j] > this->group_[j + 1]) 
                swap(this->group_[j], this->group_[j+1]);
              }
        }
    }

    Student operator[](int number) {
      return this->group_[number];
      }

    ~Group() = default;

private:
    Student *group_;
    int size_, allocated_;
};

void CSVRead(string filename, map<string, Group>& list) {
    ifstream csv_file;
    csv_file.open(filename);
    string line;
    getline(csv_file, line);
    while (getline(csv_file, line)) {
        istringstream ss(line);
        string num, group, fio;
        getline(ss, num, ',');
        getline(ss, group, ',');
        getline(ss, fio, ',');
        Student student = Student(group, fio);
        list[group].addStudent(student);
    }
}

int main() {
  map<string, Group> list;
  string filename = "groups.csv";
  CSVRead(filename, list);    

  string my_fio = "Царегородцева Елизавета Игоревна";
  string target_group = "";

  for (auto elem : list) {
    for (int i = 0; i < elem.second.getSize(); i++) {
      if (elem.second.findStudentGroup(my_fio) != "") {
        target_group = elem.second.findStudentGroup(my_fio);
      }
    }
  }

  list[target_group].sortGroup();
  auto x = list[target_group];
  int count = 0;
  for (int i = 0; i < x.getSize(); i++) {
    if (x[i].getFIO() == my_fio) {
      count = i;
    }
  }

  int sum = 0;
  if (count == x.getSize() - 1) {
    sum = CodeSum(x[0].getFIO());
  }
  else {  
    count++;
    for (int i = count; i < x.getSize(); i++) {
      sum += CodeSum(x[i].getFIO());
      }
  }

  cout << sum << endl;

  return 0;
}