#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <QWidget>

namespace Ui {
class WaveForm;
}

class WaveForm : public QWidget
{
    Q_OBJECT

public:
    explicit WaveForm(QWidget *parent = nullptr);
    ~WaveForm();

private:
    Ui::WaveForm *ui;
};

#endif // WAVEFORM_H
