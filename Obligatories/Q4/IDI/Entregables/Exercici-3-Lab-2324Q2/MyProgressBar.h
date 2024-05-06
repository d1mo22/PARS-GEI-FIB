#include <QProgressBar>
#include <QTimer>

class MyProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    MyProgressBar(QWidget *parent);
    double wavelength;
    double phase;
    QTimer timer;
    bool ences;

public slots:
    void inicialize();
    void update_progressbar(int position, double a, double p);
    void update_value_WL(double wl);
    void update_value_PH(double ph);
    void oscilation();
    void timer_ences();

signals:
    void update_next(int, double, double);
    void update_wavelength(double);
    void update_phase(double);
};