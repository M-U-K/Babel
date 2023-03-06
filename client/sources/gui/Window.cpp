/*
** EPITECH PROJECT, 2021
** CallButton.cpp
** File description:
** CallButton.cpp
*/

#include "sources/gui/qtclass/Window.hpp"
#include "ContactWindow.hpp"
#include "InteractionWindow.hpp"

babel::Window::Window() :
QWidget(),
m_contact(std::make_shared<ContactWindow>()),
m_interaction(std::make_shared<InteractionWindow>())
{
    setWindowTitle("Babel_client");

    m_gird = std::make_unique<QGridLayout>();

    m_gird->setSpacing(0);
    m_gird->addWidget(m_interaction.get(), 0, 1);
    m_gird->addWidget(m_contact.get(), 0, 0);
    setLayout(m_gird.get());
}

std::shared_ptr<babel::ContactWindow> babel::Window::getContactSection()
{
    return (m_contact);
}

std::shared_ptr<babel::InteractionWindow> babel::Window::getInteractionSection()
{
    return (m_interaction);
}