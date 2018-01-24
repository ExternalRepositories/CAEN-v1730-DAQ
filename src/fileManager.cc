#include "fileManager.h"
#include <sstream>
#include <stdint.h>

void fileManager::OpenFile(){

  f = new TFile(fname.c_str(), "RECREATE");  //open TFile
  t = new TTree("data", "Waveform data");  //initalize the TTree

  //resize the vector of vectors to have 4 entries
  data.resize(8);  

  stringstream ss;
  
  //add vectors to TTree
  for(int i=0; i<8; i++){
    ss<<i;
    string branch="ch"+ss.str();
    ss.str("");
    if(mask[i]==1){
      t->Branch(branch.c_str(), &data[i]);
    }
  }

  //time is the unix time that the event occured
  t->Branch("time", &TriggerTimeTag, "time/I");

}

void fileManager::CloseFile(){
  t->Write();
  f->Close();
}


void fileManager::addEvent(CAEN_DGTZ_EventInfo_t *EventInfo, CAEN_DGTZ_UINT16_EVENT_t *Event16){
  
  for(int ch=0; ch<8; ch++){
    if(mask[ch]==0)
      continue;
    int Size=Event16->ChSize[ch];
    if(Size<=0)
      continue;

    for(int i=0; i<Size; i++){
      data[ch].push_back(Event16->DataChannel[ch][i]);
    }
    
    TriggerTimeTag = EventInfo->TriggerTimeTag;  


  }

  t->Fill();


  for(int ch=0; ch<8; ch++)
    data[ch].clear();





}