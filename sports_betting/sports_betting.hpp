#include <eosiolib/eosio.hpp>
#include <eosiolib/fixedpoint.hpp>
#include <eosiolib/time.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;


//@abi table pool i64
struct pool{
    uint64_t id;
    account_name platform_owner;
    account_name host;
    time_point expiration;
    time_point start_betting;
    time_point end_betting;
    uint8_t odd;//need checking
    asset pool_size;
    asset host_balance;

    uint64_t primary_key() const{ return id; }

    EOSLIB_SERIALIZE(pool, (id)(platform_owner)(host)(expiration)\
        (start_betting)(end_betting)(odd_1part)(odd_2part)\
        (pool_size)(host_fund))
};
typedef eosio::multi_index<N(pool), pool> pool_index;

//@abi table client_bet i64
struct client_bet{
    uint64_t id;
    account_name host;
    account_name client;
    asset client_balance;
    uint64_t primary_key() const{ return id; }
    
    EOSLIB_SERIALIZE(client_bet,(id)(client)(client_fund))
};
typedef eosio::multi_index<N(client_bet), client_bet> client_bet_index;