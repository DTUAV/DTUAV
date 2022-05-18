/*
© Guangdong University of Technology,
© The Laboratory of Intelligent Decision and Cooperative Control,
© 2021-2022,
© Author: Yuanlin Yang (yongwang0808@163.com)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
<http://www.apache.org/licenses/LICENSE-2.0>.
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
//  ---------------------- Doxygen info ----------------------
//  ----------------------------------------------------------
//   For a convenient reading of this file's source code,
//   please use a tab width of four characters.
//  ----------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>

#include <../TypeIVRML/include/ReflexxesAPI.h>
#include <../TypeIVRML/include/RMLPositionFlags.h>
#include <../TypeIVRML/include/RMLPositionInputParameters.h>
#include <../TypeIVRML/include/RMLPositionOutputParameters.h>
#include "iostream"

//*************************************************************************
// defines

#define CYCLE_TIME_IN_SECONDS                   0.1
#define NUMBER_OF_DOFS                          3


//*************************************************************************
// Main function to run the process that contains the test application
//
// This function contains source code to get started with the Type II
// Reflexxes Motion Library. Only a minimum amount of functionality is
// contained in this program: a simple trajectory for a
// three-degree-of-freedom system is executed. This code snippet
// directly corresponds to the example trajectories shown in the
// documentation.
//*************************************************************************
int main()
{
    // ********************************************************************
    // Variable declarations and definitions

    int                         ResultValue                 =   0       ;

    ReflexxesAPI                *RML                        =   NULL    ;

    RMLPositionInputParameters  *IP                         =   NULL    ;

    RMLPositionOutputParameters *OP                         =   NULL    ;

    RMLPositionFlags            Flags                                   ;

    // ********************************************************************
    // Creating all relevant objects of the Type II Reflexxes Motion Library

    RML =   new ReflexxesAPI(                   NUMBER_OF_DOFS
                                            ,   CYCLE_TIME_IN_SECONDS   );

    IP  =   new RMLPositionInputParameters(     NUMBER_OF_DOFS          );

    OP  =   new RMLPositionOutputParameters(    NUMBER_OF_DOFS          );

    // ********************************************************************
    // Set-up a timer with a period of one millisecond
    // (not implemented in this example in order to keep it simple)
    // ********************************************************************

    printf("-------------------------------------------------------\n"  );
    printf("Reflexxes Motion Libraries                             \n"  );
    printf("Example: 01_RMLPositionSampleApplication               \n\n");
    printf("This example demonstrates the most basic use of the    \n"  );
    printf("Reflexxes API (class ReflexxesAPI) using the position- \n"  );
    printf("based Type II Online Trajectory Generation algorithm.  \n\n");
    printf("Copyright (C) 2014 Reflexxes GmbH                      \n"  );
    printf("-------------------------------------------------------\n"  );

    // ********************************************************************
    // Set-up the input parameters

    // In this test program, arbitrary values are chosen. If executed on a
    // real robot or mechanical system, the position is read and stored in
    // an RMLPositionInputParameters::CurrentPositionVector vector object.
    // For the very first motion after starting the controller, velocities
    // and acceleration are commonly set to zero. The desired target state
    // of motion and the motion constraints depend on the robot and the
    // current task/application.
    // The internal data structures make use of native C data types
    // (e.g., IP->CurrentPositionVector->VecData is a pointer to
    // an array of NUMBER_OF_DOFS double values), such that the Reflexxes
    // Library can be used in a universal way.

    IP->CurrentPositionVector->VecData      [0] =    0.0      ;
    IP->CurrentPositionVector->VecData      [1] =      0.0      ;
    IP->CurrentPositionVector->VecData      [2] =    0.0      ;

    IP->CurrentVelocityVector->VecData      [0] =    0.0      ;
    IP->CurrentVelocityVector->VecData      [1] =   0.0     ;
    IP->CurrentVelocityVector->VecData      [2] =    0.0      ;

    IP->CurrentAccelerationVector->VecData  [0] =   0.0      ;
    IP->CurrentAccelerationVector->VecData  [1] =    0.0      ;
    IP->CurrentAccelerationVector->VecData  [2] =    0.0      ;

    IP->MaxVelocityVector->VecData          [0] =    2.0      ;
    IP->MaxVelocityVector->VecData          [1] =    2.0     ;
    IP->MaxVelocityVector->VecData          [2] =    2.0      ;

    IP->MaxAccelerationVector->VecData      [0] =    1.0      ;
    IP->MaxAccelerationVector->VecData      [1] =    1.0      ;
    IP->MaxAccelerationVector->VecData      [2] =    1.0      ;

    IP->MaxJerkVector->VecData              [0] =    12.0      ;
    IP->MaxJerkVector->VecData              [1] =    12.0      ;
    IP->MaxJerkVector->VecData              [2] =    12.0     ;

    IP->TargetPositionVector->VecData       [0] =   0      ;
    IP->TargetPositionVector->VecData       [1] =   2      ;
    IP->TargetPositionVector->VecData       [2] =   0      ;

    IP->TargetVelocityVector->VecData       [0] =   0       ;
    IP->TargetVelocityVector->VecData       [1] =  0      ;
    IP->TargetVelocityVector->VecData       [2] =  0       ;

    IP->SelectionVector->VecData            [0] =   true        ;
    IP->SelectionVector->VecData            [1] =   true        ;
    IP->SelectionVector->VecData            [2] =   true        ;

    // ********************************************************************
    // Starting the control loop

    while (ResultValue != ReflexxesAPI::RML_FINAL_STATE_REACHED)
    {

        // ****************************************************************
        // Wait for the next timer tick
        // (not implemented in this example in order to keep it simple)
        // ****************************************************************

        // Calling the Reflexxes OTG algorithm
        ResultValue =   RML->RMLPosition(       *IP
                                            ,   OP
                                            ,   Flags       );

        if (ResultValue < 0)
        {
            printf("An error occurred (%d).\n", ResultValue );
            break;
        }

        // ****************************************************************
        // Here, the new state of motion, that is
        //
        // - OP->NewPositionVector
        // - OP->NewVelocityVector
        // - OP->NewAccelerationVector
        //
        // can be used as input values for lower level controllers. In the
        // most simple case, a position controller in actuator space is
        // used, but the computed state can be applied to many other
        // controllers (e.g., Cartesian impedance controllers,
        // operational space controllers).
        // ****************************************************************

        // ****************************************************************
        // Feed the output values of the current control cycle back to
        // input values of the next control cycle

        *IP->CurrentPositionVector      =   *OP->NewPositionVector      ;
        *IP->CurrentVelocityVector      =   *OP->NewVelocityVector      ;
        *IP->CurrentAccelerationVector  =   *OP->NewAccelerationVector  ;
        std::cout<<"position_x: "<<IP->CurrentPositionVector->VecData[0]<<",position_y: "<<IP->CurrentPositionVector->VecData[1]<<",position_z: "<<IP->CurrentPositionVector->VecData[2]<<std::endl;
    }

    // ********************************************************************
    // Deleting the objects of the Reflexxes Motion Library end terminating
    // the process

    delete  RML         ;
    delete  IP          ;
    delete  OP          ;

    exit(EXIT_SUCCESS)  ;
}
