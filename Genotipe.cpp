#include "Genotipe.h"
#include <cstdint>
#include "MyUtility.h"

Genotipe::Genotipe()
{
    //ctor
}

Genotipe::~Genotipe()
{
    //dtor
}


Genotipe::Genotipe(const std::string& geneticCode)
{
    m_manyGen = static_cast<int>(geneticCode.length())/2;
    m_binGen = encodeGenToBin(geneticCode);
    m_firstLetter = geneticCode[0];
    if(static_cast<int>(geneticCode[0])/32 == 3 )
    {
        //then this is lowerCase letter
        m_firstLetter -= 32;
    }
}

Genotipe::Genotipe(const std::string& geneticCode, int manyGen)
    :m_manyGen{manyGen}
{
    m_binGen = encodeGenToBin(geneticCode);
    m_firstLetter = geneticCode[0];
    if(static_cast<int>(geneticCode[0])/32 == 3 )
    {
        //then this is lowerCase letter
        m_firstLetter -= 32;
    }
}

Genotipe::Genotipe(const Gamet& g1, const Gamet& g2)
    :m_manyGen{g1.m_manyGen},
     m_firstLetter{g1.m_firstLetter}
{
    assert(g1.m_manyGen == g2.m_manyGen);
    auto bin1 = g1.m_binGamet;
    auto bin2 = g2.m_binGamet;

    for(int i = 0 ; i < m_manyGen; i++)
    {
        if(bin1.test(i) - bin2.test(i) == -1)
        {
            bin1.test(i)?m_binGen.set(2 * i):m_binGen.reset(2 * i);
            bin2.test(i)?m_binGen.set(2 * i + 1):m_binGen.reset(2 * i + 1);
        }
        else
        {
            bin2.test(i)?m_binGen.set(2 * i):m_binGen.reset(2 * i);
            bin1.test(i)?m_binGen.set(2 * i + 1):m_binGen.reset(2 * i + 1);
        }
    }
}

const Genotipe Genotipe::createRandGenotipe(int manyGen)
{
    assert("max gen is 8" && manyGen <= 8);

    int n{};
    std::bitset<8> binGamet{};

    n = getRand(pow(2,manyGen));
    binGamet = static_cast<std::bitset<8>>(n-1);
    Gamet gametA{binGamet, manyGen, 'A'};

    n = getRand(pow(2,manyGen));
    binGamet = static_cast<std::bitset<8>>(n-1);
    Gamet gametB{binGamet, manyGen, 'A'};

    return Genotipe(gametA, gametB);
}

std::bitset<16> Genotipe::encodeGenToBin(const std::string& geneticCode)
{
    unsigned int length{geneticCode.length()};
    // encode it to binary and store it to 16 bitset variable
    std::bitset<16> binCode{};
    for (unsigned int i = 0; i < length; i++)
    {
        // the 3rd column char code is capital later
        // and the 4th column char code is lower later
        // which its column have 32 diff symbol
        unsigned int n = floor(static_cast<unsigned int>(geneticCode[i]) / 32u);
        // we don't need to check the lower code because its encode
        // to zero(0)
        (n == 2)?binCode.set(length - 1u - i):binCode.reset(length -1u - i);
    }
    return binCode;
}

std::vector<Gamet> Genotipe::getAllPossibleGamet()const
{
    std::vector<Gamet> gamet{};
    for(int i{0}; i < pow(2, m_manyGen); i++)
    {
        std::bitset<8> binGamet{static_cast<unsigned int>(i)};
        std::bitset<8> isGenMatch{};
        for(int i{0}; i < m_manyGen; i++)
        {
            if((binGamet.test(i) == m_binGen.test(2*i+1)) || (binGamet.test(i) == m_binGen.test(2*i)))
                isGenMatch.set(i);
        }

        if(isGenMatch == bitTrue(m_manyGen))
        {
            Gamet newGamet{binGamet, m_manyGen, m_firstLetter};
            gamet.push_back(newGamet);
        }
    }

    return gamet;
}

