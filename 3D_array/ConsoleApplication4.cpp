#include <iostream>
#include <vector>
#include <locale.h>

class Array3d {
private:
    std::vector<int> data; // хранит данные трехмерного массива в одномерном векторе
    int dim0, dim1, dim2; // размерности трехмерного массива

public:
    //конструктор
    Array3d(int dim0, int dim1, int dim2) : dim0(dim0), dim1(dim1), dim2(dim2) {
        data.resize(dim0 * dim1 * dim2); // изменение размера вектора для хранения трехмерного массива
    }

    // перегруженный оператор позволяет получать доступ к элементам по координатам
    int& operator()(int i, int j, int k) {
        return data[i * dim1 * dim2 + j * dim2 + k];
    }

    std::vector<int> GetValues0(int i) {
        std::vector<int> values;
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues1(int j) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues2(int k) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
            }
        }
        return values;
    }

    std::vector<int> GetValues01(int i, int j) {
        std::vector<int> values;
        for (int k = 0; k < dim2; ++k) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    std::vector<int> GetValues02(int i, int k) {
        std::vector<int> values;
        for (int j = 0; j < dim1; ++j) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    std::vector<int> GetValues12(int j, int k) {
        std::vector<int> values;
        for (int i = 0; i < dim0; ++i) {
            values.push_back(data[i * dim1 * dim2 + j * dim2 + k]);
        }
        return values;
    }

    void SetValues0(int i, std::vector<int> newValues) {
        for (int j = 0; j < dim1; ++j) {
            for (int k = 0; k < dim2; ++k) {
                data[i * dim1 * dim2 + j * dim2 + k] = newValues[j * dim2 + k];
            }
        }
    }

    void SetValues1(int j, std::vector<int> newValues) {
        for (int i = 0; i < dim0; ++i) {
            for (int k = 0; k < dim2; ++k) {
                data[i * dim1 * dim2 + j * dim2 + k] = newValues[i * dim2 + k];
            }
        }
    }

    void SetValues2(int k, std::vector<int> newValues) {
        for (int i = 0; i < dim0; ++i) {
            for (int j = 0; j < dim1; ++j) {
                data[i * dim1 * dim2 + j * dim2 + k] = newValues[i * dim1 + j];
            }
        }
    }

    void SetValues01(int i, int j, std::vector<int> newValues) {
        for (int k = 0; k < dim2; ++k) {
            data[i * dim1 * dim2 + j * dim2 + k] = newValues[k];
        }
    }

    void SetValues02(int i, int k, std::vector<int> newValues) {
        for (int j = 0; j < dim1; ++j) {
            data[i * dim1 * dim2 + j * dim2 + k] = newValues[j];
        }
    }

    void SetValues12(int j, int k, std::vector<int> newValues) {
        for (int i = 0; i < dim0; ++i) {
            data[i * dim1 * dim2 + j * dim2 + k] = newValues[i];
        }
    }

    static Array3d ones(int dim0, int dim1, int dim2) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = 1;
        }
        return array;
    }

    static Array3d zeros(int dim0, int dim1, int dim2) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = 0;
        }
        return array;
    }

    static Array3d fill(int dim0, int dim1, int dim2, int value) {
        Array3d array(dim0, dim1, dim2);
        for (int i = 0; i < dim0 * dim1 * dim2; ++i) {
            array.data[i] = value;
        }
        return array;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // Создаем экземпляр класса Array3d
    Array3d arr(3, 3, 3);

    // Устанавливаем значение элемента массива по трехмерным координатам
    arr(1, 1, 1) = 5;
    std::cout << "Значение в (1, 1, 1): " << arr(1, 1, 1) << std::endl;

    // Получаем срез массива по второй координате
    auto values1 = arr.GetValues1(1);
    std::cout << "Значения для j=1: ";
    for (int val : values1) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Получаем срез массива по первой и второй координатам
    auto values01 = arr.GetValues01(1, 1);
    std::cout << "Значения для i=1, j=1: ";
    for (int val : values01) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Устанавливаем новые значения для среза массива по первой и второй координате
    arr.SetValues01(1, 1, { 10, 11, 12 });
    auto updatedValues01 = arr.GetValues01(1, 1);
    std::cout << "Изменены значения для i=1, j=1: ";
    for (int val : updatedValues01) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // Создаем массивы с одинаковыми элементами
    auto onesArr = Array3d::ones(2, 2, 2);
    auto zerosArr = Array3d::zeros(2, 2, 2);
    auto fillArr = Array3d::fill(2, 2, 2, 5);

    // Вывод значений массивов в консоль
    std::cout << "Массив единиц:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << onesArr(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Массив нулей:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << zerosArr(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Заполненный массив с 5:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                std::cout << fillArr(i, j, k) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}