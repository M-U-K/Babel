/*
** EPITECH PROJECT, 2021
** ContactWindow.cpp
** File description:
** ContactWindow.cpp
*/

#include "sources/gui/qtclass/ContactWindow.hpp"

babel::ContactWindow::ContactWindow(QWidget *parent) :
QWidget(parent),
m_contactLayout(std::make_unique<QVBoxLayout>()),
m_contacts(std::map<std::string, std::unique_ptr<Contact>>())
{
    setFixedWidth(300);
    setLayout(m_contactLayout.get());
    m_contactLayout->setAlignment(Qt::AlignTop);

    setStyleSheet("background-color:green;");
}

void babel::ContactWindow::addContact(std::string name)
{
    auto newContact = m_contacts.emplace(name, std::make_unique<babel::Contact>()).first;

    m_contactLayout->addWidget(newContact->second.get());
    newContact->second->setName(name);
}