Sheet of Flame Simulation

  This is a bare-bones Geant4 simulation where we can study the sheet
  of flame produced from the beam hitting the frozen ammonia target.
  Hits in a spherical sensitive detector are saved to a root tree.

1. Geometry
	
   The geometry is constructed in the B1DetectorConstruction class.
   A tiny cylindrical target cell is placed within a spherical sensitive
   detector inside a cubic world volume.

2. Physics List	

   The particle's type and the physic processes which will be available
   in this example are set in the QBBC physics list. This physics list 
   requires data files for electromagnetic and hadronic processes.
   See more on installation of the datasets in
   <a href="http://geant4.web.cern.ch/geant4/UserDocumentation/UsersGuides
                                         /InstallationGuide/html/ch03s03.html">
   Geant4 Installation Guide, Chapter 3.3: Note On Geant4 Datasets </a>.
   The following datasets: G4LEDATA, G4LEVELGAMMADATA, G4NEUTRONXSDATA,
   G4SAIDXSDATA and G4ENSDFSTATEDATA are mandatory for this example.
 
   In addition the build-in interactive command:
\verbatim
/process/(in)activate processName
\endverbatim
     allows to activate/inactivate the processes one by one.
     
3. Action Initialization

   A newly introduced class, B1ActionInitialization, instantiates and registers 
   to Geant4 kernel all user action classes.

   While in sequential mode the action classes are instatiated just once,
   via invoking the method:
      B1ActionInitialization::Build() 
   in multi-threading mode the same method is invoked for each thread worker
   and so all user action classes are defined thread-local.

   A run action class is instantiated both thread-local 
   and global that's why its instance is created also in the method
      B1ActionInitialization::BuildForMaster() 
   which is invoked only in multi-threading mode.
     
4. Primary Generator

   The primary generator is defined in the B1PrimaryGeneratorAction class.
   The default kinematics is a 2.2 GeV electron.
   This default setting can be changed via the Geant4 built-in commands 
   of the G4ParticleGun class.
   
5. Detector Response

   A sensitive detector (B1SphereSD) has been implemented to record the
   amount of radiation leaving the target.

   At end of event, the tree is filled with all hit information
   from the event.



The following paragraphs are common to all basic examples

\section B1_A VISUALISATION

   The visualization manager is set via the G4VisExecutive class
   in the main() function in exampleB1.cc.    
   The initialisation of the drawing is done via a set of /vis/ commands
   in the macro vis.mac. This macro is automatically read from
   the main function when the example is used in interactive running mode.

   By default, vis.mac opens an OpenGL viewer (/vis/open OGL).
   The user can change the initial viewer by commenting out this line
   and instead uncommenting one of the other /vis/open statements, such as
   HepRepFile or DAWNFILE (which produce files that can be viewed with the
   HepRApp and DAWN viewers, respectively).  Note that one can always
   open new viewers at any time from the command line.  For example, if
   you already have a view in, say, an OpenGL window with a name
   "viewer-0", then
\verbatim
/vis/open DAWNFILE
\endverbatim
   then to get the same view
\verbatim
/vis/viewer/copyView viewer-0
\endverbatim
   or to get the same view *plus* scene-modifications
\verbatim
/vis/viewer/set/all viewer-0
\endverbatim
   then to see the result
\verbatim
/vis/viewer/flush
\endverbatim

   The DAWNFILE, HepRepFile drivers are always available
   (since they require no external libraries), but the OGL driver requires
   that the Geant4 libraries have been built with the OpenGL option.

   From Release 9.6 the vis.mac macro in example B1 has additional commands
   that demonstrate additional functionality of the vis system, such as
   displaying text, axes, scales, date, logo and shows how to change
   viewpoint and style.  Consider copying these to other examples or
   your application.  To see even more commands use help or
   ls or browse the available UI commands in the Application
   Developers Guide, Section 7.1.

   For more information on visualization, including information on how to
   install and run DAWN, OpenGL and HepRApp, see the visualization tutorials,
   for example,\n
   - <a href="http://geant4.slac.stanford.edu/Presentations/vis/G4OpenGLTutorial/G4OpenGLTutorial.html">
     OpenGL Tutorial </a>
   - <a href="http://geant4.slac.stanford.edu/Presentations/vis/G4DAWNTutorial/G4DAWNTutorial.html">
     DAWN Tutorial </a>
   - <a href="http://geant4.slac.stanford.edu/Presentations/vis/G4HepRAppTutorial/G4HepRAppTutorial.html">
     HepRApp Tutorial </a>

   The tracks are automatically drawn at the end of each event, accumulated
   for all events and erased at the beginning of the next run.


\section B1_B USER INTERFACES
 
   The user command interface is set via the G4UIExecutive class
   in the main() function in exampleB1.cc 
   The selection of the user command interface is then done automatically 
   according to the Geant4 configuration or it can be done explicitly via 
   the third argument of the G4UIExecutive constructor (see exampleB4a.cc). 
   
\section B1_C HOW TO RUN

   - Execute exampleB1 in the 'interactive mode' with visualization
\verbatim
% exampleB1
and type in the commands from run1.mac line by line:
Idle> /control/verbose 2
Idle> /tracking/verbose 1
Idle> /run/beamOn 10 
Idle> ...
Idle> exit
\endverbatim                
      or
\verbatim
Idle> /control/execute run1.mac
....
Idle> exit
\endverbatim                

   - Execute exampleB1 in the 'batch' mode from macro files 
   (without visualization)
\verbatim
% exampleB1 run2.mac
% exampleB1 exampleB1.in > exampleB1.out
\endverbatim                

*/

	
