// Make this appear first!
#include "G4Timer.hh"

#include "EicDircStandaloneRunAction.hh"

#include "G4Run.hh"

#include "EicDircStandaloneAnalysis.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneRunAction::EicDircStandaloneRunAction()
{
  timer = new G4Timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneRunAction::~EicDircStandaloneRunAction()
{
  delete timer;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandaloneRunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " starts." << G4endl;
  timer->Start();

  //inform the runManager to save random number seed
  //G4RunManager::GetRunManager()->SetRandomNumberStore(true);

  // Book histograms, ntuple
  //

  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType()
         << " analysis manager" << G4endl;

  // Create directories
  //analysisManager->SetHistoDirectoryName("histograms");
  //analysisManager->SetNtupleDirectoryName("ntuple");

  // Open an output file
  //
  G4String fileName = "simData_EicDircStandalone";
  analysisManager->OpenFile(fileName);

  // Creating tree
  //
  analysisManager->CreateNtuple("photoHits", "photon hits on GEM stack");
  analysisManager->CreateNtupleDColumn("event");
  analysisManager->CreateNtupleDColumn("nhit");
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("wavelength");
  analysisManager->CreateNtupleDColumn("ntotal");
  analysisManager->FinishNtuple();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandaloneRunAction::EndOfRunAction(const G4Run* aRun)
{
  timer->Stop();
  G4int nofEvents = aRun->GetNumberOfEvent();
  G4cout << "number of event = " << nofEvents << " " << *timer << G4endl;

  if ( nofEvents == 0 ) return;

  // save analysis output
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();

  // complete cleanup
  //
  delete G4AnalysisManager::Instance();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
