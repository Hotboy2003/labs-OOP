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
public:
    int id;
    std::string login;
    std::string password;
    std::string name;

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

public:
    std::vector<T> GetAll() override {
        std::vector<T> users;
        T user;
        std::ifstream file(filename); // открываем файл
        // последовательно читаем файл и создаем объекты и помещаем их в вектор 
        while (file >> user.id >> user.login >> user.password >> user.name) {
            users.push_back(user); 
        }
        file.close();
        return users;
    }

    void Add(const T& user) override {
        std::ofstream file(filename, std::ios_base::app); // открываем файл
        file << user.id << " " << user.login << " " << user.password << " " << user.name << std::endl; // записываем переданный объект
        file.close();
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
            if (u.id == user.id) {
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
            file << user.id << " " << user.login << " " << user.password << " " << user.name << std::endl;
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
        if (lastLoggedInUser.id == user.id) {
            lastLoggedInUser = User{}; // Сбрасываем информацию о последнем вошедшем пользователе
            ClearLastLoggedInUserFile(); // очищаем файл с информацией о последнем вошедшем пользователе
        }
    }

    // проверяем авторизован ли какой-либо пользователь
    bool isAuthorized() const override {
        return !lastLoggedInUser.name.empty();
    }

private:
    // сохраняем информацию о пользователе
    void SaveLastLoggedInUserToFile(const User& user) {
        std::ofstream file(lastLoggedInUserFile);
        file << user.id << " " << user.login << " " << user.password << " " << user.name << std::endl;
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
    FileUserRepository<User> userRepository;
    FileUserManager userManager;

    // Регистрация нового пользователя
    User user1 = { 1, "user1", "password1", "Саша" };
    userRepository.Add(user1);

    // Получение всех пользователей
    std::vector<User> allUsers = userRepository.GetAll();
    for (const User& user : allUsers) {
        std::cout << "ID: " << user.id << ", Имя: " << user.name << ", Логин: " << user.login << std::endl;
    }

    // Авторизация пользователя
    userManager.SignIn(user1);
    if (userManager.isAuthorized()) {
        std::cout << "Пользователь " << user1.name << " авторизован." << std::endl;
    }

    // Изменение информации о пользователе
    user1.name = "Александр";
    userRepository.Update(user1);

    // Получение пользователя по ID
    User retrievedUser = userRepository.GetById(1);
    if (retrievedUser.id != 0) {
        std::cout << "Полученный Пользователь - ID: " << retrievedUser.id << ", Имя: " << retrievedUser.name << ", Логин: " << retrievedUser.login << std::endl;
    }

    // Удаление пользователя
    // userRepository.Remove(retrievedUser);

    // Попытка получения удаленного пользователя
    User deletedUser = userRepository.GetById(1);
    if (deletedUser.id == 0) {
        std::cout << "Пользователь с ID 1 удален" << std::endl;
    }

    // Выход пользователя из аккаунта
    userManager.SignOut(user1);
    if (!userManager.isAuthorized()) {
        std::cout << "Пользователь " << user1.name << " вышел." << std::endl;
    }

    return 0;
}