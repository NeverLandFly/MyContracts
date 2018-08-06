#include "future.hpp"
#include <eosiolib/contract.hpp>

class future: public contract{
public:
    future(account_name self)
    :contract(self),
     current_description(_self, _self){}

    contract_description current_description;

    //@abi action
    void describe(const uint8_t multiple){
        auto info = current_description.emplace(_self, [&](auto& info){
            info.id = current_description.available_primary_key();
            info.multiple = multiple;
        });
    }
};

EOSIO_ABI(future, (describe))