#include "sports_betting.hpp"

class sports_betting : public eosio::contract{
    public:
        pool_index pools;
        client_bet_index client_bets;

        sports_betting(account_name self)
            :eosio::contract(self),
             pools(_self, _self),
             client_bets(_self, _self)
            {}
        
        //@abi action
        void SetPoolInfo(){
            
        }
             
}