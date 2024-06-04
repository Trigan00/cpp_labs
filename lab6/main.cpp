#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

bool approximatelyEqual(double a, double b, double epsilon)
{
    return fabs(a - b) <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * epsilon);
}
bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon)
{
    double diff = fabs(a - b);
    if (diff <= absEpsilon)
        return true;
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}
bool check(int& argc, char* argv[])
{
    int digit{};
    if (argc == 1)
    {
        return 1;
    }
    std::string k = argv[1];
    if (!(k == "approximatelyEqual" || k == "approximatelyEqualAbsRel"))
    {
        return 1;
    }
    if (k == "approximatelyEqual") { digit = 3; }
    if (k == "approximatelyEqualAbsRel") {digit = 4;}
    if (argc != digit + 2)
    {
        return 1;
    }
    double temp{};
    std::stringstream convert;
    for (int i{ 2 }; i < digit + 2; i++)
    {
        convert << static_cast<std::string>(argv[i]);
        if (!(convert >> temp))
        {
            return 1;
        }
        convert.str(std::string());
        convert.clear();
    }
    return 0;
}
int main(int argc, char* argv[])
{
    if (check(argc, argv))
    {
        std::cout << "Ошибка ввода входных данных.";
        exit(1);
    }
    if (static_cast<std::string>(argv[1]) == "approximatelyEqual")
    {
        if (approximatelyEqual(std::stod(argv[2]), std::stod(argv[3]), std::stod(argv[4])))
        {
            std::cout << argv[2] << " равно " << argv[3] << " при заданном eps=" << argv[4] << std::endl;
        }
        else
        {
            std::cout << argv[2] << " НЕ равно " << argv[3] << " при заданном eps=" << argv[4] << std::endl;
        }
    }
    else
    {
        if (approximatelyEqualAbsRel(std::stod(argv[2]), std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5])))
        {
            std::cout << argv[2] << " равно " << argv[3] << " при заданных absEpsilon=" << argv[4] <<" и relEpsilon=" << argv[5] << std::endl;
        }
        else
        {
            std::cout << argv[2] << " НЕ равно " << argv[3] << " при заданных absEpsilon=" << argv[4] << " и relEpsilon=" << argv[5] << std::endl;
        }
    }
}