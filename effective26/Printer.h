//
// Created by peter on 4/23/21.
//

#ifndef NOTELEARNING_PRINTER_H
#define NOTELEARNING_PRINTER_H

#endif //NOTELEARNING_PRINTER_H

class PrintJob;
class Printer
{
public:
    void submitJob(const PrintJob& job);
    void reset();
    void performSelfTest();

    friend Printer& thePrinter();

private:
    Printer();
    Printer(const Printer&);
};

Printer& thePrinter()
{
    static Printer p;
    return p;
}

class PrintJob
{
public:
    PrintJob(const string& whatToPrint);
};

string buffer;
thePrinter().reset();
thePrinter().submitJob(buffer);