std::vector<Gamet> Genotipe::getRandGamet(int manyGamet)const
{
    std::vector<Gamet> allGamet{getAllPossibleGamet()};

    std::vector<Gamet> randGamet{};
    for(int i{0}; i < manyGamet; i++)
    {
        int numb = getRand(allGamet.size()) - 1;
        randGamet.push_back(allGamet.at(numb));
    }
    return randGamet;
}

Gamet Genotipe::getRandGamet() const
{
    return (getRandGamet(1)).at(0);
}

std::string Genotipe::getGeneticCode() const
{
    std::string genCode {};
    for(int i = 0; i < m_manyGen; i++)
    {
        int binPos = 2 * (m_manyGen - i - 1);
        (m_binGen.test(binPos + 1))?(genCode += m_firstLetter + i):(genCode += m_firstLetter + i + 32);
        (m_binGen.test(binPos))?(genCode += m_firstLetter + i):(genCode += m_firstLetter + i + 32);
    }
    return genCode;
}

long int Genotipe::allGametCount()
{
    int heterozygot{0};

    for(int i = 1; i <= m_manyGen; i++)
    {
        if(m_binGen.test(2*i-1) != m_binGen.test(2*i-2))
            heterozygot++;
    }
    return pow(2,heterozygot);
}

Genotipe Genotipe::fusionGenotipe(const Genotipe& gen) const
{
    assert(m_manyGen == gen.m_manyGen);

    Gamet g1{this->getRandGamet()};
    Gamet g2{gen.getRandGamet()};

    return Genotipe(g1, g2);
}


//read function
int Genotipe::readUsingAtavisme() const
{
    int typeNumb{static_cast<int>(pow(2, m_manyGen)) - 1};
    for(int i{m_manyGen-1}; i >= 0; i--)
    {
        if(m_binGen.test(2u*i+1u) || m_binGen.test(2u*i))
        {
            typeNumb -= pow(2, i);
        }
    }
    return typeNumb;
}

//same method with epistasis resesif
int Genotipe::readUsingKriptomeri() const
{
    //set numb to last numb n-1 = 2^(t-1)
    int firstGen{m_manyGen-1};
    long int typeNumb{static_cast<long int>(pow(2, firstGen))};

    //read first gen
    if(!(m_binGen.test(2u*firstGen + 1) || m_binGen.test(2u*firstGen)))
    {
        return typeNumb;
    }
    else
    {
        typeNumb -= 1;
    }

    //read 2nd gen and other
    for(int i{firstGen-1}; i >= 0; i--)
    {
        if(m_binGen.test(2u*i+1u) || m_binGen.test(2u*i))
        {
            //dominan
            typeNumb -= pow(2, i);
        }
    }
    return typeNumb;
}

int Genotipe::readUsingEpistasisD() const
{
    //epistasis dominan
    //set numb to last-1 numb n-1 = 2^(t-1)
    int firstGen{m_manyGen-1};
    long int typeNumb{static_cast<long int>(pow(2, firstGen))};

    //read first gen
    if(m_binGen.test(2u*firstGen + 1) || m_binGen.test(2u*firstGen))
        return 0;

    //read 2nd gen and other
    for(int i{firstGen-1}; i >= 0; i--)
    {
        if(m_binGen.test(2u*i+1u) || m_binGen.test(2u*i))
            typeNumb -= pow(2, i);
    }
    return typeNumb;
}

int Genotipe::readUsingEpistasisDR() const
{
    int typeNumb{readUsingEpistasisD()};
    //if typeNumb is last gen then return 0
    return (typeNumb == pow(2, m_manyGen-1))? 0:typeNumb;
}

int Genotipe::readUsingAbsKomplementer() const
{
    //komplementer absolute
    //hanya ada 2 type(muncul(0) dan tidak muncul(1))
    for(int i{m_manyGen-1}; i >= 0; i--)
    {
        if(!(m_binGen.test(2u*i+1u) || m_binGen.test(2u*i)))
        {
            return 1;
        }
    }
    return 0;
}

