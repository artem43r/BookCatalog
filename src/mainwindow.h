#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLineEdit;
class QComboBox;
class QSpinBox;
class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void clearForm();
    void saveBookPlaceholder();
    void searchPlaceholder();
    void showAbout();

private:
    void createActions();
    void createMenus();
    void createToolBar();
    void createCentralWidget();

    QLineEdit *m_titleEdit = nullptr;
    QLineEdit *m_authorEdit = nullptr;
    QComboBox *m_genreCombo = nullptr;
    QSpinBox *m_ratingSpin = nullptr;

    QAction *m_newAction = nullptr;
    QAction *m_clearAction = nullptr;
    QAction *m_searchAction = nullptr;
    QAction *m_exitAction = nullptr;
    QAction *m_aboutAction = nullptr;
};

#endif // MAINWINDOW_H
