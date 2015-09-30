#include "EicDircStandaloneEventAction.hh"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "EicDircStandaloneAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneEventAction::EicDircStandaloneEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EicDircStandaloneEventAction::~EicDircStandaloneEventAction()
{}


EicDircStandalonePhotoHitsCollection* EicDircStandaloneEventAction::GetPhotoHitsCollection(const G4String& hcName, const G4Event* event)
{
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(hcName);

  EicDircStandalonePhotoHitsCollection* hitsCollection
    = static_cast<EicDircStandalonePhotoHitsCollection*>(
                                           event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4cerr << "Cannot access hitsCollection " << hcName << G4endl;
    exit(1);
  }

  return hitsCollection;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandaloneEventAction::BeginOfEventAction(const G4Event*)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EicDircStandaloneEventAction::EndOfEventAction(const G4Event* evt)
{
  // Get hits collections
  //
  EicDircStandalonePhotoHitsCollection* photoHits = GetPhotoHitsCollection("PhotoHitsCollection", evt);

  //photoHits->PrintAllHits();

  // Print per event (modulo n)
  //
  G4int eventID = evt->GetEventID();

  // Fill histograms, ntuple
  //

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill ntuple
  for ( G4int ihit = 0; ihit < (G4int)photoHits->GetSize(); ihit++ )
    {
      EicDircStandalonePhotoHit* photoHit_i = static_cast<EicDircStandalonePhotoHit*>( photoHits->GetHit(ihit) );
      analysisManager->FillNtupleDColumn(0, eventID);
      analysisManager->FillNtupleDColumn(1, ihit+1 );
      analysisManager->FillNtupleDColumn(2, photoHit_i->GetHitPos().getX() );
      analysisManager->FillNtupleDColumn(3, photoHit_i->GetHitPos().getY() );
      analysisManager->FillNtupleDColumn(4, photoHit_i->GetHitPos().getZ() );
      analysisManager->FillNtupleDColumn(5, photoHits->GetSize() );
      analysisManager->AddNtupleRow();
    }

  // periodic printing
  //
  if (eventID < 100 || eventID%100 == 0) {
    G4cout << ">>> Event " << evt->GetEventID() << " finished." << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
