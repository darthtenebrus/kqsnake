//
// Created by esorochinskiy on 30.10.23.
//

#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <random>
#include <QDesktopWidget>
#include <QApplication>
#include "snakegame.h"
#include "constants.h"

#ifdef _DEBUG
#include <QDebug>
#endif


SnakeGame::SnakeGame(int timerInterval, QWidget *parent) : QWidget(parent), mTimer(new QTimer()) {
    m_TimerInterval = DIVISOR / timerInterval;

    initTotalCells();
    renewGame(false);
    connect(mTimer, &QTimer::timeout, this, &SnakeGame::nextMove);

}

SnakeGame::~SnakeGame() {
    delete mTimer;
    delete mApples;
    delete mSnake;
}

void SnakeGame::resizeEvent(QResizeEvent *event) {
    recalcScreenCells();
    QWidget::resizeEvent(event);

}

void SnakeGame::recalcScreenCells() {
    int h = height();
    int w = width();
    QPoint fd = getStandardFieldDefs(w, h);

    m_ScrCellsX = fd.x() / (MIN_CELL_SIZE);
    m_ScrCellsY = fd.y() / (MIN_CELL_SIZE);
    m_remScrX = (fd.x() - (MIN_CELL_SIZE) * m_ScrCellsX) / 2;
    m_remScrY = (fd.y() - (MIN_CELL_SIZE) * m_ScrCellsY) / 2;


}

QPoint SnakeGame::getStandardFieldDefs(int &x, int &y) {
    return {x - (FIELD_OFFSET + SPACE) * 2, y - (FIELD_OFFSET + SPACE) * 2};
}


void SnakeGame::paintEvent(QPaintEvent *e) {
    actualDoRePaint();
}

QPoint SnakeGame::getMainOffset() const {
    return {FIELD_OFFSET + SPACE + m_remScrX, FIELD_OFFSET + SPACE + m_remScrY};
}


void SnakeGame::actualDoRePaint() {

    QPainter painter(this);
    painter.setBackground(QBrush("#232323"));

    const QPoint &mainOffset = getMainOffset();
    painter.translate(mainOffset.x(), mainOffset.y());

    for (int y = 0; y < m_ScrCellsY; ++y) {
        for (int x = 0; x < m_ScrCellsX; ++x) {
            painter.fillRect(QRect(x * (MIN_CELL_SIZE), y * (MIN_CELL_SIZE),
                                   MIN_CELL_SIZE, MIN_CELL_SIZE), QBrush("#000000"));

        }
    }
    drawApples(painter);
    mSnake->drawInitial(painter);

}

void SnakeGame::renewGame(bool fromScreen) {

    if (mApples) {
        mApples->clear();
    } else {
        mApples = new QList<GameObject>();
    }

    if (mSnake) {
        delete mSnake;
    }

    mSnake = new Snake(m_cellsX / 2, m_cellsY / 2);
    for (int i = 0; i <= 2; i++) {
        createNewApple(fromScreen);
    }


}


void SnakeGame::initTotalCells() {

    QDesktopWidget *desktopwidget = QApplication::desktop(); // Get display resolution
    int dw = desktopwidget->width();
    int dh = desktopwidget->height();
    QPoint fd = getStandardFieldDefs(dw, dh);

    m_cellsX = fd.x() / (MIN_CELL_SIZE);
    m_cellsY = fd.y() / (MIN_CELL_SIZE);

}

int SnakeGame::getScreenCellsX() {
    return m_ScrCellsX;
}

int SnakeGame::getScreenCellsY() {
    return m_ScrCellsY;
}

int SnakeGame::getMemCellsX() {
    return m_cellsX;
}

int SnakeGame::getMemCellsY() {
    return m_cellsY;
}

void SnakeGame::createNewApple(bool fromScreen) {
    int randX;
    int randY;
    int cellsX = fromScreen ? getScreenCellsX() : getMemCellsX();
    int cellsY = fromScreen ? getScreenCellsY() : getMemCellsY();

    do {
        randX = localRand(cellsX - 1);
        randY = localRand(cellsY - 1);

    } while (mSnake->checkCollision(randX, randY) || collizedApple(randX, randY));

    mApples->append(GameObject(randX, randY));
}

QList<GameObject> *SnakeGame::getApples() {
    return mApples;
}

void SnakeGame::drawApples(QPainter &painter) {
    for(GameObject &g : *mApples) {
        painter.drawPixmap(QRect(g.x() * (MIN_CELL_SIZE), g.y() * (MIN_CELL_SIZE),
                               MIN_CELL_SIZE, MIN_CELL_SIZE), QPixmap(":/images/apple.png"));
    }

}

int SnakeGame::localRand(int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, max);
    int ret = abs(dist(mt));

    return ret;
}

bool SnakeGame::collizedApple(int x, int y) {
    return std::any_of(mApples->begin(), mApples->end(), [&](GameObject &c){
        return c.intersects(x,y);
    });
}

void SnakeGame::startGame() {
    if (!mTimer->isActive()) {
        mTimer->start(m_TimerInterval);

    }
}

void SnakeGame::cancelTimerInstantly() {
    if (mTimer->isActive()) {
        mTimer->stop();
    }

}


void SnakeGame::nextMove(void) {

    mSnake->move(this);
    if (!mSnake->isAlive()) {
        stopGame();
        emit enableStart(false);
        QMessageBox::critical(this, QObject::tr("You lost"), QObject::tr("Sorry, you lost"));
    } else {
        maxTurnsBefore++;
        if (maxTurnsBefore == 5) {
            createNewApple(true);
            maxTurnsBefore = 0;
        }
        repaint();
        if (mSnake->length() >= m_ScrCellsX * 2) {
            stopGame();
            emit enableStart(false);
            QMessageBox::information(this, QObject::tr("You win"), QObject::tr("You win!"));
        }
    }
}

void SnakeGame::keyPressEvent(QKeyEvent *event) {
    if (!mTimer->isActive()) {
        return;
    }
    Snake::Direction &cDir = mSnake->getDirection();
    switch (event->key()) {
        case Qt::Key_Left:
        case Qt::Key_A:
            --cDir;
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            ++cDir;
            break;
    }
}

void SnakeGame::newGameTrigger(bool b) {
    cancelTimerInstantly();
    renewGame(true);
    emit enableStart(true);
    emit changeControls(false);
    repaint();
}

void SnakeGame::mousePressEvent(QMouseEvent *event) {
    if (!mTimer->isActive()) {
        return;
    }
    Snake::Direction &cDir = mSnake->getDirection();
    switch (event->button()) {
        case Qt::LeftButton:
            --cDir;
            break;
        case Qt::RightButton:
            ++cDir;
            break;
        default:
            break;

    }
}

void SnakeGame::timerChanged(int timerInterval) {
    m_TimerInterval = DIVISOR / timerInterval;
    if (mTimer->isActive()) {
        mTimer->stop();
        mTimer->start(m_TimerInterval);
    }

}

void SnakeGame::startStopTrigger(bool) {
    if (mTimer->isActive()) {
        stopGame();
    } else {
        startGame();
    }
    emit changeControls(mTimer->isActive());

}

void SnakeGame::stopGame() {
    cancelTimerInstantly();
}


