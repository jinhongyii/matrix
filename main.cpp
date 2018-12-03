#include <iostream>
#include <vector>
#include "matrix-blank.hpp"

using namespace sjtu;
std::pair<bool, std::string> RE(const std::string &name)
{
    return std::make_pair(false, "Runtime Error! (" + name + ")");
};

std::pair<bool, std::string> WA(const std::string &name)
{
    return std::make_pair(false, "wrong answer! (" + name + ")");
};
std::pair<bool, std::string> testOperations()
{
    std::initializer_list<std::initializer_list<int>> intIl= {{ 0, 1, 2, 3 },
                                                              { 1, 2, 3, 4 },
                                                              { 2, 3, 4, 5 }};
    Matrix<int> a = intIl;

    auto iterCheck = [&](std::function<bool(std::size_t, std::size_t)> condition)
    {
        for (std::size_t i = 0; i < 3; ++i)
            for (std::size_t j = 0; j < 4; ++j)
                if (!condition(i, j))
                    return false;
        return true;
    };

    a = a = a = a = a;
    // tran
    try
    {
        Matrix<int> stdt(4, 3);
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 4; ++j)
                stdt((std::size_t) j, (std::size_t) i) = i + j;
        if (a.tran() != stdt)
            return WA("tran");
    } catch (...)
    {
        return RE("tran");
    }

    // ==, !=
    try
    {
        Matrix<long> l(a);
        if (a != l)
            return WA("!=");
        l.resize(1, 1);
        if (a == l)
            return WA("==");
    } catch (...)
    {
        return RE("==/!=");
    }

    // -, *=
    try
    {
        auto b = a;
        b *= 2;
        if (!iterCheck([&](std::size_t i, std::size_t j)
                       {
                           return b(i, j) == 2 * a(i, j);
                       }))
            return WA("*=");
        b = -b;
        if (!iterCheck([&](std::size_t i, std::size_t j)
                       {
                           return b(i, j) == -2 * a(i, j);
                       }))
            return WA("-");
    } catch (...)
    {
        return RE("- / *=");
    }

    bool thrown = false;
    // +=, -=
    try
    {
        auto b = a;
        b += a;
        if (b != 2 * a)
            return WA("+=");
        b -= a;
        if (b != a)
            return WA("-=");
        Matrix<int> c(1, 2);
        b += c;
    } catch (const std::invalid_argument &msg)
    {
        thrown = true;
    } catch (...)
    {
        return RE("+= / -=");
    }
    if (!thrown)
        return WA("+=");

    // +, -, *
    thrown = false;
    try
    {
        Matrix<double> b(a);
        auto c = a + b;
        if (typeid(c(0, 0)) != typeid(b(0, 0)))
            return WA("+");
        Matrix<int> d = a + a;
        if (d != 2 * a)
            return WA("+");
        d = d - a;
        if (d != a)
            return WA("-");
        auto e = 2.0 * a;
        if (typeid(e(0, 0)) != typeid(2.0))
            return WA("scalar multiplication");
        auto f = b * a.tran();
        if (typeid(f(0, 0)) != typeid(b(0, 0)))
            return WA("*");
    } catch (...)
    {
        return RE("+ / - / *");
    }
    try
    {
        Matrix<int> b(1, 1);
        auto c = a * b;
    } catch (const std::invalid_argument &msg)
    {
        thrown = true;
    } catch (...)
    {
        return RE("+ / - / *");
    }
    if (!thrown)
        return WA("*");

    return { true, "Congratulation!" };
};
int main() {
    testOperations();
}