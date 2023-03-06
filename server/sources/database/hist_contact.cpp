/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** hist_contact
*/

#include "Database.hpp"
#include <cassert>
using namespace sqlite_orm;
using namespace babel;

void Database::add_histo(int& id, int& id_add, std::string& date)
{
    std::string result = storage.select(&User::histo, where(c(&User::id) == id))[0];
    result.append(";"+std::to_string(id_add)+":"+date);
    storage.update_all(sqlite_orm::set(c(&User::histo) = result), where(c(&User::id) == id));
}

void Database::rm_all_histo(int& id)
{
    std::string result = storage.select(&User::histo, where(c(&User::id) == id))[0];
    result.clear();    
    storage.update_all(sqlite_orm::set(c(&User::histo) = result), where(c(&User::id) == id));
}

void Database::add_contact(int& id, int& id_add)
{
    std::string result = storage.select(&User::histo, where(c(&User::id) == id))[0];
    result.append(";"+std::to_string(id_add)+":"+Database::get<fields::name, int, std::string>(id_add));
    storage.update_all(sqlite_orm::set(c(&User::histo) = result), where(c(&User::id) == id));
}

void Database::rm_all_contact(int& id)
{
    std::string result = storage.select(&User::contact, where(c(&User::id) == id))[0];
    result.clear();    
    storage.update_all(sqlite_orm::set(c(&User::contact) = result), where(c(&User::id) == id));
}

void Database::rm_contact(int& id, int& id_suppr)
{
    std::string result = storage.select(&User::contact, where(c(&User::id) == id))[0];
    result.erase(result.find(std::to_string(id_suppr)), result.substr(result.find(std::to_string(id_suppr))).find(";")+1);
}