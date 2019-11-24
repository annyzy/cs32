//
//  Genome.cpp
//  project4
//
//  Created by Ziying Yu on 3/8/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream> //std::ifstream, the input file stream class, and std::ofstream, the output file stream class

using namespace std;

//todo: may use any STL containers
class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_nm;
    string m_sequence;
    int m_length;
    
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
{
    m_nm = nm;
    m_sequence = sequence;
    m_length = int (sequence.size());
}

//todo: load genome data which contains both name and DNA sequences, return a vector of Genome objects
//details: repeatedly
bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string data;
    string name="";
    string dna ="";
    bool firstLine = true;
    bool lastLineIsGenome = true;
    while (getline(genomeSource, data))
    {
        if (data.at(0) == '>') { // this line is name
            if (firstLine)
                firstLine = false;
            if (!lastLineIsGenome)
                return false;
            
            if( dna!="" && name!="") {
                genomes.push_back(Genome(name, dna));
                dna = "";
                name = "";
            }
            name = data.substr(1);
            lastLineIsGenome = false;
        }
        else {  // this line is not name
            if (firstLine)
                return false;
            char ch;
            for (int i = 0; i < data.size(); i++)
            {
                ch = data[i];
                if (ch == 'A' || ch == 'T' || ch == 'G' || ch == 'C' || ch == 'N')
                    dna += ch;
                else
                    return false;
            }
            lastLineIsGenome = true;
        }
    }
    
    if( dna!="" && name!="")
        genomes.push_back(Genome(name, dna));
    
    return true;
}

//return completely length of the DNA sequence, specifically the total count of As, Cs, Ts (and Ns) found in the sequence held by the object
int GenomeImpl::length() const
{
    //require O(1); instead of return sequence.size() which requires O(N);
    return m_length;
}

//return the name of the genome
string GenomeImpl::name() const
{
    return m_nm;
}


//return true if successfully extracts a string of the specified length
bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    
    if( position + length <= m_length )
    {
        //set fragment to a copy of a portion of the Genome's DNA sequence
        fragment = m_sequence.substr(position, length);
        return true;
    }
    return false;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

//when called, it forwards that call to the name() function in the GenomeLmpl class
string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}

