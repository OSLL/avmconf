#ifndef TESTS_H
#define TESTS_H

#include <QtTest>
#include "AndroidDevice.h"
#include <sstream>


using namespace QTest;


class Tests : public QObject
{
Q_OBJECT
public:

    static void runTests();

private slots:

    void simpleTest();
    void stateTest();
    void manyContainersTest();

};

#endif // TESTS_H
