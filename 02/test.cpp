#pragma once
#include "parser.hpp"
#include <fstream>
#include <iostream>

static bool begin_flag = false;
static bool end_flag = false;
static bool str_flag = false;
static bool num_flag = false;

// void my_begin();
// void my_end();
// void my_str(const char* str);
// void my_num(const int& Num);

void Test_2();  // Проверяет, верные ли токены отдаются в колбэки
void Test_1();  // Проверяет, действительно ли работает логика переопределения и вызова колбэков

int main()
{

    Test_1();
    Test_2();
    


    return 0;
}

void Test_1()
{
    
    auto b = [](){begin_flag = true;};
    auto e = [](){end_flag = true;};

    auto st = [](const char* str){str_flag = true;};
    auto num = [](const int& n){num_flag = true;};

    std::ifstream IN;
    IN.open("test_1.txt");

    Parser P;
    P.reg_call_back_begin(b);
    P.reg_call_back_end(e);
    P.reg_call_back_num(num);
    P.reg_call_back_str(st);

    P.parse(IN);

    bool res = begin_flag && end_flag && str_flag && num_flag;


    IN.close();

    if (res)
        std::cout << "Test 1 :: 1\n" ;
    else 
        std::cout << "Test 1 :: 0\n" ;



}

void Test_2()
{
    

}