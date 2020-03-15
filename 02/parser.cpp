#include "parser.hpp"
#include <string>
#include <iostream>


void Parser::parse(std::ifstream& IN)
{
    if (begin_handler)
        begin_handler();


        std::string line;
        std::string token;

        size_t sep_ind = 0;

        while(std::getline(IN, line))
        {
            
            while (line.length())
            {
                
                sep_ind = line.find_first_of(" \t\n",0);
                if (sep_ind == std::string::npos)
                    sep_ind = line.length()-1;
                if (sep_ind == 0 && sep_ind!= line.length()-1)
                    {
                        line = line.substr(line.find_first_not_of(" \n\t"), line.length()-1);
                        continue;
                    }
                if (sep_ind != line.length()-1)
                    sep_ind--;

                
                    token = line.substr(0,sep_ind+1);
                    std::cout << "Token is ::" << token << std::endl;
                    line = line.substr(sep_ind+1,line.length()-sep_ind-1);
                
                
                
                    if(std::string::npos != token.find_first_not_of("0123456789"))
                    {

                        const char* kk = token.c_str();
                        if(str_handler)
                            str_handler(kk);

                    }
                    else 
                    {
                        
                        int kk = atoi(token.c_str());
                        if(num_handler)
                            num_handler(kk);
                    }
                

                

            }
            
        }

    

    if(end_handler)
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
