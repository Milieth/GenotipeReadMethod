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
#include "MyUtility.h"
#include "Genotipe.h"
#include "randomGenerator.h"

std::string getGenCodeFromUser()
{
    std::string geneticCode{};
    std::getline(std::cin >> std::ws,geneticCode);

    return geneticCode;
}

class BettaConst
{
public:
    //many layer do betta have
    static constexpr int maxLayerCount{5};
    static constexpr int bodyLayerCount{5};
    static constexpr int otherPartLayerCount{4};

    static constexpr int bodyIridLayer{4};
    static constexpr int otherPartIridLayer{3};

};

class BettaType
{
public:
    enum class Part
    {
        analFin,
        tail,
        ventral,
        dorsal,
        body,
        pectoral,

        max_part
    };

    enum class Sex
    {
        betina,
        jantan,

        max_sex
    };

    enum class Ventral
    {
        common,
        jabot,
        mini,

        max_ventral
    };

    enum class Tail
    {
        crown,
        comb,
        feather,
        halfSun,
        hm,
        ohm,
        plakatHM,
        rose,
        delta,
        sDelta,
        plakat,
        doubleDelta,
        round,
        spade,
        veil,
        doubleRound,

        max_tail
    };

    enum class Pectoral
    {
        dumbo,
        common,

        max_pectoral
    };

    enum  class Body
    {
        betinaG,
        betinaM,
        betinaS,
        jantanG,
        jantanM,
        jantanS,

        max_body

    };

    enum class Anal
    {
        common,
        crownA,
        crownB,
        halfSun,
        comb,
        heavyA,
        heavyB,
        trapesium,

        max_anal
    };

    enum class Dorsal
    {
        common,
        crownA,
        crownB,
        halfSun,
        comb,
        heavyA,
        heavyB,
        lightA,
        lightB,

        max_dorsal
    };

    enum class IridCol
    {
        white,
        green,
        silver,
        gold,
        teal,
        torquise,
        purple,

        max_iridCol
    };

    BettaType();
    virtual ~BettaType();
};

class BettaPart
{
protected:
    Genotipe m_gen{};
    int m_type{};
public:
    BettaPart() {}
    virtual ~BettaPart() {}

    virtual const Genotipe& getGenotipe() const
    {
        return m_gen;
    }

    virtual std::string getName() const = 0;
};

//use genMA
class Tail: public BettaPart
{
private:
    GenotipeManyAllel m_genMA{};
public:
    Tail(const GenotipeManyAllel& gen)
        :m_genMA{gen}
    {
        m_type = gen.readUsingFirstMA();
    }
    Tail() {}
    virtual ~Tail() {}

    const GenotipeManyAllel& getGenotipeMA()
    {
        return m_genMA;
    }

    static const Tail createRand()
    {
        return Tail(GenotipeManyAllel::createRandGenotipe(3, 3));
    }

    const Tail fusionGenotipe(const Tail& tail) const
    {
        return Tail(m_genMA.fusionGenotipe(tail.m_genMA));
    }

    std::string getName() const override
    {
        switch(static_cast<BettaType::Tail>(m_type))
        {
        case BettaType::Tail::crown:
            return "Crown";
        case BettaType::Tail::halfSun:
            return "Halfsun";
        case BettaType::Tail::feather:
            return "Feather";
        case BettaType::Tail::comb:
            return "Comb";
        case BettaType::Tail::hm:
            return "Half Moon";
        case BettaType::Tail::ohm:
            return "Over Half Moon";
        case BettaType::Tail::plakatHM:
            return "Plakat HM";
        case BettaType::Tail::rose:
            return "Rose";
        case BettaType::Tail::delta:
            return "Delta";
        case BettaType::Tail::sDelta:
            return "Super Delta";
        case BettaType::Tail::plakat:
            return "Plakat";
        case BettaType::Tail::doubleDelta:
            return "Double Delta";
        case BettaType::Tail::round:
            return "Round";
        case BettaType::Tail::spade:
            return "Spade";
        case BettaType::Tail::veil:
            return "Veil";
        case BettaType::Tail::doubleRound:
            return "Double Round";
        default:
            return "UNDEFINED";
        }
    }
};

