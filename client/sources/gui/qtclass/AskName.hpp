/*
** EPITECH PROJECT, 2021
** CallButton.cpp
** File description:
** CallButton.cpp
*/
#ifndef BABEL_ASKNAME_HPP
#define BABEL_ASKNAME_HPP

#include <QWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QGridLayout>
#include <memory>

namespace babel
{
    class AskName :
        public QInputDialog {
            Q_OBJECT
        public:
            explicit AskName(QWidget *parent = nullptr);
        public slots:
            void validateName(QString name);
    };
}


#endif //BABEL_ASKNAME_HPP
