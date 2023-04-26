#include "mcmini/transitions/wrappers/MCBankAccountWrappers.h"
#include "mcmini/objects/MCBankAccount.h"
#include "mcmini/transitions/MCTransitionsShared.h"
#include "mcmini/transitions/misc/MCBankAccountDecrement.h"
#include "mcmini/transitions/misc/MCBankAccountIncrement.h"

void
mc_increment_bank_account(int *bank, int amount)
{
  auto shadow = MCBankAccountShadow(bank, amount);
  thread_post_visible_operation_hit<MCBankAccountShadow>(
    typeid(MCBankAccountIncrement), &shadow);
  thread_await_scheduler();
  *bank += amount;
}

void
mc_decrement_bank_account(int *bank, int amount)
{
  auto shadow = MCBankAccountShadow(bank, amount);
  thread_post_visible_operation_hit<MCBankAccountShadow>(
    typeid(MCBankAccountDecrement), &shadow);
  thread_await_scheduler();
  *bank -= amount;
}