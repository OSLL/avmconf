#ifndef RESTORER_H
#define RESTORER_H

#include <fstream>
#include <string>
#include "Container.h"

#include <map>

class Saver {
    friend class Container;

public:
    Saver();
    int save(const std::map<std::string, Container*> & containers);
    int save(Container * container);
    int restore(std::map<std::string, Container*> & containers);

private:
    std::string fileName;
    int writeContainer(std::ofstream &, Container *);
    Container * readContainer(std::ifstream &);
};

#endif // RESTORER_H
