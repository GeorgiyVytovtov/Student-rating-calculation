#include"Header.h"

double averageScore(const std::vector<int> marks)
{
    double averageScore=0;

    for (auto& element : marks)
    {
        averageScore += element;
    }
    averageScore = averageScore / marks.size();
    return averageScore;
}