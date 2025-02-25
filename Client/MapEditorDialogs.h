#ifndef DEF_MAPEDITORDIALOGS
#define DEF_MAPEDITORDIALOGS

#include <QDialog>
#include "../Shared/Constants.h"
#include "ui_MapEditorAddObjectDialog.h"
#include "ui_MapEditorNewMapDialog.h"

class QLineEdit;
class QSpinBox;
class QPushButton;
class QColorPickerWidget;


class RSIDDialog : public QDialog
{
    public:

    RSIDDialog(QWidget* parent=0);

    int newLine();

    int changeLine(RSID id, const QString& name = QString());

    RSID getRSID() const { return m_spinBox->value(); }
    QString getName() const {  return m_lineEdit->text(); }

    private:

    bool m_used;

    QSpinBox* m_spinBox;
    QLineEdit* m_lineEdit;
    QPushButton* m_accept;
    QPushButton* m_cancel;

};

class AddObjectDialog : public QDialog
{
    Q_OBJECT
    public:
    AddObjectDialog(QWidget* parent=0, QPoint defaultCase=QPoint(), QPoint maxCase=QPoint(MAP_MAX_SIZE,MAP_MAX_SIZE), QString defaultText=QString(), RSID defaultRSID=0);

    QPoint getCoords() const;
    QString getText() const;
    RSID getRSID() const;
    QColor getColor() const;
    int getColorValue() const;

    private slots:
    void vcng(int);

    private:

    bool b;

    QColorPickerWidget* m_colorPicker;

    Ui::NewMapItemDialog ui;
};

class NewMapDialog : public QDialog
{
    Q_OBJECT
    public:
    NewMapDialog(QWidget* parent=0);

    QString getName() const;
    QString getMapFile() const;
    QString getRessourceList() const;
    RSID getRSID() const;
    QPoint getSize() const;

    bool isEmptyMap() const;

    private slots:
    void on_browse_pressed();
    void on_mbrowse_pressed();
    void on_typeCB_currentIndexChanged(int ind);

    private:
    Ui::NewMapDialog ui;
};

#endif //Guard
