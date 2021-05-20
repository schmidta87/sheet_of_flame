//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "B1MagneticField.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4MagneticField.hh"

#include "G4Element.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{ 
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  // World **********************************************
  G4double world_size=2.2*m;
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
	      0.5*world_size, 0.5*world_size, 0.5*world_size);     //its size

  
  G4Element* elH  = nist->FindOrBuildElement(1,true);
  //G4Element* elC  = nist->FindOrBuildElement(7,true);
  G4Element* elN  = nist->FindOrBuildElement(7,true);
  G4Element* elO  = nist->FindOrBuildElement(8,true);

  G4Material* high_vacuum = new G4Material("high_vacuum",1.e-16*g/cm3,2,kStateGas,300.*kelvin,1.e-13*atmosphere);
  high_vacuum->AddElement(elN,0.8);
  high_vacuum->AddElement(elO,0.2);

      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
			high_vacuum,         //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking

  // Target Cell **************************************

  G4Tubs* solidTarget = new G4Tubs("Target",  // name
				   0.,        // inner radius
				   2.1*cm,    // outer radius
				   1.5*cm,    // half-length
				   0.,        // starting angle
				   360.*deg); // spanning angle
				   
  G4Material * frozen_ammonia = new G4Material("frozen_ammonia",0.817*g/cm3,2);
  frozen_ammonia->AddElement(elN,0.25);
  frozen_ammonia->AddElement(elH,0.75);

  G4LogicalVolume* logicTarget = new G4LogicalVolume(solidTarget,
						     frozen_ammonia,
						     "Target");

  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicTarget,             //its logical volume
                    "Target",                //its name
                    logicWorld,              //its mother volumee
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking


  // Detector Shell **************************************

  G4Sphere * solidDet = new G4Sphere("Det",     // name
				     1.0*m,     // inner rad
				     1.001*m,   // outer rad
				     0.*deg,    // starting phi
				     360.*deg,  // ending phi
				     0.*deg,    // starting theta
				     180.*deg); // ending theta
				     
  G4LogicalVolume* logicDet = new G4LogicalVolume(solidDet,
						  high_vacuum,
						  "Det");


  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicDet,                //its logical volume
                    "Det",                   //its name
                    logicWorld,              //its mother volumee
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
  
  fScoringVolume = logicDet;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
