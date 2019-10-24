#include "newgamewindow.h"

#include <QHBoxLayout>

newgamewindow::newgamewindow(QWidget *parent) : QDialog(parent)
{
    setMinimumSize(300,300);
    setWindowTitle(tr("New Game"));
    setModal(true);
    layoutSize = new QLabel(tr("Size:"));
    tableSize = new QSpinBox();
    tableSize->setRange(7,15);
    tableSize->setSingleStep(4);

    ok = new QPushButton(tr("OK"));
    cancel = new QPushButton(tr("Cancel"));

    connect(ok, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancel, SIGNAL(clicked()), this, SLOT(reject()));

    QHBoxLayout *upperLayout = new QHBoxLayout();
    upperLayout->addWidget(tableSize);
    upperLayout->addWidget(tableSize);

    QHBoxLayout *lowerLayout = new QHBoxLayout();
    lowerLayout->addWidget(ok);
    lowerLayout->addWidget(cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(upperLayout);
    mainLayout->addLayout(lowerLayout);

    setLayout(mainLayout);
}