int Genotipe::readUsingDualKomplementer() const
{
    assert("m_manyGen must be even numb" && m_manyGen % 2 == 0);
    //dual gen komplementer
    int typeNumb{static_cast<int>(pow(2, m_manyGen/2)-1)};
    for(int i{m_manyGen-1}; i >= 0;)
    {
        int fenotip{(i+1)/2};
        bool noHomoRese{true};  //no homozygot resesif
        for(int n{0}; n < 2; n++) //cek 2 gen
        {
            noHomoRese = noHomoRese && (m_binGen.test(2u*i+1) || m_binGen.test(2u*i));
            i--;
        }

        if(noHomoRese)
            typeNumb -= pow(2, fenotip - 1);
    }
    return typeNumb;
}

int Genotipe::readUsingIncompleteD() const
{
    int typeNumb{static_cast<int>(pow(3, m_manyGen)) - 1};
    for(int i{m_manyGen-1}; i >= 0; i--)
    {
        if(m_binGen.test(2u*i+1u) && m_binGen.test(2u*i))
        {
            typeNumb -= 2*pow(3, i);
        }
        else if(m_binGen.test(2u*i+1u) || m_binGen.test(2u*i))
        {
            typeNumb -= pow(3, i);
        }
    }
    return typeNumb;
}

int Genotipe::readUsingPolimeri() const
{
    int dominan{static_cast<int>(m_binGen.count())};
    int percent = 100 * dominan / (m_manyGen*2);
    return percent;
}

std::ostream& operator<<(std::ostream& out, const Genotipe& gen)
{
    out << gen.getGeneticCode() << '\n';
    return out;
}

///////////////////////////////
///////Genotipe Multiple Allel
GenotipeManyAllel::GenotipeManyAllel()
{
}

GenotipeManyAllel::~GenotipeManyAllel()
{

}

GenotipeManyAllel::GenotipeManyAllel(const std::string& geneticCode, int manyAllel)
    :m_manyAllel{manyAllel}
{
    encodeGenToVecInt(geneticCode);
    m_firstLetter = geneticCode[0];
    if(static_cast<int>(geneticCode[0])/32 == 3 )
        m_firstLetter -= 32;
    m_manyGen = static_cast<int>(m_intGen.size()) / 2;
}

GenotipeManyAllel::GenotipeManyAllel(const GametMA& g1, const GametMA& g2)
    :m_manyGen{g1.m_manyGen},
     m_firstLetter{g1.m_firstLetter},
     m_manyAllel{g1.m_manyAllel}
{
    assert(g1.m_manyGen == g2.m_manyGen);

    auto intGen1{g1.m_intGen};
    auto intGen2{g2.m_intGen};

    for(int i{0}; i < m_manyGen; i++)
    {
        m_intGen.push_back(intGen1.at(i));
        m_intGen.push_back(intGen2.at(i));
        if(intGen1.at(i) < intGen2.at(i))
            std::swap(m_intGen.at(2*i), m_intGen.at(2*i+1));
    }

}
void GenotipeManyAllel::encodeGenToVecInt(const std::string& geneticCode) //helper function
{
    for(int i{0}; i < static_cast<int>(geneticCode.length()); i++)
    {
        int n = floor(static_cast<int>(geneticCode[i]) / 32);
        if(n == 3)
        {
            //gen resesif
            m_intGen.push_back(0);
        }
        else if(n == 2)
        {
            //gen dominan
            int allelType{static_cast<int>(geneticCode[++i]) - 48};
            allelType += 1;
            m_intGen.push_back(allelType);
        }
    }
}

std::string GenotipeManyAllel::getGeneticCode() const
{
    std::string genStr{};
    for(int i{0}; i < m_manyGen; i++)
    {
        for(int n{2*i}; n < 2*i+2; n++)
        {
            if(m_intGen[n])
            {
                genStr += m_firstLetter + i;
                genStr += m_intGen[n]-1+48;
            }
            else
            {
                genStr += m_firstLetter + i + 32;
            }
        }
    }
    return genStr;
}

