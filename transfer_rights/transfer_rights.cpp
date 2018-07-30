#include "transfer_rights.hpp"
#include "abieos_numeric.hpp"

using namespace eosio;
using namespace std;

class transfer_rights: public contract{
    public:

    transfer_rights(account_name self): eosio::contract(self){}

    //must have eosio.code permission in owner group
    void transfer(const string key_str){
        const abieos::public_key pubkey = 
            abieos::string_to_public_key(key_str);

        array<char, 33> pubkey_char;
        copy(pubkey.data.begin(), pubkey.data.end(),
            pubkey_char.begin());

        const auto auth = authority{
            1, {{{(uint8_t)abieos::key_type::k1, pubkey_char}, 1}}, {}, {}
        };

        INLINE_ACTION_SENDER(call::eosio, updateauth)
        (N(eosio), {{_self, N(owner)}}, {_self, N(active), N(owner), auth});

        INLINE_ACTION_SENDER(call::eosio, updateauth)
        (N(eosio), {{_self, N(owner)}}, {_self, N(owner), N(), auth});
    }
};

EOSIO_ABI(transfer_rights, (transfer))