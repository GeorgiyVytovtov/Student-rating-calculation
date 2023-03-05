#include"Header.h"

double averageScore(const std::vector<double> scores)
{
    double averageScore=0;

    for (auto& element : scores)
    {
        averageScore += element;
    }
    averageScore = averageScore / scores.size();
    return averageScore;
}