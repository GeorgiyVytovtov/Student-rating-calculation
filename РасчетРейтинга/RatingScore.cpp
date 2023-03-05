#include"Header.h"

// The implementation of this function may vary depending on the ranking formula for your university.
// In my case, the rating calculation formula looks like:
// Q * (( S1 * C1 + S2 * C2 + ... + Si * Ci ) / R * M ) + D
// Q - The maximum possible score for study.
// Si - Discipline score.
// Ci - Discipline coefficient. 
// R - sum all Ci.
// D - extra points 
// M - The maximum possible score for discipline
double ratingScore(const std::vector<double> scores,const std::vector<double> coef,const double dopScores)
{
    double ratingScore, sumWeightScore = 0, sumCoef =0;
    const int MAX_SCORE = 94;                   // The maximum possible score for study.
    const int BEST_SCORE = 100;                 // The maximum possible score for discipline.
    std::vector<double>::const_iterator iterCurrentScote = scores.begin();

    for (auto& currentCoef : coef)
    {
        sumCoef += currentCoef;                 
        int currentScore = *(iterCurrentScote++);
        sumWeightScore = sumWeightScore + (currentCoef * (currentScore));
    }

    ratingScore = MAX_SCORE * (sumWeightScore / (sumCoef * BEST_SCORE)) + dopScores;
    return ratingScore;
}