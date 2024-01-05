#ifndef GENOTIPE_H
#define GENOTIPE_H
#include "MyUtility.h"
#include "../randomGenerator.h"
#include <array>
#include <vector>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cmath>
#include <bitset>
#include <string>
#include <assert.h>
#include <limits>



struct Gamet
{
    std::bitset<8> m_binGamet{};
    int m_manyGen{};
    char m_firstLetter{};
};

class Genotipe
{
private:
    std::bitset<16> m_binGen{};
    int m_manyGen{};
    char m_firstLetter{};

public:
    //setter
    Genotipe();
    Genotipe(const std::string& geneticCode);
    Genotipe(const std::string& geneticCode, int manyGen);
    Genotipe(const Gamet& g1, const Gamet& g2);
    ~Genotipe();
    std::bitset<16> encodeGenToBin(const std::string& geneticCode); //helper function
    static const Genotipe createRandGenotipe(int manyGen);

    //getter
    std::bitset<16> getBinGen()
    {
        return m_binGen;
    }
    std::bitset<16> getBinGen()const
    {
        return m_binGen;
    }
    int getManyGen()
    {
        return m_manyGen;
    }
    int getManyGen()const
    {
        return m_manyGen;
    }
    std::vector<Gamet> getAllPossibleGamet() const;
    std::vector<Gamet> getRandGamet(int manyGamet) const;
    Gamet getRandGamet() const;
    std::string getGeneticCode() const;
    long int allGametCount();
    //fusion
    Genotipe fusionGenotipe(const Genotipe& gen) const;
    //read genotipe
    int readUsingAtavisme() const;
    int readUsingKriptomeri() const;
    int readUsingEpistasisD() const;
    int readUsingEpistasisDR() const;
    int readUsingAbsKomplementer() const;
    int readUsingDualKomplementer() const;
    int readUsingIncompleteD() const;
    int readUsingPolimeri() const;

    friend std::ostream& operator<<(std::ostream& out, const Genotipe& gen);
};

struct GametMA
{
    std::vector<int> m_intGen{};
    char m_firstLetter{};
    int m_manyGen{};
    int m_manyAllel{};
};

class GenotipeManyAllel
{
public:
    std::vector<int> m_intGen{};
    char m_firstLetter{};
    int m_manyGen{};
    int m_manyAllel{};

public:
    GenotipeManyAllel();
    GenotipeManyAllel(const std::string& geneticCode, int manyAllel = 3);
    GenotipeManyAllel(const GametMA& g1, const GametMA& g2);
    ~GenotipeManyAllel();
    void encodeGenToVecInt(const std::string& geneticCode); //helper function
    std::string getGeneticCode() const;
    static const GenotipeManyAllel createRandGenotipe(int manyGen, int manyAllel);

    //getter
    std::vector<int> getIntGen()
    {
        return m_intGen;
    }
    std::vector<int> getIntGen()const
    {
        return m_intGen;
    }
    int getManyGen()
    {
        return m_manyGen;
    }
    int getManyGen()const
    {
        return m_manyGen;
    }
    int getManyAllel()
    {
        return m_manyAllel;
    }
    int getManyAllel()const
    {
        return m_manyAllel;
    }
    std::vector<GametMA> getAllPossibleGamet() const;
    std::vector<GametMA> getRandGamet(int manyGamet) const;
    GametMA getRandGamet() const;
    long int allGametCount();
    //fusion
    GenotipeManyAllel fusionGenotipe(const GenotipeManyAllel& gen) const;

    //read Method
    int readUsingFirstMA() const;
    friend std::ostream& operator<<(std::ostream& out, const GenotipeManyAllel& gen);

};



#endif // GENOTIPE_H
