//
//  DNAseq.h
//  CS 204 HW4
//
//  Created by Alp Demir Ekinci on 9.04.2024.
//

#ifndef DNAseq_h
#define DNAseq_h

#include <string>
#include <iostream>
#include <ostream>
using namespace std;
enum Nucleotide {A, C, G, T};

class DNAseq
{
    private:
        int length;
        Nucleotide* narray;
    public:
        DNAseq () : length(0), narray(nullptr){}; //default constructor
        DNAseq(const string& sequence); //parametric constructor
        DNAseq (const DNAseq& dcopy); //deep copy
        ~DNAseq(); //deconstructor
        int lengthgetter() const //lengthgetter (as its name might suggest.
        {
            return length;
        }
        const Nucleotide* narraygetter() const //likewise narray getter
        {
            return narray;
        }
        Nucleotide* narraygetter() //another narray getter that is not a const val.
        {
            return narray;
        }
        //following are the member functions.
        DNAseq operator * (int rhs);
        const DNAseq& operator = (const DNAseq & rhs);
        DNAseq operator - (const DNAseq & rhs);
        DNAseq operator + (const DNAseq & rhs);
        DNAseq operator += (const DNAseq & rhs);
};
//following are free functions.
bool operator <= (const DNAseq & lhs, const DNAseq & rhs);
int operator % (const DNAseq & lhs, Nucleotide rhsnucleotide);
DNAseq operator ! (const DNAseq & dnasequence);
DNAseq operator + (Nucleotide lhsnucleotide, const DNAseq& rhs);
ostream& operator << (ostream& output, const DNAseq& rhs);
#endif /* DNAseq_h */
