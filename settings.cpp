#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings),
    _settings(new QSettings("openscreencloud"))
{
    ui->setupUi(this);

    connect(ui->submitButtons, SIGNAL(accepted()),
            this, SLOT(accept()));
}

Settings::~Settings()
{
    delete ui;
}

bool Settings::isValid()
{
    QString serverUrl = getServer();
    bool isValid = serverUrl.length() > 0;

    if (isValid) {
        emit(valid());
    }

    return isValid;
}

QString Settings::getServer()
{
    return _settings->value("server/url").toString();
}

void Settings::accept()
{
    _settings->setValue("server/checked", ui->serverRadioButton->isChecked());
    _settings->setValue("server/url", ui->serverEdit->text());

    if (!isValid()) {
        return;
    }

    hide();
}
