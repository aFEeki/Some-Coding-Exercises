//Alp Demir Ekinci 31935
#include "DNAseq.h"
DNAseq::DNAseq (const string& sequence) //parametric constructor
{
    length = sequence.length();
    narray = new Nucleotide[length];
    for (int i = 0; i < length; i++)
    {
        if (sequence[i] == 'A')
        {
            narray[i] = A;
        }
        else if (sequence[i] == 'C')
        {
            narray[i] = C;
        }
        else if (sequence[i] == 'G')
        {
            narray[i] = G;
        }
        else if (sequence[i] == 'T')
        {
            narray[i] = T;
        }
    }
}
DNAseq::DNAseq (const DNAseq& dcopy) //deep copy
{

    length = dcopy.length;
    narray = new Nucleotide[length];
    for (int i = 0; i < length; i++)
    {
        narray[i] = dcopy.narray[i];
    }
}
DNAseq::~DNAseq() //deconstructor
{
    length = 0;
    delete[] narray;
}
DNAseq DNAseq::operator * (int rhs) //multiplier
{
    DNAseq multiplied; //creates a new DNAseq object to be returned.
    int multipliedlength = rhs * length; //multiplies the length with rhs.
    multiplied.length = multipliedlength;
    multiplied.narray = new Nucleotide[multipliedlength]; //creates a new narray with the given length
    for (int i = 0; i < multipliedlength; i++) //goes through each index then matches them to multiplied narray
    {
        multiplied.narray[i] = narray[i % length];
    }
    return multiplied;
}
const DNAseq& DNAseq::operator = (const DNAseq& rhs) //taken from lab 7 recitation codes. With only the variable names changing.
{
    if (this != &rhs) // if they are not already equal
    {
        // first delete left hand side
        length = 0;
        delete[] narray;

        // create new vector for left hand side
        length = rhs.length;
        narray = new Nucleotide[length];

        for(int i = 0; i < length; i++)
        {
            narray[i] = rhs.narray[i]; // assign content
        }
    }

    return *this;
}
DNAseq DNAseq::operator - (const DNAseq & rhs) //takes out the first occurence of rhs from lhs
{
    DNAseq copyminus(*this); //creates a copy called copyminus
    bool leave = false; //boolean expression to be used to leave the while loop.
    for (int i = 0; i < length; i++)
    {
        int counter = 0;
        int j = i;
        while (j < length && counter < rhs.length && copyminus.narray[j] == rhs.narray[counter] && leave == false)
        {
            j += 1;
            counter += 1;
        }
        if (counter == rhs.length)
        {
            leave = true; //once it encounters a suitable match it changes the boolean value. Makes it not execute the prior while loop.
            for (int k = i; k < length - rhs.length; k++) //Assigns the values after the deleted part to where the deleted part is.
            {
                copyminus.narray[k] = copyminus.narray[k + rhs.length];
            }
            copyminus.length -= rhs.length; //shortens the length of the narray.
        }
    }
    return copyminus;
}
DNAseq DNAseq::operator + (const DNAseq& rhs)
{
    if (length == 0)
    {
        DNAseq incasecopy(rhs);
        return incasecopy;
    }
    DNAseq lol(*this);
    int counter = 0;
    int position = -1;
    bool leave = false;
    while (leave == false && counter < lol.length)
    {
        if (narray[counter] == rhs.narray[0])
        {
            position = counter;
            leave = true;
        }
        counter += 1;
    }
    if (position != -1) //if the first nucleotide of rhs exists in lhs.
    {
        int totallength = length + rhs.length;
        Nucleotide* totalsequence = new Nucleotide[totallength];
        for (int i = 0; i <= position; i++) //assigns the values in lhs before the insert position into a new sequence.
        {
            totalsequence[i] = lol.narray[i];
        }
        for (int i = 0; i < rhs.length; i++) //assigns the rhs to the new sequence.
        {
            totalsequence[position + i + 1] = rhs.narray[i];
        }
        for (int i = position + 1; i < length; i++) //assigns the values in lhs after the insert position.
        {
            totalsequence[i + rhs.length] = lol.narray[i];
        }
        lol.length = totallength;
        lol.narray = totalsequence;
        return lol;
    }
    else //if the first nucleotide in rhs does not exist in lhs
    {
        int totallength = length + rhs.length;
        Nucleotide* totalsequence = new Nucleotide[totallength];
        for (int i = 0; i < length; i++) //first adds the lhs
        {
            totalsequence[i] = narray[i];
        }
        for (int i = 0; i < rhs.length; i++) //appends the rhs to the lhs later.
        {
            totalsequence[i + length] = rhs.narray[i];
        }
        lol.length = totallength;
        lol.narray = totalsequence;
        return lol;
    }
}
DNAseq DNAseq:: operator += (const DNAseq & rhs)
{
    *this = *this + rhs;
    return *this;
}
bool operator <= (const DNAseq & lhs, const DNAseq & rhs) //subsequence checker.
{
    int lhslength = lhs.lengthgetter();
    const Nucleotide* lhsnarray = lhs.narraygetter();
    int rhslength = rhs.lengthgetter();
    const Nucleotide* rhsnarray = rhs.narraygetter();
    if (lhslength > rhslength) // It cannot be a subsequence if the lhs is larger than the rhs.
    {
        return false;
    }
    for (int i = 0; i < rhslength; i++) //goes through every index of rhs
    {
        int counter = 0;
        int j = i;
        while ((lhsnarray[counter] == rhsnarray[j]) && (counter < lhslength) && (j < rhslength)) //checks after i if there is a subsequence
        {
            j += 1;
            counter += 1;
        }
        if (counter == lhslength) //if there is it returns true.
        {
            return true;
        }
    }
    return false;
}
int operator % (const DNAseq & lhs, Nucleotide rhsnucleotide) //number of occurences checker
{
    int count = 0;
    int lhslength = lhs.lengthgetter(); //getter's used to acces class info.
    const Nucleotide* lhsnarray = lhs.narraygetter();
    for (int i = 0; i < lhslength; i++) //goes through each index to find the number of nucleotides
    {
        if (lhsnarray[i] == rhsnucleotide)
        {
            ++count;
        }
    }
    return count;
}
DNAseq operator ! (const DNAseq & dnasequence) //compliment
{
    DNAseq complement(dnasequence); //creates a copy of dnasequence named complement to be returned.
    for (int i = 0; i < complement.lengthgetter(); i++) //goes through each index.
    {
        if (complement.narraygetter()[i] == A) //changes the values with their complements.
        {
            complement.narraygetter()[i] = T;
        }
        else if (complement.narraygetter()[i] == T)
        {
            complement.narraygetter()[i] = A;
        }
        else if (complement.narraygetter()[i] == C)
        {
            complement.narraygetter()[i] = G;
        }
        else if (complement.narraygetter()[i] == G)
        {
            complement.narraygetter()[i] = C;
        }
    }
    return complement;
}
DNAseq operator + (Nucleotide lhsnucleotide, const DNAseq& rhs) //2nd overload of +.
{
    string totalsequence;
    if (lhsnucleotide == A) //takes the lhs nucleotide and assigns it to a string.
    {
        totalsequence += 'A';
    }
    else if (lhsnucleotide == C)
    {
        totalsequence += 'C';
    }
    else if (lhsnucleotide == G)
    {
        totalsequence += 'G';
    }
    else if (lhsnucleotide == T)
    {
        totalsequence += 'T';
    }
    for (int i = 0; i < rhs.lengthgetter(); ++i) //goes through each index in rhs and assigns them to the string that lhs is in.
    {
        if (rhs.narraygetter()[i] == A)
        {
            totalsequence += 'A';
        }
        else if (rhs.narraygetter()[i] == C)
        {
            totalsequence += 'C';
        }
        else if (rhs.narraygetter()[i] == G)
        {
            totalsequence += 'G';
        }
        else if (rhs.narraygetter()[i] == T)
        {
            totalsequence += 'T';
        }
    }
    DNAseq total(totalsequence); //creates a new object using the string.
    return total;
}
ostream& operator << (ostream& output, const DNAseq& rhs) //output
{
    for (int i = 0; i < rhs.lengthgetter(); i++)
    {
        if (rhs.narraygetter()[i] == A)
        {
            output << "A";
        }
        else if (rhs.narraygetter()[i] == C)
        {
            output << "C";
        }
        else if (rhs.narraygetter()[i] == G)
        {
            output << "G";
        }
        else if (rhs.narraygetter()[i] == T)
        {
            output << "T";
        }
    }
    return output;
}
/*
 #include "DNAseq.h"
 DNAseq::DNAseq (const string& sequence)
 {
     length = sequence.length();
     narray = new Nucleotide[length];
     for (int i = 0; i < length; i++)
     {
         if (sequence[i] == 'A')
         {
             narray[i] = A;
         }
         else if (sequence[i] == 'C')
         {
             narray[i] = C;
         }
         else if (sequence[i] == 'G')
         {
             narray[i] = G;
         }
         else if (sequence[i] == 'T')
         {
             narray[i] = T;
         }
     }
 }
 DNAseq::DNAseq (const DNAseq& dcopy)
 {

     length = dcopy.length;
     narray = new Nucleotide[length];
     for (int i = 0; i < length; i++)
     {
         narray[i] = dcopy.narray[i];
     }
 }
 DNAseq::~DNAseq()
 {
     length = 0;
     delete[] narray;
 }
 DNAseq DNAseq::operator * (int rhs)
 {
     DNAseq multiplied;
     int multipliedlength = rhs * length;
     multiplied.length = multipliedlength;
     multiplied.narray = new Nucleotide[multipliedlength];
     for (int i = 0; i < multipliedlength; i++)
     {
         multiplied.narray[i] = narray[i % length];
     }
     return multiplied;
 }
 const DNAseq& DNAseq::operator = (const DNAseq& rhs)
 {
     if (this != &rhs) // if they are not already equal
     {
         // first delete left hand side
         length = 0;
         delete[] narray;

         // create new vector for left hand side
         length = rhs.length;
         narray = new Nucleotide[length];

         for(int i = 0; i < length; i++)
         {
             narray[i] = rhs.narray[i]; // assign content
         }
     }

     return *this;
 }
 DNAseq DNAseq::operator - (const DNAseq & rhs)
 {
     DNAseq copyminus(*this);
     bool leave = false;
     for (int i = 0; i < length; i++)
     {
         int counter = 0;
         int j = i;
         while (j < length && counter < rhs.length && copyminus.narray[j] == rhs.narray[counter] && leave == false)
         {
             j += 1;
             counter += 1;
         }
         if (counter == rhs.length)
         {
             leave = true;
             for (int k = i; k < length - rhs.length; k++) // -i
             {
                 copyminus.narray[k] = copyminus.narray[k + rhs.length];
             }
             copyminus.length -= rhs.length;
         }
     }
     return copyminus;
 }
 DNAseq DNAseq::operator + (const DNAseq& rhs)
 {
     if (length == 0)
     {
         DNAseq incasecopy(rhs);
         return incasecopy;
     }
     DNAseq lol(*this);
     int counter = 0;
     int position = -1;
     bool leave = false;
     while (leave == false && counter < lol.length)
     {
         if (narray[counter] == rhs.narray[0])
         {
             position = counter;
             leave = true;
         }
         counter += 1;
     }
     if (position != -1)
     {
         int totallength = length + rhs.length;
         Nucleotide* totalsequence = new Nucleotide[totallength];
         for (int i = 0; i <= position; i++)
         {
             totalsequence[i] = lol.narray[i];
         }
         for (int i = 0; i < rhs.length; i++)
         {
             totalsequence[position + i + 1] = rhs.narray[i];
         }
         for (int i = position + 1; i < length; i++)
         {
             totalsequence[i + rhs.length] = lol.narray[i];
         }
         lol.length = totallength;
         lol.narray = totalsequence;
         return lol;
     }
     else
     {
         int totallength = length + rhs.length;
         Nucleotide* totalsequence = new Nucleotide[totallength];
         for (int i = 0; i < length; i++)
         {
             totalsequence[i] = narray[i];
         }
         for (int i = 0; i < rhs.length; i++)
         {
             totalsequence[i + length] = rhs.narray[i];
         }
         lol.length = totallength;
         lol.narray = totalsequence;
         return lol;
     }
 }
 DNAseq DNAseq:: operator += (const DNAseq & rhs)
 {
     *this = *this + rhs;
     return *this;
 }
 bool operator <= (const DNAseq & lhs, const DNAseq & rhs)
 {
     int lhslength = lhs.lengthgetter();
     const Nucleotide* lhsnarray = lhs.narraygetter();
     int rhslength = rhs.lengthgetter();
     const Nucleotide* rhsnarray = rhs.narraygetter();
     if (lhslength > rhslength)
     {
         return false;
     }
     for (int i = 0; i < rhslength; i++)
     {
         int counter = 0;
         int j = i;
         while ((lhsnarray[counter] == rhsnarray[j]) && (counter < lhslength) && (j < rhslength))
         {
             j += 1;
             counter += 1;
         }
         if (counter == lhslength)
         {
             return true;
         }
     }
     return false;
 }
 int operator % (const DNAseq & lhs, Nucleotide rhsnucleotide)
 {
     int count = 0;
     int lhslength = lhs.lengthgetter();
     const Nucleotide* lhsnarray = lhs.narraygetter();
     for (int i = 0; i < lhslength; i++)
     {
         if (lhsnarray[i] == rhsnucleotide)
         {
             ++count;
         }
     }
     return count;
 }
 DNAseq operator ! (const DNAseq & dnasequence)
 {
     DNAseq complement(dnasequence);
     for (int i = 0; i < complement.lengthgetter(); i++)
     {
         if (complement.narraygetter()[i] == A)
         {
             complement.narraygetter()[i] = T;
         }
         else if (complement.narraygetter()[i] == T)
         {
             complement.narraygetter()[i] = A;
         }
         else if (complement.narraygetter()[i] == C)
         {
             complement.narraygetter()[i] = G;
         }
         else if (complement.narraygetter()[i] == G)
         {
             complement.narraygetter()[i] = C;
         }
     }
     return complement;
 }
 DNAseq operator + (Nucleotide lhsnucleotide, const DNAseq& rhs)
 {
     string totalsequence;
     if (lhsnucleotide == A)
     {
         totalsequence += 'A';
     }
     else if (lhsnucleotide == C)
     {
         totalsequence += 'C';
     }
     else if (lhsnucleotide == G)
     {
         totalsequence += 'G';
     }
     else if (lhsnucleotide == T)
     {
         totalsequence += 'T';
     }
     for (int i = 0; i < rhs.lengthgetter(); ++i)
     {
         if (rhs.narraygetter()[i] == A)
         {
             totalsequence += 'A';
         }
         else if (rhs.narraygetter()[i] == C)
         {
             totalsequence += 'C';
         }
         else if (rhs.narraygetter()[i] == G)
         {
             totalsequence += 'G';
         }
         else if (rhs.narraygetter()[i] == T)
         {
             totalsequence += 'T';
         }
     }
     DNAseq total(totalsequence);
     return total;
 }
 ostream& operator << (ostream& output, const DNAseq& rhs)
 {
     for (int i = 0; i < rhs.lengthgetter(); i++)
     {
         if (rhs.narraygetter()[i] == A)
         {
             output << "A";
         }
         else if (rhs.narraygetter()[i] == C)
         {
             output << "C";
         }
         else if (rhs.narraygetter()[i] == G)
         {
             output << "G";
         }
         else if (rhs.narraygetter()[i] == T)
         {
             output << "T";
         }
     }
     return output;
 }


 */
