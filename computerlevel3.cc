#include "computerlevel3.h"
#include "computerlevel1.h"
#include <stdexcept>

// calcs the score of a move
int getMoveScore(const MoveEvaluation &evaluation) {
    int score = 0;

    // safe moves give more score than captures, unlike level 2
    if (evaluation.isSafe) {
        score += 100;
    }

    // potentially risky captures are disincentivized
    if (evaluation.move.isCapture) {
        score += 10;
    }

    // checks are also not as high of a priority
    if (evaluation.givesCheck) {
        score += 5;
    }

    return score;
}

Move chooseLevel3(const std::vector<MoveEvaluation> &evaluations) {
    if (evaluations.empty()) {
        throw std::runtime_error("No legal moves available");
    }

    int bestScore = -1;
    std::vector<Move> bestMoves;

    // checks every available move
    for (const MoveEvaluation &evaluation : evaluations) {
        int score = getMoveScore(evaluation);

        if (score > bestScore) {
            bestScore = score;
            bestMoves.clear();
            bestMoves.push_back(evaluation.move);
        } else if (score == bestScore) {
            bestMoves.push_back(evaluation.move);
        }
    }

    // ramdonly picks a move with the highest score
    return chooseLevel1(bestMoves);
}
