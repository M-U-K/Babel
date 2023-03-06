/*
** EPITECH PROJECT, 2021
** Contact.hpp
** File description:
** Contact.hpp
*/

#ifndef BABEL_CONTACT_HPP
#define BABEL_CONTACT_HPP

#include <QWidget>
#include <QPushButton>
#include <string>
#include "InteractionWindow.hpp"
#include "Name.hpp"

namespace babel
{
    class Contact
        : public QPushButton
    {
        Q_OBJECT
    private:
        std::unique_ptr<QIcon> m_icon;
        std::string m_name;

    public:
        explicit Contact(QWidget *parent = nullptr);
        void setName(std::string& name);
        [[nodiscard]] std::string getName() const;

    public slots:
        void displayContact();
    };
}

#endif //BABEL_CONTACT_HPP
