/*
** EPITECH PROJECT, 2021
** CallButton.cpp
** File description:
** CallButton.cpp
*/

#ifndef BABEL_WINDOW_HPP
#define BABEL_WINDOW_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QIcon>
#include <QGridLayout>
#include <memory>

namespace babel
{
    class ContactWindow;
    class InteractionWindow;

    class Window
        : public QWidget
    {
    public:
        Window();
        ~Window() override = default;

        [[nodiscard]] std::shared_ptr<ContactWindow> getContactSection();
        [[nodiscard]] std::shared_ptr<InteractionWindow> getInteractionSection();
    private:
        std::unique_ptr<QGridLayout> m_gird;

        std::shared_ptr<ContactWindow> m_contact;
        std::shared_ptr<InteractionWindow> m_interaction;

    };

}

#endif //BABEL_WINDOW_HPP
