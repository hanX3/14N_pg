#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#include "G4RunManager.hh"

#include "G4UImanager.hh"
#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"

#include "time.h"
#include "Randomize.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "sys/stat.h" //  mkdir

#include "TROOT.h"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
  gROOT->Reset();

  //  creat file
  G4int saveFlag = 1;
  mkdir("../data", 0777);

  // Detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = 0;
  if(argc==1){
    ui = new G4UIExecutive(argc, argv);
  }

  // Set the Random engine and the seed
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
  G4long seed = time(NULL);
  CLHEP::HepRandom::setTheSeed(seed);

  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // Set mandatory initialization classes
  runManager->SetUserInitialization(new DetectorConstruction());
  G4VModularPhysicsList *physicsList = new PhysicsList();
  //physicsList->RegisterPhysics(new G4StepLimiterPhysics());//set step limit
  runManager->SetUserInitialization(physicsList);
  // Set user action classes
  runManager->SetUserInitialization(new ActionInitialization(saveFlag));
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  // Process macro or start UI session
  if(!ui){
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else{
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    if(ui->IsGUI()) {
      UImanager->ApplyCommand("/control/execute gui.mac");
    }
    ui->SessionStart();
    delete ui;
  }

  delete visManager;
  delete runManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
