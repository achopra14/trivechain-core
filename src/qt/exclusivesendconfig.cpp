#include "exclusivesendconfig.h"
#include "ui_exclusivesendconfig.h"

#include "bitcoinunits.h"
#include "guiconstants.h"
#include "optionsmodel.h"
#include "exclusivesend-client.h"
#include "walletmodel.h"

#include <QMessageBox>
#include <QPushButton>
#include <QKeyEvent>
#include <QSettings>

ExclusivesendConfig::ExclusivesendConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExclusivesendConfig),
    model(0)
{
    ui->setupUi(this);

    connect(ui->buttonBasic, SIGNAL(clicked()), this, SLOT(clickBasic()));
    connect(ui->buttonHigh, SIGNAL(clicked()), this, SLOT(clickHigh()));
    connect(ui->buttonMax, SIGNAL(clicked()), this, SLOT(clickMax()));
}

ExclusivesendConfig::~ExclusivesendConfig()
{
    delete ui;
}

void ExclusivesendConfig::setModel(WalletModel *model)
{
    this->model = model;
}

void ExclusivesendConfig::clickBasic()
{
    configure(true, 1000, 2);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("ExclusiveSend Configuration"),
        tr(
            "ExclusiveSend was successfully set to basic (%1 and 2 rounds). You can change this at any time by opening Trivechain's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void ExclusivesendConfig::clickHigh()
{
    configure(true, 1000, 8);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("ExclusiveSend Configuration"),
        tr(
            "ExclusiveSend was successfully set to high (%1 and 8 rounds). You can change this at any time by opening Trivechain's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void ExclusivesendConfig::clickMax()
{
    configure(true, 1000, 16);

    QString strAmount(BitcoinUnits::formatWithUnit(
        model->getOptionsModel()->getDisplayUnit(), 1000 * COIN));
    QMessageBox::information(this, tr("ExclusiveSend Configuration"),
        tr(
            "ExclusiveSend was successfully set to maximum (%1 and 16 rounds). You can change this at any time by opening Trivechain's configuration screen."
        ).arg(strAmount)
    );

    close();
}

void ExclusivesendConfig::configure(bool enabled, int coins, int rounds) {

    QSettings settings;

    settings.setValue("nExclusiveSendRounds", rounds);
    settings.setValue("nExclusiveSendAmount", coins);

    exclusiveSendClient.nExclusiveSendRounds = rounds;
    exclusiveSendClient.nExclusiveSendAmount = coins;
}
