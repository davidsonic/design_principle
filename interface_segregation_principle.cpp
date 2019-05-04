#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
using namespace std;
using namespace boost;


struct Document{
    string name;
};

//struct IMachine{
//    virtual void print(Document&doc)=0;
//    virtual void scan(Document&doc) =0;
//    virtual void fax(Document&doc)=0;
//};
//
//struct MFP: IMachine{
//    void print(Document &doc) override {
//        //ok
//
//    }
//
//    void scan(Document &doc) override {
//
//    }
//
//    void fax(Document &doc) override {
//
//    }
//};
//
//struct Scanner:IMachine{
//    void print(Document &doc) override {
//
//    }
//
//    void scan(Document &doc) override {
//        //ok
//
//    }
//
//    void fax(Document &doc) override {
//
//    }
//};

struct IPrinter{
    virtual void print(Document&doc)=0;
};

struct IScanner{
    virtual void scan(Document&doc)=0;
};


struct Printer: IPrinter{
    void print(Document &doc) override {
        cout<<"print"<<endl;
    }
};

struct Scanner:IScanner{
    void scan(Document &doc) override {
        cout<<"scan"<<endl;
    }
};

struct IMachine: IPrinter, IScanner{};

struct Machine: IMachine{
    IPrinter&printer;
    IScanner &scanner;

    Machine(IPrinter &printer, IScanner &scanner) : printer(printer), scanner(scanner) {}

    void print(Document &doc) override {
        printer.print(doc);

    }

    void scan(Document &doc) override {
        scanner.scan(doc);
    }
};



int main(){
    Printer p;
    Scanner s;
    Machine m(p, s);
    Document d{"document"};
    m.print(d);
    return 0;
}