#pragma once

#include <QPlastiqueStyle>
#include <QPalette>
#include <string>

class QPainterPath;

namespace mars
{
    namespace gui
    {

        /**
         * \brief A custom GUI style
         */
        class MarsStyle : public QPlastiqueStyle
        {
            Q_OBJECT

        public:
            MarsStyle(std::string stylePath_) : stylePath(stylePath_) {}

            void polish(QPalette &palette);
            void polish(QWidget *widget);
            void unpolish(QWidget *widget);
            int pixelMetric(PixelMetric metric, const QStyleOption *option,
                            const QWidget *widget) const;
            int styleHint(StyleHint hint, const QStyleOption *option,
                          const QWidget *widget, QStyleHintReturn *returnData) const;
            void drawPrimitive(PrimitiveElement element, const QStyleOption *option,
                               QPainter *painter, const QWidget *widget) const;
            void drawControl(ControlElement control, const QStyleOption *option,
                             QPainter *painter, const QWidget *widget) const;
        private:
            std::string stylePath;
     
            static void setTexture(QPalette &palette, QPalette::ColorRole role,
                                   const QPixmap &pixmap);
            static QPainterPath roundRectPath(const QRect &rect);
        };

    } // end of namespace gui
} // end of namespace mars
