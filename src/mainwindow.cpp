#include "mainwindow.h"

#include <QAction>
#include <QComboBox>
#include <QFormLayout>
#include <QFont>
#include <QHBoxLayout>
#include <QKeySequence>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("Каталог книг"));
    resize(850, 600);
    createActions();
    createMenus();
    createToolBar();
    createCentralWidget();

    statusBar()->showMessage(QStringLiteral("Готово. Каркас приложения запущен."));
}

void MainWindow::createActions()
{
    m_newAction = new QAction(QStringLiteral("Новая книга"), this);
    m_newAction->setShortcut(QKeySequence::New);
    connect(m_newAction, &QAction::triggered, this, &MainWindow::clearForm);

    m_clearAction = new QAction(QStringLiteral("Очистить форму"), this);
    connect(m_clearAction, &QAction::triggered, this, &MainWindow::clearForm);

    m_searchAction = new QAction(QStringLiteral("Поиск"), this);
    m_searchAction->setShortcut(QKeySequence::Find);
    connect(m_searchAction, &QAction::triggered, this, &MainWindow::searchPlaceholder);

    m_exitAction = new QAction(QStringLiteral("Выход"), this);
    m_exitAction->setShortcut(QKeySequence::Quit);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

    m_aboutAction = new QAction(QStringLiteral("О программе"), this);
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu(QStringLiteral("Файл"));
    fileMenu->addAction(m_newAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);

    QMenu *editMenu = menuBar()->addMenu(QStringLiteral("Правка"));
    editMenu->addAction(m_clearAction);
    editMenu->addAction(m_searchAction);

    QMenu *helpMenu = menuBar()->addMenu(QStringLiteral("Справка"));
    helpMenu->addAction(m_aboutAction);
}

void MainWindow::createToolBar()
{
    QToolBar *toolBar = addToolBar(QStringLiteral("Основные действия"));
    toolBar->setMovable(false);
    toolBar->addAction(m_newAction);
    toolBar->addAction(m_clearAction);
    toolBar->addAction(m_searchAction);
}

void MainWindow::createCentralWidget()
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    auto *rootLayout = new QVBoxLayout(central);
    rootLayout->setContentsMargins(18, 18, 18, 18);
    rootLayout->setSpacing(12);

    auto *heading = new QLabel(QStringLiteral("Каталог книг"), central);
    QFont headingFont = heading->font();
    headingFont.setPointSize(18);
    headingFont.setBold(true);
    heading->setFont(headingFont);
    rootLayout->addWidget(heading);

    auto *description = new QLabel(
        QStringLiteral("Стартовый каркас приложения. Сейчас готовится интерфейс; работу с данными добавим следующим этапом."),
        central);
    description->setWordWrap(true);
    rootLayout->addWidget(description);

    auto *formGroup = new QGroupBox(QStringLiteral("Сведения о книге"), central);
    auto *formLayout = new QFormLayout(formGroup);
    formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);

    m_titleEdit = new QLineEdit(formGroup);
    m_titleEdit->setPlaceholderText(QStringLiteral("Введите название книги"));
    formLayout->addRow(QStringLiteral("Название:"), m_titleEdit);

    m_authorEdit = new QLineEdit(formGroup);
    m_authorEdit->setPlaceholderText(QStringLiteral("Введите автора"));
    formLayout->addRow(QStringLiteral("Автор:"), m_authorEdit);

    m_genreCombo = new QComboBox(formGroup);
    m_genreCombo->addItems({
        QStringLiteral("Фантастика"),
        QStringLiteral("Фэнтези"),
        QStringLiteral("Роман"),
        QStringLiteral("Детектив"),
        QStringLiteral("Научная литература"),
        QStringLiteral("Другое")
    });
    formLayout->addRow(QStringLiteral("Жанр:"), m_genreCombo);

    m_ratingSpin = new QSpinBox(formGroup);
    m_ratingSpin->setRange(1, 5);
    m_ratingSpin->setValue(5);
    formLayout->addRow(QStringLiteral("Рейтинг (1–5):"), m_ratingSpin);

    rootLayout->addWidget(formGroup);

    auto *buttonLayout = new QHBoxLayout();
    auto *saveButton = new QPushButton(QStringLiteral("Сохранить книгу"), central);
    auto *clearButton = new QPushButton(QStringLiteral("Очистить"), central);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveBookPlaceholder);
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::clearForm);
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addStretch();
    rootLayout->addLayout(buttonLayout);

    auto *futureArea = new QLabel(
        QStringLiteral("Здесь на следующем этапе появится список книг (QTableView и модель данных)."),
        central);
    futureArea->setWordWrap(true);
    futureArea->setMinimumHeight(90);
    futureArea->setAlignment(Qt::AlignCenter);
    futureArea->setStyleSheet(QStringLiteral(
        "QLabel { border: 1px dashed palette(mid); border-radius: 6px; padding: 12px; color: palette(mid); }"));
    rootLayout->addWidget(futureArea, 1);
}

void MainWindow::clearForm()
{
    m_titleEdit->clear();
    m_authorEdit->clear();
    m_genreCombo->setCurrentIndex(0);
    m_ratingSpin->setValue(5);
    m_titleEdit->setFocus();
    statusBar()->showMessage(QStringLiteral("Форма очищена."), 3000);
}

void MainWindow::saveBookPlaceholder()
{
    statusBar()->showMessage(
        QStringLiteral("Это макет интерфейса: добавление книг реализуем на следующем этапе."), 5000);
}

void MainWindow::searchPlaceholder()
{
    statusBar()->showMessage(
        QStringLiteral("Поиск будет подключён после появления списка книг."), 5000);
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, QStringLiteral("О программе"),
        QStringLiteral("Каталог книг\nУчебный сквозной проект на Qt Widgets и C++.\n\nТекущий этап: каркас интерфейса."));
}