class Dorsal: public BettaPart
{
public:
    Dorsal(const Genotipe& gen)
    {
        m_gen = gen;
        m_type = gen.readUsingEpistasisD();
    }
    Dorsal() {}
    virtual ~Dorsal() {}

    static const Dorsal createRand()
    {
        return Dorsal(Genotipe::createRandGenotipe(4));
    }

    const Dorsal fusionGenotipe(const Dorsal& dorsal) const
    {
        return Dorsal(m_gen.fusionGenotipe(dorsal.m_gen));
    }

    std::string getName() const override
    {
        switch(static_cast<BettaType::Dorsal>(m_type))
        {
        case BettaType::Dorsal::common:
            return "Common";
        case BettaType::Dorsal::crownA:
            return "Crown A";
        case BettaType::Dorsal::crownB:
            return "Crown B";
        case BettaType::Dorsal::halfSun:
            return "Halfsun";
        case BettaType::Dorsal::comb:
            return "Comb";
        case BettaType::Dorsal::heavyA:
            return "Heavy A";
        case BettaType::Dorsal::heavyB:
            return "Heavy B";
        case BettaType::Dorsal::lightA:
            return "Light A";
        case BettaType::Dorsal::lightB:
            return "Light B";
        default:
            return "UNDEFINED";
        }
    }
};

class AnalFin: public BettaPart
{
public:
    AnalFin(const Genotipe& gen)
    {
        m_gen = gen;
        m_type = gen.readUsingEpistasisDR();
    }
    AnalFin() {}
    virtual ~AnalFin() {}

    static const AnalFin createRand()
    {
        return AnalFin(Genotipe::createRandGenotipe(4));
    }

    const AnalFin fusionGenotipe(const AnalFin& analfin) const
    {
        return AnalFin(m_gen.fusionGenotipe(analfin.m_gen));
    }

    std::string getName() const override
    {
        switch(static_cast<BettaType::Anal>(m_type))
        {
        case BettaType::Anal::common:
            return "Common";
        case BettaType::Anal::crownA:
            return "Crown A";
        case BettaType::Anal::crownB:
            return "Crown B";
        case BettaType::Anal::halfSun:
            return "Halfsun";
        case BettaType::Anal::comb:
            return "Comb";
        case BettaType::Anal::heavyA:
            return "Heavy A";
        case BettaType::Anal::heavyB:
            return "Heavy B";
        case BettaType::Anal::trapesium:
            return "Trapesium";
        default:
            return "UNDEFINED";
        }
    }
};

class Ventral: public BettaPart
{
public:
    Ventral(const Genotipe& gen)
    {
        m_gen = gen;
        m_type = gen.readUsingKriptomeri();
    }
    Ventral() {}
    virtual ~Ventral() {}

    static const Ventral createRand()
    {
        return Ventral(Genotipe::createRandGenotipe(2));
    }

    const Ventral fusionGenotipe(const Ventral& ventral) const
    {
        return Ventral(m_gen.fusionGenotipe(ventral.m_gen));
    }

    std::string getName()const override
    {
        switch(static_cast<BettaType::Ventral>(m_type))
        {
        case BettaType::Ventral::common:
            return "Common";
        case BettaType::Ventral::jabot:
            return "Jabot";
        case BettaType::Ventral::mini:
            return "Mini";
        default:
            return "UNDEFINED";
        }
    }
};

class Pectoral: public BettaPart
{
public:
    Pectoral(const Genotipe& gen)
    {
        m_gen = gen;
        m_type = gen.readUsingAbsKomplementer();
    }
    Pectoral() {}
    virtual ~Pectoral() {}

    static const Pectoral createRand()
    {
        return Pectoral(Genotipe::createRandGenotipe(5));
    }

    const Pectoral fusionGenotipe(const Pectoral& pectoral) const
    {
        return Pectoral(m_gen.fusionGenotipe(pectoral.m_gen));
    }

