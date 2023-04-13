# Программирование на современном C++ 

ФИО: Архипова Дарья Витальевна

Группа: ML-11

Ментор: Пешков Дмитрий

Преподаватель: Илья Крамичев

# task2

Вариант #2
Необходимо написать программу, реализующую функционал калькулятора с использованием ООП.
Необходимо реализовать поддержку операций +, - и скобок ( ).
Для реализации вычислений утверждается следующий интерфейс ICalculatable.
Наследник ICalculatable обязан реализовать метод double Calculate();
Каждая операция наследуется от интерфейса ICalculatable, бинарные операции могут принимать два ICalculatable, а унарные один ICalculatable.
Число тоже ICalculatable.
Программа должна парсить выражение, переданное в аргументах командной строки и строить древовидную структуру из наследников ICalculatable.
Выражение можно парсить предельно строго ( например, недопускаются лишние пробелы или их отсутствие )
Результат вычисления получается вызовом метода Calculate у корневой вершины структуры.
Пример (при вводе в терминале выражение с пробелами нужно обернуть, например, в одинарные кавычки)
./calculator '23 + 7 - ( 10 + 12 )'

Внутри программы представляется как:

/\
+ +
/\ /\
23 7 10 12

Ваш вариант:
Добавьте к вашей реализации операции /, cos, tan     (есть в <cmath>)

