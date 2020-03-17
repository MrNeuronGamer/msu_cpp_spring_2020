#include <fstream>
#include <string>




class Parser
{

    using on_num    = void(*)(int Num);
    using on_str    = void(*)(const std::string& str);
    using on_begin  = void(*)();
    using on_end    = void(*)();



public:
    void parse(std::ifstream& IN);   //Из потока IN считывает данные для парсинга считывает пока get_line != false
    void parse(std::string str);
    void reg_call_back_begin(on_begin handler);
    void reg_call_back_end(on_end handler);
    void reg_call_back_num(on_num handler);
    void reg_call_back_str(on_str handler);

private:
    on_num num_handler      = nullptr;
    on_str str_handler      = nullptr;
    on_begin begin_handler  = nullptr;
    on_end end_handler      = nullptr;

};