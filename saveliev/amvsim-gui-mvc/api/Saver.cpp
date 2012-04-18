
#include <QDebug>

#include <iostream>

#include "Saver.h"
#include "Container.h"

using std::ofstream;
using std::ifstream;
using std::endl;
using std::map;
using std::string;
using std::pair;
using std::ios;

Saver::Saver() : fileName("device.txt") {
}


int Saver::save(const std::map<std::string, Container *> & containers) {
    ofstream out;
    out.open(fileName.c_str());
    for (map<string, Container*>::const_iterator it = containers.begin(); it != containers.end(); ++it) {
        if (writeContainer(out, it->second) != 0) {
            out.close();
            return -1;
        }
    }
    out.close();
    return 0;
}

int Saver::writeContainer(std::ofstream & out, Container * container) {
    try {
        out << container->getName() << endl;
        out << container->getImageAddress() << endl;
        return 0;
    } catch (...) {
        return -1;
    }
}

int Saver::save(Container * container) {
    ofstream out;
    out.open(fileName.c_str());
    try {
        out << container->getName() << endl;
        out << container->getImageAddress() << endl;
        out.close();
    } catch (...) {
        out.close();
        return -1;
    }
    return 0;
}

int Saver::restore(map<string, Container*> & containers) {
    ifstream in;
    in.open(fileName.c_str());
    if (!in) {
        return -1;
    } else {
        while (Container * cont = readContainer(in)) {
            std::cout << cont->getName() << std::endl;
            containers.insert(make_pair(cont->getName(), cont));
        }
        in.close();
    }
    return 0;
}

Container * Saver::readContainer(ifstream & in) {
    Container * cont;

    char name[32768], address[32768];
    in.getline(name, 32768);
    if (!in.eof()) {
        in.getline(address, 32768);
        qDebug() << name << " " << address;
        cont = new Container(name);
        if (cont->restoreImage(address) != 0) {
            delete cont;
            cont = 0;
        }
    } else {
        cont = 0;
    }

    return cont;
}





