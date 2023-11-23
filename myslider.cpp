//
// Created by esorochinskiy on 23.11.23.
//

#include <KLocalizedString>
#include "myslider.h"

MySlider::MySlider(Qt::Orientation orientation, QWidget *parent) :
            QSlider(orientation, parent) {

        setValue(5);
        setSliderPosition(5);
        setSingleStep(1);
        setPageStep(1);
        setMinimum(1);
        setMaximum(10);
        setTracking(true);
        setFixedWidth(200);

}

void MySlider::retranslateUi() {
    setToolTip(i18n("Snake Movement Speed"));
    setWhatsThis(i18n("Change Snake Movement Speed dynamically"));
}
