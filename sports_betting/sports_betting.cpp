#include "sports_betting.hpp"

class sports_betting : public eosio::contract{
    public:
        pool_index pools;
        client_bets
        sports_betting(account_name self)
            :eosio::contract(self),
             pools(_self, _self),
             client
             
}