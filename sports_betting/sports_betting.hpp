#include <eosiolib/eosio.hpp>
#include <eosiolib/fixedpoint.hpp>
#include <eosiolib/time.hpp>

using namespace eosio;

struct pool{
    uint64_t id;
    account_name platform_owner;
    account_name host;
    time_point expiration;
    time_point start_betting;
    time_point end_betting;
    uint8_t odd_1part;//need checking
    uint8_t odd_2part;//need checking
    fixed_point128<4> pool_size{};
    fixed_point128<4> host_fund{};
    

    EOSLIB_SERIALIZE(pool, (id)(platform_owner)(host)(expiration)\
        (start_betting)(end_betting)(odd_1part)(odd_2part)\
        (pool_size)(host_fund))
};

struct client_bet{
    uint64_t id;
    account_name client;
    fixed_point128<4> client_fund;
    EOSLIB_SERIALIZE(client_bet,(id)(client)(client_fund))
};