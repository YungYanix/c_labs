#include <math.h>
#define pi 3.14159265358979323846

//нахождение факториала
int fact(int k)
{
    int f = 1, i;
    for (i = 2; i <= k; i++)
        f = f * i;
    return f;
}



double mysin(double x, double ep)
{
    double S = 0, S_1; // S - сумма ряда, S_1 - предыдущее значение суммы ряда
    int zn = 1, n = 1, sign = 1; // sign - для убирания периодов 

    // при x < 0 идем в положительную часть синуса
    if (x < 0)
    {
        sign = -1;     //меняем знак на минус
        x = fabs(x);  //угол делаем по модулю
    }

    //если угол больше 2Пи, то идём в область от 0 до 2Пи 
    x = fmod(x, 2 * pi);//делим угол на 2Пи, получая остаток от деления

    //если x больше Пи, то идем в область от 0 до Пи
    if (x > pi)
    {
        x = x - pi; 
        sign = sign * (-1); // меняем знак на противоположный. (если был -, будет +) 
    }

    //x > (pi/2) peremeshtaem v interval [0..pi/2]
    if (x > (pi / 2))
        x = pi - x; // пример: если из Пи вычесть 3/4Пи получим числый угол Пи/4 (синус(3/4Пи) = синус(Пи/4)) 

    do
    {
        S_1 = S;
        S = S + (zn * pow(x, 2 * n - 1) / fact(2 * n - 1));
        n = n + 1;
        zn = zn * (-1);
    } while (fabs(S - S_1) > ep); //остаемся в цикле до тех пор пока выполняется условие
    S = S * sign;
    return S;
}
double mycos(double x, double ep)
{
    double S = 0, S_1;
    int zn = 1, n = 1, sign = 1;

    //если х меньше 0, берем по модулю
    if (x < 0) x = fabs(x);
    //eсли x>2Pi перемещаем в интервал [0..2pi]
    x = fmod(x, 2 * pi);//остаток от деления x/(2*pi) , убираем период

    //x > pi перемещаем в интервал [0..pi]
    if (x > pi)
    {
        x = 2 * pi - x; // чтобы получить угол от 0 до пи, вычитаем из 2пи найденный угол >пи 
    }

    //x > (pi/2) peremeshtaem v interval [0..pi/2]
    if (x > (pi / 2))
    {
        x = pi - x;
        sign = sign * (-1); //т.к от 0 до пи/2 знак + а от пи/2 до пи знак -, то меняем знак 
    }

    do
    {
        S_1 = S; //предыдущее значение суммы
        S = S + (zn * pow(x, 2 * n - 2) / fact(2 * n - 2));
        n = n + 1;
        zn = zn * (-1);
    } while (fabs(S - S_1) > ep);
    S = S * sign;
    return S;
}
double mytan(double x, double ep) //ищем тангенс из деления двух функций
{
    double s, c; // s -синус, c - косинус

    s = mysin(x, ep); //идёт в функцию синуса
    c = mycos(x, ep); //идёт в функцию косинуса
    return(s/c);

}
int main(void)
{
    double ep = 0.000001;
    double g; // для подсчёта угла

    for (g = -2 *pi; g  <= 2 * pi; g = g + pi / 10.) // с шагом 1/10 pi идём до 6pi от нуля (перебираем разные углы, чтобы посчитать тангенс)
    {
        if (fabs(fmod(fabs(g), pi) - pi / 2)>=ep) //все точки pi/2 этой функцией убираем
        {
            printf("mytg(%8.5f) = %9.6f  tg(%8.5f) =%9.6f\n", g, mytan(g, ep),g, tan(g)); // печать двух вещ. чисел с заданной точностью с жёстким порядком
        }
        else
        {
             printf("no result\n"); // разница между числами меньше EP
        }

    }
    return 0;


}