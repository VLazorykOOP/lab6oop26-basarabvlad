#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/* ============================
   ЗАВДАННЯ 1
   ============================ */

   // Без віртуального успадкування
class A {
public:
    int a;
    A() { a = 1; cout << "A created\n"; }
    ~A() { cout << "A destroyed\n"; }
};

class B : public A {
public:
    int b;
    B() { b = 2; cout << "B created\n"; }
    ~B() { cout << "B destroyed\n"; }
};

class C : public A {
public:
    int c;
    C() { c = 3; cout << "C created\n"; }
    ~C() { cout << "C destroyed\n"; }
};

class D : public B, public C {
public:
    int d;
    D() { d = 4; cout << "D created\n"; }
    ~D() { cout << "D destroyed\n"; }
};

// З віртуальним успадкуванням
class Av {
public:
    int a;
    Av() { a = 10; cout << "Av created\n"; }
    ~Av() { cout << "Av destroyed\n"; }
};

class Bv : virtual public Av {
public:
    int b;
    Bv() { b = 20; cout << "Bv created\n"; }
    ~Bv() { cout << "Bv destroyed\n"; }
};

class Cv : virtual public Av {
public:
    int c;
    Cv() { c = 30; cout << "Cv created\n"; }
    ~Cv() { cout << "Cv destroyed\n"; }
};

class Dv : public Bv, public Cv {
public:
    int d;
    Dv() { d = 40; cout << "Dv created\n"; }
    ~Dv() { cout << "Dv destroyed\n"; }
};

/* ============================
   ЗАВДАННЯ 2
   ============================ */

   // Абстрактний клас
class Data {
public:
    virtual void display() = 0;
    virtual void save(ofstream& out) = 0;
    virtual void process() = 0;
    virtual ~Data() {
        cout << "Data destroyed\n";
    }
};

// Сигнал
class SignalData : public Data {
    int value;
public:
    SignalData(int v = 0) : value(v) {
        cout << "SignalData created\n";
    }

    void display() override {
        cout << "Signal: " << value << endl;
    }

    void save(ofstream& out) override {
        out << "Signal: " << value << endl;
    }

    void process() override {
        value *= 2;
    }

    ~SignalData() {
        cout << "SignalData destroyed\n";
    }
};

// Результат
class ResultData : public Data {
    double result;
public:
    ResultData(double r = 0) : result(r) {
        cout << "ResultData created\n";
    }

    void display() override {
        cout << "Result: " << result << endl;
    }

    void save(ofstream& out) override {
        out << "Result: " << result << endl;
    }

    void process() override {
        result += 100;
    }

    ~ResultData() {
        cout << "ResultData destroyed\n";
    }
};

// Допоміжні дані
class HelperData : public Data {
    string text;
public:
    HelperData(string t = "") : text(t) {
        cout << "HelperData created\n";
    }

    void display() override {
        cout << "Helper: " << text << endl;
    }

    void save(ofstream& out) override {
        out << "Helper: " << text << endl;
    }

    void process() override {
        text += "_processed";
    }

    ~HelperData() {
        cout << "HelperData destroyed\n";
    }
};

/* ============================
   ЗАВДАННЯ 3
   ============================ */

class Person {
protected:
    string name;
public:
    Person(string n = "Unknown") : name(n) {
        cout << "Person created\n";
    }
    virtual ~Person() {
        cout << "Person destroyed\n";
    }

    virtual void show() {
        cout << "Name: " << name << endl;
    }
};

class Student : virtual public Person {
protected:
    int course;
public:
    Student(string n = "", int c = 1) : Person(n), course(c) {
        cout << "Student created\n";
    }

    void show() override {
        cout << "Student: " << name << ", course: " << course << endl;
    }

    ~Student() {
        cout << "Student destroyed\n";
    }
};

class Father : virtual public Person {
protected:
    int children;
public:
    Father(string n = "", int ch = 0) : Person(n), children(ch) {
        cout << "Father created\n";
    }

    void show() override {
        cout << "Father: " << name << ", children: " << children << endl;
    }

    ~Father() {
        cout << "Father destroyed\n";
    }
};

class StudentFather : public Student, public Father {
public:
    StudentFather(string n, int c, int ch)
        : Person(n), Student(n, c), Father(n, ch) {
        cout << "StudentFather created\n";
    }

    void show() override {
        cout << "Student-Father: " << name
            << ", course: " << course
            << ", children: " << children << endl;
    }

    ~StudentFather() {
        cout << "StudentFather destroyed\n";
    }
};

/* ============================
   ТЕСТИ + ВВЕДЕННЯ
   ============================ */

void testTask1() {
    cout << "\n--- Task 1 ---\n";

    D obj1;
    Dv obj2;

    cout << "Size without virtual: " << sizeof(obj1) << endl;
    cout << "Size with virtual: " << sizeof(obj2) << endl;
}

void testTask2() {
    cout << "\n--- Task 2 ---\n";

    srand(time(0));

    Data* arr[3];

    // випадкові дані
    arr[0] = new SignalData(rand() % 100);
    arr[1] = new ResultData(rand() % 100);
    arr[2] = new HelperData("test");

    ofstream file("data.txt");

    for (int i = 0; i < 3; i++) {
        arr[i]->process();
        arr[i]->display();
        arr[i]->save(file);
    }

    file.close();

    for (int i = 0; i < 3; i++) {
        delete arr[i];
    }
}

void testTask3() {
    cout << "\n--- Task 3 ---\n";

    string name;
    int course, children;

    cout << "Enter name: ";
    cin >> name;
    cout << "Enter course: ";
    cin >> course;
    cout << "Enter children: ";
    cin >> children;

    StudentFather obj(name, course, children);
    obj.show();
}

/* ============================
   MAIN
   ============================ */

int main() {

    testTask1();
    testTask2();
    testTask3();

    return 0;
}