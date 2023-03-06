/*
** EPITECH PROJECT, 2021
** InteractionWindow.hpp
** File description:
** InteractionWindow.hpp
*/

#ifndef BABEL_INTERACTIONWINDOW_HPP
#define BABEL_INTERACTIONWINDOW_HPP

#include <QWidget>
#include <QGridLayout>
#include <QLabel>

#include "CallButton.hpp"

namespace babel
{
    class InteractionWindow
        : public QWidget
    {
    private:
        std::unique_ptr<QGridLayout> m_contactLayout;
        std::unique_ptr<QLabel> m_mainIcon;
        std::shared_ptr<Name> m_name;
        std::shared_ptr<CallButton> m_buttons;

    public:
        explicit InteractionWindow(QWidget *parent = nullptr);
        std::shared_ptr<Name>& getNameSection();
        std::shared_ptr<CallButton>& getButtonSection();
    };
}

#endif //BABEL_INTERACTIONWINDOW_HPP
