#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>


// определяет общие методы для работы с хранилищем объектов типа T
// методы помечены как виртуальные => класс наследник должен реализовать их
template <class T>
class IRepository {
public:
    virtual std::vector<T> GetAll() = 0;
    virtual void Add(const T& item) = 0;
    virtual void Remove(const T& item) = 0;
    virtual void Update(const T& item) = 0;
};


// объект пользователя
class User {
private:
    int id;
    std::string login;
    std::string password;
    std::string name;

public:
    // конструктор по умолчанию
    User() : id(0), login(""), password(""), name("") {}

    // конструктор с параметрами
    User(int id, const std::string& login, const std::string& password, const std::string& name)
        : id(id), login(login), password(password), name(name) {}

    // геттеры и сеттеры для всех полей класса
    int getId() const { return id; }
    void setId(int id) { this->id = id; }

    std::string getLogin() const { return login; }
    void setLogin(const std::string& login) { this->login = login; }

    std::string getPassword() const { return password; }
    void setPassword(const std::string& password) { this->password = password; }

    std::string getName() const { return name; }
    void setName(const std::string& name) { this->name = name; }

    // перегруженные операторы
    bool operator==(const User& other) const {
        return (id == other.id && login == other.login && password == other.password && name == other.name);
    }

    bool operator!=(const User& other) const {
        return !(*this == other);
    }
};


// шаблонный интерфейс наследует интерфейс IRepository и добавляет методы для работы с объектами
template <class T>
class IUserRepository : public IRepository<T> {
public:
    virtual T GetById(int id) = 0;
    virtual T GetByLogin(const std::string& login) = 0;
};

//абстрактный класс, определяющий методы для управления пользователями
class IUserManager {
public:
    virtual void SignIn(const User& user) = 0;
    virtual void SignOut(const User& user) = 0;
    virtual bool isAuthorized() const = 0;
};

// интерфейс для работы с объектами пользователей
template <class T>
class FileUserRepository : public IRepository<T> {
private:
    std::string filename = "users.txt";

private:
    std::vector<T> GetAll() override {
        std::vector<T> users;
        T user;
        std::ifstream file(filename); // открываем файл
        // последовательно читаем файл и создаем объекты и помещаем их в вектор 
        int id;
        std::string login, password, name;
        while (file >> id >> login >> password >> name) {
            user.setId(id);
            user.setLogin(login);
            user.setPassword(password);
            user.setName(name);
            users.push_back(user);
        }
        file.close();
        return users;
    }

    void Add(const T& user) override {
        std::ofstream file(filename, std::ios_base::app); // открываем файл
        file << user.getId() << " " << user.getLogin() << " " << user.getPassword() << " " << user.getName() << std::endl; // записываем переданный объект
        file.close();

        std::ofstream lastUserFile("last_user.txt");
        lastUserFile << user.getId() << " " << user.getLogin() << " " << user.getPassword() << " " << user.getName() << std::endl;
        lastUserFile.close();
    }

    void Remove(const T& user) override {
        std::vector<T> users = GetAll(); // получаем всех пользователей
        auto it = std::remove(users.begin(), users.end(), user); // удаляем пользователя из вектора
        users.erase(it, users.end());
        UpdateFileContent(users); // обновляем файл
    }

    void Update(const T& user) override {
        std::vector<T> users = GetAll(); // получаем всех пользователей
        // находим всех пользователей с указанным id в векторе
        // заменяет его на переданный объект пользователя
        for (T& u : users) {
            if (u.getId() == user.getId()) {
                u = user;
                break;
            }
        }
        UpdateFileContent(users); // обновление файла
    }

    User GetById(int id) {
        std::ifstream file(filename); // открываем файл
        User user;
        // последовательно читаем и ищем пользвателя с заданным id
        while (file >> user.id >> user.login >> user.password >> user.name) {
            if (user.id == id) {
                file.close();
                return user;
            }
        }
        file.close();
        // Если пользователь с указанным ID не найден, вернем пустого пользователя
        return User{};
    }

    User GetByLogin(const std::string& login) {
        std::ifstream file(filename); // открываем файл
        User user;
        // последовательно читаем и ищем пользователя с заданным логином
        while (file >> user.id >> user.login >> user.password >> user.name) {
            if (user.login == login) {
                file.close();
                return user;
            }
        }
        file.close();
        // Если пользователь с указанным логином не найден, вернем пустого пользователя
        return User{};
    }

private:
    void UpdateFileContent(const std::vector<T>& users) {
        std::ofstream file(filename); // открываем файл
        // записываем пользователей из переданного ветора в файл
        for (const T& user : users) {
            file << user.getId() << " " << user.getLogin() << " " << user.getPassword() << " " << user.getName() << std::endl;
        }
        file.close();
    }
};

class FileUserManager : public IUserManager {
private:
    std::string lastLoggedInUserFile = "last_logged_in_user.txt";
    std::string usersFile = "users.txt";
    User lastLoggedInUser;

public:
    void SignIn(const User& user) override {
        lastLoggedInUser = user; // сохраняем в качестве последнего вошедшего пользователя
        SaveLastLoggedInUserToFile(user); // сохраняем информацию о вошедшем пользователе
    }

    void SignOut(const User& user) override {
        // соответствует ли переданный пользоватеь последнему вошедшему
        if (lastLoggedInUser.getId() == user.getId()) {
            lastLoggedInUser = User{}; // Сбрасываем информацию о последнем вошедшем пользователе
            ClearLastLoggedInUserFile(); // очищаем файл с информацией о последнем вошедшем пользователе
        }
    }

    // проверяем авторизован ли какой-либо пользователь
    bool isAuthorized() const override {
        return !lastLoggedInUser.getName().empty();
    }

private:
    // сохраняем информацию о пользователе
    void SaveLastLoggedInUserToFile(const User& user) {
        std::ofstream file(lastLoggedInUserFile);
        file << user.getId() << " " << user.getLogin()<< " " << user.getPassword() << " " << user.getName()<< std::endl;
        file.close();
    }

    // очищает содержимое файла
    void ClearLastLoggedInUserFile() {
        std::ofstream file(lastLoggedInUserFile, std::ofstream::out | std::ofstream::trunc); // Очищаем содержимое файла
        file.close();
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // создание репозитория пользователей
    IRepository<User>* userRepository = new FileUserRepository<User>();

    // добавление пользователей
    User user1(1, "Пользователь1", "password1", "Катя");
    userRepository->Add(user1);

    User user2(2, "Пользователь2", "password2", "Саша");
    userRepository->Add(user2);

    // получение всех пользователей
    std::vector<User> allUsers = userRepository->GetAll();
    for (const auto& user : allUsers) {
        std::cout << "Пользователь: " << user.getName() << std::endl;
    }

    // удаление пользователя
    userRepository->Remove(user1);

    // обновление пользователя
    user2.setName("Александр");
    userRepository->Update(user2);

    delete userRepository;

    return 0;
}