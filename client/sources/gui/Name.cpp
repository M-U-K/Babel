/*
** EPITECH PROJECT, 2021
** Name.cpp
** File description:
** Name.cpp
*/

#include "sources/gui/qtclass/Name.hpp"
#include "Client.hpp"

babel::Name::Name(QWidget *parent) :
QWidget(parent),
m_layout(std::make_unique<QVBoxLayout>()),
m_uuid(std::make_unique<QLabel>()),
m_name(std::make_unique<QLabel>()),
m_font(QFont("papyrus"))
{
    m_font.setPointSize(50);
    m_uuid->setText(babel::Client::getUuid().c_str());
    m_name->setText(babel::Client::getName().c_str());
    m_name->setFont(babel::Client::title);
    m_uuid->setFont(babel::Client::description);
    m_layout->addWidget(m_name.get());
    m_layout->addWidget(m_uuid.get());
    setLayout(m_layout.get());
    displayProfile();
}

void babel::Name::displayProfile()
{
    m_uuid->setText(babel::Client::getUuid().c_str());
    m_name->setText(babel::Client::getName().c_str());
    m_name->setFont(babel::Client::title);
    m_uuid->setFont(babel::Client::description);
}

void babel::Name::setName(std::string name)
{
    m_name->setText(name.c_str());
    m_name->setFont(babel::Client::title);
}

std::string babel::Name::getName()
{
    return (m_name->text().toLocal8Bit().data());
}