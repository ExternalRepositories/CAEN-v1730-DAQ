#include <vector>
#include <bitset>
#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>
#include "util.h"

#include "TFile.h"
#include "TTree.h"

#include "CAENdaq.h"


using namespace std;

#ifndef FILEMAN_h
#define FILEMAN_h


const double rolloverAdd=8e-9*2147483647;


class fileManager{

 public:
  fileManager(){
    initialized=false;
  }
  fileManager(string filename, uint16_t EnableMask, int saveInt){
    init(filename, EnableMask, saveInt);
  }

  ~fileManager(){
  }
    
  void init(string filename, uint16_t EnableMask, int saveInt);
  void OpenFile();
  void OpenNewFile();
  void addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16);
  void CloseFile();
  void DeleteDir();
  void setVerbose(bool v){verbose=v;}
  bool isInit(){return initialized;}

  void setRunStartTime(double rstart){
    RunStartTime=rstart;
    for(int i=0; i<8; i++){
      lastTrigTime[i]=0;
      nRollover[i]=0;
    }
  }

  
 private:

  
  bool verbose;
  bool initialized;
  
  string fname;
  string dirname;
  TFile *f;
  TTree *t;
  vector<vector<double> > data;
  bitset<8> mask;

  double RunStartTime;
  double eventTime;
  bool isOpen;

  uint32_t lastTrigTime[8];
  int nRollover[8];
  
  double xinc;

  int saveInterval;
  int counter;
  int fileCounter;

  string finalFilename;

};

#endif
