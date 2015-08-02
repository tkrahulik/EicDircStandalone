#ifndef EicDircStandaloneSteppingMessenger_h
#define EicDircStandaloneSteppingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class EicDircStandaloneSteppingAction;
class G4UIcmdWithABool;

/** @TODO Review this class completely
 */
class EicDircStandaloneSteppingMessenger: public G4UImessenger
{
public:
  EicDircStandaloneSteppingMessenger(EicDircStandaloneSteppingAction*);
  virtual ~EicDircStandaloneSteppingMessenger();

  virtual void SetNewValue(G4UIcommand*, G4String);

private:

  EicDircStandaloneSteppingAction*        fStepping;
  G4UIcmdWithABool*  fOneStepPrimariesCmd;
};

#endif
