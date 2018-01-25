#include <vector>
#include <bitset>
#include <CAENDigitizer.h>
#include <CAENDigitizerType.h>

#include "TFile.h"
#include "TTree.h"

#include "CAENdaq.h"


using namespace std;

#ifndef FILEMAN_h
#define FILEMAN_h


const double rolloverAdd=21.4748;


class fileManager{

 public:
  fileManager();
  fileManager(string filename, uint16_t EnableMask);

  ~fileManager(){
  }

  void OpenFile();
  void addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16);
  void CloseFile();

  void setRunStartTime(double rstart){
    RunStartTime=rstart;
    nRollover=0;
  }
  
 private:
  
  string fname;
  TFile *f;
  TTree *t;
  vector<vector<double> > data;
  bitset<8> mask;

  double RunStartTime;
  double eventTime;
  bool isOpen;

  uint32_t lastTrigTime;
  int nRollover;


};

#endif
