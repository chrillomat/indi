/*
    Pulsar 2 INDI driver

    Copyright (C) 2016, 2017 Jasem Mutlaq and Camiel Severijns

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef LX200PULSAR2_H
#define LX200PULSAR2_H


#include "lx200generic.h"


class LX200Pulsar2 : public LX200Generic {
 public:  
  LX200Pulsar2(void);
  virtual ~LX200Pulsar2(void) {}
    
  virtual const char *getDefaultName(void);
  virtual bool Connect         (void);
  virtual bool ReadScopeStatus (void);
  virtual void ISGetProperties (const char *dev);
  virtual bool initProperties  (void);
  virtual bool updateProperties(void);
  virtual bool ISNewSwitch     (const char *dev, const char *name, ISState *states, char *names[], int n);
  virtual bool ISNewText       (const char *dev, const char *name, char *texts[], char *names[], int n);
 
 protected:
  virtual bool SetSlewRate    (int index);
  virtual bool MoveNS         (INDI_DIR_NS dir, TelescopeMotionCommand command);
  virtual bool MoveWE         (INDI_DIR_WE dir, TelescopeMotionCommand command);
  virtual bool Abort          (void);
  
  virtual IPState GuideNorth  (float ms);
  virtual IPState GuideSouth  (float ms);
  virtual IPState GuideEast   (float ms);
  virtual IPState GuideWest   (float ms);

  virtual bool updateTime     (ln_date* utc,double utc_offset);
  virtual bool updateLocation (double latitude,double longitude,double elevation);

  virtual bool Goto           (double,double);
  virtual bool Park           (void);
  virtual bool Sync           (double ra, double dec);
  virtual bool UnPark         (void);

  virtual bool isSlewComplete (void); 
  virtual bool checkConnection(void);

  virtual void getBasicData   (void);

  // At which side of the pier the telescope is located: east or west
  ISwitchVectorProperty PierSideSP;
  ISwitch PierSideS[2];
  // Periodic error correction on or off
  ISwitchVectorProperty PeriodicErrorCorrectionSP;
  ISwitch PeriodicErrorCorrectionS[2];
  // Pole crossing on or off
  ISwitchVectorProperty PoleCrossingSP;
  ISwitch PoleCrossingS[2];
  // Refraction correction on or off
  ISwitchVectorProperty RefractionCorrectionSP;
  ISwitch RefractionCorrectionS[2];

 private:
  void sendScopeLocation(void);
  void sendScopeTime    (void);
  
  void        guideTimeout      (void);
  static void guideTimeoutHelper(void *p);

  bool isSlewing(void);

  bool just_started_slewing;
};

#endif
