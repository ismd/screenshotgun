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
    QVariant value = _settings->value("server/url");
    bool isValid = value.isValid() && value.toString().length() > 0;

    emit(valid(isValid));
    return isValid;
}

QString Settings::getServer()
{
    return _settings->value("server/url").toString();
}

void Settings::accept()
{
    _settings->setValue("server/url", ui->serverEdit->text());

    if (!isValid()) {
        return;
    }

    hide();

}
