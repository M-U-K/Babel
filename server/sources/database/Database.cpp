/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** database
*/

#include "Database.hpp"
#include <cassert>
using namespace sqlite_orm;
using namespace babel;

Database::Database()
{
    storage.sync_schema();
}

Database::~Database()
{

}

std::string Database::create_user(std::string& name)
{
    
    Database::User user{
        name,
    };
    auto all_name = storage.select(&User::name);
    if (user.name.empty())
        return("Name is already used");
    std::cout << all_name.size() << std::endl;

    for (int i = 0; i != all_name.size(); i ++) {
        if (user.name.compare(all_name[i]) == 0)
            return ("Name is already used");
    }    
    storage.insert(user);
    return ("User create");
}

void Database::dump_storage()
{
    auto allUsers = storage.get_all<User>();
    std::cout << "allUsers (" << allUsers.size() << "):" << std::endl;
    for(auto &user : allUsers)
        std::cout << storage.dump(user) << std::endl; 
}