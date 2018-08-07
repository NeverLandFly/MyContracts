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
        void create_pool(const account_name host){
            
        }

        //@abi action
        void transfer(const account_name sender, const account_name receiver){
            
        }

        //@abi action
        void verify(const account_name host){

        }

        //@abi action
        void bet(const account_name host, const asset& quantity){

        }

        //@abi action
        void reveal_result(bool is_host_win){

        }
             
        //@abi action
        void get_permission(){
            
        }
}