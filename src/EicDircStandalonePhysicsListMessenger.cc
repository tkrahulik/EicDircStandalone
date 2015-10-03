
#include "EicDircStandalonePhysicsListMessenger.hh"

#include "EicDircStandalonePhysicsList.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePhysicsListMessenger::EicDircStandalonePhysicsListMessenger(EicDircStandalonePhysicsList* pPhys)
 :pPhysicsList(pPhys)
{
  EicDircStandaloneDir = new G4UIdirectory("/EicDircStandalone/");
  EicDircStandaloneDir->SetGuidance("UI commands of this example");

  physDir = new G4UIdirectory("/EicDircStandalone/phys/");
  physDir->SetGuidance("PhysicsList control");

  verboseCmd = new G4UIcmdWithAnInteger("/EicDircStandalone/phys/verbose",this);
  verboseCmd->SetGuidance("set verbose for physics processes");
  verboseCmd->SetParameterName("verbose",true);
  verboseCmd->SetDefaultValue(1);
  verboseCmd->SetRange("verbose>=0");
  verboseCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  cerenkovCmd = new G4UIcmdWithAnInteger("/EicDircStandalone/phys/cerenkovMaxPhotons",this);
  cerenkovCmd->SetGuidance("set max nb of photons per step");
  cerenkovCmd->SetParameterName("MaxNumber",false);
  cerenkovCmd->SetRange("MaxNumber>=0");
  cerenkovCmd->AvailableForStates(G4State_Idle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandalonePhysicsListMessenger::~EicDircStandalonePhysicsListMessenger()
{
  delete verboseCmd;
  delete cerenkovCmd;
  delete physDir;
  delete EicDircStandaloneDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandalonePhysicsListMessenger::SetNewValue(G4UIcommand* command,
                                             G4String newValue)
{
  if( command == verboseCmd )
    { pPhysicsList->SetVerbose(verboseCmd->GetNewIntValue(newValue));}

  if( command == cerenkovCmd )
    {pPhysicsList->SetNbOfPhotonsCerenkov(cerenkovCmd->GetNewIntValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
