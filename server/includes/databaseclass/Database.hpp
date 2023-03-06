/*
** EPITECH PROJECT, 2021
** Delivery
** File description:
** database
*/

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <sqlite_orm/sqlite_orm.h>
#include <iostream>
#include <ostream>
#include <cstddef>
#include <variant>
#include <stdexcept>
#include <string>

using namespace sqlite_orm;


enum class fields
{
    name,
    pp,
    psw,
    status,
    ip,
    contact,
    histo,
    id
};

namespace babel
{
    class Database
    {
    public:
        using var_t = std::variant<std::string, int, bool>;
        struct User {
            std::string name;
            std::string ip;
            std::string contact;
            std::string psw;
            bool status;
            std::string histo;
            std::string pp;
            int id;
        };
    private:
        using yolo = decltype(make_storage("db.storage",
            make_table("users",
                make_column("name", &Database::User::name),
                make_column("ip", &Database::User::ip),
                make_column("contact", &Database::User::contact),
                make_column("psw", &Database::User::psw),
                make_column("status", &Database::User::status),
                make_column("histo", &Database::User::histo),
                make_column("pp", &Database::User::pp),
                make_column("id", &Database::User::id, primary_key()))));
    public:
            Database();
            ~Database();
            std::string create_user(std::string& name);
            void rem_user(int& id);
            void dump_storage();

            template<fields _User_field_policy = fields::id, typename T>
            requires (_User_field_policy < fields::ip)
                constexpr void set(int const& id, T const var)
            {
                if constexpr (_User_field_policy == fields::name)
                    storage.update_all(set(c(&User::name) = var), where(c(&User::id) == id));
                else if constexpr (_User_field_policy == fields::psw)
                    storage.update_all(set(c(&User::psw) = var), where(c(&User::id) == id));
                else if constexpr (_User_field_policy == fields::status)
                    storage.update_all(set(c(&User::status) = var), where(c(&User::id) == id));
                else if constexpr (_User_field_policy == fields::pp)
                    storage.update_all(set(c(&User::pp) = var), where(c(&User::id) == id));
                else
                    throw std::invalid_argument("bad token");
            }

            template<fields _User_field_policy = fields::id, typename T, typename A>
                requires (_User_field_policy != fields::contact || _User_field_policy != fields::histo)
                    constexpr A get(T const var)
                {
                    if constexpr (_User_field_policy == fields::id) {
                        auto result = storage.select(&User::id, where(c(&User::name) == var));
                        if (!result.empty())
                            return result[0];
                        return -1;
                    }
                    else if constexpr (_User_field_policy == fields::name) {
                        auto result = storage.select(&User::name, where(c(&User::name) == var));
                        if (!result.empty())
                            return result[0];
                        return nullptr;
                    }
                    else if constexpr (_User_field_policy == fields::psw) {
                        auto result = storage.select(&User::psw, where(c(&User::name) == var));
                        if (!result.empty())
                            return result[0];
                        return nullptr;
                    }
                    else if constexpr (_User_field_policy == fields::status) {
                        auto result = storage.select(&User::status, where(c(&User::name) == var));
                        if (!result.empty())
                            return result[0];
                        throw std::invalid_argument("no field");
                    }
                    else if constexpr (_User_field_policy == fields::pp) {
                        auto result = storage.select(&User::pp, where(c(&User::name) == var));
                        if (!result.empty())
                            return result[0];
                        return nullptr;
                    }
                        else
                            throw std::invalid_argument("bad token");
                }

            template<fields _User_field_policy = fields::contact>
                requires (_User_field_policy == fields::contact || _User_field_policy == fields::histo)
            std::vector<std::pair<int, std::string>> get_composite_data(int id)
            {
                std::vector<std::pair<int, std::string>> vector_result;
                std::string result;
                if constexpr (_User_field_policy == fields::contact) {
                    auto yolo = storage.select(&User::contact, where(c(&User::id) == id));
                    if (!yolo.empty())
                        result = yolo[0];
                    else
                        return {};
                }
                else {
                    auto yolo = storage.select(&User::name, where(c(&User::id) == id));
                    if (!yolo.empty())
                        result = yolo[0];
                    else
                        return {};
                }
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
                    pair_save = std::make_pair(std::stoi(token_2), token);
                    vector_result.push_back(pair_save);
                }
                token = result;
                while ((pos_2 = token.find(":")) != std::string::npos) {
                    token_2 = token.substr(0, pos_2);
                    token.erase(0, pos_2 + 1);
                }
                pair_save = std::make_pair(stoi(token_2), token);
                vector_result.push_back(pair_save);
                return vector_result;
            }
            std::string get_all_name();

            int get_id(std::string& name);
            //std::string get_name(int& id);
            //std::string get_psw(int& id);
            //bool get_status(int& id);
            //std::vector<std::pair<int, std::string>> get_histo(int id);
            //std::string get_pp(int& id);

            //void set_name(int& id, std::string& name);
            //void set_psw(int& id, std::string& psw);
            //void set_status(int& id, bool& status);
            //void set_pp(int& id, std::string& pp);

            void add_histo(int& id, int& id_add, std::string& date);
            void rm_all_histo(int& id);
            void add_contact(int& id, int& id_add);
            void rm_contact(int& id, int& id_suppr);
            void rm_all_contact(int& id);

        private:
            yolo storage = make_storage("db.storage",
                make_table("users",
                    make_column("name", &Database::User::name),
                    make_column("ip", &Database::User::ip),
                    make_column("contact", &Database::User::contact),
                    make_column("psw", &Database::User::psw),
                    make_column("status", &Database::User::status),
                    make_column("histo", &Database::User::histo),
                    make_column("pp", &Database::User::pp),
                    make_column("id", &Database::User::id, primary_key())));
    };
}

#endif /* !DATABASE_HPP_ */
