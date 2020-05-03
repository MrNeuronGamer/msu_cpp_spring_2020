#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <exception> 
#include <iostream>


template<class T>
std::string to_str(T&& val)
{
	std::stringstream str;
	str << val;
	return str.str();
}

template<class... Args>
std::string format(const std::string& str,Args&&... args)
{
	std::string res, buf;
	std::vector<std::string> new_arg = { to_str(std::forward<Args>(args))... };
	size_t len = str.size();
	size_t arg_len = new_arg.size();

	bool is_open = false;
	bool is_closed = true;
	char c;

	for (size_t i = 0; i < len; i++)
	{
		c = str[i];
		if (is_closed)
		{
			if (c == '{')
			{
				is_open = true;
				is_closed = false;
				continue;
			}
			else if (c == '}')
			{
				throw std::runtime_error("Error specifying argument");
			}
			else
			{
				res += str[i];
				continue;
			}
		}
		else if(is_open)
		{
			if (std::isdigit(c))
			{
				buf += c;
				continue;
			}
			else if (c == '}')
			{
				if (buf.empty())
				{
					throw std::runtime_error("argument number not specified");
				}
				else if (atoi(buf.c_str()) >= arg_len || atoi(buf.c_str())<0)
				{
					throw std::runtime_error("argument not declared");
				}
				else
				{
					is_open = false;
					is_closed = true;
					res += new_arg[atoi(buf.c_str())];
					buf.clear();
					continue;
				}
			}
			else
			{
				throw std::runtime_error("error when calling argument");
			}

		}
		else
		{
			throw std::runtime_error("ERROR");
		}
	}
	if (is_open)
	{
		throw std::runtime_error("Error specifying argument");
	}
	return res;
}