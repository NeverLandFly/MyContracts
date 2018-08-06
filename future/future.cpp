#include "future.hpp"
#include <eosiolib/contract.hpp>

class future: public contract{
public:
    future(account_name self)
    :contract(self),
     current_description(_self, _self){}

    contract_description current_description;

    //@abi action
    void describe(const uint8_t multiple, const fixed_point128<8> price_tick){
        auto info = current_description.emplace(_self, [&](auto& info){
            info.id = current_description.available_primary_key();
            info.multiple = multiple;
//            info.price_tick = price_tick;
        });
    }
};

EOSIO_ABI(future, (describe))