const GenotipeManyAllel GenotipeManyAllel::createRandGenotipe(int manyGen, int manyAllel)
{
    std::vector<int> intGen{};

    intGen.push_back(getRand(manyAllel)-1);
    for(int i{0}; i < manyGen-1; i++)
        intGen.push_back(getRand(2)-1);
    GametMA gametA{intGen, 'A', manyGen, manyAllel};

    intGen.clear();

    intGen.push_back(getRand(manyAllel)-1);
    for(int i{0}; i < manyGen-1; i++)
        intGen.push_back(getRand(2)-1);
    GametMA gametB{intGen, 'A', manyGen, manyAllel};

    return GenotipeManyAllel(gametA, gametB);
}

std::vector<GametMA> GenotipeManyAllel::getAllPossibleGamet() const
{
    std::vector<GametMA> gamet{};
    for(int i{0}; i < pow(2, m_manyGen); i++)
    {
        std::bitset<8> binGamet{static_cast<unsigned int>(i)};
        bool isGenMatch{true};
        for(int i{0}; i < m_manyGen; i++)
        {
            if(binGamet.test(i))
            {
                if(m_intGen.at(2*i) == m_intGen.at(2*i+1))
                {
                    isGenMatch = false;
                    break;
                }
            }
        }

        if(isGenMatch)
        {
            std::vector<int> intGen{};
            for(int i{0}; i < m_manyGen; i++)
            {
                binGamet.test(i)? intGen.push_back(m_intGen.at(2*i+1)):
                intGen.push_back(m_intGen.at(2*i));
            }
            GametMA newGamet{intGen, m_firstLetter, m_manyGen, m_manyAllel};
            gamet.push_back(newGamet);
        }
    }

    return gamet;
}

std::vector<GametMA> GenotipeManyAllel::getRandGamet(int manyGamet) const
{
    std::vector<GametMA> allGamet{getAllPossibleGamet()};

    std::vector<GametMA> randGamet{};
    for(int i{0}; i < manyGamet; i++)
    {
        int numb = getRand(allGamet.size()) - 1;
        randGamet.push_back(allGamet.at(numb));
    }
    return randGamet;
}

GametMA GenotipeManyAllel::getRandGamet() const
{
    return (getRandGamet(1)).at(0);
}

long int GenotipeManyAllel::allGametCount()
{
    int heterozygot{0};

    for(int i = 1; i <= m_manyGen; i++)
    {
        if(m_intGen.at(2*i-1) != m_intGen.at(2*i-2))
            heterozygot++;
    }
    return pow(2,heterozygot);
}

GenotipeManyAllel GenotipeManyAllel::fusionGenotipe(const GenotipeManyAllel& genMA) const
{
    assert(m_manyGen == genMA.getManyGen());

    GametMA g1{this->getRandGamet()};
    GametMA g2{genMA.getRandGamet()};

    return GenotipeManyAllel(g1, g2);
}

int GenotipeManyAllel::readUsingFirstMA() const
{
    int typeNumb{static_cast<int>(pow(2, m_manyGen+1))-1};

    //cek first MA gen
    for(int i{0}; i < m_manyAllel; i++)
    {
        if(m_intGen.at(0) == i)
        {
            typeNumb -= i*(pow(2, m_manyGen-1));
            if(i >= 2)
            {
                //then cek next allel
                if(m_intGen.at(1) == 1)
                    typeNumb -= pow(2, m_manyGen-1);
            }
            break; // we done reducing
        }
    }
    //cek next gen
    for(int i{1}; i < m_manyGen; i++)
    {
        int reduce{m_manyGen-i-1};
        if(m_intGen.at(2*i+1) || m_intGen.at(2*i))
        {
            typeNumb -= pow(2, reduce);
        }
    }

    return typeNumb;
}

std::ostream& operator<<(std::ostream& out, const GenotipeManyAllel& gen)
{
    out << gen.getGeneticCode() << '\n';
    for(auto allel : gen.m_intGen)
    {
        out << allel;
    }
    out << '\n' << "First Letter = " << gen.m_firstLetter << '\n';
    out << "Many Gen = " << gen.m_manyGen << '\n';
    out << "Many Allel = " << gen.m_manyAllel << '\n';
    return out;
}
