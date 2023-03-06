/*
** EPITECH PROJECT, 2021
** ContactWindow.h
** File description:
** ContactWindow.h
*/

#ifndef BABEL_CONTACTWINDOW_HPP
#define BABEL_CONTACTWINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <map>
#include <memory>

#include "Contact.hpp"

namespace babel
{
    class ContactWindow
            : public QWidget
    {
        private:
            std::unique_ptr<QVBoxLayout> m_contactLayout;
            std::map<std::string, std::unique_ptr<Contact>> m_contacts;

        public:
            explicit ContactWindow(QWidget *parent = nullptr);
            void addContact(std::string name);
    };
}

#endif //BABEL_CONTACTWINDOW_HPP
