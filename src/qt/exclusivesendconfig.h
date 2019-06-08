#ifndef EXCLUSIVESENDCONFIG_H
#define EXCLUSIVESENDCONFIG_H

#include <QDialog>

namespace Ui {
    class ExclusivesendConfig;
}
class WalletModel;

/** Multifunctional dialog to ask for passphrases. Used for encryption, unlocking, and changing the passphrase.
 */
class ExclusivesendConfig : public QDialog
{
    Q_OBJECT

public:

    ExclusivesendConfig(QWidget *parent = 0);
    ~ExclusivesendConfig();

    void setModel(WalletModel *model);


private:
    Ui::ExclusivesendConfig *ui;
    WalletModel *model;
    void configure(bool enabled, int coins, int rounds);

private Q_SLOTS:

    void clickBasic();
    void clickHigh();
    void clickMax();
};

#endif // EXCLUSIVESENDCONFIG_H
