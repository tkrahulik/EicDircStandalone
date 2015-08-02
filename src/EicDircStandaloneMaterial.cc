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
  Q = manager->FindOrBuildMaterial("G4_Silicon_Dioxide");

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

  //Quartz
  //
  //Quartz = new G4Material("Quartz", density = 2.200*g/cm3, nelements=1);
  //Quartz->AddMaterial(Q, 100.*perCent);

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

  OpticalDIRCSurface = new G4OpticalSurface("OpticalDIRCSurface", glisur, polished, dielectric_dielectric);

  G4double dirc_ephoton[32] = 
    { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
      2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
      2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
      2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
      2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
      3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
      3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
      3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV
    };


  G4double dirc_REFL[32] = 
    { 0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900,
      0.900, 0.900, 0.900, 0.900     
    };

  G4double dirc_EFF[32] = 
    { 1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.,
      1., 1., 1., 1.
    };


  G4MaterialPropertiesTable* OpticalDIRCSurface_MPT = new G4MaterialPropertiesTable();
  OpticalDIRCSurface_MPT->AddProperty("EFFICIENCY", dirc_ephoton, dirc_EFF, 32);
  OpticalDIRCSurface_MPT->AddProperty("REFLECTIVITY", dirc_ephoton, dirc_REFL, 32);
  OpticalDIRCSurface->SetMaterialPropertiesTable(OpticalDIRCSurface_MPT);

  // LHCb: There is a quartz for the mirror and
  // another quartz which is used in aerogel and
  // yet another quartz used for the quartz window.
  // Mirrorquartz

  SiO2MirrorQuartz = new G4Material("MirrorQuartz", density=2.200*g/cm3, nelements=2);
  SiO2MirrorQuartz->AddElement(Si,natoms=1);
  SiO2MirrorQuartz->AddElement(O,natoms=2);

  G4int NumPhotWaveLengthBins = 2;

  G4double MirrorQuartzRindex[2]={1.35,1.35};
  G4double MirrorQuartzAbsorpLength[2]={1,1};

  G4double PhotonMomentum[2]={0.1*eV,1000*eV};

  //  G4double* MirrorQuartzRindex=new G4double[NumPhotWaveLengthBins];
  //  G4double* MirrorQuartzAbsorpLength=new G4double[NumPhotWaveLengthBins];

  //  for (ibin=0; ibin<NumPhotWaveLengthBins; ibin++){
  //    MirrorQuartzAbsorpLength[ibin]=0.01*mm;
  //
  //  }
  G4MaterialPropertiesTable* MirrorQuartzMPT =
    new G4MaterialPropertiesTable();


  MirrorQuartzMPT->AddProperty("ABSLENGTH",PhotonMomentum,
                               MirrorQuartzAbsorpLength,NumPhotWaveLengthBins);


  SiO2MirrorQuartz->SetMaterialPropertiesTable(MirrorQuartzMPT);


  // Generate & Add Material Properties Table
  //

  //Front (reflecting surface of RichTb Mirror)
  //

  OpticalMirrorSurface = new G4OpticalSurface("OpticalMirrorSurface");

  //G4String mirrortype = "LHCb";
  G4String mirrortype = "G4example";

  if ( mirrortype == "LHCb" )
    { // LHCb mirror
      // First define wavelength in nm.
      // For now assume that all segments have the same reflectivity.
      // Hence the reflectivity is defined outside the loop of the
      // the number of segments.
      // Only the front surface is created.
      // The abosorption length is set to a small value just to
      // avoid photons exiting from the back of the mirror.
      // the efficiency is for the absorption process.

      G4int NumPhotonRichMirrorReflWaveLengthBins = 63;
      G4double PhotMomWaveConv=1243.125;

      //Mirror reflectivity
      // In the following, the bins at 100 nm, and 1000nm are
      // defined just for convenience of interpolation.
      // They are not measured points.

      static const G4double PhotonWavelengthRefl[]=
        {100.0, 200.0, 210.0, 220.0, 230.0, 240.0, 250.0, 260.0, 270.0, 280.0,
         290.0, 300.0, 310.0, 320.0, 330.0, 340.0, 350.0, 360.0, 370.0, 380.0,
         390.0, 400.0, 410.0, 420.0, 430.0, 440.0, 450.0, 460.0, 470.0, 480.0,
         490.0, 500.0, 510.0, 520.0, 530.0, 540.0, 550.0, 560.0, 570.0, 580.0,
         590.0, 600.0, 610.0, 620.0, 630.0, 640.0, 650.0, 660.0, 670.0, 680.0,
         690.0, 700.0, 710.0, 720.0, 730.0, 740.0, 750.0, 760.0, 770.0, 780.0,
         790.0, 800.0, 1000.0 };

      static const G4double RichTbMirrorReflectivity[]=
        {0.0, 0.9106, 0.9232, 0.9285, 0.9314, 0.9323, 0.9312, 0.9287, 0.9264,
         0.9234, 0.9195, 0.9156, 0.9109, 0.9066, 0.9022, 0.8981, 0.8925, 0.8883,
         0.8836, 0.8796, 0.8756, 0.8727, 0.8697, 0.8672, 0.8653, 0.8636, 0.8624,
         0.8612, 0.8608, 0.8601, 0.8601, 0.8601, 0.8600, 0.8603, 0.8603, 0.8604,
         0.8605, 0.8608, 0.8609, 0.8608, 0.8608, 0.8606, 0.8604, 0.8600, 0.8598,
         0.8591, 0.8581, 0.8573, 0.8563, 0.8549, 0.8535, 0.8517, 0.8497, 0.8475,
         0.8447, 0.8417, 0.8382, 0.8388, 0.8296, 0.8258, 0.8204, 0.8172, 0.8172 };

      static const G4double RichTbMirrorEfficiency[]=
        {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
         0.0, 0.0, 0.0 };

      G4double* PhotonMomentumRefl
        =new G4double[NumPhotonRichMirrorReflWaveLengthBins];
      G4double* PhotWaveRefl =
        new  G4double[NumPhotonRichMirrorReflWaveLengthBins];
      G4double* PhotReflEff =new  G4double[NumPhotonRichMirrorReflWaveLengthBins];
      G4double* MirrorQuRefIndex
        =new  G4double[NumPhotonRichMirrorReflWaveLengthBins];

      for (G4int ibin=0; ibin<NumPhotonRichMirrorReflWaveLengthBins; ibin++){
        PhotonMomentumRefl[ibin]=PhotMomWaveConv*eV/ PhotonWavelengthRefl[ibin];
        PhotWaveRefl[ibin]=  RichTbMirrorReflectivity[ibin];
        PhotReflEff[ibin]= RichTbMirrorEfficiency[ibin];
        //the following lines to avoid reflection at the mirror.

        MirrorQuRefIndex[ibin] = 1.40;
      }

      //      OpticalMirrorSurface->SetType(dielectric_metal);
      OpticalMirrorSurface->SetType(dielectric_dielectric);
      OpticalMirrorSurface->SetModel(glisur);
      OpticalMirrorSurface->SetFinish(polished);

      G4MaterialPropertiesTable* OpticalMirrorSurfaceMPT = new G4MaterialPropertiesTable();

      OpticalMirrorSurfaceMPT->AddProperty("RINDEX",
                                           PhotonMomentumRefl,
                                           MirrorQuRefIndex,
                                           NumPhotonRichMirrorReflWaveLengthBins);
      OpticalMirrorSurfaceMPT->AddProperty("REFLECTIVITY",
                                           PhotonMomentumRefl,
                                           PhotWaveRefl,
                                           NumPhotonRichMirrorReflWaveLengthBins);
      OpticalMirrorSurfaceMPT->AddProperty("EFFICIENCY",
                                           PhotonMomentumRefl,
                                           PhotReflEff,
                                           NumPhotonRichMirrorReflWaveLengthBins);

      OpticalMirrorSurface->SetMaterialPropertiesTable(OpticalMirrorSurfaceMPT);

      OpticalMirrorSurface->DumpInfo();
    } // end LHCb mirror

  else if ( mirrortype == "G4example" )
    { // test from G4 example
      const G4int NUM = 2;

      G4double pp[NUM] = {2.038*eV, 4.144*eV};
      //G4double specularlobe[NUM] = {0.3, 0.3};
      //G4double specularspike[NUM] = {0.2, 0.2};
      //G4double backscatter[NUM] = {0.1, 0.1};
      //G4double rindex[NUM] = {1.35, 1.40};
      G4double rindex[NUM] = {1.4, 1.4};
      G4double reflectivity[NUM] = {1.0, 1.0};
      G4double efficiency[NUM] = {0.0, 0.0};

      G4MaterialPropertiesTable* SMPT = new G4MaterialPropertiesTable();

      SMPT -> AddProperty("RINDEX",pp,rindex,NUM);
      //SMPT -> AddProperty("SPECULARLOBECONSTANT",pp,specularlobe,NUM);
      //SMPT -> AddProperty("SPECULARSPIKECONSTANT",pp,specularspike,NUM);
      //SMPT -> AddProperty("BACKSCATTERCONSTANT",pp,backscatter,NUM);
      SMPT -> AddProperty("REFLECTIVITY",pp,reflectivity,NUM);
      SMPT -> AddProperty("EFFICIENCY",pp,efficiency,NUM);

      //OpticalMirrorSurface->SetMaterialPropertiesTable(SMPT);

      OpticalMirrorSurface->SetType(dielectric_metal);
      OpticalMirrorSurface->SetModel(glisur);
      OpticalMirrorSurface->SetFinish(polished);

      OpticalMirrorSurface->DumpInfo();
    } // end test

  // GEM stack photocathode (CsI coating of top GEM)
  //
  OpticalPhotocathodeSurface = new G4OpticalSurface("OpticalPhotocathodeSurface", glisur, polished, dielectric_metal);

  G4double photocath_EPHOTON[2]={1.,1000.};
  G4double photocath_EFF[2]={1.,1.};
  G4double photocath_REFL[2]={0.,0.};

  G4MaterialPropertiesTable* OpticalPhotocathodeSurface_MPT = new G4MaterialPropertiesTable();
  OpticalPhotocathodeSurface_MPT->AddProperty("EFFICIENCY",photocath_EPHOTON,photocath_EFF,2);
  OpticalPhotocathodeSurface_MPT->AddProperty("REFLECTIVITY",photocath_EPHOTON,photocath_REFL,2);
  OpticalPhotocathodeSurface->SetMaterialPropertiesTable(OpticalPhotocathodeSurface_MPT);

  // done
  //
  return;

}


EicDircStandaloneMaterial::~EicDircStandaloneMaterial(){ }
