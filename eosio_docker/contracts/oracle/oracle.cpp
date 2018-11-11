#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class oracle : public contract {
    struct appaction {
     uint64_t key;
     std::string event;
     std::string payload;
     uint64_t primary_key() const { return key; }
  };
  public:
    
    oracle(name receiver, name code, datastream<const char*> ds):contract(receiver, code, ds) {}
    
    typedef eosio::multi_index< "appaction"_n, appaction > app_action_index;
    
    [[eosio::action]]
    void myaction(std::string event, std::string payload) {
      app_action_index app_actions(_self, _self.value);  // code, scope
      // add to table, first argument is account to bill for storage
      app_actions.emplace(_self, [&](auto& app_action) {
        app_action.key = app_actions.available_primary_key();
       app_action.event = event;
       app_action.payload = payload;
      });
    }
      

     
};
EOSIO_DISPATCH(oracle, (myaction) )