    std::string getName() const override
    {
        switch(static_cast<BettaType::Pectoral>(m_type))
        {
        case BettaType::Pectoral::dumbo:
            return "Dumbo Ear";
        case BettaType::Pectoral::common:
            return "Common";
        default:
            return "UNDEFINED";
        }
    }
};

//contain sexGen
class Body: public BettaPart
{
private:
    BettaType::Sex m_sexType{};
    Genotipe m_sexGen{};
public:
    Body(const Genotipe& body, const Genotipe& sex)
        :m_sexGen{sex}
    {
        m_gen = body;
        m_sexType = static_cast<BettaType::Sex>(sex.readUsingAtavisme());
        m_type = body.readUsingIncompleteD();
        if(m_sexType == BettaType::Sex::jantan)
            m_type += 3;
    }
    Body() {}
    virtual ~Body() {}

    static const Body createRand(BettaType::Sex sexType)
    {
        Genotipe sexGen{};
        if(sexType == BettaType::Sex::jantan)
        {
            sexGen = Genotipe("aa");
        }
        else
        {
            bool isHeterozygot{static_cast<bool>(getRand(2)-1)};
            if(isHeterozygot)
            {
                sexGen = Genotipe("Aa");
            }
            else
            {
                sexGen = Genotipe("AA");
            }
        }

        return Body(Genotipe::createRandGenotipe(1), sexGen);
    }

    const Body fusionGenotipe(const Body& body) const
    {
        auto newBodyGen{m_gen.fusionGenotipe(body.m_gen)};
        auto newSexGen{m_sexGen.fusionGenotipe(body.m_sexGen)};
        return Body(newBodyGen, newSexGen);
    }

    const Genotipe& getSexGenotipe()
    {
        return m_sexGen;
    }
    const BettaType::Sex getSexType()
    {
        return m_sexType;
    }

    std::string getName() const override
    {
        switch(static_cast<BettaType::Body>(m_type))
        {
        case BettaType::Body::jantanG:
            return "Giant Male";
        case BettaType::Body::jantanM:
            return "Plakat Male";
        case BettaType::Body::jantanS:
            return "Common Male";
        case BettaType::Body::betinaG:
            return "Giant Female";
        case BettaType::Body::betinaM:
            return "Plakat Female";
        case BettaType::Body::betinaS:
            return "Common Female";
        default:
            return "UNDEFINED";
        }
    }
};

class Betta
{
private:
    Tail m_tail{};
    Body m_body{};
    Pectoral m_pectoral{};
    Ventral m_ventral{};
    AnalFin m_analfin{};
    Dorsal m_dorsal{};
    BettaType::Sex m_sexType{};
public:
    Betta(AnalFin a,Body b, Dorsal d, Pectoral p, Tail t, Ventral v, BettaType::Sex s)
        :m_tail{t},
         m_body{b},
         m_pectoral{p},
         m_ventral{v},
         m_analfin{a},
         m_dorsal{d},
         m_sexType{s}
    {
    }
    Betta() {}
    ~Betta() {}

    void printFullName()
    {
        std::cout << "\n->" << m_body.getName() << " Betta-"
                  << m_ventral.getName()  << " Ventral-"
                  << m_pectoral.getName() << " Pectoral-"
                  << m_dorsal.getName()   << " Dorsal-\n"
                  << m_analfin.getName()  << " Analfin-"
                  << m_tail.getName()     << " Tail";
    }

    void print()
    {
        std::cout << '\n' <<"[Betta Type]" << '\n';
        std::cout << "Jenis Kelamin dan Body \t: " << m_body.getName() << " (" << m_body.getGenotipe().getGeneticCode() << ", " << m_body.getSexGenotipe().getGeneticCode() << ')' <<'\n';
        std::cout << "Ventral \t\t: " << m_ventral.getName() << " Ventral (" << m_ventral.getGenotipe().getGeneticCode() << ')' << '\n';
        std::cout << "Pectoral \t\t: " << m_pectoral.getName() << " Pectoral (" << m_pectoral.getGenotipe().getGeneticCode() << ')' << '\n';
        std::cout << "Dorsal \t\t\t: " << m_dorsal.getName() << " Dorsal (" << m_dorsal.getGenotipe().getGeneticCode() << ')' << '\n';
        std::cout << "Analfin \t\t: " << m_analfin.getName() << " Analfin (" << m_analfin.getGenotipe().getGeneticCode() << ')' << '\n';
        std::cout << "Tail \t\t\t: " << m_tail.getName() << " Tail (" << m_tail.getGenotipeMA().getGeneticCode() << ')' << '\n';
        //std::cout << "Full Name: ";
        //printFullName();
        std::cout <<'\n';
    }

