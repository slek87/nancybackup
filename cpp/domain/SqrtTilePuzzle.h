#pragma once
#include "SimpleTilePuzzle.h"
#include <math.h>
#include <algorithm>
#include <random>

class SqrtTilePuzzle : public SimpleTilePuzzle {
public:
    using SimpleTilePuzzle::SimpleTilePuzzle;

    Cost getEdgeCost(State state) { return sqrt((double)state.getFace()); }

    Cost heuristic(const State& state) {
        // Check if the heuristic of this state has been updated
        if (correctedH.find(state) != correctedH.end()) {
            return correctedH[state];
        }

        Cost h = manhattanDistanceWithInverseFaceCost(state);

        updateHeuristic(state, h);

        return correctedH[state];
    }

    Cost manhattanDistanceWithInverseFaceCost(const State& state) const {
        Cost manhattanSum = 0;

        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                auto value = state.getBoard()[r][c];
                if (value == 0) {
                    continue;
                }

                manhattanSum += (sqrt((double)value)) *
                        (abs(value / size - r) + abs(value % size - c));
                // cout << "value " << value << " sum " << manhattanSum << endl;
            }
        }

        return manhattanSum;
    }

    virtual string getSubDomainName() const { return "inverse"; }
};
