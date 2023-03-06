/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** get_base
*/

#include "Database.hpp"
#include <cassert>
#include <string>
#include <iostream>
using namespace sqlite_orm;
using namespace babel;

//get<fields::id, std::string>(std::string& name)
int Database::get_id(std::string& name)
{
    auto result = storage.select(&User::id, where(c(&User::name) == name));

    if (!result.empty())
        return (result[0]);
    return (-1);
}

/*
//get<fields::name, int>
std::string Database::get_name(int& id)
{
    std::string result = storage.select(&User::name, where(c(&User::id) == id))[0];
    return result;
}

std::string Database::get_psw(int& id)
{
    std::string result = storage.select(&User::psw, where(c(&User::id) == id))[0];
    return result;
}

bool Database::get_status(int& id)
{
    bool result = storage.select(&User::status, where(c(&User::id) == id))[0];
    return result;
}

/*
std::vector<std::pair<int, std::string>> Database::get_histo(int id)
{
    std::vector<std::pair<int, std::string>> vector_result;
    std::string result = storage.select(&User::histo, where(c(&User::id) == id))[0];
    size_t pos = 0;
    size_t pos_2 = 0;
    std::string token;
    std::string token_2;
    std::pair<int, std::string> pair_save;

    while ((pos = result.find(";")) != std::string::npos) {
        token = result.substr(0, pos);
        result.erase(0, pos + 1);
        while ((pos_2 = token.find(":")) != std::string::npos) {
            token_2 = token.substr(0, pos_2);
            token.erase(0, pos_2 + 1);
        }
        pair_save = std::make_pair(std::stoi(token_2.c_str()), token);
        vector_result.push_back(pair_save);
    }
    token = result;
    while ((pos_2 = token.find(":")) != std::string::npos) {
        token_2 = token.substr(0, pos_2);
        token.erase(0, pos_2 + 1);
    }
    pair_save = std::make_pair(std::stoi(token_2.c_str()), token);
    vector_result.push_back(pair_save);
    return vector_result;
}


std::string Database::get_pp(int& id)
{
    std::string result = storage.select(&User::psw, where(c(&User::id) == id))[0];
    return result;
}
*/

std::string Database::get_all_name()
{
    auto all_name = storage.select(&User::name);
    std::stringstream sstr;

    for (int i = 0; auto& name : all_name) {
        std::cout << name << std::endl;
        sstr << name;
        if (i < all_name.size() - 1)
            sstr << ',';
        i += 1;
    }
    return (sstr.str());
}