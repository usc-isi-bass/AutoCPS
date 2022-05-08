using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.IO.Pipes;
using System.Diagnostics;
using UnityEngine;

namespace AutocpsKsp
{
    public class AutoCpsController : Part
    {
        private Process _autocpsProcess;

        protected override void onFlightStart()
        {
            _autocpsProcess = new Process();
            _autocpsProcess.StartInfo.FileName = "";

            //at the beginning of the flight, register your fly-by-wire control function that will be called repeatedly during flight:
            vessel.OnFlyByWire += new FlightInputCallback(Fly);
        }

        private static void Fly(FlightCtrlState s) {
            s.yaw = -0.2F;  //set yaw input to 20% left
            s.pitch += 0.3F; //set pitch input to whatever the player has input + 30%
            s.roll = 0.5F;   //set roll to 50% (either clockwise or counterclockwise, try it and find out)
            s.mainThrottle = 0.8F; //set throttle to 80%
 
            //the range of yaw, pitch, and roll is -1.0F to 1.0F, and the throttle goes from 0.0F to 1.0F.
            //if your code might violate that it's probably a good idea to clamp the inputs, e.g.:
            s.roll = Mathf.Clamp(s.roll, -1.0F, +1.0F);
        }
    }
}