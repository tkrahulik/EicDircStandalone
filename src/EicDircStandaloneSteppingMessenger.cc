#include "EicDircStandaloneSteppingMessenger.hh"
#include "EicDircStandaloneSteppingAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneSteppingMessenger::EicDircStandaloneSteppingMessenger(EicDircStandaloneSteppingAction* step)
  : fStepping(step)
{
  fOneStepPrimariesCmd = new G4UIcmdWithABool("/EicDircStandalone/oneStepPrimaries",this);
  fOneStepPrimariesCmd->SetGuidance("Only allows primaries to go one step in the gas volume before being killed.");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneSteppingMessenger::~EicDircStandaloneSteppingMessenger(){
  delete fOneStepPrimariesCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void
EicDircStandaloneSteppingMessenger::SetNewValue(G4UIcommand* command,G4String newValue){
  if( command == fOneStepPrimariesCmd ){
    fStepping->SetOneStepPrimaries(fOneStepPrimariesCmd->GetNewBoolValue(newValue));
  }
}
