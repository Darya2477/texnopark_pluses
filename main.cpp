// В домашнем задании необходимо написать код программы, выполняющую определенную задачу в зависимости от варианта
// Вариант #2
// Необходимо написать программу, реализующую функционал калькулятора с использованием ООП.
// Необходимо реализовать поддержку операций +, - и скобок ( ).
// Для реализации вычислений утверждается следующий интерфейс ICalculatable.
// Наследник ICalculatable обязан реализовать метод double Calculate();
// Каждая операция наследуется от интерфейса ICalculatable, бинарные операции могут принимать два ICalculatable, а унарные один ICalculatable.
// Число тоже ICalculatable.
// Программа должна парсить выражение, переданное в аргументах командной строки и строить древовидную структуру из наследников ICalculatable.
// Выражение можно парсить предельно строго ( например, недопускаются лишние пробелы или их отсутствие )
// Результат вычисления получается вызовом метода Calculate у корневой вершины структуры.
// Пример (при вводе в терминале выражение с пробелами нужно обернуть, например, в одинарные кавычки)
// ./calculator '23 + 7 - ( 10 + 12 )'
// 8

// Внутри программы представляется как:
// -
// / //\//
// + +
// / \ / //\//
// 23 7 10 12

// Ваш вариант:
// Добавьте к вашей реализации операции /, cos, tan (есть в <cmath>)

#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
#include <cctype>
#include <typeinfo>
#include <sstream>

struct Sign
{
    unsigned int index;
    unsigned int priority;
    char sign;
    Sign(unsigned int _index, unsigned int _priority, char _sign)
    {
        index = _index;
        priority = _priority;
        sign = _sign;
    }
};

class ICalculatable
{
public:
    virtual double Calculate() = 0;
    virtual void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value) = 0;
    virtual ~ICalculatable() {}
};

class Number : public ICalculatable
{
private:
    double value;

public:
    Number(double _value)
    {
        value = _value;
    }
    double Calculate() override
    {
        return value;
    }
    void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value) override{};
};

class Plus : public ICalculatable
{
private:
    std::unique_ptr<ICalculatable> first_value;
    std::unique_ptr<ICalculatable> second_value;

public:
    Plus()
    {
        first_value = nullptr;
        second_value = nullptr;
    }
    void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value) override
    {
        first_value = std::move(_first_value);
        second_value = std::move(_second_value);
    }
    double Calculate() override
    {
        return (first_value->Calculate() + second_value->Calculate());
    }
    ~Plus(){};
};

class Minus : public ICalculatable
{
private:
    std::unique_ptr<ICalculatable> first_value;
    std::unique_ptr<ICalculatable> second_value;

public:
    Minus()
    {
        first_value = nullptr;
        second_value = nullptr;
    }
    void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value)
    {
        first_value = std::move(_first_value);
        second_value = std::move(_second_value);
    }

    double Calculate() override
    {
        return (first_value->Calculate() - second_value->Calculate());
    }
    ~Minus() {}
};

class Multiply : public ICalculatable
{
private:
    std::unique_ptr<ICalculatable> first_value;
    std::unique_ptr<ICalculatable> second_value;

public:
    Multiply()
    {
        first_value = nullptr;
        second_value = nullptr;
    }
    void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value)
    {
        first_value = std::move(_first_value);
        second_value = std::move(_second_value);
    }

    double Calculate() override
    {
        return (first_value->Calculate() * second_value->Calculate());
    }
    ~Multiply() {}
};

class Devide : public ICalculatable
{
private:
    std::unique_ptr<ICalculatable> first_value;
    std::unique_ptr<ICalculatable> second_value;

public:
    Devide()
    {
        first_value = nullptr;
        second_value = nullptr;
    }
    void SetValues(std::unique_ptr<ICalculatable> &&_first_value, std::unique_ptr<ICalculatable> &&_second_value)
    {
        first_value = std::move(_first_value);
        second_value = std::move(_second_value);
    }

    double Calculate() override
    {
        return (first_value->Calculate() / second_value->Calculate());
    }
    ~Devide() {}
};

