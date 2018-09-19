#include <QtTest>

// add necessary includes here

class testOne : public QObject
{
    Q_OBJECT
public:
    testOne();
    ~testOne();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

testOne::testOne()
{

}

testOne::~testOne()
{

}

void testOne::initTestCase()
{

}

void testOne::cleanupTestCase()
{

}

void testOne::test_case1()
{

}

QTEST_APPLESS_MAIN(testOne)

#include "tst_testone.moc"
