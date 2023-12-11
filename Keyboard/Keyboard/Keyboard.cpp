#include <iostream>
#include <unordered_map>
#include <stack>
#include <chrono>
#include <thread>

// Структура для хранения действия клавиши
struct Action {
    std::string name;
};

// Виртуальная клавиатура
class VirtualKeyboard {
private:
    std::unordered_map<char, Action> keyActions; // Соответствия клавиш и действий
    std::stack<std::unordered_map<char, Action>> undoStack; // Стек для отката действий

public:
    // привязывает действие к клавише
    void BindKey(char key, const Action& action) {
        keyActions[key] = action;
    }

    // удаляет привязку действия от клавиши
    void UnbindKey(char key) {
        keyActions.erase(key);
    }

    // выполняет действие, соответствующее нажатой клавише
    void PerformAction(char key) {
        if (keyActions.count(key) > 0) {
            Action action = keyActions[key];
            // Выполнение действия
            std::cout << "Выполнилось действие: " << action.name << std::endl;
        }
    }

    // откатывает последнее выполненное действие
    void UndoLastAction() {
        if (!undoStack.empty()) {
            keyActions = undoStack.top();
            undoStack.pop();
            std::cout << "Вернулось последнее действие" << std::endl;
        }
    }

    // сохраняет текущее состояние клавиатуры в стеке для последующего отката
    void SaveState() {
        undoStack.push(keyActions);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    VirtualKeyboard keyboard;

    Action action1{ "Действие 1" };
    Action action2{ "Действие 2" };
    keyboard.BindKey('A', action1);
    keyboard.BindKey('B', action2);


    keyboard.PerformAction('A');
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    keyboard.PerformAction('B');

    keyboard.SaveState();
    keyboard.UnbindKey('B');
    keyboard.PerformAction('B'); // Ничего не произойдет
    keyboard.UndoLastAction();
    keyboard.PerformAction('B'); // Выполнится действие "Action 2" снова

    // Пример переназначения клавиши с перезапуском WorkFlow
    Action action3{ "Action 3" };
    keyboard.BindKey('C', action3);
    keyboard.SaveState();
    keyboard.UnbindKey('C');

    keyboard.PerformAction('C'); // Ничего не произойдет
    keyboard.UndoLastAction();
    keyboard.PerformAction('C'); // Выполнится действие "Action 3" снова

    return 0;
}
