//
//  GenomeMatcher.cpp
//  project4
//
//  Created by Ziying Yu on 3/8/19.
//  Copyright © 2019 Ziying Yu. All rights reserved.
//

#include "provided.h"
#include "Trie.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

//do:maintaining a library of genomes and allow to search through these genomes for DNA sequences
//   identify genomes in the library that are realted to a queried genome
//   must use Trie class to index and search through the DNA bases of the genomes in its library
class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    struct GenomeInformation
    {
        string m_name;
        int m_position;
        
        GenomeInformation(const string& name, const int& position): m_name(name), m_position(position) {}
        
        string getGenomeInformationName() const
        {
            return m_name;
        }
        
        int getGenomeInformationPos() const
        {
            return m_position;
        }
    };
    unordered_map<string, Genome> m_genomeunordered_map; // string getGenomeInformationName() matches the whole Genome class
    Trie<GenomeInformation> m_index;
};


GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
{
    m_minSearchLength = minSearchLength;
}

//todo: add the genome to a collection of genomes(a vector/list) held by the GenomeMatcher object
//      index the DNA sequences of the newly-added genome by adding every substring of length minSearchLength of that genome's DNA
//      sequence into a Trie maintained by the Matcher
void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    //ex. "ACTG"->"ACT", "CTG"
    m_genomeunordered_map.emplace(genome.name(), genome);
    
    int genomePos=0;
    int genomeLength = minimumSearchLength();
    string searchKey;
    for(; genomePos + genomeLength <= genome.length(); genomePos++)
    {
        genome.extract(genomePos, genomeLength, searchKey);
    
        //todo: insert it into the Trie by using the insert function in Trie class
        m_index.insert(searchKey, GenomeInformation( genome.name(), genomePos) );
    }
}


int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}


//todo: search all the genomes held in the library for a given DNA sequence or some SNiP of that sequence
//      tell at what offset(s) these located sequences were found in each genome
bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    //return false if attempting to search for shorter than minimumSearchLength() sequences
    if(fragment.size() < minimumLength || minimumLength < minimumSearchLength())
        return false;
    
    matches.clear();
    
    string fragKey;
    fragKey = fragment.substr(0, minimumSearchLength());
    //a vector of GenomeInformation that contains the minimumSearchLength searchKey
    //a collection of the candidated memberInfo that contain searchKey with exactMatchOnly
    //ex.ACGTTCCA key->"ACG", minimumSearchLength = 3,
    vector<GenomeInformation> memberInfo = m_index.find(fragKey,exactMatchOnly);
    
    //for each member, verify if the member satisfy the requirment:
    int const fragmentLength = int ( fragment.size() );
    
    
    unordered_map<string, DNAMatch> matcher;
    for ( vector<GenomeInformation>::iterator it=memberInfo.begin(); it!=memberInfo.end(); it++)
    {
        int pos = (*it).getGenomeInformationPos();
        string name = (*it).getGenomeInformationName();
        Genome memberGenome = m_genomeunordered_map.at(name);
        
        string memberSegment;
        int memberSegmentLength = int(min(fragmentLength, memberGenome.length()-pos));
        memberGenome.extract(pos, memberSegmentLength, memberSegment);
        
        //check fragment are valid first;
        
        if(fragment.size() ==0)
            return false;

        bool currentGenomeExactMatchOnly = exactMatchOnly;
        int exactMatchingLength = 1;
        int index=1;
        while(index < memberSegmentLength)
        {
            if(memberSegment[index]!=fragment[index] && currentGenomeExactMatchOnly == true)
                break;
            if(memberSegment[index]!=fragment[index] && currentGenomeExactMatchOnly == false)
            {
                currentGenomeExactMatchOnly = true;
            }
            exactMatchingLength ++;
            index ++;
        }
        
        int finalMatchingLength = exactMatchingLength;
        
        if ( finalMatchingLength < minimumLength )
            continue;
        else
        {
            DNAMatch newMatch;
            newMatch.genomeName = memberGenome.name();
            newMatch.length = finalMatchingLength;
            newMatch.position = pos;
            
            //already exist
            if (matcher.find(memberGenome.name()) != matcher.end())
            {
                DNAMatch oldMatch = matcher.at(memberGenome.name());
                if (oldMatch.length < finalMatchingLength)
                    matcher[memberGenome.name()] = newMatch;
            }
            else
            {
                matcher.emplace(memberGenome.name(), newMatch);
            }
        }
        
    }
    
    for(unordered_map<string, DNAMatch>:: iterator i=matcher.begin(); i != matcher.end(); i++)
    {
        matches.push_back(i->second);
    }
    
    if(matches.empty())
        return false;
    return true;
}


//todo: search the library to identify all genomes in the library whose DNA contains at least T% overlap with a given      Genome
//      threshold T is specified by the user
bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    //compares a passed-in query for a new organism against all genomes currently held in a GenomeMatcher object's library
    //pass back a vector of all genomes that contain ore than matchPercentThreshold
    
    results.clear();
    
    if(fragmentMatchLength < minimumSearchLength())
        return false;
    
    int i=0;
    vector<string> queryFrags;
    for(; i+fragmentMatchLength <= query.length(); i+=fragmentMatchLength)
    {
        string queryFrag;
        query.extract(i, fragmentMatchLength, queryFrag);
        queryFrags.push_back(queryFrag);
    }
    
    unordered_map<string, int> relatedGenomounordered_map;
    
    for(vector<string>::iterator it = queryFrags.begin(); it != queryFrags.end(); it++)
    {
        vector<DNAMatch> match;
        findGenomesWithThisDNA((*it), fragmentMatchLength,exactMatchOnly, match);
        for (vector<DNAMatch>::iterator i = match.begin(); i != match.end(); i++)
        {
            if( relatedGenomounordered_map.find( (*i).genomeName )!= relatedGenomounordered_map.end())
                relatedGenomounordered_map[(*i).genomeName]++;
            else
                relatedGenomounordered_map[(*i).genomeName] = 1;
        }
    }
    
    for(unordered_map<string, int>::iterator j = relatedGenomounordered_map.begin(); j != relatedGenomounordered_map.end(); j++)
    {
        //compute the percentage p
        int count = j->second;
        double p = 100 * count  / queryFrags.size();
        if(p >= matchPercentThreshold)
        {
            GenomeMatch objects;
            objects.genomeName = j->first;
            objects.percentMatch = p;
            results.push_back(objects);
                                        
        }
    }
                                    
    if(results.empty())
        return false;
    return true;
}


//******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}


int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

////do: forwards the call
bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}

