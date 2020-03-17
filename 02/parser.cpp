#include "parser.hpp"
#include <iostream>

void Parser::token_proc(const std::string &token)
{

    if (std::string::npos != token.find_first_not_of("0123456789"))
    {

        const char *kk = token.c_str();
        if (str_handler)
            str_handler(kk);
    }
    else
    {
        int kk = atoi(token.c_str());
        if (num_handler)
            num_handler(kk);
    }
}

void Parser::parse(std::ifstream &IN)
{
    if (begin_handler)
        begin_handler();
    need_init_flag = false;

    std::string line;

    while (std::getline(IN, line))
    {

        this->parse(line);
    }

    if (end_handler)
        end_handler();
    need_init_flag = true;
}

void Parser::parse(const std::string &line)
{
    if (begin_handler && need_init_flag)
        begin_handler();

    std::string token;
    token.clear();
    size_t curr_ind = 0;
    std::string separators = (" \t\n");

    while (curr_ind != line.size())
    {

        if (separators.find(line[curr_ind]) != std::string::npos)
        {
            if (token.size())
            {
                token_proc(token);

                token.clear();
            }
        }
        else
        {
            token.push_back(line[curr_ind]);
        }

        curr_ind++;
    }

    if (token.size())
    {
        token_proc(token);
    }

    if (end_handler && need_init_flag)
        end_handler();
}

void Parser::reg_call_back_begin(on_begin handler)
{
    begin_handler = handler;
}

void Parser::reg_call_back_end(on_end handler)
{

    end_handler = handler;
}
void Parser::reg_call_back_num(on_num handler)
{
    num_handler = handler;
}
void Parser::reg_call_back_str(on_str handler)
{
    str_handler = handler;
}
