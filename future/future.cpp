#include "future.hpp"
#include <eosiolib/contract.hpp>
#include <eosiolib/print.hpp>

class future: public contract{
public:
    future(account_name contract_account)
    :contract(contract_account),
     descriptions(_self, _self),
     order_book(_self, _self){}

    contract_description descriptions;
    orders order_book;

    //@abi action
    void info(const uint8_t multiple, const uint32_t precision){
        auto itr = descriptions.find( _self );
        if (itr != descriptions.end()){
            descriptions.erase(itr);
        }
        auto info = descriptions.emplace(_self, [&](auto& info){
            info.contract_account = _self;
            info.multiple = multiple;
            info.precision = precision;
        });
    }

    //@abi action
    void sendorder(account_name owner, uint32_t price/*, uint32_t volume, uint8_t type, uint64_t id*/){
        auto itr = descriptions.find( _self );
        int counter = itr->counter;
        order_book.emplace(_self, [&](auto& o){
            o.id = ((uint64_t)price<<32) + counter;
            o.owner = owner;
        });
        descriptions.modify(itr, owner, [&](auto& info){
            info.counter++;
        });
    }
};

EOSIO_ABI(future, (info)(sendorder))