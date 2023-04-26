#ifndef INCLUDE_MCMINI_TRANSITIONS_MISC_MCBANKACCOUNTINCREMENT_HPP
#define INCLUDE_MCMINI_TRANSITIONS_MISC_MCBANKACCOUNTINCREMENT_HPP

#include "mcmini/MCTransition.h"
#include "mcmini/objects/MCBankAccount.h"

MCTransition *MCReadBankAccountIncrement(const MCSharedTransition *,
                                         void *, MCState *);

struct MCBankAccountIncrement : public MCTransition {
private:

  unsigned amount;

public:

  std::shared_ptr<MCBankAccount> bank;

  MCBankAccountIncrement(std::shared_ptr<MCThread> thread,
                         std::shared_ptr<MCBankAccount> bank)
    : MCTransition(std::move(thread)), bank(std::move(bank))
  {}

  std::shared_ptr<MCTransition> staticCopy() const override;
  std::shared_ptr<MCTransition>
  dynamicCopyInState(const MCState *) const override;

  void applyToState(MCState *) override;
  bool dependentWith(const MCTransition *) const override;
  void print() const override;
};

#endif // INCLUDE_MCMINI_TRANSITIONS_MISC_MCBANKACCOUNTINCREMENT_HPP
