//
// Created by Xuefeng Huang on 2020/2/1.
//

#ifndef TEXASSOLVER_BESTRESPONSE_H
#define TEXASSOLVER_BESTRESPONSE_H
#include <omp.h>
#include <ranges/PrivateCards.h>
#include <compairer/Compairer.h>
#include <Deck.h>
#include <ranges/RiverRangeManager.h>
#include <ranges/PrivateCardsManager.h>
#include <trainable/CfrPlusTrainable.h>
#include <trainable/DiscountedCfrTrainable.h>
#include <nodes/ChanceNode.h>
#include <nodes/TerminalNode.h>
#include <nodes/ShowdownNode.h>

using namespace std;

class BestResponse {
private:
    Deck& deck;
    // player -> preflop combos
    vector<vector<PrivateCards>>& private_combos;
    vector<int> player_hands;
    int player_number;
    RiverRangeManager& rrm;
    PrivateCardsManager& pcm;
    bool debug;
    vector<vector<float>> reach_probs;
    int nthreads;
public:
    BestResponse(
            vector<vector<PrivateCards>>& private_combos,
            int player_number,
            PrivateCardsManager& pcm,
            RiverRangeManager& rrm,
            Deck& deck,
            bool debug,
            int nthreads = 1);
    float printExploitability(shared_ptr<GameTreeNode> root, int iterationCount, float initial_pot, uint64_t initialBoard);
    float getBestReponseEv(shared_ptr<GameTreeNode> node, int player,vector<vector<float>> reach_probs, uint64_t initialBoard);

private:
    vector<float> bestResponse(shared_ptr<GameTreeNode> node, int player, const vector<vector<float>>& reach_probs, uint64_t board);
    vector<float> chanceBestReponse(shared_ptr<ChanceNode> node, int player, const vector<vector<float>>& reach_probs, uint64_t current_board);
    vector<float> actionBestResponse(shared_ptr<ActionNode> node, int player, const vector<vector<float>>& reach_probs, uint64_t board);
    vector<float> terminalBestReponse(shared_ptr<TerminalNode> node, int player, const vector<vector<float>>& reach_probs, uint64_t board);
    vector<float> showdownBestResponse(shared_ptr<ShowdownNode> node, int player, const vector<vector<float>>& reach_probs,uint64_t board);
};


#endif //TEXASSOLVER_BESTRESPONSE_H