    static Betta createRand(BettaType::Sex sexType)
    {
        auto a{AnalFin::createRand()};
        auto b{Body::createRand(sexType)};
        auto d{Dorsal::createRand()};
        auto p{Pectoral::createRand()};
        auto t{Tail::createRand()};
        auto v{Ventral::createRand()};
        auto s{sexType};

        return Betta(a, b, d, p, t, v, s);
    }

    static Betta getBettaFromUser()
    {

        std::cout << "->Enter Normal Genetic code (1 Gen) :";
        Genotipe sexGen{getGenCodeFromUser()};
        BettaType::Sex s{static_cast<BettaType::Sex>(sexGen.readUsingAtavisme())};
        std::cout << "->Enter Normal Genetic code (2 Gen) :";
        Ventral v{getGenCodeFromUser()};
        std::cout << "->Enter Normal Genetic code (4 Gen) :";
        Dorsal d{getGenCodeFromUser()};
        std::cout << "->Enter Normal Genetic code (4 Gen) :";
        AnalFin a{getGenCodeFromUser()};
        std::cout << "->Enter Normal Genetic code (5 Gen) :";
        Pectoral p{getGenCodeFromUser()};
        std::cout << "->Enter Normal Genetic code (1 Gen) :";
        Body b{getGenCodeFromUser(), sexGen};
        std::cout << "->Enter Multiple Alel(a,A0,A1) Genetic code (3 Gen)\n";
        std::cout << "only the first gen si MA e.g. [A1A0B0bC0c] : ";
        Tail t{getGenCodeFromUser()};

        return Betta(a, b, d, p, t, v, s);
    }

    static Betta breeding(const Betta& m, const Betta& f)
    {
        assert("must be male and female betta" && (m.m_sexType != f.m_sexType));

        auto a{m.m_analfin.fusionGenotipe(f.m_analfin)};
        auto b{m.m_body.fusionGenotipe(f.m_body)};
        auto d{m.m_dorsal.fusionGenotipe(f.m_dorsal)};
        auto p{m.m_pectoral.fusionGenotipe(f.m_pectoral)};
        auto t{m.m_tail.fusionGenotipe(f.m_tail)};
        auto v{m.m_ventral.fusionGenotipe(f.m_ventral)};
        auto s{b.getSexType()};

        return Betta(a, b, d, p, t, v, s);
    }

    static std::vector<Betta> breedBettaInPrompt(const Betta& p1, const Betta& p2, int manyChild = 10)
    {
        std::cout << "Okay, Breeding " << manyChild << " Betta\n";
        std::cout << "Please wait. .. " << '\n';
        Timer t;
        std::vector<Betta> children{};
        for(int i{0}; i < manyChild; i++)
        {
            children.push_back(Betta::breeding(p1, p2));
        }
        std::cout << "Done, Breeding Time :" << t.elapsed() << " seconds" << '\n';
        std::cout << "\n------------------" << '\n';
        std::cout << "Here is the result :" << '\n';
        std::cout << "------------------" << '\n';
        for(int i{0}; i < manyChild; i++)
        {
            std::cout << "\nChild #" << i+1;
            children.at(i).print();
        }

        std::cout << "\nSUMMARY RESULT :" << '\n';
        for(auto c : children)
        {
            c.printFullName();
            std::cout << '\n';
        }

        return children;
    }
};

bool askUserApproval()
{
    char ch{};
    std::cin >> ch;

    bool approval{true};
    if(ch == 'y' || ch == 'Y')
    {
        approval = true;
    }
    else if(ch == 'n' || ch == 'N')
    {
        approval = false;
    }

    return approval;
}

