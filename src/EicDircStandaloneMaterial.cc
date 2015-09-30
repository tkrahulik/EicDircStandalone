#include <iostream>
#include <cmath>

#include "globals.hh"

#include "EicDircStandaloneMaterial.hh"

#include "G4Isotope.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"
#include "G4Material.hh"
#include "G4MaterialTable.hh"
#include "G4UnitsTable.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4MaterialPropertyVector.hh"

//#include "EicDircStandaloneMaterialParameters.hh"
//#include "EicDircStandaloneGeometryParameters.hh"


EicDircStandaloneMaterial::EicDircStandaloneMaterial(){

  G4double a; //atomic mass
  G4double z;  //atomic number
  G4double density; //density
  G4double temperature; //temperature
  G4double pressure; //pressure

  G4int nelements;
  G4int natoms;

  //  // Elements
  //  //
  //  H  = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  //  N  = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  //  O  = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);
  //  C  = new G4Element("Carbon", "C", z=6 , a=12.01*g/mole);
  //  F  = new G4Element("Fluorine", "F", z=9 , a=19.00*g/mole);

  // G4 database on G4Elements
  G4NistManager* manager = G4NistManager::Instance();
  manager->SetVerbose(0);
  //
  // define Elements
  //

  H  = manager->FindOrBuildElement(1);
  N  = manager->FindOrBuildElement(7);
  O  = manager->FindOrBuildElement(8);
  C  = manager->FindOrBuildElement(6);
  F  = manager->FindOrBuildElement(9);
  Si = manager->FindOrBuildElement(14);

  //Vacuum
  //
  density=universe_mean_density;
  a=1.01*g/mole;
  pressure=1.e-19*pascal;
  temperature=0.1*kelvin;

  Vacuum = new G4Material("Galactic",density,nelements=1,kStateGas,temperature,pressure);
  Vacuum->AddElement(H,natoms=1);

  // Air
  //
  AmbientAir = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  AmbientAir->AddElement(N, 70.*perCent);
  AmbientAir->AddElement(O, 30.*perCent);

  const G4int air_nEntries = 32;

  G4double air_PhotonEnergy[air_nEntries] =
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV
    };

  G4double air_RefractiveIndex[air_nEntries] = 
    { 1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029,
      1.00029, 1.00029, 1.00029, 1.00029
    };
  /*
  G4double air_RefractiveIndex[air_nEntries] =
    { 1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0,
      1.0, 1.0, 1.0, 1.0
    };
  */
  G4MaterialPropertiesTable* fMPT_air = new G4MaterialPropertiesTable();

  fMPT_air->AddProperty("RINDEX", air_PhotonEnergy, air_RefractiveIndex, air_nEntries )->SetSpline(true);

  AmbientAir->SetMaterialPropertiesTable(fMPT_air);

  //Quartz
  //
  Quartz = new G4Material("Quartz", density=2.200*g/cm3, nelements=2);
  Quartz->AddElement(Si, natoms=1);
  Quartz->AddElement(O, natoms=2);

  const G4int q_nEntries = 32;

  G4double q_PhotonEnergy[q_nEntries] = 
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV
    };

  G4double q_RefractiveIndex[q_nEntries] = 
    { 1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457,
      1.457, 1.457, 1.457, 1.457
    };

  G4double q_ReflectiveIndex[q_nEntries] = 
    { 0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900     
    };

  G4MaterialPropertiesTable* fMPT_q = new G4MaterialPropertiesTable();

  fMPT_q->AddProperty("RINDEX", q_PhotonEnergy, q_RefractiveIndex, q_nEntries )->SetSpline(true);
  fMPT_q->AddProperty("REFLECTIVITY", q_PhotonEnergy, q_ReflectiveIndex, q_nEntries)->SetSpline(true);

  Quartz->SetMaterialPropertiesTable(fMPT_q);
  Quartz->SetMaterialPropertiesTable(fMPT_q);

  // done
  //
  return;

}

EicDircStandaloneMaterial::~EicDircStandaloneMaterial(){ }