template <class T>
class BinaryStruct
{
private:
    std::string stroka;
    std::string left_stroka;
    std::string right_stroka;
    std::string current_string;
    std::vector<std::string> result;

    struct Element
    {
        std::unique_ptr<T> elem;
        Element *right;
        Element *left;
        Element(std::unique_ptr<T> _elem)
        {
            elem = std::move(_elem);
            right = nullptr;
            left = nullptr;
        }
        ~Element()
        {
            delete right;
            delete left;
        }
    };

    Element *root;

    std::vector<Sign> FindSigns(std::string str)
    {
        std::vector<Sign> sign_position;
        for (unsigned int i = str.length() - 1; i > 0; --i)
        {
            char c = str[i];
            if ((c == '*') || (c == '/'))
            {
                sign_position.push_back({i, 2, str[i]});
            }
        }

        for (unsigned int i = str.length() - 1; i > 0; --i)
        {
            char c = str[i];
            if ((c == '+') || (c == '-'))
            {
                sign_position.push_back({i, 1, str[i]});
            }
        }

        if (sign_position.size() != 1)
        {
            for (unsigned int i = 0; i < sign_position.size(); ++i)
            {
                for (unsigned int j = 0; j < sign_position.size() - 1; ++j)
                {
                    if ((sign_position[j]).priority > (sign_position[j + 1]).priority)
                        std::swap(sign_position[j], sign_position[j + 1]);
                }
            }
        }
        return sign_position;
    }

    bool isNumber(const std::string &str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (i != 0)
            {
                if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') || (str[i] == '/'))
                    return false;
            }
        }
        return true;
    }

    void Build(std::string stroka)
    {
        std::vector<Sign> sign_position = FindSigns(stroka);
        current_string = stroka[(sign_position[0]).index];
        result.push_back(current_string);
        left_stroka = stroka.substr(0, sign_position[0].index);
        result.push_back(left_stroka);
        right_stroka = stroka.substr(sign_position[0].index + 1, stroka.length() - 1);
        result.push_back(right_stroka);
        if ((!isNumber(left_stroka)))
            Build(left_stroka);
        if ((!isNumber(right_stroka)))
            Build(right_stroka);
    }

    void Print()
    {
        std::vector<std::string> tmp;
        unsigned int count = 0;
        while (count < result.size())
        {
            if (!isNumber(result[count]))
            {
                tmp.assign(result.begin() + count + count + 1, result.begin() + count + count + 4);
                result.erase(result.begin() + count);
                result.erase(result.begin() + count + count, result.begin() + count + count + 3);
                result.insert(result.begin() + count, tmp.begin(), tmp.end());
            }
            count++;
        }
    }

    Element *BuildTree(std::vector<std::string> mass, int begin, int end)
    {
        if (begin > end)
        {
            return nullptr;
        }
        std::unique_ptr<T> elem;
        if (mass[begin] == "+")
        {
            elem = std::make_unique<Plus>();
        }
        else if (mass[begin] == "-")
        {
            elem = std::make_unique<Minus>();
        }
        else if (mass[begin] == "*")
        {
            elem = std::make_unique<Multiply>();
        }
        else if (mass[begin] == "/")
        {
            elem = std::make_unique<Devide>();
        }
        else
        {
            elem = std::make_unique<Number>(std::stoi(mass[begin]));
        }
        Element *node = new Element(std::move(elem));
        if (begin == end)
            return node;
        begin = begin + 1;
        end = end - 1;
        node->left = BuildTree(mass, begin, end);
        node->right = BuildTree(mass, end + 1, end + 1);
        node->elem->SetValues(std::move(node->left->elem), std::move(node->right->elem));
        return node;
    }
    void Count()
    {
        root = BuildTree(result, 0, result.size() - 1);

        std::cout << "Result value: " << root->elem->Calculate() << std::endl;
    }

public:
    BinaryStruct(std::string _stroka)
    {
        root = nullptr;
        stroka = _stroka;
        Build(stroka);
        Print();
        Count();
    }
    ~BinaryStruct()
    {
        delete root;
    }
};

int main(int argc, char *argv[])
{
    BinaryStruct<ICalculatable> bin(argv[1]);
    return 0;
}
