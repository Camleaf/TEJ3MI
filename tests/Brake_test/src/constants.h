// Effective PPR of quadrature encoders on our motors
const int kEffectivePPR = 44;

// Pins connected to respective control on motor driver
const int kIn1 = 0;
const int kIn2 = 0;

// Digital input pins which the encoder motors are connected to
const int kEncoder1 = 0;
const int kEncoder2 = 0;

// The rated RPM of the motor
const int kMotorMaxRPM = 0;

// The sample interval for Updating position. Too fast will result in noise, and too slow will result in slow response times.
const unsigned long kSampleTime = 50;

// The acceptable amount of degrees off of the desired position.
const float kPositionTolerance = 360.0/kEffectivePPR;

// PID tuned values
const int kProportional = 0;
const int kIntegral = 0;
const int kDerivative = 0;
