#include "tests.h"


void Tests::simpleTest(){
    AndroidDevice testDevice;
    StorageDescriptor testDescriptor;
    QCOMPARE(testDevice.activeContainer, (Container*)NULL);
    QCOMPARE(testDevice.myContainers.size(), (unsigned int)0);
    QCOMPARE(testDevice.createContainer("TestName", testDescriptor), 0);
    QCOMPARE(testDevice.myContainers.size(), (unsigned int)1);
    QCOMPARE(testDevice.myContainers.begin()->first, string("TestName"));
    QVERIFY(testDevice.myContainers.begin()->second != NULL);
    QCOMPARE(testDevice.myContainers.begin()->second->getName(), string("TestName"));
    QCOMPARE(testDevice.switchToContainer("TestName"), 0);
    QCOMPARE(testDevice.activeContainer, testDevice.myContainers.begin()->second);
    QCOMPARE(testDevice.destroyContainer("TestName"), 0);
    QCOMPARE(testDevice.activeContainer, (Container*)NULL);
    QCOMPARE(testDevice.myContainers.size(), (unsigned int)0);


}

void Tests::stateTest(){
    AndroidDevice testDevice;
    StorageDescriptor testDescriptor;
    QCOMPARE(testDevice.createContainer("TestName", testDescriptor), 0);
    QCOMPARE(testDevice.myContainers.begin()->second->getState(), Container::StateStopped);
    testDevice.myContainers.begin()->second->setState(Container::StateRunning);
    QCOMPARE(testDevice.myContainers.begin()->second->getState(), Container::StateRunning);
    testDevice.myContainers.begin()->second->setState(Container::StateStopped);
    QCOMPARE(testDevice.myContainers.begin()->second->getState(), Container::StateStopped);
    QCOMPARE(testDevice.startContainer("TestName"), 0);
    QCOMPARE(testDevice.myContainers.begin()->second->getState(), Container::StateRunning);
    QCOMPARE(testDevice.activeContainer, (Container*)NULL);
    QCOMPARE(testDevice.stopContainer("TestName"), 0);
    QCOMPARE(testDevice.myContainers.begin()->second->getState(), Container::StateStopped);
    QCOMPARE(testDevice.activeContainer, (Container*)NULL);
}

void Tests::manyContainersTest(){
    AndroidDevice testDevice;
    StorageDescriptor testDescriptor;
    QCOMPARE(testDevice.activeContainer, (Container*)NULL);
    for (int i = 0; i < 1000; ++i){
        std::ostringstream out;
        out << "TestName" << i;
        QCOMPARE(testDevice.myContainers.size(), (unsigned int)i);
        QCOMPARE(testDevice.createContainer(string(out.str()), testDescriptor), 0);
        QCOMPARE(testDevice.myContainers.size(), (unsigned int)i+1);
    }
}

void Tests::runTests(){
    Tests * test = new Tests();
    QTest::qExec(test);
    delete test;
}
