import abc

class NumericalIntegration(abc.ABC):
    def __init__(self, num_points, step, precision):
        self.num_points = num_points # число точек
        self.step = step # шаг
        self.precision = precision # точность

    @abc.abstractmethod
    def calc(self, func, lower_limit, upper_limit):
        pass

# метод трапеций
class TrapezoidalIntegration(NumericalIntegration):
    def calc(self, func, lower_limit, upper_limit):
        h = (upper_limit - lower_limit) / self.num_points # делим ообласть интегрирования на отрезки шиириной h
        result = 0.5 * (func(lower_limit) + func(upper_limit))
        # суммируем площади трапеций, образованных значениями функциии и шагом h
        for i in range(1, self.num_points):
            result += func(lower_limit + i * h)
        result *= h # окончательный результат - умножение суммы площадей трапеций на шаг h и деление на 2
        return result

# метод Симпсона
class SimpsonIntegration(NumericalIntegration):
    def calc(self, func, lower_limit, upper_limit):
        h = (upper_limit - lower_limit) / self.num_points # делим ообласть интегрирования на отрезки шиириной h
        # используем значения функции в концах каждого отрезка и в середине
        x = [lower_limit + i * h for i in range(self.num_points + 1)]
        # Площадь под кривой на каждом отрезке аппроксимируется квадратичной функцией, которая проходит через три
        # точки (два конца и середину).
        y = [func(val) for val in x]
        result = (h / 3) * (y[0] + y[-1] + 4 * sum(y[1:-1:2]) + 2 * sum(y[2:-1:2]))
        return result

# Пример использования
def test_function(x):
    return x**2 + 2*x + 1

analytical_result = 7.3333  # Результат аналитического вычисления интеграла

trapezoidal = TrapezoidalIntegration(num_points=100, step=0.01, precision=0.001)
trapezoidal_result = trapezoidal.calc(test_function, 1, 2)

simpson = SimpsonIntegration(num_points=100, step=0.01, precision=0.001)
simpson_result = simpson.calc(test_function, 1, 2)

print("Аналитический результат:", analytical_result)
print("Метод трапеций:", trapezoidal_result)
print("Метод Симпсона:", simpson_result)