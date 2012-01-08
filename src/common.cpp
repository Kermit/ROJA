#include "common.h"

#include <QtCore/QRegExp>

void Common::convertSpecialChars(QString &text)
{
    text.replace(QRegExp("[ęeóoąaśsłlżźzćcńnĘEÓOĄAŚSŁLŻŹZĆCŃN]"), "_");
}
