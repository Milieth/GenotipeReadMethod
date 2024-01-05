#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdint>
#include <ctime>
#include <cmath>
#include <bitset>
#include <string>


std::string getParent()
{
    std::string parentCode{};
    std::getline(std::cin >> std::ws,parentCode);

    return parentCode;
}

std::bitset<16> encodeToBin(std::string parentCode)
{
    unsigned int length{parentCode.length()};
    // encode it to binary and store it to 16 bitset variable
    std::bitset<16> parentGamet{};
    for (unsigned int i = 0; i < length; i++)
    {
        // the 3rd column char code is capital later
        // and the 4th column char code is lower later
        // which its column have 32 diff symbol
        unsigned int n = floor(static_cast<unsigned int>(parentCode[i]) / 32u);
        // we don't need to check the lower code because its encode
        // to zero(0)
        (n == 2)?parentGamet.set(length - 1u - i):parentGamet.reset(length -1u - i);
    }
    return parentGamet;
}

int getRand(int atas)
{
    // random number dari batas "bawah" sampai "atas"
    int result{};
    result = 1 + rand() % (atas);
//    return static_cast<unsigned int>(result);
    return result;
}

std::bitset<8> bitTrue(unsigned int manyTrue)
{
    unsigned int bitLenght = 8u;
    unsigned int bitDel = bitLenght-manyTrue;
    std::bitset<8> zeroBit{0b0000'0000};
    return (~zeroBit) << bitDel >> bitDel;
}

std::bitset<2048> forkLineMethod(std::bitset<16> parentGen, unsigned int manyType)
{
        // DIAGRAM GARPU ALOGARITMA(FORKED LINE METHOD)
    std::bitset<2048> gametLine {};
    std::bitset<8> isDone{0b0000'0000};
    std::bitset<8> isSR{0b0000'0000};
    std::bitset<8> isSimple{0b0000'0000};
    // run all gen path until all path is done and
    //  no different path left
    while(!((isDone & bitTrue(manyType)) == bitTrue(manyType)))
    {
        /////////////////////////////////// GEN ke-i
        for (unsigned int i = manyType-1u; i > 0u; i--)
        {
            if(parentGen.test(2u*i+1u) & parentGen.test(2u*i))
            {
                //This Gamet is Dominan-Dominan
                gametLine.set(i);
                //this is one way Path
                isSimple.set(i);
            }
            else if(parentGen.test(2u*i+1u) & !parentGen.test(2u*i))
            {
                //This Gamet is Dominan-Resesif
                if( (isDone & bitTrue(i)) == bitTrue(i))
                {
                    //change to another path(0)
                    isSR.set(i);
                    // reset Gen below to normal state
                    isDone &= (~bitTrue(i));
                    isSR &= (~bitTrue(i));
                }
                (isSR.test(i))?gametLine.reset(i):gametLine.set(i);
            }
            else
            {
                //This Gamet is Resesif-Resesif
                gametLine.reset(i);
                // this is simple path too
                isSimple.set(i);
            }
        }

        /////////////////////////////////// GEN Z99 (LAST GEN)
            if(parentGen.test(1) & parentGen.test(0))
            {
                gametLine.set(0);
                isSimple.set(0);
            }
            else if(parentGen.test(1) & !parentGen.test(0))
            {
                (isSR.test(0))?gametLine.reset(0):gametLine.set(0);
                isSR.set(0);
            }
            else
            {
                gametLine.reset(0);
                isSimple.set(0);
            }

                // Diagram Garpu on off control
            isDone |= isSimple;
            // all simple path have nothing to do
            if(!gametLine.test(0))
            {
                // last gen is done
                isDone.set(0);
            }
            for(unsigned int i = 1u; i < manyType; i++)
            {
                // other gen done
                if( (!gametLine.test(i)) && (isDone.test(i-1u)) )
                {
                    isDone.set(i);
                }
            }

        if( !((isDone & bitTrue(manyType)) == bitTrue(manyType)) )
        {
            //save current gen for later use
            //release sloth for another gen
            gametLine <<= manyType;
        }
        // dont release sloth after last gen
    }
    return gametLine;
}

unsigned int countGamet(std::bitset<16> parentGen, unsigned int manyType)
{
    unsigned int differG{0};
    unsigned int sameG{0};

    for(unsigned int i = 1; i <= manyType; i++)
    {
        (parentGen.test(2u*i-1u) == parentGen.test(2u*i-2u))?sameG++:differG++;
    }

    return pow(2,(differG+sameG))/ pow(2,sameG);
}

std::bitset<8> getChoGamet (std::bitset<16> parentGen, unsigned int manyType)
{
    std::cout << " Fork Line Method :\n";
    std::cout << " ->Creating Gametes Path\n";
    std::cout << " ->Running All Path\n";
    std::cout << " ->Constructing Gametes Line\n";
    std::bitset<2048> gametLine = forkLineMethod(parentGen,manyType);

    std::cout << " ->Done\n";
    std::cout << "Gamet Line :\n" << gametLine << '\n' << '\n';


    // random a number from 1 to manyGamet
    std::cout << "Picking random gametes\n";
    unsigned int manyGamet{countGamet(parentGen,manyType)};
    unsigned int nomorGamet = static_cast<unsigned int>( getRand(static_cast<int> (manyGamet)) );
    std::cout << "Get random number: " << nomorGamet << '\n';
    std::cout << "Creating chosen gametes\n";
    std::cout << "Done\n";
    std::cout << "Gametes ready to merge\n\n";

    // create chosen gamet as a new variable
    std::bitset<8> choGamet{};
    unsigned int x{0};
    for (unsigned int i = manyType * (nomorGamet-1u); i < manyType * nomorGamet; i++)
    {
        (gametLine.test(i))?choGamet.set(x):choGamet.reset(x);
        x++;
    }

    return choGamet;
}

std::bitset<16> combineGamet(std::bitset<8> choGamet1, std::bitset<8> choGamet2, unsigned int manyType)
{
    std::bitset<16> combinedGamet {};
    for(unsigned int i = 0 ; i < manyType; i++)
    {
        if(choGamet1.test(i) - choGamet2.test(i) == -1)
        {
            choGamet1.test(i)?combinedGamet.set(2 * i):combinedGamet.reset(2 * i);
            choGamet2.test(i)?combinedGamet.set(2 * i + 1):combinedGamet.reset(2 * i + 1);
        }
        else
        {
            choGamet2.test(i)?combinedGamet.set(2 * i):combinedGamet.reset(2 * i);
            choGamet1.test(i)?combinedGamet.set(2 * i + 1):combinedGamet.reset(2 * i + 1);
        }
    }
    return combinedGamet;
}

std::bitset<16> getFenotip(std::bitset<16> binParent1, std::bitset<16> binParent2, unsigned int manyType)
{
    std::cout << "\nDetermining inheritance gametes using Fork Line Method .. .\n";
    // we get choGamet by random generator then we need to set seed here
    std::bitset<8> choGamet1{getChoGamet(binParent1,manyType)};
    std::bitset<8> choGamet2{getChoGamet(binParent2,manyType)};
    std::cout << "Result :\n";
    std::cout << "Chosen Gamet\t: " << choGamet1;
    std::cout << "\nChosen Gamet\t: " << choGamet2;

    std::cout << "\n\n Amalgamation 2 chosen Gametes\n";
    std::bitset<16> fenotip{combineGamet(choGamet1,choGamet2,manyType)};
    std::cout << "Done\n";
    std::cout << "\n Binary phenotype 1 :" << fenotip << '\n';

    return fenotip;
}

std::string decodeBinGen(std::bitset<16> fenotip, unsigned int manyType)
{
    std::string decodedFenotip {};
    //a trivial variable to control decoding
    unsigned int x{0};
    for(unsigned int i = manyType; i > 0; i--)
    {
        if(x == 0)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'A'):(decodedFenotip += 'a');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'A'):(decodedFenotip += 'a');
        }
        else if(x == 1)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'B'):(decodedFenotip += 'b');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'B'):(decodedFenotip += 'b');
        }
        else if(x == 2)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'C'):(decodedFenotip += 'c');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'C'):(decodedFenotip += 'c');
        }
        else if(x == 3)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'D'):(decodedFenotip += 'd');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'D'):(decodedFenotip += 'd');
        }
        else if(x == 4)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'E'):(decodedFenotip += 'e');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'E'):(decodedFenotip += 'e');
        }
        else if(x == 5)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'F'):(decodedFenotip += 'f');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'F'):(decodedFenotip += 'f');
        }
        else if(x == 6)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'G'):(decodedFenotip += 'g');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'G'):(decodedFenotip += 'g');
        }
        else if(x == 7)
        {
            (fenotip.test(2 * i - 1u))?(decodedFenotip += 'H'):(decodedFenotip += 'h');
            (fenotip.test(2 * i - 2u))?(decodedFenotip += 'H'):(decodedFenotip += 'h');
        }
        x++;
    }
    return decodedFenotip;
}

 atavisme()
{
    ////////////////////GET CODE////////////////
    //ask user to enter how many gamet type he want to input
    //then we know how long the gen we have
    std::cout << "Enter first parent code :";
    std::string alphaParent1{getParent()};
    //ask parent Gamet code and encode it to binary
    std::bitset<16> binParent1{encodeToBin(alphaParent1)};
    std::cout << "Enter second parent code :";
    //ask second parent with the same lenght
    std::string alphaParent2{getParent()};
    std::bitset<16> binParent2{encodeToBin(alphaParent2)};
    unsigned int manyType{alphaParent1.length() / 2};
    std::cout << "Initializing breeding function with "<< manyType << " gen type.. .\n";
    std::cout << "Done\n\n";
    std::cout << "Encode parent code to binary code :\n";
    std::cout << "First parent code\t: " << binParent1 << '\n';
    std::cout << "Second parent code\t: " << binParent2 << '\n';

    /////////////////////////BREEDING//////////////////
    std::bitset<16> child[7]{};
    std::string alphaFenotip[7]{};
    for(int i = 0; i < 7; i++)
    {
        child[i] = getFenotip(binParent1, binParent2, manyType);
        alphaFenotip[i] = decodeBinGen(child[i],manyType);
    }

    ///////////////////////RESULT////////////////////
    for(int i = 0; i < 7; i++)
    {
        std::cout << alphaFenotip[i] << '\n';
    }
}

int main()
{
    srand((unsigned) time(0));
    atavisme();

    return 0;
}
