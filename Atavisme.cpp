#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include<cmath>
#include<algorithm>

void pseudofunc(int x, int y)
{
    x = y++;
    y = x++;
}

int countGamet(int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8)
{
    int iteration{0};

    if (n1 != 0)
    {
        iteration++;
    }
    if (n2 != 0)
    {
        iteration++;
    }
    if (n3 != 0)
    {
        iteration++;
    }
    if (n4 != 0)
    {
        iteration++;
    }
    if (n5 != 0)
    {
        iteration++;
    }
    if (n6 != 0)
    {
        iteration++;
    }
    if (n7 != 0)
    {
        iteration++;
    }
    if (n8 != 0)
    {
        iteration++;
    }

    return iteration;
}

int combineGamet(int x1, int x2, int y1, int y2, int z1, int z2)
{
    static int turn{1};
    if (turn == 1)
    {
        if (x1 != 0 && y1 != 0 && z1 != 0)
        {
            turn++;
            return (x1 * 100 + y1 * 10 + z1);
        }
        turn++;
        return 0;
    }
    else if (turn == 2)
    {
        if (x1 != 0 && y1 != 0 && z2 != 0)
        {
            turn++;
            return (x1 * 100 + y1 * 10 + z2);
        }
        turn++;
        return 0;
    }
    else if (turn == 3)
    {
        if (x1 != 0 && y2 != 0 && z1 != 0)
        {
            turn++;
            return (x1 * 100 + y2 * 10 + z1);
        }
        turn++;
        return 0;
    }
    else if (turn == 4)
    {
        if (x1 != 0 && y2 != 0 && z2 != 0)
        {
            turn++;
            return (x1 * 100 + y2 * 10 + z2);
        }
        turn++;
        return 0;
    }
    else if (turn == 5)
    {
        if (x2 != 0 && y1 != 0 && z1 != 0)
        {
            turn++;
            return (x2 * 100 + y1 * 10 + z1);
        }
        turn++;
        return 0;
    }
    else if (turn == 6)
    {
        if (x2 != 0 && y1 != 0 && z2 != 0)
        {
            turn++;
            return (x2 * 100 + y1 * 10 + z2);
        }
        turn++;
        return 0;
    }
    else if (turn == 7)
    {
        if (x2 != 0 && y2 != 0 && z1 != 0)
        {
            turn++;
            return (x2 * 100 + y2 * 10 + z1);
        }
        turn++;
        return 0;
    }
    else if (turn == 8)
    {
        if (x2 != 0 && y2 != 0 && z2 != 0)
        {
            turn = 1;
            return (x2 * 100 + y2 * 10 + z2);
        }
        turn = 1;
        return 0;
    }
    return 888;
}

int atavisme()
{
    char x1{};
    std::cin >> x1;
    char x2{};
    std::cin >> x2;
    char y1{};
    std::cin >> y1;
    char y2{};
    std::cin >> y2;
    char z1{};
    std::cin >> z1;
    char z2{};
    std::cin >> z2;

    int i1{(x1 == 'X')?1:2};
    int i2{(x2 == 'X')?1:2};
    int i3{(y1 == 'Y')?3:4};
    int i4{(y2 == 'Y')?3:4};
    int i5{(z1 == 'Z')?5:6};
    int i6{(z2 == 'Z')?5:6};
    std::cout << i1 << i2 << i3 << i4 << i5 << i6 << '\n';

    if (i1 == i2)
    {
        i2 = 0;
    }
    if (i3 == i4)
    {
        i4 = 0;
    }
    if (i5 == i6)
    {
        i6 = 0;
    }

    std::cout << i1 << i2 << i3 << i4 << i5 << i6 << '\n';

    int sGamet1{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet2{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet3{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet4{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet5{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet6{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet7{combineGamet(i1, i2, i3, i4, i5, i6)};
    int sGamet8{combineGamet(i1, i2, i3, i4, i5, i6)};

    std::cout << sGamet1 << '\n' << sGamet2 << '\n' << sGamet3 << '\n'
     << sGamet4 << '\n' << sGamet5 << '\n' << sGamet6 << '\n' << sGamet7 << '\n'
      << sGamet8 << '\n';

int jumlahGamet{countGamet(sGamet1, sGamet2, sGamet3, sGamet4, sGamet5,
                           sGamet6, sGamet7, sGamet8)};

    std::cout << jumlahGamet << '\n';
int gamet1{0};
int gamet2{0};
int gamet3{0};
int gamet4{0};
int gamet5{0};
int gamet6{0};
int gamet7{0};
int gamet8{0};

    std::cout << gamet1 << gamet2 << gamet3 << gamet4 << gamet5 << gamet6
    << gamet7 << gamet8 << '\n';
    if (jumlahGamet == 1)
    {
        gamet1 = sGamet1;
    }
    else if (jumlahGamet == 2)
    {
        if (sGamet1 != 0)
        {
            gamet1 = sGamet1;
        }
        if (sGamet2 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet2;
            }
            else
            {
                gamet2 = sGamet2;
            }
        }
        if (sGamet3 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet3;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet3;
            }
        }
        if (sGamet4 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet4;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet4;
            }
        }
        if (sGamet5 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet5;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet5;
            }
        }
        if (sGamet6 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet6;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet6;
            }
        }
        if (sGamet7 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet7;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet7;
            }
        }
        if (sGamet8 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet8;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet8;
            }
        }
    }
    else if (jumlahGamet == 4)
    {
         if (sGamet1 != 0)
        {
            gamet1 = sGamet1;
        }
        if (sGamet2 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet2;
            }
            else
            {
                gamet2 = sGamet2;
            }
        }
        if (sGamet3 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet3;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet3;
            }
            else
            {
                gamet3 = sGamet3;
            }
        }
        if (sGamet4 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet4;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet4;
            }
            else if (gamet3 == 0)
            {
                gamet3 = sGamet4;
            }
            else
            {
                gamet4 = sGamet4;
            }
        }
        if (sGamet5 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet5;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet5;
            }
            else if (gamet3 == 0)
            {
                gamet3 = sGamet5;
            }
            else
            {
                gamet4 = sGamet5;
            }
        }
        if (sGamet6 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet6;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet6;
            }
            else if (gamet3 == 0)
            {
                gamet3 = sGamet6;
            }
            else
            {
                gamet4 = sGamet6;
            }
        }
        if (sGamet7 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet7;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet7;
            }
            else if (gamet3 == 0)
            {
                gamet3 = sGamet7;
            }
            else
            {
                gamet4 = sGamet7;
            }
        }
        if (sGamet8 != 0)
        {
            if (gamet1 == 0)
            {
                gamet1 = sGamet8;
            }
            else if (gamet2 == 0)
            {
                gamet2 = sGamet8;
            }
            else if (gamet3 == 0)
            {
                gamet3 = sGamet8;
            }
            else
            {
                gamet4 = sGamet8;
            }
        }
    }
    else if(jumlahGamet == 8)
    {
        gamet1 = sGamet1;
        gamet2 = sGamet2;
        gamet3 = sGamet3;
        gamet4 = sGamet4;
        gamet5 = sGamet5;
        gamet6 = sGamet6;
        gamet7 = sGamet7;
        gamet8 = sGamet8;
    }
    std::cout << gamet1 << '\n' << gamet2 << '\n' << gamet3 << '\n' << gamet4
    << '\n' << gamet5 << '\n' << gamet6 << '\n' << gamet7 << '\n' << gamet8 <<
    '\n';

    std::cout << "Memilih Dari Acakan Gamet Yang Sudah Diurutkan :\n";
