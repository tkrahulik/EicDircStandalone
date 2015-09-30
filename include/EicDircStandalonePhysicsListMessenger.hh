#ifndef EicDircStandalonePhysicsListMessenger_h
#define EicDircStandalonePhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class EicDircStandalonePhysicsList;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class EicDircStandalonePhysicsListMessenger: public G4UImessenger
{
public:
  EicDircStandalonePhysicsListMessenger(EicDircStandalonePhysicsList* );
  ~EicDircStandalonePhysicsListMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  EicDircStandalonePhysicsList*     pPhysicsList;

  G4UIdirectory*        EicDircStandaloneDir;
  G4UIdirectory*        physDir;
  G4UIcmdWithAnInteger* verboseCmd;
  G4UIcmdWithAnInteger* cerenkovCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
