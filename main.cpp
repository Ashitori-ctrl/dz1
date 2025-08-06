#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// 2 наследование
class Person {
protected:
    string name;
    int age;

public:
    Person(const string& name, int age) : name(name), age(age) {}
    void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
};

class Student : public Person {
private:
    string university;

public:
    Student(const string& name, int age, const string& university)
        : Person(name, age), university(university) {}
    void display() const {
        Person::display();
        cout << "Университет: " << university << endl;
    }
};

// 3 полиморфизм
class Animal {
public:
    virtual void speak() const {
        cout << "Животное издает звук" << endl;
    }
    virtual ~Animal() = default; // Я не знаю точно, тут будет корректно удаляться или нет. https://ru.stackoverflow.com/questions/240150/%D0%97%D0%B0%D1%87%D0%B5%D0%BC-%D0%BD%D1%83%D0%B6%D0%B5%D0%BD-%D0%B2%D0%B8%D1%80%D1%82%D1%83%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9-%D0%B4%D0%B5%D1%81%D1%82%D1%80%D1%83%D0%BA%D1%82%D0%BE%D1%80-%D0%BF%D1%80%D0%B8-%D0%BD%D0%B0%D1%81%D0%BB%D0%B5%D0%B4%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B8 вот по этой ссылке тут взял
};

class Dog : public Animal {
public:
    void speak() const override {
        cout << "Гав-гав!" << endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        cout << "Мяу-мяу!" << endl;
    }
};

// 4 абстракция
class Shape {
public:
    virtual double area() const = 0; // можно вызывать area() через указатель на Shape, поэтому тут чисто виртуальная функция для класса Shape
    virtual ~Shape() = default; // виртуальный деструктор для задачи 5
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double area() const override {
        return width * height;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}
    double area() const override {
        return M_PI * radius * radius;
    }
};

// 5 полиформизм
void demonstrateShapes() {
    vector<Shape*> shapes;
    shapes.push_back(new Rectangle(5.0, 3.0));
    shapes.push_back(new Circle(2.0));

    for (const Shape* shape : shapes) {
        cout << "Площадь фигуры: " << shape->area() << endl;
    }

    // Очистка памяти
    for (Shape* shape : shapes) {
        delete shape;
    }
}

// 6 интерфейс
class Printable {
public:
    virtual void print() const = 0;
    virtual ~Printable() = default;
};

class Book : public Printable {
private:
    string title;

public:
    Book(const string& title) : title(title) {}
    void print() const override {
        cout << "Книга: " << title << endl;
    }
};

class Document : public Printable {
private:
    string name;

public:
    Document(const string& name) : name(name) {}
    void print() const override {
        cout << "Документ: " << name << endl;
    }
};

// 7 множ. наследрвание
class Logger {
public:
    virtual void log(const string& message) const {
        cout << "Лог: " << message << endl;
    }
    virtual ~Logger() = default;
};

class Serializable {
public:
    virtual string serialize() const {
        return "Сериализованные данные";
    }
    virtual ~Serializable() = default;
};

class User : public Logger, public Serializable {
private:
    string username;

public:
    User(const string& username) : username(username) {}
    void log(const string& message) const override {
        cout << "Пользователь " << username << ": " << message << endl;
    }
    string serialize() const override {
        return "Сериализованные данные пользователя: " + username;
    }
};

// 8 композиция
class Engine {
public:
    void start() {
        cout << "Двигатель запущен" << endl;
    }
};

class Car {
private:
    Engine engine;
    string model;

public:
    Car(const string& model) : model(model) {}
    void start() {
        cout << "Автомобиль " << model << ": ";
        engine.start();
    }
};

int main() {
    // тест 2
    cout << "\nЗадача 2: Наследование\n";
    Person person("Иван", 20);
    Student student("Анна", 22, "МГУ");
    person.display();
    student.display();

    // тест 3
    cout << "\nЗадача 3: Полиморфизм\n";
    Animal* dog = new Dog();
    Animal* cat = new Cat();
    dog->speak();
    cat->speak();
    delete dog;
    delete cat;

    // тест 4 и 5
    cout << "\nЗадача 4 и 5: Абстракция и полиморфизм\n";
    demonstrateShapes();

    // тест 6
    cout << "\nЗадача 6: Интерфейс\n";
    Printable* book = new Book("Война и мир");
    Printable* doc = new Document("Отчет.pdf");
    book->print();
    doc->print();
    delete book;
    delete doc;

    // тест 7
    cout << "\nЗадача 7: Множественное наследование\n";
    User user("Алексей");
    user.log("Вход в систему");
    cout << user.serialize() << endl;

    // тест 8
    cout << "\nЗадача 8: Композиция\n";
    Car car("Toyota");
    car.start();

    return 0;
}
