#pragma once
#include "parser.hpp"
#include <fstream>
#include <iostream>

static bool begin_flag = false;
static bool end_flag = false;
static bool str_flag = false;
static bool num_flag = false;

void Test_2();  // Проверяет, верно ли опрделяется тип токена и верно ли они обрабатываются до передачи
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

    auto st = [](const std::string& str){str_flag = true;};
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

    begin_flag = false;
    end_flag = false;
    str_flag = false;
    num_flag = false;


}


void my_begin()
{
    begin_flag = true;
}
void my_end()
{
    end_flag = true;
}
void my_str(const std::string& str)
{
    static bool w1 = false;
    static bool w2 = false;

    if (!str.compare("Foo")) w1 = true;
    if (!str.compare("Bar")) w2 = true;

    if (w1 && w2) str_flag = true;

    
}
void my_num(const int& Num)
{
    
    static bool n1 = false;
    static bool n2 = false;
   

    if (Num == 1340) n1 = true;
    if (Num == 9324) n2 = true;

    if (n1 && n2) num_flag = true;

}






void Test_2()
{
    std::ifstream IN;
    IN.open("test_2.txt");

    Parser P;

    P.reg_call_back_begin(my_begin);
    P.reg_call_back_end(my_end);
    P.reg_call_back_num(my_num);
    P.reg_call_back_str(my_str);  



    P.parse(IN);

    bool res = begin_flag && end_flag && str_flag && num_flag;


    IN.close();

    if (res)
        std::cout << "Test 2 :: 1\n" ;
    else 
        std::cout << "Test 2 :: 0\n" ;


    begin_flag = false;
    end_flag = false;
    str_flag = false;
    num_flag = false;

}