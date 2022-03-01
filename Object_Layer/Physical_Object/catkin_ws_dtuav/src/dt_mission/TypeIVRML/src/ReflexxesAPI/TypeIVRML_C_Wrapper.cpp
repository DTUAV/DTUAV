





























#include <TypeIVRML_C_Wrapper.h>
#include <RMLPositionInputParameters.h>
#include <RMLPositionOutputParameters.h>
#include <ReflexxesAPI.h>
#include <RMLPositionFlags.h>



bool MEktg=false;
unsigned int vOBw8=(0xd01+6236-0x255d);
ReflexxesAPI*zyNEr=NULL;
RMLPositionInputParameters*ckOJo=NULL;
RMLPositionOutputParameters*I0O0O=NULL;
RMLPositionFlags j2lNR;
RMLVelocityInputParameters*cBL2i=NULL;
RMLVelocityOutputParameters*o27lP=NULL;
RMLVelocityFlags g1bnB;

int TypeIVRMLCreate(const unsigned int NumberOfDOFs,const double nsANK){if((
MEktg)||(nsANK<=0.0)){return(-(0xab5+6376-0x239c));}zyNEr=new ReflexxesAPI(
NumberOfDOFs,nsANK);ckOJo=new RMLPositionInputParameters(NumberOfDOFs);I0O0O=new
 RMLPositionOutputParameters(NumberOfDOFs);cBL2i=new RMLVelocityInputParameters(
NumberOfDOFs);o27lP=new RMLVelocityOutputParameters(NumberOfDOFs);MEktg=true;
vOBw8=NumberOfDOFs;return((0x1c51+326-0x1d97));}

int TypeIVRMLPosition(const double*iPzPj,const double*AQzqu,const double*k6sf4,
const double*hxixi,const double*DAwhk,const double*b4jXr,const double*ldeCA,
const double*HcINC,const int*SelectionVector,double*zpjvt,double*JMglI,double*
Emjyn){unsigned int i=(0x33+2166-0x8a9);int ResultValue=(0x87f+2602-0x12a9);if(!
MEktg){return(-(0x1741+1744-0x1e10));}for(i=(0xf3b+3938-0x1e9d);i<vOBw8;i++){
ckOJo->CurrentPositionVector->VecData[i]=iPzPj[i];ckOJo->CurrentVelocityVector->
VecData[i]=AQzqu[i];ckOJo->CurrentAccelerationVector->VecData[i]=k6sf4[i];ckOJo
->MaxVelocityVector->VecData[i]=hxixi[i];ckOJo->MaxAccelerationVector->VecData[i
]=DAwhk[i];ckOJo->MaxJerkVector->VecData[i]=b4jXr[i];ckOJo->TargetPositionVector
->VecData[i]=ldeCA[i];ckOJo->TargetVelocityVector->VecData[i]=HcINC[i];ckOJo->
SelectionVector->VecData[i]=(SelectionVector[i]>(0x218+696-0x4d0));}ResultValue=
zyNEr->RMLPosition(*ckOJo,I0O0O,j2lNR);for(i=(0x4d9+5867-0x1bc4);i<vOBw8;i++){
zpjvt[i]=I0O0O->NewPositionVector->VecData[i];JMglI[i]=I0O0O->NewVelocityVector
->VecData[i];Emjyn[i]=I0O0O->NewAccelerationVector->VecData[i];}return(
ResultValue);}

int TypeIVRMLVelocity(const double*iPzPj,const double*AQzqu,const double*k6sf4,
const double*DAwhk,const double*b4jXr,const double*HcINC,const int*
SelectionVector,double*zpjvt,double*JMglI,double*Emjyn){unsigned int i=
(0x5cb+784-0x8db);int ResultValue=(0x13ba+1202-0x186c);if(!MEktg){return(-
(0x2d+5261-0x14b9));}for(i=(0x1ac4+300-0x1bf0);i<vOBw8;i++){cBL2i->
CurrentPositionVector->VecData[i]=iPzPj[i];cBL2i->CurrentVelocityVector->VecData
[i]=AQzqu[i];cBL2i->CurrentAccelerationVector->VecData[i]=k6sf4[i];cBL2i->
MaxAccelerationVector->VecData[i]=DAwhk[i];cBL2i->MaxJerkVector->VecData[i]=
b4jXr[i];cBL2i->TargetVelocityVector->VecData[i]=HcINC[i];cBL2i->SelectionVector
->VecData[i]=(SelectionVector[i]>(0x0+4830-0x12de));}ResultValue=zyNEr->
RMLVelocity(*cBL2i,o27lP,g1bnB);for(i=(0x1c0d+2302-0x250b);i<vOBw8;i++){zpjvt[i]
=o27lP->NewPositionVector->VecData[i];JMglI[i]=o27lP->NewVelocityVector->VecData
[i];Emjyn[i]=o27lP->NewAccelerationVector->VecData[i];}return(ResultValue);}

int TypeIVRMLDestroy(void){if(!MEktg){return(-(0x618+5265-0x1aa8));}delete zyNEr
;delete ckOJo;delete I0O0O;delete cBL2i;delete o27lP;vOBw8=(0x12ad+977-0x167e);
MEktg=false;return((0x893+5157-0x1cb8));}
