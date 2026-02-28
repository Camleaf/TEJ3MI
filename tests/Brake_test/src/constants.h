// Effective PPR of quadrature encoders on our motors
const int kEffectivePPR = 44;

// Pins connected to respective control on motor driver
const int kIn1 = 0;
const int kIn2 = 0;

// Digital input pins which the encoder motors are connected to
const int kEncoder1 = 0;
const int kEncoder2 = 0;

// The sample interval for Updating position. Too fast will result in noise, and too slow will result in slow response times.
const unsigned long kSampleTime = 20;

// The acceptable amount of counts off of the desired position.
const int kPositionTolerance = 1; // bump to 2 if this is too noisy

// PID tuned values
const int kProportional = 0;
const int kIntegral = 0;
const int kDerivative = 0;
