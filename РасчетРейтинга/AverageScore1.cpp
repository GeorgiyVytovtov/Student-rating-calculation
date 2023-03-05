#include<vector>

double averageScore1(double& reating_ball, double& coefc, std::vector<double>& bals, std::vector<double>& coef, double dop_balls)
{
    int a = 94;//максимально возможное кол балов
    //int b = 6;//доп балы
    double c, d, e;
    d = c = 0;
    e = 100;
    int i = 0;//??????
    for (auto& elemnts1 : coef)
    {
        d += elemnts1;
        //for (auto& elemnts2 : bals)
        //{
        //    c = c + (elemnts1 * elemnts2);//исправить
        //    bals.erase(bals.begin());
        //    //e += elemnts1;
        //    break;
        //}
        for (; i < bals.size(); )
        {
            auto temp = *(bals.begin() + i);
           
            c =c+( elemnts1 * (temp));//исправить
            i++;
            break;
        }
    }
    /*
    int i = 0;
    std::vector<double>::iterator it = bals.begin();
    for (auto& elemnts1 : coef)
    {
        d += elemnts1;
        std::advance(it, i);
        c = c + (elemnts1 * (*it));
        i++;
    }
    */
   // c = c / (d * e);
    if (c != 0)//??
    {
        c = c / (d * e);
    }
    //c = c / (d * e);
    reating_ball = a * c + dop_balls;
    return reating_ball;
}