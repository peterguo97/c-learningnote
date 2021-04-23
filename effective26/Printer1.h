//
// Created by peter on 4/23/21.
//

#ifndef NOTELEARNING_PRINTER1_H
#define NOTELEARNING_PRINTER1_H

#endif //NOTELEARNING_PRINTER1_H
class Printer {
public:
    class TooManyObjects{};
    Printer();
    ~Printer();

private:
    static size_t numObjects;
    Printer(const Printer& rhs);
};

size_t Printer::numObjects = 0;
Printer::Printer() {
    if ( numObjects >= 1)
    {
        throw TooManyObjects();
    }
    ++numObjects;
}

Printer::~Printer() {
    --numObjects;
}

class ColorPrinter : public Printer {

};

Printer p;
ColorPrinter p;

class CPFMachine {
private:
    Printer p;
    FaxMachine f;
};

CPFMachine c1;
