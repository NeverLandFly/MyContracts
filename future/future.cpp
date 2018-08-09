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
        auto itr = descriptions.find( _self );
        if (itr != descriptions.end()){
            descriptions.erase(itr);
        }
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
        auto o = order{0, 0, price, volume, 0, type, owner};
        auto itr = descriptions.find(_self);
        auto ask1key = itr->ask1key;
        auto bid1key = itr->bid1key;
        auto counter = itr->counter;
        auto rcounter = itr->rcounter;

        auto askitr = order_book.find(ask1key);
        auto idx = order_book.template get_index<N(rid)>();
        auto biditr = idx.find(bid1key);


        switch (type) {
            case 0: // buy open
            case 1: // buy close
                if (askitr != order_book.end()){
                    if (price < askitr->price){
                        auto id = addordertobook(o, counter, rcounter);
                        if (price > biditr->price)
                            bid1key = id;
                    }else{
                        auto current = volume;
                        while (current > 0 && ask1key != 0 && price >= askitr->price){
                            if (current < askitr->get_unclosed()){
                                order_book.modify(askitr, _self, [&](auto &o) {
                                    o.closedvolume += current;
                                current = 0;
                                });
                                break;
                            }else{
                                current -= askitr->get_unclosed();
                                if (askitr != order_book.end())
                                {
                                    auto tempitr = askitr++;
                                    order_book.erase(tempitr);
                                    ask1key = askitr->id;
                                } else{
                                    order_book.erase(askitr);
                                    ask1key = 0;
                                }
                            }
                        }
                        if (current > 0)
                        {
                            o.volume = volume;
                            o.closedvolume = volume - current;
                            auto rid = addordertobook(o, counter, rcounter, true);
                            bid1key = rid;
                        }
                    }
                }else{
                    auto rid = addordertobook(o, counter, rcounter, true);
                    if (biditr != idx.end() && biditr->price < price){
                        bid1key = rid;
                    }else if (biditr == idx.end())
                        bid1key = rid;
                }
                break;
            case 2: // sell open
            case 3: // sell close
                if (biditr != idx.end()){
                    if (price > biditr->price){
                        auto id = addordertobook(o, counter, rcounter);
                        if (price < askitr->price)
                            ask1key = id;
                    }else{
                        auto current = volume;
                        while (current > 0 && bid1key != 0 && price <= biditr->price){
                            if (current < biditr->get_unclosed()){
                                idx.modify(biditr, _self, [&](auto &o) {
                                    o.closedvolume += current;
                                });
                                current = 0;
                                break;
                            }else{
                                current -= biditr->get_unclosed();
                                if (biditr != idx.begin())
                                {
                                    auto tempitr = biditr--;
                                    idx.erase(tempitr);
                                    bid1key = biditr->rid;
                                }else{
                                    idx.erase(biditr);
                                    bid1key = 0;
                                }
                            }
                        }
                        if (current > 0)
                        {
                            o.volume = volume;
                            o.closedvolume = volume - current;
                            auto id = addordertobook(o, counter, rcounter);
                            ask1key = id;
                        }
                    }
                }else{
                    auto id = addordertobook(o, counter, rcounter);
                    if (askitr != order_book.end() && askitr->price > price){
                        ask1key = id;
                    }else if (askitr == order_book.end())
                        ask1key = id;
                }
                break;
        }
        descriptions.modify(itr, _self, [&](auto &info) {
            info.counter++;
            info.rcounter--;
            info.bid1key = bid1key;
            info.ask1key = ask1key;
        });
    }

    uint64_t addordertobook(order& o, uint32_t counter, uint32_t rcounter, bool retR = false){
        auto new_order = order_book.emplace(_self, [&](auto& new_order){
            new_order.id = ((uint64_t)o.price<<32) + counter;
            new_order.rid = ((uint64_t)o.price<<32) + rcounter;
            new_order.price = o.price;
            new_order.volume = o.volume;
            new_order.closedvolume = o.closedvolume;
            new_order.type = o.type;
            new_order.owner = o.owner;
        });
        return retR?new_order->rid:new_order->id;
    }

    void removeorder(uint64_t orderid){
        auto itr = order_book.find( orderid );
        if (itr != order_book.end()){
            order_book.erase(itr);
        }
    }

    void getridindex(){
        auto idx = order_book.template get_index<N(rid)>();
        auto biditr = idx.begin();
        auto enditr = idx.end();
        auto itr = descriptions.find(_self);
        auto bid1key = itr->bid1key;
        auto keyitr = idx.find(bid1key);
        print("begin: ", biditr->rid, ", end: ", enditr->rid, ", key: ", keyitr->rid,"\n");
        while (biditr != idx.end()){
            print("current: ", biditr->rid, "\n");
            biditr++;
        }
    }
};

EOSIO_ABI(future, (info)(insertorder)(removeorder)(getridindex))