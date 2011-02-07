/*

Copyright (C) 2009, Etienne Moutot <e.moutot@gmail.com>

This file is part of colorPickerWidget.

    colorPickerWidget is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    colorPickerWidget is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Modified by Gigotdarnaud, for the Celendel project */

#ifndef COLORPICKERWIDGET_H
#define COLORPICKERWIDGET_H

#include <QtGui/QWidget>
#include <QtGui/QPushbutton>
#include <QtGui/QGridLayout>
#include <QtGui/QSlider>
#include "qtcolortriangle.h"
#include "colorviewer.h"
#include "screen.h"

class ColorPickerWidget : public QWidget
{
    Q_OBJECT

public:
    ColorPickerWidget(QWidget *parent = 0);
    ~ColorPickerWidget();

    QColor color() const;

Q_SIGNALS:
    void colorChanged(const QColor &col);

public Q_SLOTS:
    void setColor(const QColor &col);

private slots:
    void pickMode();
    void colorChgd();

private:
    QtColorTriangle *colorTriangle;
    ColorViewer *colorView;
    QPushButton *pickColor;

    QSlider *alpha;

    QGridLayout *layout;

    screen *ecran;
};

#endif // COLORPICKERWIDGET_H
