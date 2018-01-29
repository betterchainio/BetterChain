/**
 *  @file
 *  @copyright defined in BetterChain/LICENSE.txt
 */

namespace dice {

   struct offer_bet {
      betterchain::tokens   amount;
      account_name  player;
      uint256       commitment;
   };

   struct cancel_offer {
      uint256  commitment;
   };

   struct reveal {
      uint256  commitment;
      uint256  source;
   };

   struct claim_expired {
      uint64_t gameid = 0;
   };

   using betterchain_tokens = betterchain::tokens;

   struct offer_primary_key {
      betterchain_tokens          bet;
      account_name        owner;
   };

   /**
    *  This struct is used with i128xi128 index which allows us to lookup and
    *  iterate over offers by either {bet,owner,commitment} or {commitment,bet,owner} 
    *
    *  Only the first 128 bits of commitment ID are used in the index, but there will
    *  be a requirement that these first 128 bits be unique and any collisions will
    *  be rejected.
    *
    *  If there is no existing offer of equal bet size then gameid is set as 0, if it is 
    *  matched then a new game record is created and the offer is modified so that bet
    *  goes to 0 (and therefore moves to end of queue and not matched with other bets) and
    *  the gameid of both offers are updated.
    */
   struct PACKED( offer ) {
      offer_primary_key  primary;
      uint256            commitment;
      uint32_t           gameid = 0;
   };

   struct player {
      uint256     commitment;
      uint256     reveal;
   };

   /**
    *
    */
   struct PACKED( game ) {
      uint32_t   gameid;
      betterchain_tokens bet;
      time       deadline;
      player     player1;
      player     player2;
   };

   struct Packed( global_dice ) {
      uint32_t nextgameid = 0;
   };


   struct PACKED( account ) {
      account( account_name o = account_name() ):owner(o){}

      account_name        owner;
      betterchain_tokens          betterchain_balance;
      uint32_t            open_offers = 0;

      bool is_empty()const { return ! ( bool(betterchain_balance) |  open_offers); }
   };

   using accounts = betterchain::table<N(dice),N(dice),N(account),account,uint64_t>;
   using global_dices = betterchain::table<N(dice),N(dice),N(global),global_dice,uint64_t>;
   using offers = betterchain::table<N(dice),N(dice),N(global),global_dice,offer_primary_key,uint128_t>;

   inline account get_account( account_name owner ) {
      account owned_account(owner);
      accounts::get( owned_account );
      return owned_account;
   }

};
