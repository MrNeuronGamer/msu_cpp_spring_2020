#pragma once
#include <iostream>
#include "allocator.hpp"
using namespace std;

void Test_1()
{
    /*
        Данный тест проверит цикл процедур в цепочке : 
                makeAllocator -- > alloc  untill fail  --> clear -- alloc untill fail --> clear
                --> remake -- > alloc untill success
        
        takes                       : NONE
        prints to console std out   : "Test_1 : 1" if success  "Test_1 : 0"  if fail
    */

    makeAllocator(3);
    char* buffs[3];
    buffs[0] = alloc(2);
    buffs[1] = alloc(1);
    buffs[2] = alloc(1);

    *buffs[0] = 'a';
    *(buffs[0]+1) = 'b';
    *buffs[1] = 'c';


    bool flag = false;

    flag = buffs[2] == nullptr;
    flag = flag && (*buffs[0] == 'a');
    flag = flag && (*(buffs[0]+1) == 'b');
    flag = flag && (*buffs[1] == 'c');

    reset();
    
    buffs[0] = alloc(2);
    buffs[1] = alloc(1);
    buffs[2] = alloc(1);

    *buffs[0] = 'a';
    *(buffs[0]+1) = 'b';
    *buffs[1] = 'c';



    flag = flag && (buffs[2] == nullptr);
    flag = flag && (*buffs[0] == 'a');
    flag = flag && (*(buffs[0]+1) == 'b');
    flag = flag && (*buffs[1] == 'c');



    makeAllocator(4);

    buffs[0] = alloc(2);
    buffs[1] = alloc(1);
    buffs[2] = alloc(1);

    *buffs[0] = 'a';
    *(buffs[0]+1) = 'b';
    *buffs[1] = 'c';
    *buffs[2] = 'd';


    flag = *buffs[2] == 'd';
    flag = flag && (*buffs[0] == 'a');
    flag = flag && (*(buffs[0]+1) == 'b');
    flag = flag && (*buffs[1] == 'c');


    if (flag)
        cout << "Test_1 : 1" <<endl;
    else 
        cout << "Test_1 : 0" << endl;


}





int main()
{

    
    Test_1();

    return 0;
}
