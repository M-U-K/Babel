/*
** EPITECH PROJECT, 2021
** InteractionWindow.cpp
** File description:
** InteractionWindow.cpp
*/

#include "InteractionWindow.hpp"

babel::InteractionWindow::InteractionWindow(QWidget *parent) :
QWidget(parent),
m_contactLayout(std::make_unique<QGridLayout>()),
m_mainIcon(std::make_unique<QLabel>()),
m_name(std::make_shared<Name>()),
m_buttons(std::make_shared<CallButton>(m_name))
{
    m_mainIcon->setPixmap(QPixmap("../images/fish.jpg").scaled(255, 255, Qt::KeepAspectRatio));
    auto oui = new QWidget;

    oui->setStyleSheet("background-color:blue;");
    m_name->setStyleSheet("background-color:red;");
    m_buttons->setStyleSheet("background-color:aqua;");
    m_mainIcon->setStyleSheet("background-color:orange;");


    m_contactLayout->addWidget(oui, 1, 0, 2, 5);
    m_contactLayout->addWidget(m_name.get(), 0, 1, 1, 3);
    m_contactLayout->addWidget(m_buttons.get(), 0, 4);
    m_contactLayout->addWidget(m_mainIcon.get(), 0, 0);
    m_contactLayout->setSpacing(0);
    setLayout(m_contactLayout.get());
}

std::shared_ptr<babel::Name>& babel::InteractionWindow::getNameSection()
{
    return (m_name);
}

std::shared_ptr<babel::CallButton>& babel::InteractionWindow::getButtonSection()
{
    return (m_buttons);
}