#ifndef OPTION_H
#define OPTION_H

#include <iostream>
#include <string>

using namespace std;
class Option
{
    friend ostream& operator<<(ostream&, const Option&);
    friend istream& operator>>(istream&, Option&);

    private:
        string code;
        string intitule;
        float prix;

    public:
        Option();
        Option(string, string, float);
        Option(const Option &);
        ~Option();

        string getCode() const;
        string getIntitule() const;
        float getPrix() const;

        void setCode(string);
        void setIntitule(string);
        void setPrix(float);
        
        void Affiche() const;

};

#endif
