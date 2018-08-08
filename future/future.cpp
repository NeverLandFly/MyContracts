#include "future.hpp"
#include <eosiolib/contract.hpp>
#include <eosiolib/print.hpp>
#include <string.h>

class future: public contract{
public:
    future(account_name contract_account)
    :contract(contract_account),
     descriptions(_self, _self),
     order_book(_self, _self){}

    contract_description descriptions;
    orders order_book;

    //@abi action
    void info(uint32_t multiple, uint32_t precision,std::string underlying, uint64_t expiration){
        /*auto itr = descriptions.find( _self );
        if (itr != descriptions.end()){
            descriptions.erase(itr);
        }*/
        auto info = descriptions.emplace(_self, [&](auto& info){
            info.contract_account = _self;
            info.multiple = multiple;
            info.precision = precision;
            info.underlying = underlying;
            info.expiration = expiration;
        });
    }

    //@abi action
    void insertorder(account_name owner, uint32_t price, uint32_t volume, uint8_t type) {
        auto o = order{0, price, volume, type, owner};
        auto itr = descriptions.find(_self);
        auto ask1key = itr->ask1key;
        auto bid1key = itr->bid1key;
        auto counter = itr->counter;

        if (ask1key == 0) {
            addordertobook(o, counter);
            descriptions.modify(itr, _self, [&](auto &info) {
                info.counter++;

            });
        }

        switch (type) {
            case 0: // buy open
            case 1: // buy close

                break;
            case 2: // sell open
            case 3: // sell close

                break;
        }
    }

    void addordertobook(order& o, uint32_t counter){
        order_book.emplace(_self, [&](auto& new_order){
            new_order.id = ((uint64_t)o.price<<32) + counter;
            new_order.price = o.price;
            new_order.volume = o.volume;
            new_order.type = o.type;
            new_order.owner = o.owner;
        });
    }

    void removeorder(uint64_t orderid){
        auto itr = order_book.find( orderid );
        if (itr != order_book.end()){
            order_book.erase(itr);
        }
    }
};

EOSIO_ABI(future, (info)(insertorder)(removeorder))