int gametTerpilih{0};
int result{0};
pseudofunc(gametTerpilih,result);
srand((unsigned) time(0));

    if (jumlahGamet == 1)
    {
        result = 1 + (rand() % jumlahGamet);
        std::cout << result << '\n';
        if(result == 1)
        {
            gametTerpilih = gamet1;
        }
        else
        {
            std::cout << "Error\n";
        }
    }
    else if (jumlahGamet == 2)
    {
        result = 1 + (rand() % jumlahGamet);
        std::cout << result << '\n';
        if(result == 1)
        {
            gametTerpilih = gamet1;
        }
        else if(result == 2)
        {
            gametTerpilih = gamet2;
        }
        else
        {
            std::cout << "Error\n";
        }
    }
    else if (jumlahGamet == 4)
    {
        result = 1 + (rand() % jumlahGamet);
        std::cout << result << '\n';
        if(result == 1)
        {
            gametTerpilih = gamet1;
        }
        else if(result == 2)
        {
            gametTerpilih = gamet2;
        }
        else if(result == 3)
        {
            gametTerpilih = gamet3;
        }
        else if(result == 4)
        {
            gametTerpilih = gamet4;
        }
        else
        {
            std::cout << "Error\n";
        }
    }
    else if (jumlahGamet == 8)
    {
        result = 1 + (rand() % jumlahGamet);
        std::cout << result << '\n';
        if(result == 1)
        {
            gametTerpilih = gamet1;
        }
        else if(result == 2)
        {
            gametTerpilih = gamet2;
        }
        else if(result == 3)
        {
            gametTerpilih = gamet3;
        }
        else if(result == 4)
        {
            gametTerpilih = gamet4;
        }
        else if(result == 5)
        {
            gametTerpilih = gamet5;
        }
        else if(result == 6)
        {
            gametTerpilih = gamet6;
        }
        else if(result == 7)
        {
            gametTerpilih = gamet7;
        }
        else if(result == 8)
        {
            gametTerpilih = gamet8;
        }
        else
        {
            std::cout << "Error\n";
        }
    }

    std::cout << "Gamet yang terpilih : " << gametTerpilih << '\n';
    return gametTerpilih;

}

int main()
{
    std::cout << "Masukkan Gen Parent 1: ";
    // user memasukkan gen parent dan menghasilkan gamet secara acak dengan
    // atavisme
    int gametTP1{atavisme()};
    std::cout << "Masukkan Gen Parent 2: ";
    int gametTP2{atavisme()};
    std::cout << "gametnya adalah : " << gametTP1 << " dan " << gametTP2 << '\n';

    int n = gametTP1;
    int i1{};
    int i2{};
    int i3{};
    int i4{};
    int i5{};
    int i6{};
    int m {};
    m = floor(n/10);
    i5 = n-m*10;
    n = floor(m/10);
    i3 = m-n*10;
    m = floor(n/10);
    i1 = n-m*10;

    n = gametTP2;
    m = floor(n/10);
    i6 = n-m*10;
    n = floor(m/10);
    i4 = m-n*10;
    m = floor(n/10);
    i2 = n-m*10;

    char x1 = (i1 == 1)?'X':'x';
    char x2 = (i2 == 1)?'X':'x';
    char y1 = (i3 == 3)?'Y':'y';
    char y2 = (i4 == 3)?'Y':'y';
    char z1 = (i5 == 5)?'Z':'z';
    char z2 = (i6 == 5)?'Z':'z';

    std::cout << "\n Gen Anak Berta Yang Dilahirkan : " << x1 << x2 << y1 <<
     y2 << z1 << z2;

    return 0;
}