void testBreeding()
{
    bool isManual{true};
    int generation{0};  //using generation to control flow
    int manyChild{20};
    std::vector<Betta> children{};
    Betta parent1{};
    Betta parent2{};
    while(true)
    {
        if(isManual)
        {
            std::cout << "Breeding Betta Genotipe Function()" << '\n';
            std::cout << "----------------------------------" << '\n';
            std::cout << "Do you want to input manually? if no we will create it for you randomly(y/n)" << '\n';
            if(askUserApproval())
            {
                std::cout << "Please input first parent code(follow the instruction):" << '\n';
                parent1 = Betta::getBettaFromUser();
                parent1.print();
                std::cout << "input second parent code:" << '\n';
                parent2 = Betta::getBettaFromUser();
                parent2.print();
            }
            else
            {
                std::cout << "Create Female Betta :" << '\n';
                parent1 = Betta::createRand(BettaType::Sex::betina);
                parent1.print();
                std::cout << "Create Male Betta :" << '\n';
                parent2 = Betta::createRand(BettaType::Sex::jantan);
                parent2.print();
            }
        }
        else
        {
            std::cout << "----------------------" << '\n';
            std::cout << "Breeding Generation #" << generation << '\n';
            std::cout << "----------------------" << '\n';
            std::cout << "Which Child?(from 1-20)" << '\n';
            std::cout << "Parent 1 :";
            int i{};
            std::cin >> i;
            parent1 = children.at(i-1);
            parent1.print();
            std::cout << "Parent 2 :";
            std::cin >> i;
            parent2 = children.at(i-1);
            parent2.print();
        }

        std::cout << "are you sure using these betta?('y'/'n')" << '\n';
        if(askUserApproval())
        {
            children = Betta::breedBettaInPrompt(parent1, parent2, manyChild);
        }
        else
        {
            std::cout << "End Breeding Session?(y/n)" << '\n';
            if(askUserApproval())
            {

                std::cout << "See you next time." << '\n';
                break;
            }
        }

        std::cout << "\n_________________________________________________" << '\n';
        std::cout << "Do you want to breed the next generation?(y/n)" << '\n';
        if(askUserApproval())
        {
            generation++;
            isManual = false;
        }
        else
        {
            isManual = true;
        }
    }
}

void testReadMethod()
{
    std::cout << "Enter Normal Genetic code :";
    Genotipe gen(getGenCodeFromUser());

    std::cout <<"Atavisme \t\t\t: " << gen.readUsingAtavisme() << '\n';
    std::cout <<"Kriptomeri \t\t\t: " << gen.readUsingKriptomeri() << '\n';
    std::cout <<"Epistasis Dominan \t\t: " << gen.readUsingEpistasisD() << '\n';
    std::cout <<"Epistasis Dominan-Resesif\t: " << gen.readUsingEpistasisDR() << '\n';
    std::cout <<"Absolute Komplementer \t\t: " << gen.readUsingAbsKomplementer() << '\n';
    std::cout <<"Dual Gen Komplementer \t\t: " << gen.readUsingDualKomplementer() << '\n';
    std::cout <<"Incomplete Dominance \t\t: " << gen.readUsingIncompleteD() << '\n';
    std::cout <<"Polimeri \t\t\t: " << gen.readUsingPolimeri() << '\n';

    std::cout << "\nEnter Multiple Allel Genetic(only first gen is MA) code :";
    GenotipeManyAllel genMA{getGenCodeFromUser()};

    std::cout <<"First MA \t\t\t: " << genMA.readUsingFirstMA() << '\n';
}



int main()
{
    srand((unsigned) time(0));

    //while(true)
    //{

    //additional feature 1 random betta
    //-create random genotipe
    //--create 2 random gamet
    //---create random numb from 1-2^n
    //---create gamet with numb-1, A letter, n many gen
    //--combine to create genotipe
    //-create random betta
    //--create random betta part
    //--combine all the betta part

    //


//testReadMethod();
    testBreeding();
    return 0;
}
