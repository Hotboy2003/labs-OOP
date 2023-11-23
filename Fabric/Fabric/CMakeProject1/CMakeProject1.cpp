#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

// Абстрактный класс Control (базовый)
class Control {
public:
    // расположение контролла
    virtual void setPosition(int x, int y) = 0;
    // получение расположения контролла
    virtual std::pair<int, int> getPosition() = 0;
    virtual ~Control() {}
};

// Подклассы контролов
// наследуются от Control и переопределяют его виртуальные методы
class Form : public Control {
public:
    void addControl(Control* control) {
        std::cout << "В форму добавлен control" << std::endl;
    }

    // Реализация виртуальных методов
    void setPosition(int x, int y) override {
        std::cout << "Вызвался setPosition" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Вызвался getPosition" << std::endl;
        return { 0, 0 };
    }
};

class Label : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "Label текст установлен: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "Вызвался Label getText" << std::endl;
        return "Sample text";
    }

    void setPosition(int x, int y) override {
        std::cout << "Вызвался Label setPosition" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Вызвался Label getPosition" << std::endl;
        return { 0, 0 };
    }
};

class TextBox : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "TextBox текст установлен: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "Вызвался TextBox getText" << std::endl;
        return "Sample text";
    }

    void OnValueChanged() {
        std::cout << "Значение TextBox изменилось" << std::endl;
    }

    // Реализация виртуальных методов
    void setPosition(int x, int y) override {
        std::cout << "Вызвался TextBox setPosition" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Вызвался TextBox getPosition" << std::endl;
        return { 0, 0 };
    }
};

class ComboBox : public Control {
public:
    void setItems(const std::vector<std::string>& items) {
        std::cout << "Элементы ComboBox установлены: " << std::endl;
    }

    void setSelectedIndex(int index) {
        std::cout << "Выбранный индекс в ComboBox selected установлен" << index << std::endl;
    }

    int getSelectedIndex() {
        std::cout << "ComboBox возвращает выбранный индекс" << std::endl;
        return 0;
    }

    std::vector<std::string> getItems() {
        std::cout << "Вызвался ComboBox get items" << std::endl;
        return { "Item 1", "Item 2" };
    }

    void setPosition(int x, int y) override {
        std::cout << "Вызвался ComboBox setPosition" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Вызвался ComboBox getPosition" << std::endl;
        return { 0, 0 };
    }
};

class Button : public Control {
public:
    void setText(const std::string& text) {
        std::cout << "Установлен текст Button: " << text << std::endl;
    }

    std::string getText() {
        std::cout << "Вызвался Button getText" << std::endl;
        return "Sample text";
    }

    void Click() {
        std::cout << "Button нажалась" << std::endl;
    }

    void setPosition(int x, int y) override {
        std::cout << "Вызвался Button setPosition" << std::endl;
    }

    std::pair<int, int> getPosition() override {
        std::cout << "Вызвался Button getPosition" << std::endl;
        return { 0, 0 };
    }
};

// Абстрактная фабрика
// определили методы для создания каждого типа контроллера
class AbstractFactory {
public:
    virtual Form* createForm() = 0;
    virtual Label* createLabel() = 0;
    virtual TextBox* createTextBox() = 0;
    virtual ComboBox* createComboBox() = 0;
    virtual Button* createButton() = 0;
    virtual ~AbstractFactory() {}
};

// Подклассы фабрик для каждой операционной системы
class WindowsFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class LinuxFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

class MacOSFactory : public AbstractFactory {
public:
    Form* createForm() override {
        return new Form();
    }

    Label* createLabel() override {
        return new Label();
    }

    TextBox* createTextBox() override {
        return new TextBox();
    }

    ComboBox* createComboBox() override {
        return new ComboBox();
    }

    Button* createButton() override {
        return new Button();
    }
};

// использует абстрактную фабрику для создания контроллов и вызова их методов
class Client {
public:
    // создаем экземпляры всех типов контроллов
    void run(AbstractFactory* factory) {
        Form* form = factory->createForm();
        Label* label = factory->createLabel();
        TextBox* textBox = factory->createTextBox();
        ComboBox* comboBox = factory->createComboBox();
        Button* button = factory->createButton();

        // добавляем их на форму
        form->addControl(label);
        form->addControl(textBox);
        form->addControl(comboBox);
        form->addControl(button);

        // устанавливаем свойства
        label->setText("Hello, world!");
        label->setPosition(10, 10);

        textBox->setText("Sample text");
        textBox->setPosition(20, 20);

        comboBox->setItems({ "Item 1", "Item 2" });
        comboBox->setPosition(30, 30);

        button->setText("Click me!");
        button->setPosition(40, 40);

        // Удаление контролов
        delete form;
        delete label;
        delete textBox;
        delete comboBox;
        delete button;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Определяем текущую операционную систему
    #ifdef _WIN32
        WindowsFactory factory;
    #elif __linux__
        LinuxFactory factory;
    #elif __APPLE__
        MacOSFactory factory;
    #else
        std::cerr << "Unsupported operating system" << std::endl;
        return 1;
    #endif

    // запускаем контроллы, используя соответствующую фабрику
    Client client;
    client.run(&factory);

    return 0;
}