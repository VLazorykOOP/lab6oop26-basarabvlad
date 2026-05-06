#include <iostream>
#include <string>
using namespace std;

//////////////////////////////////////////////////////////////
// 🔹 ЗАВДАННЯ 1
// Віртуальне та невіртуальне успадкування
//////////////////////////////////////////////////////////////

class Base {
protected:
    int value;
public:
    Base(int v = 0) : value(v) {
        cout << "Base constructor\n";
    }

    virtual void show() {
        cout << "Base value: " << value << endl;
    }

    virtual ~Base() {
        cout << "Base destructor\n";
    }
};

// ВІРТУАЛЬНЕ УСПАДКУВАННЯ
class Derived1 : virtual public Base {
protected:
    int d1;
public:
    Derived1(int v, int d) : Base(v), d1(d) {
        cout << "Derived1 constructor\n";
    }

    void show() override {
        cout << "Derived1: " << value << ", " << d1 << endl;
    }

    virtual ~Derived1() {
        cout << "Derived1 destructor\n";
    }
};

class Derived2 : virtual public Base {
protected:
    int d2;
public:
    Derived2(int v, int d) : Base(v), d2(d) {
        cout << "Derived2 constructor\n";
    }

    void show() override {
        cout << "Derived2: " << value << ", " << d2 << endl;
    }

    virtual ~Derived2() {
        cout << "Derived2 destructor\n";
    }
};

class FinalVirtual : public Derived1, public Derived2 {
    int f;
public:
    FinalVirtual(int v, int d1, int d2, int f)
        : Base(v), Derived1(v, d1), Derived2(v, d2), f(f) {
        cout << "FinalVirtual constructor\n";
    }

    void show() override {
        cout << "FinalVirtual: " << value << ", " << d1 << ", " << d2 << ", " << f << endl;
    }

    ~FinalVirtual() {
        cout << "FinalVirtual destructor\n";
    }
};

// БЕЗ ВІРТУАЛЬНОГО УСПАДКУВАННЯ
class Base2 {
public:
    int value;
};

class Derived1_2 : public Base2 {
public:
    int d1;
};

class Derived2_2 : public Base2 {
public:
    int d2;
};

class FinalNonVirtual : public Derived1_2, public Derived2_2 {
public:
    int f;
};

//////////////////////////////////////////////////////////////
// 🔹 ЗАВДАННЯ 2
// Абстрактний клас
//////////////////////////////////////////////////////////////

class Quadrilateral {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual void info() = 0;
    virtual ~Quadrilateral() {}
};

class Square : public Quadrilateral {
    double a;
public:
    Square(double a) : a(a) {}

    double area() override { return a * a; }
    double perimeter() override { return 4 * a; }

    void info() override {
        cout << "Square side=" << a << endl;
    }
};

class Rectangle : public Quadrilateral {
    double a, b;
public:
    Rectangle(double a, double b) : a(a), b(b) {}

    double area() override { return a * b; }
    double perimeter() override { return 2 * (a + b); }

    void info() override {
        cout << "Rectangle sides=" << a << "," << b << endl;
    }
};

class Parallelogram : public Quadrilateral {
    double a, b, h;
public:
    Parallelogram(double a, double b, double h)
        : a(a), b(b), h(h) {
    }

    double area() override { return a * h; }
    double perimeter() override { return 2 * (a + b); }

    void info() override {
        cout << "Parallelogram: a=" << a << " b=" << b << " h=" << h << endl;
    }
};

class Trapezoid : public Quadrilateral {
    double a, b, c, d, h;
public:
    Trapezoid(double a, double b, double c, double d, double h)
        : a(a), b(b), c(c), d(d), h(h) {
    }

    double area() override { return (a + b) / 2 * h; }
    double perimeter() override { return a + b + c + d; }

    void info() override {
        cout << "Trapezoid: bases=" << a << "," << b << endl;
    }
};

//////////////////////////////////////////////////////////////
// 🔹 ЗАВДАННЯ 3
// Множинне наслідування
//////////////////////////////////////////////////////////////

class Human {
protected:
    string name;
public:
    Human(string name = "Unknown") : name(name) {}

    virtual void show() {
        cout << "Human: " << name << endl;
    }

    virtual ~Human() {}
};

class Father : virtual public Human {
protected:
    int age_f;
public:
    Father(string name, int age) : Human(name), age_f(age) {}

    void show() override {
        cout << "Father: " << name << " age=" << age_f << endl;
    }
};

class Mother : virtual public Human {
protected:
    int age_m;
public:
    Mother(string name, int age) : Human(name), age_m(age) {}

    void show() override {
        cout << "Mother: " << name << " age=" << age_m << endl;
    }
};

class Son : public Father, public Mother {
    int age_s;
public:
    Son(string name, int af, int am, int as)
        : Human(name), Father(name, af), Mother(name, am), age_s(as) {
    }

    void show() override {
        cout << "Son: " << name << " age=" << age_s << endl;
        cout << "Father age=" << age_f << endl;
        cout << "Mother age=" << age_m << endl;
    }
};

//////////////////////////////////////////////////////////////
// 🔹 MAIN
//////////////////////////////////////////////////////////////

int main() {

    cout << "===== TASK 1 =====\n";
    FinalVirtual obj(10, 20, 30, 40);
    obj.show();

    cout << "\nSizes (virtual):\n";
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived1) << endl;
    cout << sizeof(Derived2) << endl;
    cout << sizeof(FinalVirtual) << endl;

    cout << "\nSizes (non-virtual):\n";
    cout << sizeof(Base2) << endl;
    cout << sizeof(Derived1_2) << endl;
    cout << sizeof(Derived2_2) << endl;
    cout << sizeof(FinalNonVirtual) << endl;

    cout << "\n===== TASK 2 =====\n";
    Quadrilateral* arr[4];

    arr[0] = new Square(5);
    arr[1] = new Rectangle(4, 6);
    arr[2] = new Parallelogram(5, 3, 4);
    arr[3] = new Trapezoid(3, 5, 4, 4, 2);

    for (int i = 0; i < 4; i++) {
        arr[i]->info();
        cout << "Area=" << arr[i]->area() << endl;
        cout << "Perimeter=" << arr[i]->perimeter() << endl;
        cout << "------\n";
    }

    for (int i = 0; i < 4; i++) delete arr[i];

    cout << "\n===== TASK 3 =====\n";
    Son s("Ivan", 45, 43, 20);
    s.show();

    return 0;
}