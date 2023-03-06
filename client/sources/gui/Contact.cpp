/*
** EPITECH PROJECT, 2021
** Contact.cpp
** File description:
** Contact.cpp
*/

#include "Contact.hpp"
#include "Client.hpp"

babel::Contact::Contact(QWidget *parent) :
QPushButton(parent),
m_name("profile_name"),
m_icon(std::make_unique<QIcon>(QIcon("../images/fish.jpg")))
{
    setStyleSheet("text-align:left;");
    setFixedHeight(70);
    setIcon(*m_icon);
    setIconSize({50, 50});
    setText(m_name.c_str());
    setFont(babel::Client::info);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setCursor(QCursor(Qt::PointingHandCursor));

    QObject::connect(this, SIGNAL(clicked()), this, SLOT(displayContact()));
}

void babel::Contact::setName(std::string& name)
{
    m_name = name;
    setText(m_name.c_str());
}

std::string babel::Contact::getName() const
{
    return (m_name);
}

void babel::Contact::displayContact()
{
    babel::Client::GetApp()->getInteractionSection()->getNameSection()->setName(m_name);
    babel::Client::GetApp()->getInteractionSection()->getButtonSection()->setSelection(true);
    babel::Client::GetApp()->getInteractionSection()->getButtonSection()->updateButton();
}